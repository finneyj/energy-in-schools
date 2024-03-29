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

WeatherServiceForecastNow WeatherService::getForecastNow(int locationType, ManagedString location, ManagedString country) {
    ManagedString query = "/weather/";
    query = query + locationType;
    query = query + "/" + location;
    query = query + "/" + country;
    query = query + "/forecastNow/";

    ManagedString res = radio.get(query);

    WeatherServiceForecastNow ret;

    ret.text = PeridoUtil::getString(res, 0);
    ret.high = 0;
    ret.low = 0;
    
    return ret;
}

WeatherServiceForecastTomorrow WeatherService::getForecastTomorrow(int locationType, ManagedString location, ManagedString country) {
    ManagedString query = "/weather/";
    query = query + locationType;
    query = query + "/" + location;
    query = query + "/" + country;
    query = query + "/forecastTomorrow/";

    ManagedString res = radio.get(query);

    WeatherServiceForecastTomorrow ret;
    ret.text = PeridoUtil::getString(res, 0);
    ret.high = 0;
    ret.low = 0;
    return ret;
}

ManagedString WeatherService::getTemperature(int locationType, ManagedString location, ManagedString country) {
    ManagedString query = "/weather/";
    query = query + locationType;
    query = query + "/" + location;
    query = query + "/" + country;
    query = query + "/temperature/";

    ManagedString res = radio.get(query);

    return PeridoUtil::getString(res, 0);
}

WeatherServiceWind WeatherService::getWind(int locationType, ManagedString location, ManagedString country) {
    ManagedString query = "/weather/";
    query = query + locationType;
    query = query + "/" + location;
    query = query + "/" + country;
    query = query + "/wind/";
    
    ManagedString res = radio.get(query);

    WeatherServiceWind ret;
    ret.direction = PeridoUtil::getString(res, 0);
    ret.chill = "";
    ret.speed = "";
    return ret;
}
