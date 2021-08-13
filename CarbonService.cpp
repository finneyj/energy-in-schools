#include "CarbonService.h"

CarbonService::CarbonService(PeridoRESTClient& r) : radio(r)
{
    
}

ManagedString CarbonService::getCarbonIndex(ManagedString endpoint) {
    ManagedString res = radio.get("/carbon/" + endpoint + "/");
    return PeridoUtil::getString(res, 0);
}
ManagedString CarbonService::getCarbonValue(ManagedString endpoint) {
    ManagedString res = radio.get("/carbon/" + endpoint + "/");
    return PeridoUtil::getString(res, 0);
}
ManagedString CarbonService::getCarbonGenerationMix(ManagedString endpoint) {
    ManagedString res = radio.get("/carbon/" + endpoint + "/");
    return PeridoUtil::getString(res, 0);
}
