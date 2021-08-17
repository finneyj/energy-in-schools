#include "pxt.h"
#include "PeridoBridge.h"

PeridoBridge *peridoBridge = NULL;
    
namespace peridobridge {
    
    //%
    int enable() {
        if (peridoBridge == NULL)
        {
            peridoBridge = new PeridoBridge(uBit.radio, uBit.serial, uBit.messageBus, uBit.display);
            peridoBridge->enable();
        }

        return 0;
    }
};
