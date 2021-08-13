#ifndef ISSSERVICE_SERVICE_H
#define ISSSERVICE_SERVICE_H

#include "PeridoRESTClient.h"

class IssService
{
    PeridoRESTClient& radio;

    public:

    IssService(PeridoRESTClient& r);

    ManagedString getName(ManagedString endpoint);
    int getAltitude(ManagedString endpoint);
    ManagedString getSolarlocation(ManagedString endpoint);
    ManagedString getVisibility(ManagedString endpoint);
    int getDaynum(ManagedString endpoint);
    ManagedString getLocation(ManagedString endpoint);
    int getVelocity(ManagedString endpoint);
    int getId(ManagedString endpoint);
};

#endif