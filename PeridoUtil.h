#ifndef PERIDO_UTIL_H
#define PERIDO_UTIL_H

#include "pxt.h"
#include "MicroBitRadio.h"
#include "MicroBitSerial.h"
#include "MicroBitEvent.h"
#include "MicroBitDisplay.h"
#include "MicroBitComponent.h"

#if !MICROBIT_CODAL

#include "MicroBitMessageBus.h"
typedef MicroBitSerial NRF52Serial;
#define MICROBIT_MESSAGE_BUS_TYPE MicroBitMessageBus

#else

#include "MessageBus.h"
#define MICROBIT_MESSAGE_BUS_TYPE MessageBus

#endif

#define REQUEST_TYPE_GET_REQUEST            0x01
#define REQUEST_TYPE_POST_REQUEST           0x02
#define REQUEST_TYPE_CLOUD_VARIABLE         0x04
#define REQUEST_TYPE_BROADCAST              0x08

#define REQUEST_TYPE_HELLO                  0x10
#define REQUEST_STATUS_ACK                  0x20
#define REQUEST_STATUS_ERROR                0x40
#define REQUEST_STATUS_OK                   0x80

#define SUBTYPE_STRING              0x01
#define SUBTYPE_INT                 0x02
#define SUBTYPE_FLOAT               0x04
#define SUBTYPE_EVENT               0x08

struct PeridoBridgeSerialPacket
{
    uint8_t app_id;
    uint8_t namespace_id;
    uint16_t request_id;

    uint8_t payload[250];
}__attribute((packed));


class PeridoUtil
{
    public:
    static int getLength(PacketBuffer b);
    static uint8_t* getPointerToIndex(PacketBuffer b, int index);
    static ManagedString getString(PacketBuffer b, int index);
    static int getInteger(PacketBuffer b, int index);
    static float getFloat(PacketBuffer b, int index);

    static int getLength(ManagedString b);
    static uint8_t* getPointerToIndex(ManagedString b, int index);
    static ManagedString getString(ManagedString b, int index);
    static int getInteger(ManagedString b, int index);
    static float getFloat(ManagedString b, int index);


};

#endif