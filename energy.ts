/**
 * Query selected energy type consumption for my or another school for different periods
 */
//% color=#006f00 weight=100 icon="\uf275" block="School Energy"
namespace energy {

    //% weight=96
    //% blockId=energy_queryOtherSchool
    //% block="get school %school instantaneous power (W)"
    //% shim=energy::querySchoolEnergyFor
    export function querySchoolEnergyFor(school: string): number {
        return Math.floor(Math.random() * 25) + 100;
    }

    //% weight=97
    //% blockId=energy_querySchoolEnergyPeriod
    //% inlineInputMode=inline
    //% block="get school %school electricity usage (Wh) for %units %period ago"
    //% units.min=1 units.defl=1
    //% shim=energy::querySchoolEnergyAgo
    export function queryHistoricSchoolEnergyFor(school: string, units: number, period: TimeType): number {
        return Math.floor(Math.random() * 25) + 100;
    }
}