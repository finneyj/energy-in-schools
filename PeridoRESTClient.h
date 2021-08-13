#ifndef PERIDO_REST_CLIENT_H
#define PERIDO_REST_CLIENT_H

#include "PeridoBridge.h"

#if !MICROBIT_CODAL
#include "MicroBitFiber.h"
#include "MicroBitLock.h"
typedef MicroBitLock FiberLock;
#endif

class PeridoRESTClient
{
    FiberLock mutex;
    MicroBitRadio &radio;
    PeridoFrag radioTxRx;
    NRF52Serial &serial;
    uint16_t request_id;
    bool awaitingResponse;
    PacketBuffer response;

    public:

    PeridoRESTClient(MicroBitRadio& r, MicroBitMessageBus& b, NRF52Serial &s);
    ManagedString get(ManagedString request);
    void onRadioPacket(MicroBitEvent);
};

#endif