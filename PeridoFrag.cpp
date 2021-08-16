#include "MicroBitConfig.h"
#include "PeridoFrag.h"

#if MICROBIT_CODAL
using namespace codal;
#endif

#define PERIDO_MAXIMUM_FRAGMENT_SIZE (MICROBIT_RADIO_MAX_PACKET_SIZE - MICROBIT_RADIO_HEADER_SIZE)

PeridoFrag::PeridoFrag(MicroBitRadio& r) : radio(r)
{
    reset();
}

void PeridoFrag::reset() 
{
    request_id = -1;
    count = 0;

    for(int i=0; i<PERIDO_MAX_FRAGMENTS; i++)
        fragment[i] = PacketBuffer::EmptyPacket;

    packet = PacketBuffer::EmptyPacket;
}

void PeridoFrag::send(PacketBuffer p, int len) 
{
    // Fast path for short frames
    if (len <= PERIDO_MAXIMUM_FRAGMENT_SIZE)
    {
        p[0] |= 0x80;
        radio.datagram.send(&p[0], len);
        DMESG("FAST PATH FRAGMENT SENT: ");
        for (int i=0; i<p.length(); i++)
            DMESGN("%x ", p[i]);
        DMESGN("\n");
        return;
    }

    uint8_t frag = 0;
    uint8_t *data = &p[4];
    uint8_t *end = &p[0] + len;

    PacketBuffer fragment(PERIDO_MAXIMUM_FRAGMENT_SIZE);
    memcpy(&fragment[0], &p[0], 4);

    while (data < end)
    {
        int toSend = min(end-data, PERIDO_MAXIMUM_FRAGMENT_SIZE-4);
        memcpy(&fragment[4], data, toSend);

        data += toSend;

        fragment[0] = frag | (data == end ? 0x80 : 0x00);
        radio.datagram.send(&fragment[0], toSend+4);

        DMESG("FRAGMENT SENT: ");
        for (int i=0; i<toSend+4; i++)
            DMESGN("%c ", fragment[i]);
        DMESGN("\n");

        frag++;
    }
}

void PeridoFrag::recv() 
{
    PacketBuffer b = radio.datagram.recv();
    PeridoBridgeSerialPacket *pkt = (PeridoBridgeSerialPacket *) &b[0];

    // Validate
    if (b.length() < 4)
        return;

    bool last = b[0] & 0x80;
    uint8_t frag = b[0] & 0x7F;

    pkt->app_id = 0;
    pkt->namespace_id = 0;

    DMESG("\nFRAGMENT RECEIVED: [FRAG:%d|%d][LAST:%d] [ID:%d|%d]", frag, count, (int)last, pkt->request_id, request_id);
    DMESG("FRAGMENT: ");
    for (int i=0; i<b.length(); i++)
        DMESGN("%c ", b[i]);
    DMESGN("\n");

    if (pkt->request_id != request_id || count >= PERIDO_MAX_FRAGMENTS || frag != count)
    {
        DMESG("RESETTING");
        reset();
        request_id = pkt->request_id;
    }

    if (frag == count)
    {
        DMESG("STORING [FRAG: %d] [PAYLOAD: %c ... %c]", frag, b[4], b[b.length()-1]);
        fragment[count++] = b;

        if (last)
        {
            DMESG("REASSEMBLING");
            // Calculate final size of the packet and allocate.
            int len = 4;

            for (int i=0; i<count; i++)
                len += fragment[i].length() - 4;
            
            packet = PacketBuffer(len);

            uint8_t *data = &packet[0];
            memcpy(data, &fragment[0][0], 4);
            data += 4;

            for (int i=0; i<count; i++)
            {
                int l = fragment[i].length() - 4;
                memcpy(data, &fragment[i][4], l);
                data += l;
            }
        }
    }
}

bool PeridoFrag::recvComplete() 
{
    return !(packet == PacketBuffer::EmptyPacket);
}

PacketBuffer PeridoFrag::getPacket() 
{
    return packet;
}
