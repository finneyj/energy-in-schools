#include "WeatherService.h"

WeatherService::WeatherService(PeridoRESTClient& r) : radio(r)
{
    
}

int WeatherService::setRoomNone(ManagedString room, int temperature, int light_level, int humidity) {
    return 0;
}
int WeatherService::setRoomLightlevel(ManagedString room, int light_level) {
    return 0;
}
int WeatherService::setRoomTemperature(ManagedString room, int temperature) {
    return 0;
}
int WeatherService::setRoomHumidity(ManagedString room, int humidity) {
    return 0;
}

WeatherServiceForecastNow WeatherService::getForecastNow(int locationType, ManagedString location) {
    ManagedString res = radio.get("/weather/" + location + "/forecastNow/");

    WeatherServiceForecastNow ret;

    ret.high = PeridoUtil::getInteger(res, 0);
    ret.low = PeridoUtil::getInteger(res, 1);
    ret.text = PeridoUtil::getString(res, 2);
    return ret;
}

WeatherServiceForecastTomorrow WeatherService::getForecastTomorrow(int locationType, ManagedString location) {
    ManagedString res = radio.get("/weather/" + location + "/forecastTomorrow/");

    WeatherServiceForecastTomorrow ret;
    ret.high = PeridoUtil::getInteger(res, 0);
    ret.low = PeridoUtil::getInteger(res, 1);
    ret.text = PeridoUtil::getString(res, 2);
    return ret;
}

ManagedString WeatherService::getTemperature(int locationType, ManagedString location) {
    ManagedString res = radio.get("/weather/" + location + "/temperature/");
    return PeridoUtil::getString(res, 0);
}

WeatherServiceWind WeatherService::getWind(int locationType, ManagedString location) {
    ManagedString res = radio.get("/weather/" + location + "/wind/");
    WeatherServiceWind ret;
    ret.chill = PeridoUtil::getString(res, 0);
    ret.direction = PeridoUtil::getString(res, 1);
    ret.speed = PeridoUtil::getString(res, 2);
    return ret;
}
