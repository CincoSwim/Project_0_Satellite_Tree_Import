/*
 * EECS 2150 Project 0 - Binary Search Tree of Satellites
 * Author: Christopher Pucko
 *
 * Class file for BinNode Object class. Defines actions of the getters/setters declared in the header file.
 */

#include "BinNode.h";



Satellite BinNode::getItem(){
    return item;
}

void BinNode::setItem(Satellite item) {
    BinNode::item = item;
}

BinNode *BinNode::getLeft(){
    return left;
}

void BinNode::setLeft(BinNode *left) {
    BinNode::left = left;
}

BinNode *BinNode::getRight(){
    return right;
}

void BinNode::setRight(BinNode *right) {
    BinNode::right = right;
}




