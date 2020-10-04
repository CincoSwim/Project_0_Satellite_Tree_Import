/*
 * EECS 2150 Project 0 - Binary Search Tree of Satellites
 * Author: Christopher Pucko
 *
 * Header for Satellite object class. Defines variables, an empty constructor, and setters for each variable.
 */
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


        const string &getSatName() const {return SatName;}
        void setSatName(const string &satName) {SatName = satName;}

        void setCountry(const string &country) {
            Country = country;
        }

        void setOpName(const string &opName) {
            OpName = opName;
        }

        void setSatType(const string &satType) {
            SatType = satType;
        }

        void setTask(const string &task) {
            Task = task;
        }

        void setLongTask(const string &longTask) {
            LongTask = longTask;
        }

        void setOrbitType(const string &orbitType) {
            OrbitType = orbitType;
        }

        void setLnchDate(const string &lnchDate) {
            LnchDate = lnchDate;
        }

        void setLnchSite(const string &lnchSite) {
            LnchSite = lnchSite;
        }

        void setLnchVehicle(const string &lnchVehicle) {
            LnchVehicle = lnchVehicle;
        }

        void setApogee(float apogee) {
            Satellite::apogee = apogee;
        }

        void setPerigee(float perigee) {
            Satellite::perigee = perigee;
        }

        void setPeriod(float period) {
            Satellite::period = period;
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
