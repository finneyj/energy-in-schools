#ifndef CARBONSERVICE_SERVICE_H
#define CARBONSERVICE_SERVICE_H

#include "PeridoRESTClient.h"

class CarbonService
{
    PeridoRESTClient& radio;

    public:

    CarbonService(PeridoRESTClient& r);

    ManagedString getCarbonIndex(ManagedString endpoint);
    ManagedString getCarbonValue(ManagedString endpoint);
    ManagedString getCarbonGenerationMix(ManagedString endpoint);
};

#endif