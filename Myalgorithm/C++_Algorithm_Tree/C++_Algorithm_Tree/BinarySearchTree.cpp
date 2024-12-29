//
//  BinarySearchTree.cpp
//  C++_Algorithm_Tree
//
//  Created by sunjian on 2024/11/12.
//

#include "BinarySearchTree.hpp"
#include <queue>

template <typename T>
BinarySearchTree<T>::BinarySearchTree():BBST<T>(){}

template <typename T>
BinarySearchTree<T>::~BinarySearchTree(){}

template <typename T>
void BinarySearchTree<T>::afterAdd(shared_ptr<TreeNode<T>> node){
    //找到最近失衡祖父节点
    while ((node = node->parent) != nullptr) {
        if (isBalance(node)) {//左右子节点的高度差<=1
            updateHeight(node);
        }else{
            reBalance(node);
            break;
        }
    }
}

template <typename T>
void BinarySearchTree<T>::reBalance(shared_ptr<TreeNode<T>> grand){
    auto parent = dynamic_pointer_cast<AVLNode>(grand)->tallerChild();
    auto node = parent->tallerChild();
    if (parent->isLeftChild()) {
        if (node->isLeftChild()) {//LL
            BBST<T>::rotateRight(grand);
        }else{//LR
            BBST<T>::rotateLeft(parent);
            BBST<T>::rotateRight(grand);
        }
    }else{
        if (node->isLeftChild()) {//RL
            BBST<T>::rotateRight(parent);
            BBST<T>::rotateLeft(grand);
        }else{//RR
            this->rotateLeft(grand);
        }
    }
}

template <typename T>
void BinarySearchTree<T>::afterRotate(shared_ptr<TreeNode<T>> grand, shared_ptr<TreeNode<T>> parent, shared_ptr<TreeNode<T>> child){
    BBST<T>::afterRotate(grand, parent, child);
    updateHeight(grand);
    updateHeight(parent);
}

template <typename T>
bool BinarySearchTree<T>::isBalance(shared_ptr<TreeNode<T>> node){
    shared_ptr<AVLNode> avlNode = dynamic_pointer_cast<AVLNode>(node);
    return abs(avlNode->balanceFactor()) <= 1;
}

template <typename T>
void BinarySearchTree<T>::updateHeight(shared_ptr<TreeNode<T>> node){
    shared_ptr<AVLNode> avlNode = dynamic_pointer_cast<AVLNode>(node);
    return avlNode->updateHeight();
}

template <typename T>
void BinarySearchTree<T>::afterRemove(shared_ptr<TreeNode<T>> node){
    //找到最近失衡祖父节点
    while ((node = node->parent) != nullptr) {
        if (isBalance(node)) {
            updateHeight(node);
        }else{
            reBalance(node);
            break;
        }
    }
}


template class
BinarySearchTree<int>;
