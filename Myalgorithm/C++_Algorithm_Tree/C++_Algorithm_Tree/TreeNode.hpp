//
//  TreeNode.hpp
//  C++_Algorithm_Tree
//
//  Created by sunjian on 2024/11/13.
//

#ifndef TreeNode_hpp
#define TreeNode_hpp

#include <stdio.h>
#include <memory>
#include <iostream>

using namespace std;

template <typename T>
class TreeNode{
public:
    T element;
    shared_ptr<TreeNode> left;
    shared_ptr<TreeNode> right;
    shared_ptr<TreeNode> parent;
    
    TreeNode(const T& value, shared_ptr<TreeNode> parent):element(value),left(nullptr),right(nullptr),parent(parent){}
    
    virtual ~TreeNode(){}
    
    bool hasTwoChild(){
        return this->left != nullptr && this->right != nullptr;
    }
    
    bool isLeftChild(){
        if (this->parent && this->parent->left) {
            return this->parent != nullptr && this == this->parent->left.get();
        }else{
            return false;
        }
    }
    bool isRightChild(){
        if (this->parent && this->parent->right) {
            return this->parent != nullptr && this == this->parent->right.get();
        }else{
            return false;
        }
    }
    
    friend ostream& operator<<(ostream& os, shared_ptr<TreeNode>& node){
        if(node == nullptr) return os;
        os << node->element;
        if(node->parent != nullptr){
            os << '(' << node->parent->element << ')';
        }else{
            os<< "()";
        }
        return os;
    }
};

#endif /* TreeNode_hpp */
