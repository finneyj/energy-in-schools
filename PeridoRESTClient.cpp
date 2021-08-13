#include "MicroBitConfig.h"

#include "PeridoRESTClient.h"
#include "MicroBitDevice.h"

#if MICROBIT_CODAL
using namespace codal;
#endif

void PeridoRESTClient::onRadioPacket(MicroBitEvent)
{
    serial.printf("FRAME RECEIVED:\n");

    if (!enabled)
        return;
    
    radioTxRx.recv();
    
    if (radioTxRx.recvComplete())
    {
        PacketBuffer b = radioTxRx.getPacket();
    
        serial.printf("PACKET RECEIVED: ");
        for (int i=0; i<b.length(); i++)
            serial.printf("%x ",b[i]);
        serial.printf("\n");
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

PeridoRESTClient::PeridoRESTClient(MicroBitRadio& r, MicroBitMessageBus& b, NRF52Serial &s) : radio(r), radioTxRx(r), serial(s)
{
    enabled = false;

    // Attach event listeners to radio and serial interfaces
    b.listen(MICROBIT_ID_RADIO, MICROBIT_RADIO_EVT_DATAGRAM, this, &PeridoRESTClient::onRadioPacket);
}

ManagedString PeridoRESTClient::get(ManagedString request)
{
    mutex.wait();

    enable();

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

    int timeout = 20000;
    int quantum = 100;
    int t = 0;

    while(awaitingResponse)
    {
        if (t == 0)
        {
            radioTxRx.send(p, p.length());
            serial.printf("PACKET SENT: ");
            for (int i=0; i<p.length(); i++)
                serial.printf("%x ", p[i]);
            serial.printf("\n");
        }

        fiber_sleep(quantum);
        t+= quantum;

        if (t >= timeout)
            t = 0;
    }

    serial.printf("RESPONSE RECEIVED\n");
    mutex.notify();

    return "BOO";
}