#include "pxt.h"
#include "WeatherService.h"

extern PeridoRESTClient *radioTxRx;
WeatherService *weatherService = NULL;
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
        if (radioTxRx == NULL)
            radioTxRx = new PeridoRESTClient(uBit.radio, uBit.messageBus, uBit.serial);

        if (weatherService == NULL)
            weatherService = new WeatherService(*radioTxRx);

        return 0;
    }

    //%
    String getTemperature(WeatherLocationType locationType, String location, String country)
    {
        init();
        ManagedString s = weatherService->getTemperature((int)locationType, MSTR(location), MSTR(country));
        return PSTR(s);
    }

    //%
    String getWindDirection(WeatherLocationType locationType, String location, String country)
    {
        init();
        WeatherServiceWind w = weatherService->getWind((int)locationType, MSTR(location), MSTR(country));
        return PSTR(w.direction);
    }

    //%
    String getWeatherForecast(WeatherLocationType locationType, String location, String country)
    {
        init();
        WeatherServiceForecastNow w = weatherService->getForecastNow((int)locationType, MSTR(location), MSTR(country));
        return PSTR(w.text);
    }

    //%
    String getWeatherForecastTomorrow(WeatherLocationType locationType, String location, String country)
    {
        init();
        WeatherServiceForecastTomorrow w = weatherService->getForecastTomorrow((int)locationType, MSTR(location), MSTR(country));
        return PSTR(w.text);
    }
}