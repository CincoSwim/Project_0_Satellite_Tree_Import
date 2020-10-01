//
// Created by Chris on 9/30/2020.
//

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




