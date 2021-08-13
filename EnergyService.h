#ifndef ENERGYSERVICE_SERVICE_H
#define ENERGYSERVICE_SERVICE_H

#include "PeridoRESTClient.h"

class EnergyService
{
    PeridoRESTClient& radio;

    public:

    EnergyService(PeridoRESTClient& r);

    ManagedString getEnergyLevel(ManagedString endpoint);

    
};

#endif