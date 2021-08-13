#ifndef INITSERVICE_SERVICE_H
#define INITSERVICE_SERVICE_H

#include "PeridoRESTClient.h"

class InitService
{
    PeridoRESTClient& radio;

    public:

    InitService(PeridoRESTClient& r);

    ManagedString setReset(ManagedString reset);
    ManagedString setSchoolId(ManagedString schoolid);
    ManagedString setPiId(ManagedString piid);
};

#endif