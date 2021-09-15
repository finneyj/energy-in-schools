/**
 * Get information about carbon emission level for different energy types
 */
//% color=#004d00 weight=90 icon="\uf3fd" block="Carbon"
namespace carbon {

    /**
     * Sets carbon index value type
     * @param index target carbon index type; eg: CarbonIndex.moderate
     */
    //% help=carbon/set-carbon-index-value-type
    //% weight=100
    //% blockId=carbon_setCarbonIndexValueType
    //% block="carbon index level %index"
    //% shim=carbon::setCarbonIndexValueType
    export function setCarbonIndexValueType(index:CarbonIndex): number {
        return index;
    }

    /**
     * Get current carbon emission value
     */
    //% help=carbon/query-carbon-value
    //% weight=99
    //% blockId=carbon_queryCarbonValue
    //% block="get carbon value"
    //% shim=carbon::queryCarbonValue
    export function queryCarbonValue(): number {
        return Math.floor(Math.random() * 25) + 100;
    }

    /**
     * Get current carbon emission index level
     */
    //% help=carbon/query-carbon-index
    //% weight=98
    //% blockId=carbon_queryCarbonIndex
    //% block="get carbon index level"
    //% shim=carbon::queryCarbonIndex
    export function queryCarbonIndex(): number {
        return Math.floor(Math.random() * 25) + 100;
    }

    /**
     * Get current carbon emission index level as text
     */
    //% help=carbon/query-carbon-index-text
    //% weight=97
    //% blockId=carbon_queryCarbonIndexText
    //% block="get carbon index level as text"
    //% shim=carbon::queryCarbonIndexText
    export function queryCarbonIndexText(): string {
        let n = Math.floor(Math.random() * 5);
        
        switch(n)
        {
            case 0:
                return "very low";
            case 1:
                return "low";
            case 2:
                return "moderate";
            case 3:
                return "high";
            case 4:
                return "very high";
        }
        return "moderate";
    }

    /**
     * Get current carbon generation mix for specific type
     * @param mixType mixType; eg: GenerationMixType.gas
     */
    //% help=carbon/query-carbon-generation-mix
    //% weight=96
    //% blockId=carbon_queryCarbonGenerationMix
    //% block="get carbon generation mix|for type %mix"
    //% shim=carbon::queryCarbonGenerationMix
    export function queryCarbonGenerationMix(mixType : GenerationMixType): number
    {
        if(mixType == GenerationMixType.biomass){
            return Math.floor(Math.random() * 10) + 5;
        }
        if(mixType == GenerationMixType.coal){
            return Math.floor(Math.random() * 10) + 15;
        }
        if(mixType == GenerationMixType.imports){
            return Math.floor(Math.random() * 10) + 5;
        }
        if(mixType == GenerationMixType.gas){
            return Math.floor(Math.random() * 10) + 20;
        }
        if(mixType == GenerationMixType.nuclear){
            return Math.floor(Math.random() * 10) + 10;
        }
        if(mixType == GenerationMixType.hydro){
            return Math.floor(Math.random() * 10) + 1;
        }
        if(mixType == GenerationMixType.solar){
            return Math.floor(Math.random() * 10) + 10;
        }
        if(mixType == GenerationMixType.wind){
            return Math.floor(Math.random() * 10) + 2;
        }
        return 0;
    }
}