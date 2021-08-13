#ifndef WEATHERSERVICE_SERVICE_H
#define WEATHERSERVICE_SERVICE_H

#include "PeridoRESTClient.h"

struct WeatherServiceForecastNow {
    int high;
    int low;
    ManagedString text;
};

struct WeatherServiceForecastTomorrow {
    ManagedString high;
    ManagedString low;
    ManagedString text;
};

struct WeatherServiceWind {
    ManagedString chill;
    ManagedString direction;
    ManagedString speed;
};


class WeatherService
{
    PeridoRESTClient& radio;

    public:

    WeatherService(PeridoRESTClient& r);

    int setRoomNone(ManagedString room, int temperature, int light_level, int humidity);
    int setRoomLightlevel(ManagedString room, int light_level);
    int setRoomTemperature(ManagedString room, int temperature);
    int setRoomHumidity(ManagedString room, int humidity);

    WeatherServiceForecastNow getForecastNow(int locationType, ManagedString location);
    WeatherServiceForecastTomorrow getForecastTomorrow(int locationType, ManagedString location);
    ManagedString getTemperature(int locationType, ManagedString location);
    WeatherServiceWind getWind(int locationType, ManagedString location);
};

#endif