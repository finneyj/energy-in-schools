/**
 * Query selected energy type consumption for my or another school for different periods
 */
//% color=#006f00 weight=100 icon="\uf275" block="School Energy"
namespace energy {

    //% weight=96
    //% blockId=energy_queryOtherSchool
    //% block="get school %school %energyType usage"
    //% shim=energy::querySchoolEnergyFor
    export function querySchoolEnergyFor(school: string, energyType: EnergyType): number {
        return Math.floor(Math.random() * 25) + 100;
    }

    //% weight=97
    //% blockId=energy_querySchoolEnergyPeriod
    //% inlineInputMode=inline
    //% block="get school %school %energyType usage for %units %period ago"
    //% shim=energy::querySchoolEnergyAgo
    export function queryHistoricSchoolEnergyFor(school: string, energyType: EnergyType, units: number, period: TimeType): number {
        return Math.floor(Math.random() * 25) + 100;
    }
}