#include "pxt.h"
#include "WeatherService.h"

extern PeridoRESTClient radioTxRx;
WeatherService weatherService(radioTxRx);
/**
 * share
 * use
 */

enum class WeatherLocationType
{
    city,
    postcode
};

//% color=243 weight=100 icon="\uf185" block="Weather"
namespace weather {

    int init() {
        return 0;
    }

    //%
    String getTemperature(WeatherLocationType locationType, String location)
    {
        init();
        ManagedString s = weatherService.getTemperature((int)locationType, MSTR((location)));
        return PSTR(s);
    }

    //%
    String getWindDirection(WeatherLocationType locationType, String location)
    {
        init();
        WeatherServiceWind w = weatherService.getWind((int)locationType, MSTR(location));
        return PSTR(w.direction);
    }

    //%
    String getWeatherForecast(WeatherLocationType locationType, String location)
    {
        init();
        WeatherServiceForecastNow w = weatherService.getForecastNow((int)locationType, MSTR(location));
        return PSTR(w.text);
    }

    //%
    String getWeatherForecastTomorrow(WeatherLocationType locationType, String location)
    {
        init();
        WeatherServiceForecastTomorrow w = weatherService.getForecastTomorrow((int)locationType, MSTR(location));
        return PSTR(w.text);
    }
}