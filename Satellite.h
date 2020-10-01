//
// Created by Chris on 9/26/2020.
//
#include <string>
#ifndef PROJECT_0_SATELLITE_TREE_IMPORT_SATELLITE_H
#define PROJECT_0_SATELLITE_TREE_IMPORT_SATELLITE_H

using namespace std;

class Satellite {

    public:
        //double check these to make sure they're the right primitive type!!!
        string SatName, Country, OpName, SatType;
        string Task, LongTask, OrbitType, LnchDate, LnchSite, LnchVehicle, ExpLife;
        float apogee, perigee, period;
        int NORADNum;


        Satellite ();

        Satellite (string SatName);


        const string &getSatName() const {return SatName;}
        void setSatName(const string &satName) {SatName = satName;}
        const string &getCountry() const {
            return Country;
        }
        void setCountry(const string &country) {
            Country = country;
        }
        const string &getOpName() const {
            return OpName;
        }
        void setOpName(const string &opName) {
            OpName = opName;
        }
        const string &getSatType() const {
            return SatType;
        }
        void setSatType(const string &satType) {
            SatType = satType;
        }
        const string &getTask() const {
            return Task;
        }
        void setTask(const string &task) {
            Task = task;
        }
        const string &getLongTask() const {
            return LongTask;
        }
        void setLongTask(const string &longTask) {
            LongTask = longTask;
        }
        const string &getOrbitType() const {
            return OrbitType;
        }
        void setOrbitType(const string &orbitType) {
            OrbitType = orbitType;
        }
        const string &getLnchDate() const {
            return LnchDate;
        }
        void setLnchDate(const string &lnchDate) {
            LnchDate = lnchDate;
        }
        const string &getLnchSite() const {
            return LnchSite;
        }
        void setLnchSite(const string &lnchSite) {
            LnchSite = lnchSite;
        }
        const string &getLnchVehicle() const {
            return LnchVehicle;
        }
        void setLnchVehicle(const string &lnchVehicle) {
            LnchVehicle = lnchVehicle;
        }
        float getApogee() const {
            return apogee;
        }
        void setApogee(float apogee) {
            Satellite::apogee = apogee;
        }
        float getPerigee() const {
            return perigee;
        }
        void setPerigee(float perigee) {
            Satellite::perigee = perigee;
        }
        float getPeriod() const {
            return period;
        }
        void setPeriod(float period) {
            Satellite::period = period;
        }
        string getExpLife() const {
            return ExpLife;
        }
        void setExpLife(string expLife) {
            ExpLife = expLife;
        }
        int getNoradNum() const {
            return NORADNum;
        }
        void setNoradNum(int noradNum) {
            NORADNum = noradNum;
        }
};


#endif //PROJECT_0_SATELLITE_TREE_IMPORT_SATELLITE_H
