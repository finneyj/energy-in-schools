#ifndef PERIDO_BRIDGE_H
#define PERIDO_BRIDGE_H

#include "pxt.h"
#include "MicroBitRadio.h"
#include "MicroBitSerial.h"
#include "MicroBitEvent.h"
#include "MicroBitDisplay.h"
#include "MicroBitComponent.h"
#include "PeridoUtil.h"
#include "PeridoFrag.h"

// the header is only the first two bytes, as the id is placed inside the payload
#define BRIDGE_SERIAL_PACKET_HEADER_SIZE        2

#define BRIDGE_STATUS_OK                        0x01
#define BRIDGE_STATUS_ERROR                     0x02
#define BRIDGE_DISPLAY_BIG                      0x10

#define BLINK_POSITION_X                        3
#define BLINK_POSITION_Y                        1

class PeridoBridge : public MicroBitComponent
{
    MicroBitRadio& radio;
    PeridoFrag radioTxRx;
    NRF52Serial& serial;
    MicroBitDisplay& display;
    PeridoBridgeSerialPacket serialPacket; // holds data being received

    uint32_t packetCount;

    void sendHelloPacket();
    void handleHelloPacket(PacketBuffer b);
    void sendSerialPacket(PacketBuffer b);
    void onRadioPacket(MicroBitEvent e);
    void onSerialPacket(MicroBitEvent e);

    public:

    PeridoBridge(MicroBitRadio& r, NRF52Serial& s, MICROBIT_MESSAGE_BUS_TYPE& b, MicroBitDisplay& display);

    void enable();
};


#endif