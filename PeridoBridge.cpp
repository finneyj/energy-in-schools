#include "MicroBitConfig.h"

#include "PeridoBridge.h"
#include "EventModel.h"

#define SLIP_END                0xC0
#define SLIP_ESC                0xDB
#define SLIP_ESC_END            0xDC
#define SLIP_ESC_ESC            0xDD

#if MICROBIT_CODAL
using namespace codal;
#endif

const char* SCHOOL_ID = "820CA";
const char* HUB_ID = "SyHbe";

const MicroBitImage smile_small = MicroBitImage("0, 0, 0, 0, 0\n0, 255, 0, 0, 0\n0, 0, 0, 0, 0\n255, 0, 0, 0, 255\n0, 255, 255, 255, 0\n");
const MicroBitImage smile_big = MicroBitImage("0, 0, 0, 0, 0\n0, 255, 0, 0, 0\n0, 0, 0, 0, 0\n255, 255, 255, 255, 255\n0, 255, 255, 255, 0\n");
const MicroBitImage neutral_small = MicroBitImage("0, 0, 0, 0, 0\n0, 255, 0, 255, 0\n0, 0, 0, 0, 0\n0, 255, 255, 255, 0\n0, 255, 255, 255, 0\n");
const MicroBitImage neutral_big = MicroBitImage("0, 0, 0, 0, 0\n0, 255, 0, 255, 0\n0, 0, 0, 0, 0\n255, 255, 255, 255, 255\n0, 0, 0, 0, 0\n");
const MicroBitImage sad_small = MicroBitImage("0, 0, 0, 0, 0\n0, 255, 0, 0, 0\n0, 0, 0, 0, 0\n0, 255, 255, 255, 0\n255, 0, 0, 0, 255\n");
const MicroBitImage sad_big = MicroBitImage("0, 0, 0, 0, 0\n0, 255, 0, 0, 0\n0, 0, 0, 0, 0\n0, 255, 255, 255, 0\n255, 255, 255, 255, 255\n");

void PeridoBridge::sendHelloPacket()
{
    PacketBuffer b(23);
    const uint8_t helloHeader[] = {0x00, 0x00, 0x00, 0x00, 0x10, 0x02, 0x00, 0x00, 0x00, 0x00};

    // Insert basic header.
    memcpy(&b[0], helloHeader, 10);

    // Add in String subtype and SchoolId
    b[10] = 0x01;
    memcpy(&b[11], SCHOOL_ID, 6);

    // Add in String subtype and HubId. 5 for compat - old version had bug, that we're replicating here.
    b[17] = 0x01;
    memcpy(&b[18], HUB_ID, 5);

    // SLIP encode packet and transmit
    sendSerialPacket(b);
}

void PeridoBridge::handleHelloPacket(PacketBuffer b)
{
    uint32_t status;
    memcpy(&status, &b[5], 4);

    display.clear();

    if (status == MICROBIT_OK)
    {
        this->status = BRIDGE_STATUS_OK;
        display.print(smile_small);
    }
    else
    {
        this->status = BRIDGE_STATUS_ERROR;
        display.print(sad_small);
    }

    status |= BRIDGE_DISPLAY_BIG;
}

void PeridoBridge::sendSerialPacket(PacketBuffer b)
{
    int len = b.length();

    for (uint16_t i = 0; i < len; i++)
    {
        if (b[i] == SLIP_ESC)
        {
            serial.putc(SLIP_ESC);
            serial.putc(SLIP_ESC_ESC);
            continue;
        }

        if(b[i] == SLIP_END)
        {
            serial.putc(SLIP_ESC);
            serial.putc(SLIP_ESC_END);
            continue;
        }

        serial.putc(b[i]);
    }

    serial.putc(SLIP_END);
}

void PeridoBridge::onRadioPacket(MicroBitEvent)
{
    radioTxRx.recv();

    if (radioTxRx.recvComplete())
    {
        PacketBuffer b = radioTxRx.getPacket();

        sendSerialPacket(b);
        this->packetCount++;
    
        display.clear();

        // big smile
        if (this->status & BRIDGE_STATUS_OK)
        {
            if (this->status & BRIDGE_DISPLAY_BIG)
            {
                display.image.paste(smile_small);
                this->status &= ~BRIDGE_DISPLAY_BIG;
            }
            else
            {
                display.image.paste(smile_big);
                this->status |= BRIDGE_DISPLAY_BIG;
            }
        }
        else if (this->status & BRIDGE_STATUS_ERROR)
        {
            if (this->status & BRIDGE_DISPLAY_BIG)
            {
                display.image.paste(sad_small);
                this->status &= ~BRIDGE_DISPLAY_BIG;
            }
            else
            {
                display.image.paste(sad_big);
                this->status |= BRIDGE_DISPLAY_BIG;
            }
        }
        else
        {
            if (this->status & BRIDGE_DISPLAY_BIG)
            {
                display.image.paste(neutral_small);
                this->status &= ~BRIDGE_DISPLAY_BIG;
            }
            else
            {
                display.image.paste(neutral_big);
                this->status |= BRIDGE_DISPLAY_BIG;
            }
        }
    }
}

void PeridoBridge::onSerialPacket(MicroBitEvent)
{
    PacketBuffer b(sizeof(PeridoBridgeSerialPacket));
    uint16_t len = 0;
    char c = 0;

    while ((c = serial.read()) != SLIP_END)
    {
        if (len >= sizeof(PeridoBridgeSerialPacket))
        {
            len++;
            continue;
        }

        if (c == SLIP_ESC)
        {
            char next = serial.read();

            if (next == SLIP_ESC_END)
                c = SLIP_END;
            else if (next == SLIP_ESC_ESC)
                c = SLIP_ESC;
            else
            {
                b[len++] = c;
                b[len++] = next;
                continue;
            }            
        }

        b[len++] = c;
    }

    len = PeridoUtil::getLength(b);

    if (len > MICROBIT_RADIO_MAX_PACKET_SIZE)
        len = MICROBIT_RADIO_MAX_PACKET_SIZE;

    if (b[4] == REQUEST_TYPE_HELLO)
        handleHelloPacket(b);
    else
        radioTxRx.send(b, len);
}

void PeridoBridge::enable()
{
    display.print(neutral_big);

    // max size of a DataPacket
    serial.setRxBufferSize(240);

    // configure an event for SLIP_END
    serial.eventOn((char)SLIP_END);

    // Turn on the radio.
    radio.enable();

    // Announce our arrival
    sendHelloPacket();
}

PeridoBridge::PeridoBridge(MicroBitRadio& r, NRF52Serial& s, MicroBitMessageBus& b, MicroBitDisplay& display) : radio(r), radioTxRx(r), serial(s), display(display)
{
    this->packetCount = 0;
    this->status = 0;

    // Attach event listeners to radio and serial interfaces
    b.listen(MICROBIT_ID_RADIO, MICROBIT_RADIO_EVT_DATAGRAM, this, &PeridoBridge::onRadioPacket, MESSAGE_BUS_LISTENER_IMMEDIATE);
    b.listen(MICROBIT_ID_SERIAL, MICROBIT_SERIAL_EVT_DELIM_MATCH, this, &PeridoBridge::onSerialPacket);

}
