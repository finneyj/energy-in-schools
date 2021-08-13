#include "pxt.h"
#include "EnergyService.h"

enum class EnergyType{
    electricity = 0,
    gas = 1,
    solar = 2,
};

enum class HourType{
    _1_hour_ago = 1,
    _2_hours_ago = 2,
    _3_hours_ago = 3,
    _4_hours_ago = 4,
    _5_hours_ago = 5,
    _6_hours_ago = 6,
    _7_hours_ago = 7,
    _8_hours_ago = 8,
    _9_hours_ago = 9,
    _10_hours_ago = 10,
    _11_hours_ago = 11,
    _12_hours_ago = 12,
    _13_hours_ago = 13,
    _14_hours_ago = 14,
    _15_hours_ago = 15,
    _16_hours_ago = 16,
    _17_hours_ago = 17,
    _18_hours_ago = 18,
    _19_hours_ago = 19,
    _20_hours_ago = 20,
    _21_hours_ago = 21,
    _22_hours_ago = 22,
    _23_hours_ago = 23,
    _24_hours_ago = 24,
    _25_hours_ago = 25,
};

enum class DayType{
    yesterday = 1,
    _2_days_ago = 2,
    _3_days_ago = 3,
    _4_days_ago = 4,
    _5_days_ago = 5,
    _6_days_ago = 6,
    _7_days_ago = 7,
    _8_days_ago = 8,
};

enum class WeekType{
    last_week = 1,
    _2_weeks_ago = 2,
    _3_weeks_ago = 3,
    _4_weeks_ago = 4,
    _5_weeks_ago = 5,
};

enum class MonthType{
    last_month = 1,
    _2_months_ago = 2,
    _3_months_ago = 3,
    _4_months_ago = 4,
    _5_months_ago = 5,
    _6_months_ago = 6,
    _7_months_ago = 7,
    _8_months_ago = 8,
    _9_months_ago = 9,
    _10_months_ago = 10,
    _11_months_ago = 11,
    _12_months_ago = 12,
    _13_months_ago = 13,
};



/**
* share
* use
*/
extern PeridoRESTClient radioTxRx;
EnergyService EnergyService(radioTxRx);

//% color=#006f00 weight=100 icon="\uf275" block="School Energy"
namespace energy {

    int init() {

    }

    int stringToNumber(ManagedString input)
    {
        ManagedString resultString = "";
        int result = 0;

        int l = input.length();
        for(int x=0; x < l; ++x)
        {
            if(input.charAt(x) != '\n' && input.charAt(x) != '\r')
            {
                if(isdigit(input.charAt(x)) || input.charAt(x) == '.')
                {
                    resultString = resultString + input.charAt(x);
                }
                else
                {
                    result = -1;
                    break;
                }
            }
        }
        if(result > -1)
        {
            float f = atof(resultString.toCharArray());
            result = round(f);
        }
        return result;
    }


    // Commands at Raspberry Pi
    //
    //  Query Energy Electric for MY School and Other School 655BD
    //          energy/energyLevel/0/local
    //          energy/energyLevel/0/655BD
    //                            |  |
    //                            |  }--> School Id or local
    //                            }--> Energy Type: Gas = 0, Electric = 1, Solar = 2
    //
    //  Historical
    //
    //  Query Energy Historical Electric by DAY for My School and Other School 655BD
    //          energy/historical/energyLevel/0/day/3/local
    //          energy/historical/energyLevel/0/day/3/655BD
    //                 |                      |  |  | |
    //                 |                      |  |  | }--> School Id or local
    //                 |                      |  |  }-->Amount of days back: 1 = yesterday, 2 = the day before
    //                 |                      |  }--> Type of historical time:  hour, day, week, month
    //                 |                      }--> Energy Type: Gas = 0, Electric = 1, Solar = 2
    //                 }--> historical, So we know this is looking for historical data


