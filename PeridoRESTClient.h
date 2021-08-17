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

#define PERIDO_REST_RATE_LIMIT      1000

class PeridoRESTClient
{
    MICROBIT_LOCK_TYPE mutex;
    MicroBitRadio &radio;
    PeridoFrag radioTxRx;
    NRF52Serial &serial;
    uint16_t request_id;
    bool awaitingResponse;
    ManagedString response;
    bool enabled;
    uint32_t nextTx;

    public:

    PeridoRESTClient(MicroBitRadio& r, MICROBIT_MESSAGE_BUS_TYPE& b, NRF52Serial &s);
    ManagedString get(ManagedString request);
    void onRadioPacket(MicroBitEvent);
    void enable();
};

#endif