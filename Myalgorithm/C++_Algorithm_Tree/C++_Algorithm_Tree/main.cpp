//
//  main.cpp
//  C++_Algorithm_Tree
//
//  Created by sunjian on 2024/11/9.
//

#include <iostream>
#include <memory>
#include <vector>
#include <queue>
#include <stack>
#include <deque>
#include "BinarySearchTree.hpp"
#include "TemplateClass.hpp"
#include "RBTree.hpp"

using namespace std;


class BinaryTreeNode{
public:
    int m_num;
    shared_ptr<BinaryTreeNode> left;
    shared_ptr<BinaryTreeNode> right;
    BinaryTreeNode(int num):m_num(num),left(nullptr),right(nullptr){}
    
    
    friend ostream& operator<<(ostream& os, shared_ptr<BinaryTreeNode> node){
        return os << node->m_num;
    }
    
    //前序
    static void pre(shared_ptr<BinaryTreeNode> head){
        if(head == nullptr) return;
        cout << head->m_num << ' ';
        pre(head->left);
        pre(head->right);
    }
    
    //中序
    static void mid(shared_ptr<BinaryTreeNode> head){
        if(head == nullptr) return;
        mid(head->left);
        cout << head->m_num << ' ';
        mid(head->right);
    }
    
    //后序
    static void lat(shared_ptr<BinaryTreeNode> head){
        if(head == nullptr) return;
        lat(head->left);
        lat(head->right);
        cout << head->m_num << ' ';
    }
    
    //层序
    static void level(shared_ptr<BinaryTreeNode> head){
        if (head == nullptr) {
            return;
        }
        queue<shared_ptr<BinaryTreeNode>> queue;
        queue.push(head);
        while (!queue.empty()) {
            auto node = queue.front();
            if (node->left != nullptr) queue.push(node->left);
            if (node->right != nullptr) queue.push(node->right);
            cout << node->m_num << ' ';
            queue.pop();
        }
    }
    
    static void levels(shared_ptr<BinaryTreeNode> head){
        if (head == nullptr) {
            return;
        }
        queue<shared_ptr<BinaryTreeNode>> queue;
        queue.push(head);
        int curCount = 1;
        int nextCount = 0;//下一层的数量
        while (!queue.empty()) {
            auto node = queue.front();
            cout << node->m_num << ' ';
            if (node->left != nullptr){
                ++nextCount;
                queue.push(node->left);
            }
            if (node->right != nullptr){
                ++nextCount;
                queue.push(node->right);
            }
            queue.pop();
            --curCount;
            if (curCount == 0) {
                cout << endl;
                curCount = nextCount;
                nextCount = 0;
            }
        }
    }
    
    static void zlevel(shared_ptr<BinaryTreeNode> head){
        if (head == nullptr) {
            return;
        }
        queue<shared_ptr<BinaryTreeNode>> queue;
        queue.push(head);
        int curCount = 1;
        int nextCount = 0;
        int reverse = false;
        while (!queue.empty()) {
            auto node = queue.front();
            cout << node->m_num << ' ';
            queue.pop();
            --curCount;
            if (curCount == 0) {
                reverse = true;
                cout << endl;
            }
            if (reverse) {
                if (node->right) {
                    queue.push(node->right);
                    nextCount++;
                }
                if (node->left) {
                    queue.push(node->left);
                    nextCount++;
                }
            }else{
                if (node->left) {
                    queue.push(node->left);
                    nextCount++;
                }
                if (node->right) {
                    queue.push(node->right);
                    nextCount++;
                }
            }
            if (curCount == 0) {
                curCount = nextCount;
                nextCount = 0;
            }
        }
    }
};

struct Display{
    void operator()(shared_ptr<BinaryTreeNode> a){
        cout << a << " ";
    }
};

/*
 重建二叉树：
 输入某个二叉树的前序和中序遍历的结果，请重建二叉树
 1.首先先确定根节点
 2.前序遍历的首个节点就是根节点
 3.中序遍历根节点在中间，
 因此可以分别通过前序和中序对序列分为左右
 */
