/*
 * EECS 2150 Project 0 - Binary Search Tree of Satellites
 * Author: Christopher Pucko
 *
 * A terminal-based C++ program to access and manipulate data on orbiting/deorbited satellites.
 * Satellites and their related data are stored within a Binary Tree that sorts by ASCII comparison of the satellite's name.
 * These trees can be searched, added to, saved to file, or read from file.
 * Satellites in the Orbit tree can also be moved to the Deorbit tree to denote their Decommissioned state.
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "Satellite.h"
#include "BinNode.h"
using namespace std;

void Insert(BinNode *&rt, Satellite sat){
    //Inserts a Satellite object into a tree, starting at pointer 'rt';

    if (rt == NULL){ //If tree is empty, inserted sat becomes new Root.
        rt = new BinNode(sat);
    }
    else if (sat.getSatName() < rt->getItem().getSatName() ){
        //Inserts to left side, introduces recursion to continue down a tree.
        Insert(rt->left, sat);
    }
    else {
        //Inserts to right side, also recursive to go down tree.
        Insert(rt->right, sat);
    }

};

void findNode(BinNode *&cursor, string search, BinNode *&precursor){
    //Moves a pointer (cursor) down a binary tree to find a node.
    //When completed, cursor will be a pointer for the node requested.
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
    //Finds the node of the smallest value going down a tree from pointer 'cursor'.
    while(cursor->getLeft() != NULL){
        cursor = cursor->left;
    }
    return cursor;
}

void printAll(BinNode *root){
    //Prints the name of all Satellite nodes in a tree using an in-order traversal.
    if (root != NULL){
        printAll(root->left);
        cout << root->getItem().getSatName() << endl;
        printAll(root->right);
    }
}

Satellite Deorbit(BinNode *root, string delSearch){
    //Deorbits a Satellite by finding it, saving its values, removing the node, then returning the retained value.
    //The satellite is returned outside this function so that Deorbit() can be used recursively without issue.
    BinNode* precursor = NULL;
    BinNode* cursor = root;

    findNode(cursor, delSearch, precursor); //Finds the node requested, then saves it
    Satellite returnedSat = cursor->getItem();     //to 'returnedSat' for later use.

    Satellite nullSat;
    nullSat.setNoradNum(1010101010);

    if (cursor == NULL){
        cout<< "Satellite not found. Please try a different search term." << endl;
        return nullSat; //Satellite not found by string, dummy Satellite returned.

    }else if (cursor->left == NULL && cursor->right == NULL){
        //Case 1 - Satellite for removal is a leaf.
        //precursor is checked to find whether cursor is a left or right child, then precursor's reference to cursor
        //is removed. Then memory for cursor is freed to remove the item fully.
        if (cursor != root){
            if (precursor->right == cursor){
                precursor->right = NULL;
            }else
                precursor->left = NULL;
        }else
            root = NULL;

        free(cursor);


    }else if (cursor->left != NULL && cursor->right != NULL){
        //Case 2 - Satellite for removal has both children.
        //The lowest value is found under cursor, and its value is saved to rpSat. The Deorbit() function is then
        //called recursively to shift the tree to accomodate rpSat's new position at cursor's address. Then rpSat
        //is set as the new Satellite object for cursor's location.
        BinNode* replace = findLowest(cursor->right);
        Satellite rpSat = replace->getItem();

        Deorbit(root, replace->getItem().SatName);

        cursor->setItem(rpSat);
        free(cursor);
    }
    else{
        //Case 3 - Satellite for removal has 1 child.
        //Program checks which side has child, then shifts the child up to take cursor's place.
        //cursor memory is then freed.
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

void deleteTree(BinNode *root){\
    //Performs a post-order transversal to free each node as it travels up a branch.
    //Ends by freeing memory of the root node.
    //Used to clear trees before reading from file.
    if (root == NULL){
        return;
    }
    deleteTree(root->left);
    deleteTree(root->right);
    cout<< "deleting node" <<endl;
    free(root);
}

BinNode* readFiles(string filename){
    //Reads an input file line-by-line, then sets those values to a satellite, which is then inserted into a new tree
    //at *root.
    //Filename is passed as an argument to allow its use on both Orbit.txt and Deorbit.txt files.
    Satellite fileRead;
    BinNode * root;
    root = NULL;

    ifstream readFile;
    string SatName, Country, OpName, SatType, Task, ExpLife, LongTask, OrbitType, LnchDate, LnchSite, LnchVehicle;
    string discard;
    float apogee, perigee, period;
    int NORADNum;

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
    //Reads tree through a pre-order traversal, and writes details of each node to file to save information stored.
    //A pre-order traversal is used to write Satellites in an order that, when read by readFiles(), is similar the tree
    //at time of saving.
    ofstream write;
    write.open(filename, ios::out | ios::app); //Appends on end of file to prevent line overwrites.
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
    //Searches tree to find satellite with matching name as string 'search'.
    //If a matching satellite is found, its details are printed and the function returns a true output.
    //If no match is found, the function returns false.
    if (root == NULL){
        return false;
    }
    else if (root->getItem().getSatName() == search) {
        Satellite Sat = root->getItem();
        cout << "**Name: " << Sat.SatName << endl;
        cout << "**NORAD Tracking No.: " << Sat.NORADNum << endl;
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
    bool quitProgram = false; // When set to true by 'Q' input, while loop breaks and program exits gracefully.

    ofstream fileClear;
    BinNode *root;
    BinNode *rootDeorbit;
    Satellite satInput;

    root = NULL;        //At program initialization, root and rootDeorbit trees are initiallized as empty.
    rootDeorbit = NULL;

    string searchTerm, SatName, Country, OpName, SatType;
    string Task, LongTask, OrbitType, LnchDate, LnchSite, LnchVehicle, ExpLife;
    float apogee, perigee, period;
    int NORADNum;

    while (quitProgram == false){
        cout << endl;
        cout << "Please input a command - (L)aunch, (D)eorbit, (F)ind, (A)ll, (R)ead, (S)ave, (Q)uit :";

        char inputCMD;
        cin  >> setw(1) >> inputCMD;
        char input = toupper(inputCMD); //Input character is parsed to be correct case and length for switch statement.

        switch (input) { //takes in character input and does the requested action.
            case 'L': //takes in input of satellite information, then inserts new Satellie to root tree with that info.
                cin.clear();
                while (cin.get()!= '\n'){continue;} //Clears cin to prevent garbage or whitespace input.
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

            case 'D': //User inputs name of satellite for Deorbit.
                      //That satellite is searched for, and deorbited if found.

                cout << "Enter satellite for removal: ";
                cin.clear();
                while (cin.get()!= '\n'){continue;}
                getline(cin, searchTerm);
                satInput = Deorbit(root, searchTerm);
                if (satInput.getNoradNum() == 1010101010){ //Satellite is not found by search, no action taken.
                    cout << "Satellite not found. Aborting..." <<endl;
                    break;
                }else {
                    Insert(rootDeorbit, satInput);  //Satellite placed in Deorbit tree.
                    cout << '\n' << "Satellite deorbited." << endl;
                }

                break;

            case 'F': //User enters name of satellite for search.
                      //That satellite is searched for in both trees, and its info is printed if found.
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

            case 'A': //Prints the name of all Satellites containted in both trees.
                cout << "---------ORBITING---------" << endl;
                printAll(root);
                cout << "------DECOMMSSIONED-------" << endl;
                printAll(rootDeorbit);
                break;

            case 'R': //Frees all nodes from both trees, then reads new trees in from file.
                deleteTree(root);
                deleteTree(rootDeorbit);
                root = readFiles("orbit.txt");
                rootDeorbit = readFiles("deorbit.txt");
                cout << "Files read!" << endl;
                break;

            case 'S': //Saves all nodes in both trees to their respective .txt files.

                //Files are opened, truncated, and closed to remove all information in the files.
                //This is to prevent strange behavior from appending to a file that already contains text.
                fileClear.open("orbit.txt", ios::out| ios::trunc);
                fileClear.close();
                fileClear.open("deorbit.txt", ios::out| ios::trunc);
                fileClear.close();

                saveFiles(root, "orbit.txt");
                saveFiles(rootDeorbit, "deorbit.txt");
                cout << "Saved to file!" << endl;
                break;

            case 'Q': //Sets quitProgram to true, causing the while loop to break on next check and exit program.
                cout << "Quitting Program";
                quitProgram = true;
                break;

            default: //If input could not be parsed, user is prompted again.
                cout << "No program run, please check input.";

        }
    }
    return 0;
}
