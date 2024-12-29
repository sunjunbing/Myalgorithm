//
//  BST.hpp
//  C++_Algorithm_Tree
//
//  Created by sunjian on 2024/11/13.
//

#ifndef BST_hpp
#define BST_hpp

#include <stdio.h>
#include "TreeNode.hpp"
#include <queue>
#include <memory>

template <typename T>
class BST {
protected:
    shared_ptr<TreeNode<T>> root;
    int m_size;
    function<int(const T& t1, const T& t2)> cmp;
    
    shared_ptr<TreeNode<T>> containNode(const T &element){
        if(this->root == nullptr) return nullptr;
        if(this->root->element == element) return this->root;
        auto node = this->root;
        auto cmp = 0;
        while (node != nullptr) {
            cmp = compare(element, node->element);
            if (cmp > 0) {
                node = node->right;
            }else if(cmp < 0){
                node = node->left;
            }else{
                return node;
            }
        }
        return nullptr;
    }

    void removeNode(shared_ptr<TreeNode<T>> node){
        if(node == nullptr) return;
        m_size--;
        if (node->hasTwoChild()) {//度为2的节点
            //找到前继或后即节点
            auto suc = successor(node);
            node->element = suc->element;
            node = suc;
        }
        auto replacement = node->left != nullptr ? node->left : node->right;
        if (replacement != nullptr) {
            replacement->parent = node->parent;
            if (node->parent == nullptr) {
                this->root = replacement;
            }else if(node == node->parent->left){
                node->parent->left = replacement;
            }else {
                node->parent->right = replacement;
            }
            afterRemove(replacement);
        }else if(node->parent == nullptr){
            this->root = nullptr;
            afterRemove(node);
        }else{
            if (node == node->parent->left) {
                node->parent->left = nullptr;
            }else{
                node->parent->right = nullptr;
            }
            afterRemove(node);
        }
    }

    shared_ptr<TreeNode<T>> precessor(shared_ptr<TreeNode<T>> node){
        if (node == nullptr) return nullptr;
        auto suc = node->left;
        while (suc != nullptr) {
            while (suc->right != nullptr) {
                suc = suc->right;
            }
            return suc;
        }
        while (node->parent != nullptr && node == node->parent->right) {
            node = node->parent;
        }
        return node->parent;
    }

    shared_ptr<TreeNode<T>> successor(shared_ptr<TreeNode<T>> node){
        if (node == nullptr) return nullptr;
        auto suc = node->right;
        while (suc != nullptr) {
            while (suc->left != nullptr) {
                suc = suc->left;
            }
            return suc;
        }
        while (node->parent != nullptr && node == node->parent->left) {
            node = node->parent;
        }
        return node->parent;
    }

    
    int compare(const T& t1, const T& t2){
        if (cmp) {
            return cmp(t1, t2);
        }else{
            return t1 > t2 ? 1 : (t1 < t2 ? -1 : 0);
        }
    }
    
    virtual void afterAdd(shared_ptr<TreeNode<T>> node){}
    virtual void afterRemove(shared_ptr<TreeNode<T>> node){}
    virtual shared_ptr<TreeNode<T>> createNode(const T& element, shared_ptr<TreeNode<T>> parent){
        return nullptr;
    }
public:
    BST():root(nullptr),m_size(0),cmp(nullptr){}
    ~BST(){}
    int size(){return m_size;}
    bool isEmpty(){return m_size == 0;}
    void clear(){
        while (this->root != nullptr) {
            removeNode(this->root);
        }
    }
    void add(const T& element){
        if (this->root == nullptr) {
            this->root = createNode(element, nullptr);
            m_size++;
            afterAdd(this->root);
            return;
        }
        auto parent = this->root;
        auto node = this->root;
        auto cmp = 0;
        while (node != nullptr) {
            parent = node;
            cmp = compare(element, node->element);
            if (cmp > 0) {
                node = node->right;
            }else if(cmp < 0){
                node = node->left;
            }else{
                node->element = element;
                return;
            }
        }
        auto newNode = createNode(element, parent);
        if (cmp > 0) {
            parent->right = newNode;
        }else{
            parent->left = newNode;
        }
        m_size++;
        afterAdd(newNode);
    }
    void remove(const T& element){
        auto node = containNode(element);
        if(node == nullptr) return;
        removeNode(node);
    }
    bool contain(const T& element){
        if(this->root == nullptr) return false;
        if (containNode(element) != nullptr) {
            return true;
        }
        return false;
    }
    void levelsDisplay(){
        queue<shared_ptr<TreeNode<T>>> queue;
        queue.push(this->root);
        int curCount = 1;
        int nextCount = 0;
        while (!queue.empty()) {
            auto node = queue.front();
            queue.pop();
            cout << node;
            --curCount;
            if (node->left != nullptr) {
                queue.push(node->left);
                nextCount++;
            }
            if (node->right != nullptr) {
                queue.push(node->right);
                nextCount++;
            }
            if (curCount == 0) {
                curCount = nextCount;
                nextCount = 0;
                cout << endl;
            }
        }
    }
};

#endif /* BST_hpp */
