#ifndef PERIDO_UTIL_H
#define PERIDO_UTIL_H

#include "MicroBitRadio.h"
#include "MicroBitSerial.h"
#include "MicroBitEvent.h"
#include "MicroBitDisplay.h"
#include "MicroBitComponent.h"
#include "MicroBitMessageBus.h"

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
    static int getLength(ManagedBuffer b);
    static uint8_t* getPointerToIndex(ManagedBuffer b, int index);
    static ManagedString getString(ManagedBuffer b, int index);
    static int getInteger(ManagedBuffer b, int index);
    static float getFloat(ManagedBuffer b, int index);
};

#endif