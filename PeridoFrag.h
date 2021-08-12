#ifndef PERIDO_FRAG_H
#define PERIDO_FRAG_H

#include "MicroBitRadio.h"
#include "PeridoUtil.h"

#define PERIDO_MAX_FRAGMENTS 10

class PeridoFrag
{
    int request_id;
    int count = 0;
    MicroBitRadio &radio;
    PacketBuffer fragment[PERIDO_MAX_FRAGMENTS];
    PacketBuffer packet;


    public:
    PeridoFrag(MicroBitRadio& r);
    void send(ManagedBuffer p);
    void recv();

    PacketBuffer getPacket();
    bool recvComplete();

    private:
    void reset();
};

#endif