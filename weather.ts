//% color=243 weight=100 icon="\uf185" block="Weather"
namespace weather {

    /**
      * Get current temperature in city or by location postcode
      * @param weatherLocationType city or postcode; eg: WeatherLocationType.city
      * @param location city name or location postcode; eg: "London"
      */
    //% help=weather/get-temperature
    //% weight=96
    //% blockId=get_place_temp
    //% block="get|temperature|for %weatherLocationType | %location" blockGap=8
    //% inlineInputMode=inline
    //% shim=weather::getTemperature
    export function getTemperature(weatherLocationType: WeatherLocationType, location: string) : string
    {
        return Math.floor(Math.random() * 25).toString();
    }

    /**
      * Get current wind direction in city or by location postcode
      * @param weatherLocationType city or postcode; eg: WeatherLocationType.city
      * @param location city name or location postcode; eg: "London"
      */
    //% help=weather/get-wind-direction
    //% weight=96
    //% blockId=get_wind_dir
    //% block="get|wind direction for %weatherLocationType | %location" blockGap=8
    //% shim=weather::getWindDirection
    export function getWindDirection(weatherLocationType: WeatherLocationType, location: string) : string
    {
        let directions = ["N", "NW", "NE","S","SE","SW","E","W"]
        return directions[Math.floor(Math.random() * 7)]
    }

    /**
      * Get current weather forecast for city or by location postcode
      * @param weatherLocationType city or postcode; eg: WeatherLocationType.city
      * @param location city name or location postcode; eg: "London"
      */
    //% help=weather/get-weather-forecast
    //% weight=96
    //% blockId=get_forecast_now
    //% block="get|weather forecast for %weatherLocationType | %location" blockGap=8
    //% shim=weather::getWeatherForecast
    export function getWeatherForecast(weatherLocationType: WeatherLocationType, location: string) : string
    {
        let weather = ["overcast", "raining", "sunny", "snowing", "thunder"]
        return weather[Math.floor(Math.random() * 4)]
    }

    /**
      * Get tomorrows weather forecast for city or by location postcode
      * @param weatherLocationType city or postcode; eg: WeatherLocationType.city
      * @param location city name or location postcode; eg: "London"
      */
    //% help=weather/get-weather-forecast-tomorrow
    //% weight=96
    //% blockId=get_forecast_tom block="get|tomorrows weather forecast for %weatherLocationType | %location" blockGap=8
    //% shim=weather::getWeatherForecastTomorrow
    export function getWeatherForecastTomorrow(weatherLocationType: WeatherLocationType, location: string)
    {
        let weather = ["overcast", "raining", "sunny", "snowing", "thunder"]
        return weather[Math.floor(Math.random() * 4)]
    }
}