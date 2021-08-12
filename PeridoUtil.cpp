#include "MicroBitConfig.h"
#include "PeridoUtil.h"
#include "EventModel.h"

#define SLIP_END                0xC0
#define SLIP_ESC                0xDB
#define SLIP_ESC_END            0xDC
#define SLIP_ESC_ESC            0xDD

using namespace codal;

int PeridoUtil::getLength(ManagedBuffer b)
{
    uint8_t* payloadPtr = &b[5];
    uint8_t* payloadEnd = &b[b.length()];

    while(1)
    {
        if (payloadPtr >= payloadEnd)
            return payloadEnd - &b[0];

        uint8_t subtype = *payloadPtr++;

        if (subtype & SUBTYPE_STRING)
            while(*payloadPtr++ != 0);

        if (subtype & SUBTYPE_INT)
            payloadPtr += sizeof(int);

        if (subtype & SUBTYPE_FLOAT)
            payloadPtr += sizeof(float);

        if ((*payloadPtr & (SUBTYPE_STRING | SUBTYPE_INT | SUBTYPE_FLOAT)) == 0)
            break;
    }

    return payloadPtr - &b[0];
}

uint8_t* PeridoUtil::getPointerToIndex(ManagedBuffer b, int index)
{
    uint8_t* payloadPtr = &b[5];
    uint8_t* payloadEnd = &b[b.length()];

    for (int i = 0; i < index; i++)
    {
        if (payloadPtr >= payloadEnd)
            return NULL;

        uint8_t subtype = *payloadPtr++;

        if (subtype & SUBTYPE_STRING)
            while(*payloadPtr++ != 0);

        if (subtype & SUBTYPE_INT)
            payloadPtr += sizeof(int);

        if (subtype & SUBTYPE_FLOAT)
            payloadPtr += sizeof(float);
    }

    return payloadPtr;
}

ManagedString PeridoUtil::getString(ManagedBuffer b, int index)
{
    uint8_t *data = getPointerToIndex(b, index);

    if (data == NULL || !(*data & SUBTYPE_STRING))
        return ManagedString();

    // move past subtype byte
    data++;

    return ManagedString((char*)data);
}

int PeridoUtil::getInteger(ManagedBuffer b, int index)
{
    uint8_t *data = getPointerToIndex(b, index);

    if (data == NULL || !(*data & SUBTYPE_INT))
        return MICROBIT_INVALID_PARAMETER;

    // move past subtype byte
    data++;

    int res;
    memcpy(&res, data, sizeof(int));

    return res;
}

float PeridoUtil::getFloat(ManagedBuffer b, int index)
{
    uint8_t *data = getPointerToIndex(b, index);

    if (data == NULL || !(*data & SUBTYPE_FLOAT))
        return MICROBIT_INVALID_PARAMETER;

    // move past subtype byte
    data++;

    float res;
    memcpy(&res, data, sizeof(float));

    return res;
}