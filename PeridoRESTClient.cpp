#include "MicroBitConfig.h"

#include "PeridoRESTClient.h"
#include "MicroBitDevice.h"

#if MICROBIT_CODAL
using namespace codal;
#endif

void PeridoRESTClient::onRadioPacket(MicroBitEvent)
{
    if (!enabled)
        return;
    
    radioTxRx.recv();
    
    if (radioTxRx.recvComplete())
    {
        PacketBuffer b = radioTxRx.getPacket();
    
        // If the request_id matches and outstanding request, process it.
        PeridoBridgeSerialPacket *pkt = (PeridoBridgeSerialPacket *) &b[0];
        if (awaitingResponse && pkt->request_id == request_id)
        {
            uint8_t *tmp = (uint8_t *)malloc(b.length());
            memset(tmp, 'A', b.length());

            ManagedString s((const char *)tmp, b.length());
            memcpy((void *)s.toCharArray(), b.getBytes(), b.length());

            free(tmp);

            response = s;
            awaitingResponse = false;
        }
    }
}

void PeridoRESTClient::enable()
{
    if (!enabled)
    {
        radio.enable();
        enabled = true;
    }
}

PeridoRESTClient::PeridoRESTClient(MicroBitRadio& r, MICROBIT_MESSAGE_BUS_TYPE& b, NRF52Serial &s) : radio(r), radioTxRx(r), serial(s)
{
    enabled = false;
    nextTx = 0;

    // Attach event listeners to radio and serial interfaces
    b.listen(MICROBIT_ID_RADIO, MICROBIT_RADIO_EVT_DATAGRAM, this, &PeridoRESTClient::onRadioPacket);
}

ManagedString PeridoRESTClient::get(ManagedString request)
{
    mutex.wait();

    enable();

    // State variables
    int timeout = 2500+microbit_random(500);
    int quantum = 100;
    int t = 0;

    // Perform some rate limiting, in case kids busy loop...
    while(system_timer_current_time() < nextTx)
        fiber_sleep(100+microbit_random(quantum));

    PacketBuffer p(request.length() + 7);
    PeridoBridgeSerialPacket *pkt = (PeridoBridgeSerialPacket *) &p[0];
    request_id = microbit_random(65535);

    pkt->app_id = 0;
    pkt->namespace_id = 0;
    pkt->request_id = request_id;
    pkt->payload[0] = REQUEST_TYPE_GET_REQUEST;
    pkt->payload[1] = SUBTYPE_STRING;
    strcpy((char *) &pkt->payload[2], (char *) request.toCharArray());

    awaitingResponse = true;

    while(awaitingResponse)
    {
        if (t == 0)
            radioTxRx.send(p, p.length());

        fiber_sleep(quantum);
        t+= quantum;

        if (t >= timeout)
            t = 0;
    }

    nextTx = system_timer_current_time() + PERIDO_REST_RATE_LIMIT;
    mutex.notify();

    return response;
}