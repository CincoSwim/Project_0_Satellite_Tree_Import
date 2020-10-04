/*
 * EECS 2150 Project 0 - Binary Search Tree of Satellites
 * Author: Christopher Pucko
 *
 * Header for "BinNode" or Binary Node Object class. Declares a BinNode as containing a Satellite object, and two p
 * pointers to other BinNodes. Also declares a constructor that sets left and right pointers equal to NULL, and
 * getters/setters for BinNode variables.
 */
#include "Satellite.h"
#ifndef PROJECT_0_SATELLITE_TREE_IMPORT_BINNODE_H
#define PROJECT_0_SATELLITE_TREE_IMPORT_BINNODE_H


class BinNode {
public:
        Satellite item;
        BinNode *left;
        BinNode *right;

    BinNode(Satellite str){
        item = str;
        left = NULL;
        right = NULL;
    }

    Satellite getItem();
    void setItem(Satellite item);
    BinNode * getLeft();
    BinNode * getRight();
    void setLeft(BinNode * Left);
    void setRight(BinNode * Right);

};




#endif //PROJECT_0_SATELLITE_TREE_IMPORT_BINNODE_H