    //%
    StringData* queryEnergyText(EnergyType energyType, ManagedString schoolId, ManagedString historicData)
    {
        init();

        //protect against invalid input
        if(energyType < EnergyType::electricity)
        {
            energyType = EnergyType::electricity;
        }
        if(energyType > EnergyType::solar)
        {
            energyType = EnergyType::solar;
        }

        ManagedString command = "nrgLvl/";

        char eType[5];
        memset(eType,0,sizeof(eType));
        sprintf(eType,"%d",(int)energyType);

        command = command + eType;
        command = command + "/";

        command = command + schoolId;
        command = command + "/";

        if(historicData.length() > 0)
        {
            command = command + "hst/";
        }

         if(historicData.length() > 0)
        {
            command = command + historicData;
        }

        ManagedString reply = EnergyService.getEnergyLevel(command);
        return reply.leakData();
    }

    //%
    int queryEnergy(EnergyType energyType, String schoolId)
    {
        ManagedString result = queryEnergyText(energyType,MSTR(schoolId),"");
        int value = stringToNumber(result);
        return value;
    }


    //%
    int queryEnergyHour(EnergyType energyType, HourType hourType, String schoolId)
    {
        char buffer[6];
        memset(buffer,0,sizeof(buffer));
        sprintf(buffer,"hour/%d", (int)hourType);
        ManagedString result = queryEnergyText(energyType, MSTR(schoolId), ManagedString(buffer));
        int value = stringToNumber(result);
        return value;
    }

    //%
    int queryEnergyDay(EnergyType energyType, DayType dayType, String schoolId)
    {
        char buffer[6];
        memset(buffer,0,sizeof(buffer));
        sprintf(buffer,"day/%d", (int)dayType);
        ManagedString result = queryEnergyText(energyType, MSTR(schoolId), ManagedString(buffer));
        int value = stringToNumber(result);
        return value;
    }

    //%
    int queryEnergyWeek(EnergyType energyType, WeekType weekType, String schoolId)
    {
        char buffer[6];
        memset(buffer,0,sizeof(buffer));
        sprintf(buffer,"week/%d", (int)weekType);
        ManagedString result = queryEnergyText(energyType, MSTR(schoolId), ManagedString(buffer));
        int value = stringToNumber(result);
        return value;
    }

    //%
    int queryEnergyMonth(EnergyType energyType, MonthType monthType, String schoolId)
    {
        char buffer[6];
        memset(buffer,0,sizeof(buffer));
        sprintf(buffer,"month/%d", (int)monthType);
        ManagedString result = queryEnergyText(energyType, MSTR(schoolId), ManagedString(buffer));
        int value = stringToNumber(result);
        return value;
    }

    //%
    int querySchoolEnergy(EnergyType energyType)
    {
        ManagedString result = queryEnergyText(energyType, ManagedString("local"), "");
        int value = stringToNumber(result);
        return value;
    }



    //%
    int querySchoolEnergyDay(EnergyType energyType, DayType dayType)
    {
        char buffer[6];
        memset(buffer,0,sizeof(buffer));
        sprintf(buffer,"day/%d", (int)dayType);
        ManagedString result = queryEnergyText(energyType, ManagedString("local"), ManagedString(buffer));
        int value = stringToNumber(result);
        return value;
    }

    //%
    int querySchoolEnergyHour(EnergyType energyType, HourType hourType)
    {
        char buffer[6];
        memset(buffer,0,sizeof(buffer));
        sprintf(buffer,"hour/%d", (int)hourType);
        ManagedString result = queryEnergyText(energyType, ManagedString("local"), ManagedString(buffer));
        int value = stringToNumber(result);
        return value;
    }

    //%
    int querySchoolEnergyWeek(EnergyType energyType, WeekType weekType)
    {
        char buffer[6];
        memset(buffer,0,sizeof(buffer));
        sprintf(buffer,"week/%d", (int)weekType);
        ManagedString result = queryEnergyText(energyType, ManagedString("local"), ManagedString(buffer));
        int value = stringToNumber(result);
        return value;
    }

    //%
    int querySchoolEnergyMonth(EnergyType energyType, MonthType monthType)
    {
        char buffer[6];
        memset(buffer,0,sizeof(buffer));
        sprintf(buffer,"month/%d", (int)monthType);
        ManagedString result = queryEnergyText(energyType, ManagedString("local"), ManagedString(buffer));
        int value = stringToNumber(result);
        return value;
    }

};
