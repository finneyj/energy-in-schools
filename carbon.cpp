#include "pxt.h"
#include "CarbonService.h"

enum class GenerationMixType{
    gas = 0,
    coal = 1, 
    solar = 2, 
    wind = 3, 
    nuclear = 4, 
    hydro = 5, 
    biomas = 6, 
    imports = 7, 
    other = 8,
};

enum class CarbonIndex{
    very_low = 0,
    low = 1, 
    moderate = 2, 
    high = 3, 
    very_high = 4, 
};

static const char* const generationTypes[] = {"gas","coal","solar","wind","nuclear","hydro","biomas","imports","other"}; 
static const char* const carbonIndexValueTypes[] = {"very_low","low","moderate","high","very_high"}; 

/**
* share
* use
*/
PeridoRESTClient *radioTxRx = NULL;
CarbonService *carbonService = NULL;

//% color=#000000 weight=100 icon="\uf216" block="Carbon"
namespace carbon {

    int init() {
        if (radioTxRx == NULL)
            radioTxRx = new PeridoRESTClient(uBit.radio, uBit.messageBus, uBit.serial);

        if (carbonService == NULL)
            carbonService = new CarbonService(*radioTxRx);    

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

    //%
    int queryCarbonValue()
    {
        init();
        ManagedString reply = carbonService->getCarbonValue("value");
        int value = stringToNumber(reply);
        return value;
    }

    //Convert the carbon index from string to int
    // 'very low' 'low' 'moderate' 'high' 'very high'
    //  0          1     2          3      4
    //%
    int queryCarbonIndex()
    {
        init();

        ManagedString reply = carbonService->getCarbonIndex("index");

        int replyValue = -1;

        for(int loop=0; loop < 5; ++ loop)
        {
            //Compare the response text with the items in the array
            //if we get a match, the loop value is the correct number to return
            if(strcmp(carbonIndexValueTypes[loop], reply.toCharArray()) == 0)
            {
                replyValue = loop;
                break;
            }
        }
        return replyValue;
    }

    //%
    String queryCarbonIndexText()
    {
        init();

        ManagedString reply = carbonService->getCarbonIndex("index");
        return PSTR(reply);
    }

    //%
    int queryCarbonGenerationMix(GenerationMixType mix)
    {
        init();
        //Check the input value bounds
        if(mix < GenerationMixType::gas)
        {
            mix = GenerationMixType::gas;
        }

        if(mix > GenerationMixType::other)
        {
            mix = GenerationMixType::other;
        }
               
        ManagedString command = "genmix/";
        command = command + generationTypes[(int)mix];
        
        ManagedString reply = carbonService->getCarbonGenerationMix(command);
        int value = stringToNumber(reply);
        return value;
    }


    //%
    int setGenerationMixType(GenerationMixType GenerationMixType)
    {
        return (int)GenerationMixType;
    }

    //%
    int setCarbonIndexValueType(CarbonIndex index)
    {
        return (int)index;
    }

    
};
