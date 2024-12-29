//
//  BBST.hpp
//  C++_Algorithm_Tree
//
//  Created by sunjian on 2024/11/13.
//

#ifndef BBST_hpp
#define BBST_hpp

#include <stdio.h>
#include "TreeNode.hpp"
#include <memory>
#include "BST.hpp"

template <typename T>
class BBST : public BST<T>{
public:
    BBST():BST<T>(){}
    virtual ~BBST(){}
protected:
    
    void rotateLeft(shared_ptr<TreeNode<T>> grand){
        auto parent = grand->right;
        auto child = parent->left;
        grand->right = child;
        parent->left = grand;
        afterRotate(grand, parent, child);
    }
    
    void rotateRight(shared_ptr<TreeNode<T>> grand){
        auto parent = grand->left;
        auto child = parent->right;
        grand->left = child;
        parent->right = grand;
        afterRotate(grand, parent, child);
    }
    
    virtual void afterRotate(shared_ptr<TreeNode<T>> grand, shared_ptr<TreeNode<T>> parent, shared_ptr<TreeNode<T>> child){
        parent->parent = grand->parent;
        
        if (grand->isRightChild()) {
            grand->parent->right = parent;
        }else if(grand->isLeftChild()){
            grand->parent->left = parent;
        }else{
            this->root = parent;
        }
        
        if (child != nullptr) {
            child->parent = grand;
        }
        
        grand->parent = parent;
    }
};

#endif /* BBST_hpp */
