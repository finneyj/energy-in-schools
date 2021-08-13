#include "MicroBitConfig.h"

#include "PeridoRESTClient.h"
#include "MicroBitDevice.h"

using namespace codal;


void PeridoRESTClient::onRadioPacket(MicroBitEvent)
{
    DMESG("FRAME RECEIVED:");
    
    radioTxRx.recv();
    
    if (radioTxRx.recvComplete())
    {
        PacketBuffer b = radioTxRx.getPacket();
    
        DMESG("PACKET RECEIVED:");
        for (int i=0; i<b.length(); i++)
            DMESGN("%x ",b[i]);
        DMESG("");
    }
}

PeridoRESTClient::PeridoRESTClient(MicroBitRadio& r, MicroBitMessageBus& b) : radio(r), radioTxRx(r)
{
    // Attach event listeners to radio and serial interfaces
    b.listen(MICROBIT_ID_RADIO, MICROBIT_RADIO_EVT_DATAGRAM, this, &PeridoRESTClient::onRadioPacket);
    radio.enable();
}

ManagedString PeridoRESTClient::get(ManagedString request)
{
    mutex.wait();

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
            DMESGF("PACKET SENT:");
            for (int i=0; i<p.length(); i++)
                DMESGN("%x ", p[i]);
            DMESG("");
        }

        fiber_sleep(quantum);
        t+= quantum;

        if (t >= timeout)
            t = 0;
    }

    DMESG("RESPONSE RECEIVED");
    mutex.notify();

    return "BOO";
}