shared_ptr<BinaryTreeNode> getNodeFromArray(vector<shared_ptr<BinaryTreeNode>> preArray, vector<shared_ptr<BinaryTreeNode>> midArray){
    if(midArray.size() == 1) {
        return midArray[0];
    }
    auto root = preArray[0];
    auto index = 0;
    for (int i = 0 ; i < midArray.size(); i++) {
        if (root->m_num == midArray[i]-> m_num) {
            index = i;
            break;
        }
    }
    int leftLen = index;
    if(index > 0){
        vector<shared_ptr<BinaryTreeNode>> leftPreArray(preArray.begin()+1, preArray.begin()+1+leftLen);
        vector<shared_ptr<BinaryTreeNode>> leftMidArray(midArray.begin(), midArray.begin() + index);
        root->left = getNodeFromArray(leftPreArray, leftMidArray);
    }
    if (index < preArray.size() - 1) {
        vector<shared_ptr<BinaryTreeNode>> rightPreArray(preArray.begin()+leftLen + 1, preArray.end());
        vector<shared_ptr<BinaryTreeNode>> rightMidArray(midArray.begin()+(index+1), midArray.end());
        root->right = getNodeFromArray(rightPreArray, rightMidArray);
    }
    return root;
}

void Tree(){
    int pre[] = {1,2,4,7,3,5,6,8};
    int mid[] = {4,7,2,1,5,3,8,6};
    vector<shared_ptr<BinaryTreeNode>> preArray;
    vector<shared_ptr<BinaryTreeNode>> midArray;
    for(int i = 0; i < 8; i++){
        preArray.push_back(make_shared<BinaryTreeNode>(pre[i]));
    }
    for (int i = 0; i < 8; i++) {
        midArray.push_back(make_shared<BinaryTreeNode>(mid[i]));
    }
    auto root = getNodeFromArray(preArray, midArray);
    BinaryTreeNode::pre(root); cout << endl;
    BinaryTreeNode::mid(root); cout << endl;
    BinaryTreeNode::lat(root); cout << endl;
}

/*
 树的子结构：
 给定两棵二叉树A 和 B，判断 B 是否是 A 的子结构
 解法一：通过获取它们的前序或者中序遍历的结果，判断其中一个是否是另外一的子数组，这样会增加时间复杂度
 解法二；通过前序遍历，判读是否相等
 */
bool dfs(shared_ptr<BinaryTreeNode> tree1, shared_ptr<BinaryTreeNode> tree2){//深度优先
    if (tree2 == nullptr) {
        return true;
    }
    if (tree1 == nullptr || tree1->m_num != tree2->m_num) {
        return false;
    }
    return dfs(tree1->left, tree2->left) || dfs(tree1->right, tree2->right);
}

bool isSubStruction(shared_ptr<BinaryTreeNode> tree1, shared_ptr<BinaryTreeNode> tree2){
    if (tree1 == nullptr || tree2 == nullptr) {
        return false;
    }
    return dfs(tree1, tree2) || isSubStruction(tree1->left, tree2) || isSubStruction(tree1->right, tree2);
}

void Tree2(){
    auto node1 = make_shared<BinaryTreeNode>(8);
    auto node2 = make_shared<BinaryTreeNode>(8);
    auto node3 = make_shared<BinaryTreeNode>(7);
    node1->left = node2;
    node1->right = node3;
    
    auto node4 = make_shared<BinaryTreeNode>(9);
    auto node5 = make_shared<BinaryTreeNode>(2);
    node2->left = node4;
    node2->right = node5;
    
    auto node6 = make_shared<BinaryTreeNode>(4);
    auto node7 = make_shared<BinaryTreeNode>(7);
    node5->left = node6;
    node5->right = node7;
    
    BinaryTreeNode::mid(node1);
    cout << endl;
    
    
    auto node8 = make_shared<BinaryTreeNode>(8);
    auto node9 = make_shared<BinaryTreeNode>(9);
    auto node10 = make_shared<BinaryTreeNode>(2);
    node8->left = node9;
    node8->right = node10;
    
    BinaryTreeNode::mid(node8);
    cout << endl;
    
    cout << isSubStruction(node1, node8) << endl;
}


/*
 二叉树的镜像
 解法一：就是交换左右节点就行
 */
void MirrorTree(shared_ptr<BinaryTreeNode> head){
    if (head == nullptr || head->left == nullptr || head->right == nullptr) {
        return;
    }
    MirrorTree(head->left);
    MirrorTree(head->right);
    auto temp = head->left;
    head->left = head->right;
    head->right = temp;
}
void Tree3(){
    auto node1 = make_shared<BinaryTreeNode>(8);
    auto node2 = make_shared<BinaryTreeNode>(6);
    auto node3 = make_shared<BinaryTreeNode>(10);
    node1->left = node2;
    node1->right = node3;
    
    auto node4 = make_shared<BinaryTreeNode>(5);
    auto node5 = make_shared<BinaryTreeNode>(7);
    node2->left = node4;
    node2->right = node5;
    
    auto node6 = make_shared<BinaryTreeNode>(9);
    auto node7 = make_shared<BinaryTreeNode>(11);
    node3->left = node6;
    node3->right = node7;
    
    BinaryTreeNode::level(node1);
    cout << endl;
    
    MirrorTree(node1);
    
    BinaryTreeNode::level(node1);
    cout << endl;
}

