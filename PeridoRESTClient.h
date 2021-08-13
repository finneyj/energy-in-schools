#ifndef PERIDO_REST_CLIENT_H
#define PERIDO_REST_CLIENT_H

#include "PeridoBridge.h"

#if !MICROBIT_CODAL
#include "MicroBitFiber.h"
#include "MicroBitLock.h"
#define MICROBIT_LOCK_TYPE MicroBitLock
#else
#define MICROBIT_LOCK_TYPE FiberLock
#endif

class PeridoRESTClient
{
    MICROBIT_LOCK_TYPE mutex;
    MicroBitRadio &radio;
    PeridoFrag radioTxRx;
    NRF52Serial &serial;
    uint16_t request_id;
    bool awaitingResponse;
    PacketBuffer response;
    bool enabled;

    public:

    PeridoRESTClient(MicroBitRadio& r, MICROBIT_MESSAGE_BUS_TYPE& b, NRF52Serial &s);
    ManagedString get(ManagedString request);
    void onRadioPacket(MicroBitEvent);
    void enable();
};

#endif