#include "EnergyService.h"

EnergyService::EnergyService(PeridoRESTClient& r) : radio(r)
{
    
}

ManagedString EnergyService::getEnergyLevel(ManagedString endpoint) {
    ManagedString res = radio.get("/energy/" + endpoint + "/");
    return PeridoUtil::getString(res, 0);
}
