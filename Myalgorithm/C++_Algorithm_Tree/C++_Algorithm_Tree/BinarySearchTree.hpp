//
//  BinarySearchTree.hpp
//  C++_Algorithm_Tree
//
//  Created by sunjian on 2024/11/12.
//

#ifndef BinarySearchTree_hpp
#define BinarySearchTree_hpp

#include <stdio.h>
#include <iostream>
#include <memory>
#include "TreeNode.hpp"
#include "BBST.hpp"

using namespace std;

template <typename T>
class BinarySearchTree : public BBST<T>{
private:
    class AVLNode : public TreeNode<T> {
    public:
        int height;
        AVLNode(const T& value, shared_ptr<TreeNode<T>> parent):TreeNode<T>(value, parent), height(1){}
        int balanceFactor(){
            shared_ptr<AVLNode> leftAVLNode = this->left == nullptr ? nullptr : dynamic_pointer_cast<AVLNode>(this->left);
            shared_ptr<AVLNode> rightAVLNode = this->right == nullptr ? nullptr : dynamic_pointer_cast<AVLNode>(this->right);
            if (leftAVLNode && rightAVLNode) {
                return leftAVLNode->height - rightAVLNode->height;
            }else if(leftAVLNode){
                return leftAVLNode->height;
            }else if(rightAVLNode){
                return rightAVLNode->height;
            }else{
                return 1;
            }
        }
        void updateHeight(){
            shared_ptr<AVLNode> leftAVLNode = this->left == nullptr ? nullptr : dynamic_pointer_cast<AVLNode>(this->left);
            shared_ptr<AVLNode> rightAVLNode = this->right == nullptr ? nullptr : dynamic_pointer_cast<AVLNode>(this->right);
            if (leftAVLNode && rightAVLNode) {
                this->height = 1 + max(leftAVLNode->height, rightAVLNode->height);
            }else if(leftAVLNode){
                this->height = 1 + leftAVLNode->height;
            }else if(rightAVLNode){
                this->height = 1 + rightAVLNode->height;
            }else{
                this->height = 1;
            }
        }
        shared_ptr<AVLNode> tallerChild(){
            shared_ptr<AVLNode> leftAVLNode = this->left == nullptr ? nullptr : dynamic_pointer_cast<AVLNode>(this->left);
            shared_ptr<AVLNode> rightAVLNode = this->right == nullptr ? nullptr : dynamic_pointer_cast<AVLNode>(this->right);
            int leftHeight = this->left == nullptr ? 0 : leftAVLNode->height;
            int rightHeight = this->right == nullptr ? 0 : rightAVLNode->height;
            if(leftHeight < rightHeight) return rightAVLNode;
            if(leftHeight > rightHeight) return leftAVLNode;
            return TreeNode<T>::isLeftChild() ? leftAVLNode : rightAVLNode;
        }
    };
    void afterAdd(shared_ptr<TreeNode<T>> node);
    void afterRemove(shared_ptr<TreeNode<T>> node);
    bool isBalance(shared_ptr<TreeNode<T>> node);
    void reBalance(shared_ptr<TreeNode<T>> node);
    void updateHeight(shared_ptr<TreeNode<T>> node);
    void afterRotate(shared_ptr<TreeNode<T>> grand, shared_ptr<TreeNode<T>> parent, shared_ptr<TreeNode<T>> child);
    shared_ptr<TreeNode<T>> createNode(const T& element, shared_ptr<TreeNode<T>> parent){
        return make_shared<AVLNode>(element, parent);
    }
public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
};

#endif /* BinarySearchTree_hpp */