/*
 对称二叉树
 思路：这道题还是比较简单的，找到一种算法，能够先 根、右、左 就 ok 了
 */
shared_ptr<BinaryTreeNode> makeTree1(){
    auto node1 = make_shared<BinaryTreeNode>(8);
    auto node2 = make_shared<BinaryTreeNode>(6);
    auto node3 = make_shared<BinaryTreeNode>(9);
    
    node1->left = node2;
    node1->right = node3;
    
    auto node4 = make_shared<BinaryTreeNode>(5);
    auto node5 = make_shared<BinaryTreeNode>(7);
    node2->left = node4;
    node2->right = node5;

    auto node6 = make_shared<BinaryTreeNode>(7);
    auto node7 = make_shared<BinaryTreeNode>(5);
    node3->left = node6;
    node3->right = node7;
    
    return node1;
}

shared_ptr<BinaryTreeNode> makeTree2(int count){
    auto root = make_shared<BinaryTreeNode>(1);
    int index = 1;
    queue<shared_ptr<BinaryTreeNode>> queue;
    queue.push(root);
    while (index < count) {
        auto node = queue.front();
        queue.pop();
        node->left = make_shared<BinaryTreeNode>(++index);
        queue.push(node->left);
        node->right = make_shared<BinaryTreeNode>(++index);
        queue.push(node->right);
    }
    return root;
}

bool dfs1(shared_ptr<BinaryTreeNode> left, shared_ptr<BinaryTreeNode> right){
    if (left == nullptr && right == nullptr) {
        return true;
    }
    if (left == nullptr || right == nullptr) {
        return false;
    }
    if (left->m_num != right->m_num) {
        return false;
    }
    return dfs1(left->left, right->right) && dfs1(left->right, right->left);
}

bool isSymmetric(shared_ptr<BinaryTreeNode> head){
    if(head == nullptr) return false;
    return dfs1(head->left, head->right);
}

void tree4(){
    auto tree = makeTree1();
    BinaryTreeNode::level(tree); cout << endl;
    cout << isSymmetric(tree) << endl;
}


/*
 1.不分从上到下打印
 2.分行从上到下打印
 */
void tree5(){
    auto tree = makeTree1();
    BinaryTreeNode::level(tree);
    cout << endl;
    auto tree2 = makeTree2(15);
    BinaryTreeNode::levels(tree2);
    cout << endl;
    BinaryTreeNode::zlevel(tree2);
    cout << endl;
}

/*
 二叉树中和为某一值的路径
 解法一：还是递归，找到从头开始找，不相等时，返回上一层继续找
 */
void dfs2(vector<shared_ptr<BinaryTreeNode>> array, shared_ptr<BinaryTreeNode> node, int value, int sum){//深度优先算法
    if(node == nullptr) return;
    sum += node->m_num;
    array.push_back(node);
    if (node->left == nullptr && node->right == nullptr && sum == value) {
        for_each(array.begin(), array.end(), Display());
        return;
    }
    dfs2(array, node->left, value, sum);
    dfs2(array, node->right, value, sum);
    array.pop_back();
}
void tree6(){
    auto tree2 = makeTree2(8);
    BinaryTreeNode::levels(tree2);
    
    vector<shared_ptr<BinaryTreeNode>> vector;
    dfs2(vector, tree2, 15, 0);
    for_each(vector.begin(), vector.end(), Display());
    cout << endl;
}

/*
 序列化二叉树
 序列化：就是就是将二叉树转换成字符串或数组，用来保存或传输
 反序列化：就是将字符串或数组重新还原成二叉树的过程
 */

void Serialize(shared_ptr<BinaryTreeNode> head, ostream& stream){
    if (head == nullptr) {
        stream << "$,";
        return;
    }
    stream << head->m_num << ',';
    Serialize(head->left, stream);
    Serialize(head->right, stream);
}

bool ReadStream(istream& stream, int* number)
{
    if(stream.eof())
        return false;

    char buffer[32];
    buffer[0] = '\0';

    char ch;
    stream >> ch;
    int i = 0;
    while(!stream.eof() && ch != ',')
    {
        buffer[i++] = ch;
        stream >> ch;
    }

    bool isNumeric = false;
    if(i > 0 && buffer[0] != '$')
    {
        *number = atoi(buffer);
        isNumeric = true;
    }

    return isNumeric;
}

void Deserialize(shared_ptr<BinaryTreeNode>& node, istream& stream){
    int number;
    if (ReadStream(stream, &number)) {
        node = make_shared<BinaryTreeNode>(number);
        Deserialize(node->left, stream);
        Deserialize(node->right, stream);
    }
}

