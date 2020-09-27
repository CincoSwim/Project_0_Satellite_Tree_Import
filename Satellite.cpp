//
// Created by Chris on 9/26/2020.
//

#include "Satellite.h"

//Constructor
Satellite::Satellite(string SatName, string Country, string OpName, string SatType, string Task, string LongTask,
                     string OrbitType, string LnchDate, string LnchSite, string LnchVehicle, int apogee, int perigee,
                     int period, int ExpLife, int NORADNum) {
        setSatName(SatName);
        setCountry(Country);
        setOpName(OpName);
        setSatType(SatType);
        setTask(Task);
        setLongTask(LongTask);
        setOrbitType(OrbitType);
        setLnchDate(LnchDate);
        setLnchSite(LnchSite);
        setLnchVehicle(LnchVehicle);
        setApogee(apogee);
        setPerigee(perigee);
        setPeriod(period);
        setExpLife(ExpLife);
        setNoradNum(NORADNum);
}