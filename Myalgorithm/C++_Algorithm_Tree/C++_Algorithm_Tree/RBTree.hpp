//
//  RBTree.hpp
//  C++_Algorithm_Tree
//
//  Created by sunjian on 2024/11/13.
//

#ifndef RBTree_hpp
#define RBTree_hpp

#include <stdio.h>
#include <memory>
#include <iostream>
#include "BinarySearchTree.hpp"
#include "TreeNode.hpp"

/*
 红黑树的特性：
 1.节点 RED/BLACK
 2.根节点是 BLACK
 3.叶子节点都是 BLACK
 4.RED节点的子节点是 BLACK
    RED节点的parent是 BLACK
    从根节点到叶子节点不能有两个连续的 RED 节点
 5.从任意节点到叶子节点的所有路径都包含相同数量的 BLACK 节点
 6.在添加和删除节点之后，仍让树具有以上性质就一定能保持树的稳定
 
 RBTree有很多性质是与 四阶B树相似
 四阶B树，所有节点的数量 1 <= x <= 3
 
 RBTree添加新节点一共有12种情况：
 1.其中有4种情况parent是黑色，不用作处理
 2.有四种情况需要修复性质4
    LL/RR， parent 染成黑色，grand 染成红色，grand右旋/左旋
    LR  自己染成黑色，grand 染成 红色，parent 左旋，grand 右旋
    RL  自己染成黑色，grand 染成 红色，parent 右旋，grand 左旋
 3.解决性质4、上溢问题
    父亲、uncle染成Black
    grand 染成红色，并上溢
    
 4.修复总结：
     uncle不是RED：
        LL\RR，让祖父节点进行单旋转，染成红色，让父节点成为中心，并染成黑色。
        LR\RL，让祖父节点和父节点进行旋转，让新添加成员成为中心节点，染成黑色，祖父节点染成红色。

     uncle是RED：
        父节点，叔父节点染成黑色。
        祖父节点染成红色，并上溢。
 */

const bool RED = true;
const bool BLACK = false;

template <typename T>
class RBTree : public BBST<T>{
private:
    class RBNode : public TreeNode<T>{
    public:
        bool color = RED;
        RBNode(const T& value, shared_ptr<TreeNode<T>> parent):TreeNode<T>(value, parent){}
        shared_ptr<TreeNode<T>> subling(){
            //这里直接调用父类方法
            if (TreeNode<T>::isLeftChild()) {
                return this->parent->right;
            }
            if (TreeNode<T>::isRightChild()) {
                return this->parent->left;
            }
            return nullptr;
        }
    };
    shared_ptr<RBNode> creatNode(const T& element, shared_ptr<TreeNode<T>> parent){
        return RBNode(element, parent);
    }
    shared_ptr<TreeNode<T>> color(shared_ptr<TreeNode<T>> node, bool color){
        if(node == nullptr) return nullptr;
        auto rbNode = dynamic_pointer_cast<RBNode>(node);
        rbNode->color = color;
        return dynamic_pointer_cast<TreeNode<T>>(rbNode);
    }
    shared_ptr<TreeNode<T>> red(shared_ptr<TreeNode<T>> node){
        return color(node, RED);
    }
    shared_ptr<TreeNode<T>> black(shared_ptr<TreeNode<T>> node){
        return color(node, BLACK);
    }
    bool colorOf(shared_ptr<TreeNode<T>> node){
        if(node == nullptr) return BLACK;
        auto rbNode = dynamic_pointer_cast<RBNode>(node);
        return rbNode == nullptr ? BLACK : rbNode->color;
    }
    bool isRed(shared_ptr<TreeNode<T>> node){
        return colorOf(node) == RED;
    }
    bool isBlack(shared_ptr<TreeNode<T>> node){
        return colorOf(node) == BLACK;
    }
    
    void afterAdd(shared_ptr<TreeNode<T>> node){
        auto parent = dynamic_pointer_cast<RBNode>(node->parent);
        //添加的是根节点 或者 上溢到达了根节点
        if (parent == nullptr) {
            black(node);
            return;
        }
        //如果父节点是黑色，直接返回
        if (isBlack(parent)) return;
        
        //获取uncle 节点
        auto uncle = parent->subling();
        auto grand = red(parent->parent);
        
        if (isRed(uncle)) {
            black(parent);
            black(uncle);
            afterAdd(grand);
            return;
        }
        
        if (parent->isLeftChild()) {
            if(node->isLeftChild()){//LL
                black(parent);
            }else{
                black(node);
                BBST<T>::rotateLeft(parent);
            }
            BBST<T>::rotateRight(grand);
        }else{//R
            if(node->isLeftChild()){//RL
                black(node);
                BBST<T>::rotateRight(parent);
            }else{//RR
                black(parent);
            }
            BBST<T>::rotateLeft(grand);
        }
    }
    
    void afterRemove(shared_ptr<TreeNode<T>> node){
        if (isRed(node)) {
            black(node);
            return;
        }
        auto parent = node->parent;
        if(parent == nullptr) return;
        
        //删除的是 black 节点
        bool left = parent->left == nullptr || node->isLeftChild();
        auto subling = left ? parent->right : parent->left;
        if(left){
            if(isRed(subling)){
                black(subling);
                red(parent);
                BBST<T>::rotateLeft(parent);
                subling = parent->right;
            }
            if (isBlack(subling->left) && isBlack(subling->right)) {
                bool parentBlack = isBlack(parent);
                black(parent);
                red(subling);
                if(parentBlack){
                    afterRemove(parent);
                }
            }else{
                if(isBlack(subling->left)){
                    BBST<T>::rotateRight(subling);
                    subling = parent->right;
                }
                color(subling, colorOf(parent));
                black(subling->right);
                black(parent);
                BBST<T>::rotateLeft(parent);
            }
        }else{
            if(isRed(subling)){
                black(subling);
                red(parent);
                BBST<T>::rotateRight(parent);
                subling = parent->left;
            }
            if (isBlack(subling->left) && isBlack(subling->right)) {
                bool parentBlack = isBlack(parent);
                black(parent);
                red(subling);
                if(parentBlack){
                    afterRemove(parent);
                }
            }else{
                if(isBlack(subling->left)){
                    BBST<T>::rotateLeft(subling);
                    subling = parent->left;
                }
                color(subling, colorOf(parent));
                black(subling->left);
                black(parent);
                BBST<T>::rotateRight(parent);
            }
        }
    }
    
    shared_ptr<TreeNode<T>> createNode(const T& element, shared_ptr<TreeNode<T>> parent){
        return make_shared<RBNode>(element, parent);
    }
public:
    RBTree(){}
    virtual ~RBTree(){}
};

#endif /* RBTree_hpp */