void tree7(){
    auto node1 = make_shared<BinaryTreeNode>(1);
    auto node2 = make_shared<BinaryTreeNode>(2);
    auto node3 = make_shared<BinaryTreeNode>(3);
    
    node1->left = node2;
    node1->right = node3;
    
    auto node4 = make_shared<BinaryTreeNode>(4);
    node2->left = node4;

    auto node6 = make_shared<BinaryTreeNode>(5);
    auto node7 = make_shared<BinaryTreeNode>(6);
    node3->left = node6;
    node3->right = node7;
    
//    BinaryTreeNode::levels(node1);
    
    Serialize(node1, cout);
    cout << endl;
    
//    shared_ptr<BinaryTreeNode> head;
//    Deserialize(head, cin);
//    BinaryTreeNode::levels(head);
}

/*
 二叉树的深度
 解法一：递归遍历每一个节点，到达叶子节点时，等到 max
 */
void depthOfTree(shared_ptr<BinaryTreeNode> node, int& depth, int& maxDepth){
    if (node == nullptr) return;
    depth++;
    if (node->left == nullptr && node->right == nullptr) {
        maxDepth = max(depth, maxDepth);
    }
    depthOfTree(node->left, depth, maxDepth);
    depthOfTree(node->right, depth, maxDepth);
    depth--;
}
void tree8(){
    auto node1 = make_shared<BinaryTreeNode>(1);
    auto node2 = make_shared<BinaryTreeNode>(2);
    auto node3 = make_shared<BinaryTreeNode>(3);
    
    node1->left = node2;
    node1->right = node3;
    
    auto node4 = make_shared<BinaryTreeNode>(4);
    node2->left = node4;

    auto node6 = make_shared<BinaryTreeNode>(5);
    auto node7 = make_shared<BinaryTreeNode>(6);
    node3->left = node6;
    node3->right = node7;
    
    auto node8 = make_shared<BinaryTreeNode>(7);
    node7->left = node8;
    
    BinaryTreeNode::levels(node1);
    
    int depth = 0;
    int maxDepth = 0;
    depthOfTree(node1, depth, maxDepth);
    cout << "树的深度是 " << maxDepth << endl;
}

/*
 平衡二叉树
 */
int treeDepth(shared_ptr<BinaryTreeNode> node){
    if (node == nullptr) return 0;
    int depth = 1;
    return depth += max(treeDepth(node->left), treeDepth(node->right));
}
bool balanceTree(shared_ptr<BinaryTreeNode> node){
    if(node == nullptr) return true;
    int leftDepth = treeDepth(node->left);
    int rightDepth = treeDepth(node->right);
    if (abs(leftDepth - rightDepth) > 1) {
        return false;
    }
    return balanceTree(node->left) && balanceTree(node->right);
}
void tree9(){
    auto node1 = make_shared<BinaryTreeNode>(1);
    auto node2 = make_shared<BinaryTreeNode>(2);
    auto node3 = make_shared<BinaryTreeNode>(3);
    
    node1->left = node2;
    node1->right = node3;
    
    auto node4 = make_shared<BinaryTreeNode>(4);
    node2->left = node4;

    auto node6 = make_shared<BinaryTreeNode>(5);
    auto node7 = make_shared<BinaryTreeNode>(6);
    node3->left = node6;
    node3->right = node7;
    
    auto node8 = make_shared<BinaryTreeNode>(7);
    node4->left = node8;
    
    BinaryTreeNode::levels(node1);
    
    cout << "node1 is " << balanceTree(node1)  << " balance tree" << endl;
}


/*
 二叉搜索树
 */
void tree10(){
    BinarySearchTree<int> bst;
    for(int  i = 1; i < 10; i++){
        bst.add(i);
    }
    bst.levelsDisplay();
    bst.remove(2);
    bst.levelsDisplay();
    bst.remove(3);
    bst.levelsDisplay();
    bst.remove(4);
    bst.levelsDisplay();
    bst.clear();
    
    
    RBTree<int> rbt;
    for(int  i = 1; i < 10; i++){
        rbt.add(i);
    }
    rbt.levelsDisplay();
    rbt.remove(2);
    rbt.levelsDisplay();
    rbt.remove(3);
    rbt.levelsDisplay();
    rbt.remove(4);
    rbt.levelsDisplay();
    rbt.clear();
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    Tree();
    
    Tree2();
    
    Tree3();
    
    tree4();
    
    tree5();
    
    tree6();
    
    tree7();
    
    tree8();
    
    tree9();
    
    tree10();
    
    return 0;
}
