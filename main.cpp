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
        //rt->getItem().setSatName(sat.getSatName());

    }
    else if (sat.getSatName() < rt->getItem().getSatName() ){
        Insert(rt->left, sat);
    }
    else {
        Insert(rt->right, sat);
    }

};

void Deorbit(BinNode *root, string delSearch){

}

void deleteTree(BinNode *root){
    if (root == NULL){
        return;
    }
    deleteTree(root->left);
    deleteTree(root->right);
    cout<< "deleting node" <<endl;
    free(root);
}

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

void saveFiles(BinNode *root, string filename){
    ofstream write;
    write.open(filename, ios::out | ios::app);
    if (root != NULL){
        saveFiles(root->left, filename);
        write << root->getItem().SatName << endl;
        write << root->getItem().Country << endl;
        write << root->getItem().OpName << endl;
        write << root->getItem().SatType << endl;
        write << root->getItem().Task << endl;
        write << root->getItem().LongTask << endl;
        write << root->getItem().OrbitType << endl;
        write << root->getItem().apogee << endl;
        write << root->getItem().perigee << endl;
        write << root->getItem().period << endl;
        write << root->getItem().LnchDate << endl;
        write << root->getItem().ExpLife << endl;
        write << root->getItem().LnchSite << endl;
        write << root->getItem().LnchVehicle << endl;
        write << root->getItem().NORADNum << endl;
        saveFiles(root->right, filename);
    }
    write.close();
}

void printAll(BinNode *root){
    if (root != NULL){
        printAll(root->left);
        cout << root->getItem().getSatName() << endl;
        printAll(root->right);
    }
}

bool findName(BinNode *root, string search){
    if (root == NULL){
        cout << "Tree is Empty" << endl;
        return false;
    }
    else if (root->getItem().getSatName() == search) {
        Satellite Sat = root->getItem();
        cout << "**Name: " << Sat.SatName << endl;
        cout << "**NORAD Tracking No.: " << Sat.getNoradNum() << endl;
        cout << "**Sat. Type: " << Sat.SatType << endl;
        cout << "**Country of Ownership: " << Sat.Country << endl;
        cout << "**Operator Name: " << Sat.OpName << endl;
        cout << "**Purpose: " << Sat.Task << endl;
        cout << "**Detailed Purpose: " << Sat.LongTask << endl;
        cout << "**Expected Lifetime: " << Sat.ExpLife << endl;
        cout << "**Orbit Type: " << Sat.OrbitType << endl;
        cout << "**Apogee/Perigee/Period: "<< Sat.apogee<< "/"<< Sat.perigee<< "/"<< Sat.period<< endl;
        cout << "**Launched On: " << Sat.LnchDate << endl;
        cout << "**Launched From: " << Sat.LnchSite << endl;
        cout << "**Launch Vehicle: " << Sat.LnchVehicle << endl;
        return true;
    }
    else if (search < root->getItem().getSatName())
        return findName(root->left, search );
    else{
        return findName(root->right, search );
    }
}

int main() {
    bool quitProgram = false;

    ofstream fileClear;
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
        cout << "Please input a command - (L)aunch, (D)eorbit, (F)ind, (A)ll, (R)ead, (S)ave, (Q)uit :";

        char inputCMD;
        cin >> inputCMD;
        char input = toupper(inputCMD);

        switch (input) {
            case 'L':
                cout << "Input Satellite Name: ";
                cin >> noskipws >> SatName;
                cout << "Input Country of Ownership: ";
                cin >> noskipws >> Country;
                cout << "Input Name of Operator: ";
                cin >> noskipws >> OpName;
                cout << "Input Satellite Type: ";
                cin >> noskipws >>  SatType;
                cout << "Input Purpose of Operation: ";
                cin >> noskipws >>  Task;
                cout << "Input Detailed Purpose, or n/a if no detail given: ";
                cin >> noskipws >> LongTask;
                cout << "Input Orbit Type: ";
                cin >> noskipws >> OrbitType;
                cout << "Input Apogee: ";
                cin >>  apogee;
                cout << "Input Perigee: ";
                cin >>  perigee;
                cout << "Input Period: ";
                cin >>  period;
                cout << "Input Date of Launch: ";
                cin >>  LnchDate;
                cout << "Input Expected Lifetime: ";
                cin >> noskipws >>  ExpLife;
                cout << "Input Launch Site Location: ";
                cin >> noskipws >> LnchSite;
                cout << "Input Launch Vehicle: ";
                cin >> noskipws >> LnchVehicle;
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
                //------------------------------------------------------------
                //------------------------------------------------------------
                break;

            case 'F':
                bool searchTest;

                cout << "Please enter name of satellite to search: ";
                cin >> noskipws >> searchTerm;

                cout << "Checking Orbit..." << endl;
                searchTest = findName(root, searchTerm);
                if (!searchTest) cout << "Term not Found" << endl;
                cout << endl;

                cout << "Checking Decommissions...";
                searchTest = findName(rootDeorbit, searchTerm);
                if (!searchTest) cout << "Term not Found" << endl;

                break;

            case 'A':
                cout << "---------ORBITING---------" << endl;
                printAll(root);
                cout << "------DECOMMSSIONED-------" << endl;
                printAll(rootDeorbit);
                break;

            case 'R':
                deleteTree(root);
                deleteTree(rootDeorbit);
                root = readFiles("orbit.txt");
                rootDeorbit = readFiles("deorbit.txt");
                cout << "Files read!" << endl;
                break;

            case 'S':

                fileClear.open("orbit.txt", ios::out| ios::trunc);
                fileClear.close();
                fileClear.open("deorbit.txt", ios::out| ios::trunc);
                fileClear.close();

                saveFiles(root, "orbit.txt");
                saveFiles(rootDeorbit, "deorbit.txt");
                cout << "Saved to file!" << endl;
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
