//
// Created by Chris on 9/30/2020.
//
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
