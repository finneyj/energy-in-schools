#include "IssService.h"

IssService::IssService(PeridoRESTClient& r) : radio(r)
{
    
}

ManagedString IssService::getName(ManagedString endpoint) {
    ManagedString res = radio.get("/iss/" + endpoint + "/");
    return PeridoUtil::getString(res, 0);
}
int IssService::getAltitude(ManagedString endpoint) {
    ManagedString res = radio.get("/iss/" + endpoint + "/");
    return PeridoUtil::getInteger(res, 0);
}
ManagedString IssService::getSolarlocation(ManagedString endpoint) {
    ManagedString res = radio.get("/iss/" + endpoint + "/");
    return PeridoUtil::getString(res, 0);
}
ManagedString IssService::getVisibility(ManagedString endpoint) {
    ManagedString res = radio.get("/iss/" + endpoint + "/");
    return PeridoUtil::getString(res, 0);
}
int IssService::getDaynum(ManagedString endpoint) {
    ManagedString res = radio.get("/iss/" + endpoint + "/");
    return PeridoUtil::getInteger(res, 0);
}
ManagedString IssService::getLocation(ManagedString endpoint) {
    ManagedString res = radio.get("/iss/" + endpoint + "/");
    return PeridoUtil::getString(res, 0);
}
int IssService::getVelocity(ManagedString endpoint) {
    ManagedString res = radio.get("/iss/" + endpoint + "/");
    return PeridoUtil::getInteger(res, 0);
}
int IssService::getId(ManagedString endpoint) {
    ManagedString res = radio.get("/iss/" + endpoint + "/");
    return PeridoUtil::getInteger(res, 0);
}
