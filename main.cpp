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

void findNode(BinNode *&cursor, string search, BinNode *&precursor){
    while (cursor != NULL && cursor->getItem().SatName != search){
        precursor = cursor;
        if (search > cursor->getItem().SatName){
            cursor = cursor->right;
        }else{
            cursor = cursor ->left;
        }
    }
}

BinNode* findLowest(BinNode *cursor){
    while(cursor->getLeft() != NULL){
        cursor = cursor->left;
    }
    return cursor;
}

void printAll(BinNode *root){
    if (root != NULL){
        printAll(root->left);
        cout << root->getItem().getSatName() << endl;
        printAll(root->right);
    }
}

Satellite Deorbit(BinNode *root, string delSearch){
    BinNode* precursor = NULL;
    BinNode* cursor = root;
    findNode(cursor, delSearch, precursor);
    Satellite returnedSat = cursor->getItem();
    Satellite nullSat;
    nullSat.setNoradNum(1010101010);

    if (cursor == NULL){
        cout<< "Satellite not found. Please try a different search term." << endl;
        return nullSat;
    }else if (cursor->left == NULL && cursor->right == NULL){
        if (cursor != root){
            if (precursor->right == cursor){
                precursor->right = NULL;
            }else
                precursor->left = NULL;
        }else
            root = NULL;

        free(cursor);


    }else if (cursor->left != NULL && cursor->right != NULL){
        BinNode* replace = findLowest(cursor->right);
        Satellite rpSat = replace->getItem();

        Deorbit(root, replace->getItem().SatName);

        cursor->setItem(rpSat);
    }
    else{

        BinNode * child;
        if (cursor->left == NULL){
            child = cursor->right;
        }else
            child = cursor->left;

        if (cursor == root){
            root = child;
        }else if (cursor == precursor->left){
            precursor->left = child;
        }else{
            precursor->right = child;
        }
        free(cursor);
    }

    return returnedSat;
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
        cout << "File opened" <<endl;
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
        saveFiles(root->right, filename);
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

    }
    write.close();
}

bool findName(BinNode *root, string search){
    if (root == NULL){
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
                cin.clear();
                while (cin.get()!= '\n'){continue;}
                cout << "Input Satellite Name: ";
                getline(cin, SatName);
                cout << '\n' << "Input Country of Ownership: ";
                getline(cin, Country);
                cout << '\n' << "Input Name of Operator: ";
                getline(cin, OpName);
                cout << '\n' << "Input Satellite Type: ";
                getline(cin, SatType);
                cout << '\n' << "Input Purpose of Operation: ";
                getline(cin, Task);
                cout << '\n' << "Input Detailed Purpose, or n/a if no detail given: ";
                getline(cin, LongTask);
                cout << '\n' << "Input Orbit Type: ";
                getline(cin, OrbitType);
                cout << '\n' << "Input Apogee: ";
                cin >>  apogee;
                cout << '\n' << "Input Perigee: ";
                cin >>  perigee;
                cout << '\n' << "Input Period: ";
                cin >>  period;
                cin.clear();
                while (cin.get()!= '\n'){continue;}
                cout << '\n' << "Input Date of Launch: ";
                getline(cin, LnchDate);
                cout << '\n' << "Input Expected Lifetime: ";
                getline(cin, ExpLife);
                cout << '\n' << "Input Launch Site Location: ";
                getline(cin, LnchSite);
                cout << '\n' << "Input Launch Vehicle: ";
                getline(cin, LnchVehicle);
                cout << '\n' << "Input NORAD Designation Number: ";
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
                cout << "Enter satellite for removal: ";
                cin.clear();
                while (cin.get()!= '\n'){continue;}
                getline(cin, searchTerm);
                satInput = Deorbit(root, searchTerm);
                if (satInput.getNoradNum() == 1010101010){
                    cout << "Satellite not found. Aborting..." <<endl;
                    break;
                }else {
                    Insert(rootDeorbit, satInput);
                    cout << '\n' << "Satellite deorbited." << endl;
                }

                break;

            case 'F':
                bool searchTest;

                cout << "\n" << "Please enter name of satellite to search: ";
                cin.clear();
                while (cin.get()!= '\n'){
                    continue;
                }
                getline(cin, searchTerm);

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
