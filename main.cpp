#include <iostream>
#include <fstream>
#include <string>
#include "Satellite.h"
#include "BinNode.h"
using namespace std;

void Insert(BinNode *&rt, Satellite sat){

    //doesn't check condition properly, recheck
    if (rt == NULL){
        rt = new BinNode(sat);
        rt->getItem().setSatName(sat.getSatName());

    }
    else if (sat.getSatName() < rt->getItem().getSatName() ){
        Insert(rt->left, sat);
    }
    else {
        Insert(rt->right, sat);
    }

};

BinNode* readFiles(string filename){
    Satellite fileRead;
    BinNode * root;
    root = NULL;

    ifstream readFile;
    string SatName, Country, OpName, SatType, Task, ExpLife, LongTask, OrbitType, LnchDate, LnchSite, LnchVehicle;
    string discard;
    float apogee, perigee, period;
    int NORADNum;

    //first, orbit file
    readFile.open(filename);
    if (readFile.is_open()){
        cout << "File 'Orbit.txt' opened";
        while (readFile.good()){
            getline(readFile, SatName);
            if (readFile.bad() || readFile.eof()){
                readFile.close();
                break;
            }
            getline(readFile, Country);
            getline(readFile, OpName);
            getline(readFile, SatType);
            getline(readFile, Task);
            getline(readFile, LongTask);
            getline(readFile, OrbitType);
            readFile >> apogee >> perigee >> period;
            getline(readFile, discard);
            getline(readFile, LnchDate);
            getline(readFile, ExpLife);
            getline(readFile, LnchSite);
            getline(readFile, LnchVehicle);
            readFile >> NORADNum;
            getline(readFile, discard);

            fileRead.setSatName(SatName);
            fileRead.setCountry(Country);
            fileRead.setOpName(OpName);
            fileRead.setSatType(SatType);
            fileRead.setTask(Task);
            fileRead.setLongTask(LongTask);
            fileRead.setOrbitType(OrbitType);
            fileRead.setApogee(apogee);
            fileRead.setPerigee(perigee);
            fileRead.setPeriod(period);
            fileRead.setLnchDate(LnchDate);
            fileRead.setExpLife(ExpLife);
            fileRead.setLnchSite(LnchSite);
            fileRead.setLnchVehicle(LnchVehicle);
            fileRead.setNoradNum(NORADNum);

            Insert(root, fileRead);
        }

    }
    return root;

}

void printAll(BinNode *root){
    if (root != NULL){
        printAll(root->left);
        cout << root->getItem().getSatName() << endl; //change this action to dereferencing to make the delete all trees thing
        printAll(root->right);
    }

}

bool searchName(BinNode *root, string search){


    if (root == NULL){
        cout << "Tree is Empty" << endl;
        return false;

    }
    else if (root->getItem().getSatName().find(search)) {
        Satellite foundSat = root->getItem();
        cout << "Name: " << foundSat.getSatName() << endl;
        cout << "NORAD Tracking Number: " << foundSat.getNoradNum() << endl;
        return true;
    }
    else if (search < root->getItem().getSatName())
        return searchName(root->left, search );
    else{
        return searchName(root->right,search);
    }


}

int main() {
    bool quitProgram = false;

    BinNode *root;
    BinNode *rootDeorbit;
    Satellite satInput;

    root = NULL;
    rootDeorbit = NULL;

    string searchTerm, SatName, Country, OpName, SatType;
    string Task, LongTask, OrbitType, LnchDate, LnchSite, LnchVehicle, ExpLife;
    float apogee, perigee, period;
    int NORADNum;

    while (quitProgram == false){
        cout << endl;
        cout << "Please input a command - (L)aunch, (d)eorbit, (F)ind, (A)ll, (R)ead, (S)ave, (Q)uit :";

        char inputCMD;
        cin >> inputCMD;
        char input = toupper(inputCMD);

        switch (input) {
            case 'L':
                cout << "Input Satellite Name: ";
                cin >>  SatName;
                cout << "Input Country of Ownership: ";
                cin >>  Country;
                cout << "Input Name of Operator: ";
                cin >>  OpName;
                cout << "Input Satellite Type: ";
                cin >>  SatType;
                cout << "Input Purpose of Operation: ";
                cin >>  Task;
                cout << "Input Detailed Purpose, or n/a if no detail given: ";
                cin >>  LongTask;
                cout << "Input Orbit Type: ";
                cin >>  OrbitType;
                cout << "Input Apogee: ";
                cin >>  apogee;
                cout << "Input Perigee: ";
                cin >>  perigee;
                cout << "Input Period: ";
                cin >>  period;
                cout << "Input Date of Launch: ";
                cin >>  LnchDate;
                cout << "Input Expected Lifetime: ";
                cin >>  ExpLife;
                cout << "Input Launch Site Location: ";
                cin >>  LnchSite;
                cout << "Input Launch Vehicle: ";
                cin >>  LnchVehicle;
                cout << "Input NORAD Designation Number: ";
                cin >>  NORADNum;

                satInput.setNoradNum(NORADNum);
                satInput.setSatName(SatName);
                satInput.setCountry(Country);
                satInput.setOpName(OpName);
                satInput.setSatType(SatType);
                satInput.setTask(Task);
                satInput.setLongTask(LongTask);
                satInput.setOrbitType(OrbitType);
                satInput.setApogee(apogee);
                satInput.setPerigee(perigee);
                satInput.setPeriod(period);
                satInput.setLnchDate(LnchDate);
                satInput.setExpLife(ExpLife);
                satInput.setLnchSite(LnchSite);
                satInput.setLnchVehicle(LnchVehicle);

                Insert(root, satInput);
                cout << "Satellite added to launch list!" << endl;
                break;
            case 'D':
                cout << "Deorbit function ran";
                break;
            case 'F':
                bool searchTest;
                cout << "Find function ran" << endl;
                cout << "Please enter name of satellite to search: ";
                cin >> searchTerm;
                cout << "Checking Orbit..." << endl;
                searchTest = searchName(root, searchTerm);
                if (!searchTest) cout << "Term not Found" << endl;
                cout << "Checking Decommissions...";
                searchTest = searchName(rootDeorbit, "Decommissioned Satellites");
                if (!searchTest) cout << "Term not Found" << endl;
                break;
            case 'A':
                cout << "All Function ran" << endl;
                printAll(root);
                printAll(rootDeorbit);
                break;
            case 'R':
                cout << "Read function ran" << endl;
                //First, dereference anything pointed to "root" on trees to remove them

                //defererence()

                //should return pointer to root node of read trees, orbit and deorbit
                //^
                //|
                root = readFiles("orbit.txt");
                rootDeorbit = readFiles("deorbit.txt");
                break;
            case 'S':
                cout << "Save function ran";
                break;
            case 'Q':
                cout << "Quitting Program";
                quitProgram = true;
                break;
            default:
                cout << "No program run, please check input.";

        }
    }
    return 0;
}
