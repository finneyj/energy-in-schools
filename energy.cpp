#include "pxt.h"
#include "EnergyService.h"
#include "stdio.h"

enum class EnergyType{
    electricity = 0,
    gas = 1,
    solar = 2,
};

enum class TimeType{
    hours = 0,
    days = 1,
    weeks = 2,
    months = 3
};

const char *TimeTypeNames[] = {"hour", "day", "week","month"};

/**
* share
* use
*/

extern PeridoRESTClient *radioTxRx;
EnergyService *energyService = NULL;

//% color=#006f00 weight=100 icon="\uf275" block="School Energy"
namespace energy {

    int init() {
        if (radioTxRx == NULL)
            radioTxRx = new PeridoRESTClient(uBit.radio, uBit.messageBus, uBit.serial);

        if (energyService == NULL)
            energyService = new EnergyService(*radioTxRx);

        return 0;
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

        char eType[20];
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

        ManagedString reply = energyService->getEnergyLevel(command);
        return reply.leakData();
    }

    //%
    int querySchoolEnergyFor(String schoolId)
    {
        EnergyType energyType = EnergyType::electricity;
        ManagedString result = queryEnergyText(energyType,MSTR(schoolId),"");
        int value = stringToNumber(result);
        return value;

    }

    //%
    int querySchoolEnergyAgo(String schoolId, int units, TimeType period)
    {
        char buffer[20];
        memset(buffer,0,sizeof(buffer));
        sprintf(buffer,"%s/%d", TimeTypeNames[(int)period], units);

        EnergyType energyType = EnergyType::electricity;
        ManagedString result = queryEnergyText(energyType, MSTR(schoolId), ManagedString(buffer));
        int value = stringToNumber(result);
        return value;
    }
};
