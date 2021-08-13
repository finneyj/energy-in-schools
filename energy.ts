/**
 * Query selected energy type consumption for my or another school for different periods
 */
//% color=#006f00 weight=100 icon="\uf275" block="School Energy"
namespace energy {


    /**
     * Get selected energy type current usage for my school
     * @param energyType energy type; eg: EnergyType.electricity
     */
    //% help=energy/get-my-school-energy-usage
    //% weight=100
    //% blockId=energy_querySchoolEnergy
    //% block="get energy level|for %energyType |for my school"
    //% shim=energy::querySchoolEnergy
    export function querySchoolEnergy(energyType: EnergyType): number {
        return Math.floor(Math.random() * 25) + 100;
    }

    /**
     * Get my school selected energy type total usage for selected time in hours
     * @param energyType energy type; eg: EnergyType.electricity
     * @param hourType time amount; eg: HourType._1_hour_ago
     */
    //% help=energy/get-my-school-energy-usage-for-hours
    //% weight=98
    //% blockId=energy_querySchoolEnergyHour
    //% block="get energy level|for %energyType |for hour %hourType|for my school"
    //% shim=energy::querySchoolEnergyHour
    export function querySchoolEnergyHour(energyType: EnergyType, hourType: HourType): number {
        return Math.floor(Math.random() * 25) + 100;
    }

    /**
     * Get my school selected energy type total usage for selected time in days
     * @param energyType energy type; eg: EnergyType.electricity
     * @param dayType time amount; eg: DayType.yesterday
     */
    //% help=energy/get-my-school-energy-usage-for-days
    //% weight=96
    //% blockId=energy_querySchoolEnergyDay
    //% block="get energy level|for %energyType |for day %dayType|for my school"
    //% shim=energy::querySchoolEnergyDay
    export function querySchoolEnergyDay(energyType: EnergyType, dayType: DayType): number {
        return Math.floor(Math.random() * 25) + 100;
    }

    /**
     * Get my school selected energy type total usage for selected time in weeks
     * @param energyType energy type; eg: EnergyType.electricity
     * @param weekType time amount; eg: WeekType.last_week
     */
    //% help=energy/get-my-school-energy-usage-for-weeks
    //% weight=94
    //% blockId=energy_querySchoolEnergyWeek
    //% block="get energy level|for %energyType |for week %weekType|for my school"
    //% shim=energy::querySchoolEnergyWeek
    export function querySchoolEnergyWeek(energyType: EnergyType, weekType: WeekType): number {
        return Math.floor(Math.random() * 25) + 100;
    }


    /**
     * Get my school selected energy type total usage for selected time in months
     * @param energyType energy type; eg: EnergyType.electricity
     * @param monthType time amount; eg: MonthType.last_month
     */
    //% help=energy/get-my-school-energy-usage-for-months
    //% weight=92
    //% blockId=energy_querySchoolEnergyMonth
    //% block="get energy level|for %energyType |for month %monthType|for my school"
    //% shim=energy::querySchoolEnergyMonth
    export function querySchoolEnergyMonth(energyType: EnergyType, monthType: MonthType): number {
        return Math.floor(Math.random() * 25) + 100;
    }

    /**
     * Get selected energy type current usage for other school
     * @param energyType energy type; eg: EnergyType.electricity
     * @param schoolId target school ID; eg: AB123
     */
    //% help=energy/get-other-school-energy-usage
    //% weight=99
    //% blockId=energy_queryEnergy
    //% block="get energy level|for %energyType |for other school %schoolId"
    //% shim=energy::queryEnergy
    export function queryEnergy(energyType: EnergyType, schoolId: string): number {
        return Math.floor(Math.random() * 25) + 100;
    }


    /**
     * Get other school selected energy type total usage for selected time in hours
     * @param energyType energy type; eg: EnergyType.electricity
     * @param hourType time amount; eg: HourType._1_hour_ago
     * @param schoolId target school ID; eg: AB123
     */
    //% help=energy/get-other-school-energy-usage-for-hours
    //% weight=97
    //% blockId=energy_queryEnergyHour
    //% block="get energy level|for %energyType |for hour %hourType |for other school %schoolId"
    //% shim=energy::queryEnergyHour
    export function queryEnergyHour(energyType: EnergyType, hourType: HourType, schoolId: string): number {
        return Math.floor(Math.random() * 25) + 100;
    }

    /**
     * Get other school selected energy type total usage for selected time in days
     * @param energyType energy type; eg: EnergyType.electricity
     * @param dayType time amount; eg: DayType.yesterday
     * @param schoolId target school ID; eg: AB123
     */
    //% help=energy/get-other-school-energy-usage-for-days
    //% weight=95
    //% blockId=energy_queryEnergyDay
    //% block="get energy level|for %energyType |for day %dayType |for other school %schoolId"
    //% shim=energy::queryEnergyDay
    export function queryEnergyDay(energyType: EnergyType, dayType: DayType, schoolId: string): number {
        return Math.floor(Math.random() * 25) + 100;
    }

    /**
     * Get other school selected energy type total usage for selected time in weeks
     * @param energyType energy type; eg: EnergyType.electricity
     * @param weekType time amount; eg: WeekType.last_week
     * @param schoolId target school ID; eg: AB123
     */
    //% help=energy/get-other-school-energy-usage-for-weeks
    //% weight=93
    //% blockId=energy_queryEnergyWeek
    //% block="get energy level|for %energyType |for week %weekType |for other school %schoolId"
    //% shim=energy::queryEnergyWeek
    export function queryEnergyWeek(energyType: EnergyType, weekType: WeekType, schoolId: string): number {
        return Math.floor(Math.random() * 25) + 100;
    }

    /**
     * Get other school selected energy type total usage for selected time in months
     * @param energyType energy type; eg: EnergyType.electricity
     * @param monthType time amount; eg: MonthType.last_months
     * @param schoolId target school ID; eg: AB123
     */
    //% help=energy/get-other-school-energy-usage-for-months
    //% weight=91
    //% blockId=energy_queryEnergyMonth
    //% block="get energy level|for %energyType |for month %monthType |for other school %schoolId"
    //% shim=energy::queryEnergyMonth
    export function queryEnergyMonth(energyType: EnergyType, monthType: MonthType, schoolId: string): number {
        return Math.floor(Math.random() * 25) + 100;
    }
}