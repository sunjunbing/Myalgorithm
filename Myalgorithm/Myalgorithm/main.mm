//
//  main.m
//  Myalgorithm
//
//  Created by sunjian on 2020/8/21.
//  Copyright © 2020 sjuinan. All rights reserved.
//

#pragma mark - 题目列表
/*
 把这66道题，了如指掌
 01.数组中重复的数字(在正整数数组中，查找唯一一个重复的元素，至少用3种解法)
 02.二维数组中查找(1.首先二维数组是有序的 2.从右上角开始比较)
 03.字符串空格替换(1.先计算出所有的空格 2.初始化一个对应长度的字符串 3.从后向前替换)
 04.从尾到头打印链表(1.先反转列表 2.在打印链表)
 05.重建二叉树(根据前序和中序序列来重建二叉树)
 06.二叉树的下一个节点(输出中序遍历的下一个节点)
 07.用两个栈实现队列
 08.斐波那契数列(从0、1开始)
 09.旋转数组最小的数字(双指针法)
 10.矩阵中的路径(回溯)
 11.机器人的运动范围(回溯)
 12.剪绳子(贪心算法，尽量的剪长度为3)
 13.二进制中1的个数(减-处理)
 14.数值的整数次方
 15.打印从1到最大的n位数(大数问题，字符串处理)
 16.删除列表的节点(O(1)时间复杂度，复制、删除)
 17.正则表达式匹配(遍历、分情况讨论)
 18.表示数值的字符串(遍历、分情况讨论)
 19.调整数组顺序使得奇数位于偶数前面(双指针)
 20.列表中倒数第k个节点(倒数第k个节点==正数第k+1个节点)
 21.链表中环的入口节点(快慢指针 x+y = x+y+z+y => x=z)
 22.反转列表
 23.合并两个有序列表
 24.树的子结构(遍历)
 25.二叉树的镜像(判断子节点是否正好相反)
 26.对称二叉树
 27.顺时针打印矩阵
 28.包含min函数的栈(模版类)
 29.栈的压入、弹出序列(根据弹出序列与栈顶元素比较，相等弹出，不等压栈)
 30.从上到下打印二叉树(双端队列)
 31.二叉搜索树的后序遍历序列
 32.二叉搜索树和为某一值的路径
 33.复杂列表的复制
 34.二叉搜索树和双向列表
 35.序列化二叉树
 36.字符串排列(全排列)
 37.数组中出现次数超过一半的数字
 38.最小的k个数
 39.数据流中的中位数
 40.连续子数组的最大和
 41.数据流中的中位数
 42.连续子数组的最大和
 43.1～n整数中1出现的次数
 44.数字序列中某一位的数字
 45.把数组排成最小的数
 46.把数字翻译成字符串
 47.礼物的最大值
 48.最长不含重复字符的子字符串
 49.丑叔
 50.第一个只出现一次的字符
 51.数组中的逆序对
 52.连个链表的第一个公共节点
 53.在排序数组中查找数字
 54.二叉搜索树的第K大节点
 55.二叉树的深度
 56.数组中数字出现的次数
 57.和为s的数字
 58.反转字符串
 59.队列的最大值
 60.n个骰子的点数
 61.扑克牌中的顺子
 62.圆圈中最后剩下的数字
 63.股票的最大利润
 64.求1+2+3+...+n
 65.不用加减乘除做加法
 66.构建乘积数组
 67.把字符串转换为数字
 68.树中两个节点的最低公共祖先
 */

#import <Foundation/Foundation.h>
#import <vector>
#import <queue>
#include <cstdio>
#include <algorithm>
#include <functional>
#include <exception>
#include <list>
#include <map>
#include <unordered_map>
#include <stack>
#include <exception>
#include <string>
#include <iostream>
#include <fstream>
#include <functional>

using namespace std;

#pragma mark - 数组中重复出现的数字
//题目描述：在一个长度为n的数组里所有的数字都在0～n-1的范围内，数组中默写数字是重复的，但是不知道有几个重复，也不知道每个数字重复了几次，请找出数组中任意一个重复的数字
//题目解析：解法一（hashmap）空间复杂度O(n),时间复杂度O(1)
std::vector<int> appearMoreThanOnceNum(int *data, int length){
    std::vector<int> res;
    if (data == nullptr && length < 0) {
        return res;
    }
    std::map<int, int> hash;
    for (int i = 0; i < length; i++) {
        hash[data[i]]++;
    }
    std::map<int,int>::iterator iter = hash.begin();
    for(;iter != hash.end(); iter++){
        if (iter->second > 1) {
            res.push_back(iter->first);
        }
    }
    return res;
}
//题目解析：解法二
bool duplicate(int* number, int length, int* duplicate){
    //重排数组
    if (number == nullptr || length <= 1) {
        return false;
    }
    for(int i = 0; i < length; i++){
        if (number[i] < 0 || number[i] > length - 1) {
            return false;
        }
    }
    for(int j = 0; j < length; j++){
        //如果不相等，就继续交换,
        //注意：如果在一次循环中确定不了，则在for循环内，嵌套while循环 
        while (number[j] != j) {
            if (number[j] == number[number[j]]) {
                *duplicate = number[j];
                return true;
            }
            int temp = number[j];
            number[j] = number[temp];
            number[temp] = temp;
        }
    }
    return false;
}

int findNumAppearMoreThanOnce(int *data, int length){
    if (data == nullptr || length < 0) {
        return -1;
    }
    for(int i = 0; i < length; i++){
        if (i != (data[i] - 1)) {
            while (data[i] == data[data[i] - 1]) {
                return data[i];
            }
            std::swap(data[i] , data[data[i] - 1]);
        }
    }
    return 0;
}

void QuickSort(int *data, int length, int start, int end);
int findNumAppearMoreThanOnce1(int *data, int length){
    QuickSort(data, length, 0, length - 1);
    for(int i = 1; i < length; i++){
        if (data[i] == data[i - 1]) {
            return data[i];
        }
    }
    return 0;
}

//题目描述：不修改数组找出重复的数字
//题目解析：利用出现的次数是否超出一半
int countRange(int *data, int length, int start, int end){
    if (data == nullptr || length < 0 || start > end) {
        return 0;
    }
    int count = 0;
    for(int i = 0; i < length; i++)
        if (data[i]>=start && data[i]<=end)
            ++count;
    return count;
}

int duplicate2(int *data, int length){
    if (data == nullptr || length < 1) {
        return  -1;
    }
    //int middle
    int start = 0;
    int end = length - 1;
    while (start <= end) {
        int middle = ((end - start) >> 1) + start;
        int count = countRange(data, length, start, middle);
        if (start == end) {
            if (count > 1) {
                return start;
            }else{
                break;
            }
        }
        if (count > (middle - start + 1)) {
            end = middle;
        }else{
            start = middle + 1;
        }
    }
    
    return -1;
}

#pragma mark - 二维数组中的查找
/*
 1  2   8   9
 2  4   9   12
 4  7   10  13
 6  8   11  15
 */
bool findNumInMatrix(int *matrix, int rows, int colums, int num){
    if (matrix == nullptr || rows < 0 || colums < 0) {
        return false;
    }
    int row = 0;
    int colum = colums - 1;
    while (row < rows && colum > 0) {
        if (matrix[row * colums + colum] == num) {
            return true;
        }else if(matrix[row * colums + colum] > num){
            colum--;
        }else{
            row++;
        }
    }
    return false;
}

#pragma mark - 空格替换
void replaceBlank(char string[], int length){
    //1.计算所有空格的个数
    if (string == nullptr || length < 0) {
        return;
    }
    int count = 0;
    int lengthOfOrigin = 0;
    int i = 0;
    while (string[i] != '\0') {
        ++lengthOfOrigin;
        if (string[i] == ' ') {
            ++count;
        }
        ++i;
    }
    int newLength = lengthOfOrigin + count * 2;

    int indexOfOrigin = lengthOfOrigin;
    int indexOfNew = newLength;
    while (indexOfOrigin >= 0 && indexOfNew > indexOfOrigin) {
        if (string[indexOfOrigin] == ' ') {
            string[indexOfNew--] = '0';
            string[indexOfNew--] = '2';
            string[indexOfNew--] = '%';
        }else{
            string[indexOfNew--] = string[indexOfOrigin];
        }
        --indexOfOrigin;
    }
}

#pragma mark - 二叉树
#pragma mark 有关二叉搜索树的题目26、27、28、32、33、34、36、37
struct BinaryTreeNode{
    int m_nValue;
    BinaryTreeNode *m_pLeft;
    BinaryTreeNode *m_pRight;
    BinaryTreeNode *m_pParent;
};

BinaryTreeNode *createBinaryTree(int value){
    BinaryTreeNode *node = new BinaryTreeNode();
    node->m_nValue = value;
    node->m_pLeft = nullptr;
    node->m_pRight = nullptr;
    return node;
}

void DestoryTree(BinaryTreeNode *pNode){
    if (pNode) {
        delete pNode;
        return;
    }
    DestoryTree(pNode->m_pLeft);
    DestoryTree(pNode->m_pRight);
}
void connectBinaryTree(BinaryTreeNode *root, BinaryTreeNode *left, BinaryTreeNode *right){
    if (root) {
        root->m_pLeft = left;
        root->m_pRight = right;
    }
}
BinaryTreeNode* ConstructCore(int* startPreorder, int* endPreorder, int* startInorder, int* endInorder);

#pragma mark 重建二叉树，通过给定的前序遍历序列和中序遍历序列，重建二叉树，并输出根节点
//1.根据前序遍历序列，获得根节点
//2.获得 子序列
BinaryTreeNode *ConstructCore(int *startPreOrder, int *EndPreorder,
                              int *startInOrder,  int *EndInOrder);

BinaryTreeNode *Construct(int *PreOrder, int *InOrder, int length){
    if (PreOrder == nullptr || InOrder == nullptr || length < 0) {
        return nullptr;
    }
    return ConstructCore(PreOrder, PreOrder+length-1, InOrder, InOrder+length-1);
}
    
//递归调用
BinaryTreeNode *ConstructCore(int *startPreOrder, int *EndPreorder,
                              int *startInOrder,  int *EndInOrder){
    
    //get the root node
    int rootValue = startPreOrder[0];
    BinaryTreeNode *root = new BinaryTreeNode();
    root->m_nValue = rootValue;
    root->m_pLeft = root->m_pRight = nullptr;
    if (startPreOrder == EndPreorder) {
        if (startInOrder == EndInOrder && *startPreOrder == *startInOrder) {
            return root;
        }else{
            [NSException exceptionWithName:@"error" reason:@"Input valid !" userInfo:nil];
        }
    }
    int *rootInorder = startInOrder;
    while (rootInorder <= EndInOrder && *rootInorder != rootValue) {
        ++rootInorder;
    }
    //get sub nodes
    int leftLength = (int)(rootInorder - startInOrder);
    int *leftPreorderEnd = startPreOrder + leftLength;
    if (leftLength > 0) {
        root->m_pLeft = ConstructCore(startPreOrder+1, leftPreorderEnd, startInOrder, rootInorder-1);
    }
    if(leftLength < EndPreorder - startPreOrder){
        root->m_pRight = ConstructCore(leftPreorderEnd+1, EndPreorder, rootInorder+1, EndInOrder);
    }
    return root;
}

#pragma mark 32 不分行打印二叉树
void printBinaryTree(BinaryTreeNode *root){
    std::deque<BinaryTreeNode *> deque;
    deque.push_back(root);
    while (!deque.empty()) {
        BinaryTreeNode *node = deque.front();
        printf("%d \n", node->m_nValue);
        deque.pop_front();
        if (node->m_pLeft) {
            node->m_pLeft->m_pParent = node;
            deque.push_back(node->m_pLeft);
        }
        if (node->m_pRight) {
            node->m_pRight->m_pParent = node;
            deque.push_back(node->m_pRight);
        }
    }
}

#pragma mark 分行打印二叉树(双向队列)
void printBinaryTreeLevel(BinaryTreeNode *root){
    std::deque<BinaryTreeNode *> deque;
    deque.push_back(root);
    int nextLevel = 0;
    int toBePrint = 1;
    while (!deque.empty()) {
        BinaryTreeNode *node = deque.front();
        printf("%d", node->m_nValue);
        if (node->m_pLeft) {
            deque.push_back(node->m_pLeft);
            nextLevel++;
        }
        if (node->m_pRight) {
            deque.push_back(node->m_pRight);
            nextLevel++;
        }
        deque.pop_front();
        --toBePrint;
        if (toBePrint == 0) {
            printf("\n");
            toBePrint = nextLevel;
            nextLevel &= 0;
        }
    }
}

#pragma mark 之字形打印二叉树(双栈)
void printBinaryTreeWithZ(BinaryTreeNode *head){
    if (head == nullptr) {
        return;
    }
    //double stack
    std::stack<BinaryTreeNode *> frontStack;
    std::stack<BinaryTreeNode *> backStack;
    
    frontStack.push(head);
    
    while (!frontStack.empty() || !backStack.empty()) {
        while (!frontStack.empty()) {
            BinaryTreeNode *node = frontStack.top();
            printf("%d", node->m_nValue);
            frontStack.pop();
            if (node->m_pLeft) {
                backStack.push(node->m_pLeft);
            }
            if (node->m_pRight) {
                backStack.push(node->m_pRight);
            }
        }
        printf("\n");
        while (!backStack.empty()) {
            BinaryTreeNode *node = backStack.top();
            printf("%d", node->m_nValue);
            backStack.pop();
            if (node->m_pRight) {
                frontStack.push(node->m_pRight);
            }
            if (node->m_pLeft) {
                frontStack.push(node->m_pLeft);
            }
        }
        printf("\n");
    }
}

#pragma mark 二叉树的下一个节点
/*
 给定一个二叉树和其中一个节点，请找出中序遍历的下一个节点
 题目解析:有右子节点和其他节点
 */
BinaryTreeNode *getNext(BinaryTreeNode *node){
    if (node->m_pRight) {//有右子节点
        BinaryTreeNode *next = node->m_pRight;
        while (next->m_pLeft) {
            next = next->m_pLeft;
        }
        return next;
    }else if(node->m_pParent != nullptr){//其他节点
        BinaryTreeNode *current = node;
        BinaryTreeNode *parent = node->m_pParent;
        while (parent && current == parent->m_pRight) {//右子树
            current = parent;
            parent = parent->m_pParent;
        }
        return parent;
    }
    return nil;
}

#pragma mark 26 树的子结构
/*
 题目描述：给两棵树A、B，判断B是否是A的子树
 题目解析：通过两棵的遍历来判断
 */
void HasSubTreeCore(BinaryTreeNode *A, BinaryTreeNode *B, bool *bSubTree);
void HasSubTreeCore1(BinaryTreeNode *nodeA, BinaryTreeNode *nodeB);
bool hasSubTree = false;
bool HasSubTree(BinaryTreeNode *A, BinaryTreeNode *B){
    if (A == nullptr && B == nullptr) {
        return false;
    }
    HasSubTreeCore1(A, B);
    return hasSubTree;
}
//前序遍历
void HasSubTreeCore1(BinaryTreeNode *nodeA, BinaryTreeNode *nodeB){
    if (nodeA->m_nValue == nodeB->m_nValue) {
        HasSubTreeCore(nodeA, nodeB, &hasSubTree);
    }
    if (nodeA->m_pLeft) {
        HasSubTreeCore1(nodeA->m_pLeft, nodeB);
    }
    if (nodeA->m_pRight) {
        HasSubTreeCore1(nodeA->m_pRight, nodeB);
    }
}

void HasSubTreeCore(BinaryTreeNode *nodeA, BinaryTreeNode *nodeB, bool *bSubTree){
    *bSubTree = nodeA->m_nValue == nodeB->m_nValue;
    if (nodeA->m_pLeft&&nodeB->m_pLeft) {
        HasSubTreeCore(nodeA->m_pLeft, nodeB->m_pLeft, bSubTree);
    }
    if (nodeA->m_pRight&&nodeB->m_pRight) {
        HasSubTreeCore(nodeA->m_pRight, nodeB->m_pRight, bSubTree);
    }
}

#pragma mark 27 二叉树的镜像问题
/*
        1                1
      /   \            /   \
     2     3          3     2
    / \   / \        / \   / \
   4   5 6   7      7   6  5  4
 */
#pragma mark 前序遍历、交换左右节点
void MirrorBinaryTreeCore(BinaryTreeNode *node);
BinaryTreeNode *MirrorBinaryTree(BinaryTreeNode *head){
    if (head == nullptr) {
        return nullptr;
    }
    MirrorBinaryTreeCore(head);
    return head;
}
void MirrorBinaryTreeCore(BinaryTreeNode *node){
    if (node->m_pLeft && node->m_pRight) {
        BinaryTreeNode *temp = node->m_pLeft;
        node->m_pLeft = node->m_pRight;
        node->m_pRight = temp;
    }
    if (node->m_pLeft) {
        MirrorBinaryTreeCore(node->m_pLeft);
    }
    if (node->m_pRight) {
        MirrorBinaryTreeCore(node->m_pRight);
    }
}

#pragma mark 28 对称二叉树
bool isSymmetricalCore(BinaryTreeNode *head1, BinaryTreeNode *head2);
bool isSymmetrical(BinaryTreeNode *head){
    if (head == nullptr) {
        return false;
    }
    return isSymmetricalCore(head, head);
}
bool isSymmetricalCore(BinaryTreeNode *head1, BinaryTreeNode *head2){
    if (head1 == nullptr || head2 == nullptr) {
        return true;
    }
    if (head1 == nullptr || head2 == nullptr) {
        return false;
    }
    if (head1->m_nValue != head2->m_nValue) {
        return false;
    }
    return isSymmetricalCore(head1->m_pLeft, head2->m_pRight) &&  isSymmetricalCore(head1->m_pRight, head2->m_pLeft);
}

#pragma mark 33 二叉搜索树的后续遍历序列
/*
 题目描述：给定数组，判断其是否是某一个二叉搜索树的后续遍历序列
 题目解析：后续遍历序列，根节点是最后一个，获取最后一个节点，通过比较，
         获取左右子树，获取小于根节点的数据，data[i]<root break;
 */
bool verifySequenceOfBST(int *data, int length){
    if (data == nullptr || length < 0) {
        return false;
    }
    int root = data[length-1];
    int i = 0;
    for(; i < length-1; ++i){
        if(data[i]>root) break;
    }
    int j = i;
    for(; j < length-1;++j){
        if (data[j]<root) {
            return false;
        }
    }
    bool left = true;
    if (i>0) {
        left = verifySequenceOfBST(data, i);
    }
    bool right = true;
    if (i < length-1) {
        right = verifySequenceOfBST(data+i, length-i-1);
    }
    return (left && right);
}

#pragma mark 34 二叉树中和为某一值的路径
void pathOfBinaryTreeCore(BinaryTreeNode *node, int n, std::deque<int> deque);
bool isN(std::deque<int> stack, int n);
void printN(std::deque<int> stack);
void pathOfBinaryTree(BinaryTreeNode *head, int n){
    if (head == nullptr || n == 0) {
        return;
    }
    std::deque<int> deque;
    pathOfBinaryTreeCore(head, n, deque);
}
void pathOfBinaryTreeCore(BinaryTreeNode *node, int n, std::deque<int> deque){
    deque.push_back(node->m_nValue);
    if (isN(deque, n) && node->m_pLeft == nullptr && node->m_pRight == nullptr)
        printN(deque);
    if (node->m_pLeft) {
        pathOfBinaryTreeCore(node->m_pLeft, n, deque);
    }
    if (node->m_pRight) {
        pathOfBinaryTreeCore(node->m_pRight, n, deque);
    }
    deque.pop_back();
}
bool isN(std::deque<int> deque, int n){
    std::deque<int>::iterator ite = deque.begin();
    int temp = 0;
    for(;ite != deque.end();ite++){
        temp += *ite;
    }
    if (n == temp) {
        return true;
    }
    return false;
}
void printN(std::deque<int> deque){
    std::deque<int>::iterator ite = deque.begin();
    for(;ite != deque.end();ite++){
        printf("%d ", *ite);
    }
}


#pragma mark 36 二叉树中和双向列表
/*
 将一个二叉搜索树转换为有序双向列表
 中序遍历解决
 */
void convert(BinaryTreeNode *node, BinaryTreeNode **list);
BinaryTreeNode * convertNotToList(BinaryTreeNode *node){
    if (node == nullptr) {
        return nullptr;
    }
    BinaryTreeNode *list = nullptr;
    convert(node, &list);
    while (list->m_pLeft) {
        list=list->m_pLeft;
    }
    return list;
}
void convert(BinaryTreeNode *node, BinaryTreeNode **list){
    if (node == nullptr) {
        return;
    }
    BinaryTreeNode *current = node;
    if (node->m_pLeft) {
        convert(node->m_pLeft, list);
    }
    node->m_pLeft = *list;
    if (*list!=nullptr) (*list)->m_pRight = node;
    *list = current;
    if (node->m_pRight) {
        convert(node->m_pRight, list);
    }
}


/*
 实现两个函数，分别用来序列话和反序列化二叉树
 */
void Serialize(BinaryTreeNode *pNode, std::ostream& stream){
    if (pNode == nullptr) {
        stream << "$,";
        return;
    }
    stream << pNode->m_nValue << ',';
    Serialize(pNode->m_pLeft, stream);
    Serialize(pNode->m_pRight, stream);
}

bool ReadStream(std::istream& stream, int *number){
    if (stream.eof()) {
        return false;
    }
    char buffer[32];
    buffer[0] = '\0';
    
    char ch;
    stream >> ch;
    int i = 0;
    while (!stream.eof() && ch != ',') {
        buffer[i++] = ch;
        stream >> ch;
    }
    
    bool isNumeric = false;
    if (i > 0 && buffer[0] != '$') {
        *number = atoi(buffer);
        isNumeric = true;
    }
    
    return isNumeric;
}

void Deserialize(BinaryTreeNode **pNode, std::istream& stream){
    int number;
    if (ReadStream(stream, &number)) {
        *pNode = new BinaryTreeNode();
        (*pNode)->m_nValue = number;
        (*pNode)->m_pLeft = nullptr;
        (*pNode)->m_pRight = nullptr;
        Deserialize(&(*pNode)->m_pLeft, stream);
        Deserialize(&(*pNode)->m_pRight, stream);
    }
}

#pragma mark - stack & queue
//stack: FILO
//queue: FIFO
template <typename T> class CQueue{
public:
    void appendTail(const T & node);
    T deleteHead();
    
private:
    std::stack<T> stack1;
    std::stack<T> stack2;
};

template <typename T> void CQueue<T>::appendTail(const T & node){
    stack1.push(node);
}

template <typename T> T CQueue<T>::deleteHead(){
    if (stack2.size() <= 0) {
        while (stack1.size()) {
            stack2.push(stack1.top());
            stack1.pop();
        }
    }
    if (stack2.size() == 0) {
        [NSException exceptionWithName:@"error" reason:@"queue is empty" userInfo:nil];
    }
    T head = stack2.top();
    stack2.pop();
    return head;
}


#pragma mark - 斐波那契数列
/*
       |- 0             (n = 0)
f(n) = |- 1             (n = 1)
       |- f(n-1)+f(n-2) (n = 2)
*/
#pragma mark 解法一：(会有很多冗余计算)
long long Fibonacci(unsigned int n){
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    return Fibonacci(n-1)+Fibonacci(n-2);
}

#pragma mark 解法二：(0, 1, 2, ... n);
long long Fibonacci2(unsigned int n){
    int res[2] = {0,1};
    if (n < 2) {
        return res[n];
    }
    int fib0 = 0;
    int fib1 = 1;
    int fibN = 0;
    for(int i = 2; i <= n; i++){
        fibN = fib0 + fib1;
        fib0 = fib1;
        fib1 = fibN;
    }
    return fibN;
}

#pragma mark - 查找和排序
//题型包括：1.旋转数组中最小的数字 2.在排序数组中查找数字
int halfFind(int *data, int length, int num){
    if (data == nullptr || length < 0) {
        [NSException exceptionWithName:@"error" reason:@"Invalid input" userInfo:nil];
    }
    int start = 0;
    int end = length - 1;
    while (start < end) {
        int middle = ceil((float)(end - start)/2)+start;
        if (num > data[middle]) {
            start = middle;
        }else if(num < data[middle]){
            end = middle;
        }else{
            return middle;
        }
    }
    return -1;
}

#pragma mark - 快速排序算法
int RandomInRange(int start, int end){
    return rand()%((end+1) - start);
}

void Swap(int* num1,int* num2){
    int temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}

int Partition(int *data, int length, int start, int end){
    if (data == nullptr || length < 0 || start < end) {
        [NSException exceptionWithName:@"error"
                                reason:@"input invalid"
                              userInfo:nil];
    }
    
    int index = RandomInRange(start, end);
    Swap(&data[index], &data[end]);
    
    //这是精髓
    int small = start - 1;
    for (index = start; index < end; index++) {
        if (data[index] < data[end]) {
            ++small;
            if (small != index) {
                Swap(&data[small], &data[index]);
            }
        }
    }
    ++small;
    Swap(&data[small], &data[end]);
    return small;
}

void QuickSort(int *data, int length, int start, int end){
    if (data == nullptr || start > end) {
        return;
    }
    int index = Partition(data, length, start, end);
    if (index > start) {
        QuickSort(data, length, start, index - 1);
    }
    if (index < end) {
        QuickSort(data, length, index + 1, end);
    }
}

#pragma mark - 旋转数组中最小的数字
#pragma mark {3,4,5,1,2}是{1,2,3,4,5}的旋转
//输入一个递增数组的旋转，输出数组中最小的元素
int Min(int *data, int length){
    if (data == nullptr || length < 0) {
        [NSException exceptionWithName:@"error" reason:@"Invalid Input" userInfo:nil];
    }
    int index1 = 0;
    int index2 = length - 1;
    int indexMid = index1;
    while (data[index1] >= data[index2]) {
        if (index2 - index1 == 1) {
            indexMid = index2;
            break;
        }
        indexMid = ceil((float)(index2 - index1)/2)+index1;
        if (data[index1] <= data[indexMid]) {
            index1 = indexMid;
        }else if (data[index2] >= data[indexMid]){
            index2 = indexMid;
        }
    }
    return data[indexMid];
}


#pragma mark - 圆圈中最后剩下的数
#pragma mark 解法一：
int lastRemainNum(int *data, int length, int m){
    if (data == nullptr || length < 0) {
        [NSException exceptionWithName:@"error" reason:@"Invalid Input" userInfo:nil];
    }
    std::vector<int> nums;
    for(int i = 0; i < length; i++)
        nums.push_back(data[i]);
    
    std::vector<int>::iterator current = nums.begin();
    while (nums.size() > 1) {
        for(int j = 1; j < m; j++){
            current++;
            if (current == nums.end()) {
                current = nums.begin();
            }
        }
        std::vector<int>::iterator next = ++current;
        if (next == nums.end()) {
            next = nums.begin();
        }
        
        --current;
        nums.erase(current);
        current = next;
    }
    return *(current);
}

#pragma mark 解法二：使用公式计算
int theLastRemainNum(int n, int m){
    if (n == 0) {
        return -1;
    }
    if (n == 1) {
        return n;
    }
    return (theLastRemainNum(n-1, m)+m)%n;
}

#pragma mark - 回溯法
#pragma mark 矩阵中的路径
bool hasPathCore(const char *matrix,
                 int rows, int row,
                 int cols, int col,
                 const char *str, int pathLength,
                 bool *visit);
bool hasPath(const char *matrix, int rows, int cols, const char *str){
    if (matrix == nullptr || rows < 0 || cols < 0 || str == nullptr) {
        return false;
    }
    
    int pathLength = 0;
    bool visit[rows * cols];
    memset(visit, 0, rows * cols);
    
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            if (hasPathCore(matrix,
                            rows, i,
                            cols, j,
                            str, pathLength,
                            visit)) {
                return true;
            }
        }
    }
    return false;
}

bool hasPathCore(const char *matrix,
                 int rows, int row,
                 int cols, int col,
                 const char *str, int pathLength,
                 bool *visit){
    if (str[pathLength] == '\0') {
        return true;
    }
    
    bool hasPath = false;
    if (row >= 0 && row < rows &&
        col >= 0 && col < cols &&
        matrix[row * cols + col] == str[pathLength] &&
        !visit[row * cols + col]) {
        
        ++pathLength;
        visit[row * cols + col] = true;
        
        hasPath = hasPathCore(matrix, rows, row - 1, cols, col, str, pathLength, visit) ||
        hasPathCore(matrix, rows, row + 1, cols, col, str, pathLength, visit) ||
        hasPathCore(matrix, rows, row, cols, col - 1, str, pathLength, visit) ||
        hasPathCore(matrix, rows, row, cols, col + 1, str, pathLength, visit);
        
        if (!hasPath) {
            --pathLength;
            visit[row * cols + col] = false;
        }
    }
    return hasPath;
}

#pragma mark 机器人的运动范围
void robbotCore(int rows,int row,
                int cols,int col,
                int* count, bool *visit,
                int threshold);
int roboot(int m, int n, int threshold){
    if (m < 0 || n < 0) {
        return 0;
    }
    
    bool visit[m * n];
    memset(visit, 0, m * n);
    
    int count = 0;
    robbotCore(m, 0, n, 0, &count, visit, threshold);
    return count;
}

int sum(int num){
    if (num <= 0) {
        return 0;
    }
    int temp = num%10;
    num = num/10;
    return sum(num)+temp;
}
bool canIn(int row, int col, int threshold){
    return sum(row) + sum(col) <= threshold;
}
void robbotCore(int rows,int row,
                int cols,int col,
                int* count, bool *visit,
                int threshold){
    //Can in
    if (row >= 0 && row < rows &&
        col >= 0 && col < cols &&
        canIn(row, col, threshold) &&
        !visit[row * cols + col]) {
        visit[row * cols + col] = true;
        (*count)++;
        robbotCore(rows, row-1, cols, col, count, visit, threshold);
        robbotCore(rows, row+1, cols, col, count, visit, threshold);
        robbotCore(rows, row, cols, col-1, count, visit, threshold);
        robbotCore(rows, row, cols, col+1, count, visit, threshold);
    }
}

#pragma mark - 动态规划和贪心算法
#pragma mark 剪绳子，各段绳子乘积的最大值
#pragma mark 解法一：动态规划
/*
 f(n) = max(f(i)*f(n-i))
 */
int maxProduct(int length){
    if (length < 2) {
        return 0;
    }
    if (length == 2) {
        return 1;
    }
    if (length == 3) {
        return 2;
    }
    int *products = new int[length+1];
    products[0] = 0;
    products[1] = 1;
    products[2] = 2;
    products[3] = 3;
    int max = 0;
    for(int i = 4; i <= length; ++i){
        max = 0;
        for(int j = 1; j <= i/2; ++j){
            int res = products[j] * products[i - j];
            if(max < res) max = res;
        }
        products[i] = max;
    }
    max = products[length];
    delete [] products;
    return max;
}

#pragma mark 解法二：贪心算法
/*
 剪绳子是有规律的，>= 5,要多剪成3的长度的绳子
 */
int maxProduct1(int length){
    if (length < 2) {
        return 0;
    }
    if (length == 2) {
        return 1;
    }
    if (length == 3) {
        return 2;
    }
    int timesOf3 = length/3;
    if (length - timesOf3 * 3 == 1) timesOf3 -= 1;
    int timesOf2 = (length - timesOf3 * 3)/2;
    int num1 = (int)pow(3, timesOf3);
    int num2 = (int)pow(2, timesOf2);
    int ret = (int)(num1 * num2);
    return ret;
}

#pragma mark - 位运算
#pragma mark 15 二进制中1的个数
#pragma mark 解法一：常规解法
int countOf1_function1(int n){
    int count = 0;
    unsigned int flag = 1;
    while (flag) {
        if (n & flag)
            count++;
        flag = flag << 1;
    }
    return count;
}
#pragma mark 解法二：
int countOf1_function2(int n){
    int count = 0;
    while (n) {
        count++;
        n = (n-1)&n;
    }
    return count;
}

#pragma mark 56 数组中数字出现的次数
#pragma mark 数组中出现一次的两个数字
int findTheFirstBitIs1(int num);
bool isBit1(int num, unsigned int indexOf1);
void findNumsAppearOnce(int *data, int length, int* num1, int* num2){
    if (data == nullptr || length < 0) {
        [NSException exceptionWithName:@"error" reason:@"Invalid Input" userInfo:nil];
    }
    int current = 0;
    for(int i = 0; i < length; ++i){
        current ^= data[i];
    }
    int firtBitIs1 = findTheFirstBitIs1(current);
    
    *num1 = *num2 = 0;
    for(int j = 0; j < length; ++j){
        if (isBit1(data[j], firtBitIs1)) {
            int temp = data[j];
            *num1 ^= temp;
        }else{
            int temp = data[j];
            *num2 ^= temp;
        }
    }
}
int findTheFirstBitIs1(int num){
    int index = 0;
    unsigned int flag = 1;
    while (flag) {
        if(num & flag){
            break;
        }
        index++;
        flag = flag << 1;
    }
    return index;
}

bool isBit1(int num, unsigned int indexOf1){
    num = num >> indexOf1;
    return (num&1);
}

#pragma mark 数组中只出现一次的那个数字
int findNumAppearOnce(int *data, int length){
    if (data == nullptr || length < 0) {
        [NSException exceptionWithName:@"error" reason:@"Invalid Input" userInfo:nil];
    }
    int num = data[0];
    for (int i = 1; i < length; ++i) {
        num = num^data[i];
    }
    return num;
}

#pragma mark 65 不用加减乘除做加法
int Add(int num1, int num2){
    int sum = 0;
    int carry = 0;
    do{
        //0010 ^ 0100 = 0110
        sum = num1 ^ num2;
        //0010 & 0010 = 0010 << 1 = 0100
        carry = (num1 & num2) << 1;
        num1 = sum;
        num2 = carry;
    }while(num2 != 0);
    return num1;
}

#pragma mark - 16 数据的整数次方
double MyPower(double base, int expense){
    if (base == 0) {
        return 0;
    }
    if (expense == 0) {
        return 1;
    }
    double result = MyPower(base, expense>>1);
    result *= result;
    if ((expense&1) == 1) {
        result *= base;
    }
    return result;
}

#pragma mark - 列表相关操作
#pragma mark 从尾到头打印列表
struct ListNode{
    int value;
    ListNode *next;
    ListNode *m_pSibling;
};

void connectList(ListNode *head, ListNode *node){
    if (head && node) {
        head->next = node;
    }
}

ListNode *createListWithNumber(int number){
    ListNode *head = new ListNode();
    head->value = 0;
    ListNode *current = head;
    for(int i = 1; i < number; i++){
        ListNode *node = new ListNode();
        node->value = i;
        connectList(current, node);
        current = node;
    }
    return head;
}

#pragma mark 方法一：入栈再出栈
void printListFromTrail(ListNode *listNode){
    std::stack<ListNode *> stack;
    while (listNode) {
        stack.push(listNode);
        listNode = listNode->next;
    }
    while (stack.size()>0){
        printf("%d \n", stack.top()->value);
        stack.pop();
    }
}
#pragma mark 方法二：递归（递归的本质就是栈）
void printListFromTrail_1(ListNode *listNode){
    if (listNode == nullptr) {
        return;
    }
    if(listNode->next) {
        printListFromTrail_1(listNode->next);
    }
    printf("%d \n", listNode->value);
}
#pragma mark 22 列表中倒数第k个节点
#pragma mark 倒数的第k个节点 = 正数的第(n-k+1)个节点
ListNode *FindKthToTail(ListNode *head, int k){
    if (head == nullptr || k==0) {
        return nullptr;
    }
    ListNode *p1 = head;
    ListNode *p2 = nullptr;
    for(int i = 0; i < k-1; ++i){
        if (p1->next==nullptr) {
            return nullptr;
        }
        p1 = p1->next;
    }
    p2 = head;
    while (p1->next!=nullptr) {
        p1=p1->next;
        p2=p2->next;
    }
    return p2;
}

#pragma mark 列表的中间节点(快慢指针)
ListNode *middleOfList(ListNode *head){
    if (head       == nullptr ||//空列表
        head->next == nullptr) {//只有一个节点的列表
        return nullptr;
    }
    ListNode *fast = head;
    ListNode *slow = head;
    while (fast&&fast->next != nullptr) {
        fast = (fast&&fast->next)?fast->next:nullptr;
        fast = (fast&&fast->next)?fast->next:nullptr;
        slow = (slow&&slow->next)?slow->next:nullptr;
    }
    return slow;
}

#pragma mark 23 列表中环的入口(快慢指针)
ListNode *meetingNode(ListNode *head){
    if (head == nullptr) {
        return nullptr;
    }
    ListNode *fast = head->next->next;
    ListNode *slow = head->next;
    while (fast->value != slow->value) {
        fast=fast->next->next;
        slow=slow->next;
    }
    return slow;
}

ListNode *startNodeOfLoop(ListNode *head){
    if (head == nullptr) {
        return nullptr;
    }
    ListNode *meetNode = meetingNode(head);
    ListNode *nodeA = head;
    ListNode *nodeB = meetNode;
    while (nodeA->value!=nodeB->value) {
        nodeA = nodeA->next;
        nodeB = nodeB->next;
    }
    return nodeB;
}

#pragma mark 24 反转列表
void revertList(ListNode *head){
    if (head == nullptr) {
        return;
    }
    ListNode *pre = nullptr;
    ListNode *curr = head;
    while (curr != nullptr) {
        ListNode *next = curr->next;
        curr->next = pre;
        pre = curr;
        curr = next;
    }
}

#pragma mark 25 合并两个有序列表
ListNode * mergeTwoSortList(ListNode *list1, ListNode *list2){
    if (list1 == nullptr && list2 == nullptr) {
        return nullptr;
    }
    if (list1 != nullptr && list2 == nullptr) {
        return list1;
    }
    if (list1 == nullptr && list2 != nullptr) {
        return list2;
    }
    ListNode *head = new ListNode();
    ListNode *ret = head;
    ListNode *node1 = list1;
    ListNode *node2 = list2;
    while (node1 || node2) {
        if (node1 && node2) {
            if (node1->value <= node2->value) {
                head->next = node1;
                node1 = node1->next;
                head=head->next;
            }else if(node1->value > node2->value){
                head->next = node2;
                node2 = node2->next;
                head=head->next;
            }
        }else if(node1){
            head->next = node1;
            node1 = node1->next;
            head = head->next;
        }else if(node2){
            head->next = node2;
            node2 = node2->next;
            head = head->next;
        }
    }
    return ret->next;
}

#pragma mark 18 删除列表的节点
#pragma mark 题目一：在O(1)时间内删除链表的节点
#pragma mark 题目解析
ListNode * createNode(int value);
ListNode * connectNode(ListNode *head, ListNode *currentNode);
/*
 要删除节点i，那么把节点j的内容复制到节点i中，然手删除节点j就OK
 */
void deleteNode(ListNode** pListHead, ListNode* pToBeDeleted)
{
    if(!pListHead || !pToBeDeleted)
        return;

    if(pToBeDeleted->next != nullptr)
    {
        ListNode* pNext = pToBeDeleted->next;
        pToBeDeleted->value = pNext->value;
        pToBeDeleted->next = pNext->next;
 
        delete pNext;
        pNext = nullptr;
    }else if(*pListHead == pToBeDeleted){
        delete pToBeDeleted;
        pToBeDeleted = nullptr;
        *pListHead = nullptr;
    }
    else{
        ListNode* pNode = *pListHead;
        while(pNode->next != pToBeDeleted)
        {
            pNode = pNode->next;
        }
 
        pNode->next = nullptr;
        delete pToBeDeleted;
        pToBeDeleted = nullptr;
    }
}

#pragma mark 删除链表中重复的节点
void deleteDeplication(ListNode **head){
    if (*head == nullptr) {
        return;
    }
    ListNode *pPreNode = nullptr;
    ListNode *node = *head;
    while (node != nullptr) {
        ListNode *pNext = node->next;
        bool bDelte = false;
        if (pNext != nullptr && node->value == pNext->value) {
            bDelte = true;
        }
        if (!bDelte) {
            pPreNode = node;
            node = pNext;
        }else{
            int value = node->value;
            ListNode *bDelNode = node;
            while (bDelNode != nullptr && bDelNode->value == value) {
                pNext = bDelNode->next;
                delete bDelNode;
                bDelNode = nullptr;
                bDelNode = pNext;
            }
            //重新链接List
            if (pPreNode == nullptr) {
                *head = pNext;
            }else{
                pPreNode->next = pNext;
            }
            node = pNext;
        }
    }
}

ListNode * createNode(int value){
    ListNode *node = new ListNode();
    node->value = value;
    node->next = NULL;
    return node;
}
ListNode * connectNode(ListNode *head, ListNode *currentNode){
    if (head == nullptr || currentNode == nullptr) {
        return nullptr;
    }
    head->next = currentNode;
    return head;
}

#pragma mark 35 复杂列表的复制
/*
 1.复制节点
 2.链接sibling节点
 3.reconnect
 */
ListNode * copyNode(ListNode *node){
    if (node == nil) {
        return nil;
    }
    ListNode *copyNode = new ListNode();
    copyNode->value = node->value;
    copyNode->next = node->next;
    copyNode->m_pSibling = node->m_pSibling;
    return copyNode;
}

ListNode *complexListCopy(ListNode *head){
    if (head == nullptr) {
        return nil;
    }
    
    ListNode *nextNode = head;
    while (nextNode != nullptr) {
        ListNode *cpNode = copyNode(nextNode);
        ListNode *temp = nextNode->next;
        nextNode->next = cpNode;
        cpNode->next = temp;
        nextNode = temp;
    }
    
    ListNode *ntNode = head;
    ListNode *cpedNode = head->next;
    ListNode *ret = cpedNode;
    ListNode *ret1 = ret;
    while (cpedNode != nullptr) {
        if (ntNode->m_pSibling && ntNode->m_pSibling->next) {
            cpedNode->m_pSibling = ntNode->m_pSibling->next;
        }
        ntNode = cpedNode->next;
        if (ntNode ==  nullptr) {
            break;
        }
        cpedNode = ntNode->next;
        ret->next = cpedNode;
        ret = ret->next;
    }
    return ret1;
}

#pragma mark - 字符串操作
#pragma mark 17 打印从1到最大的n位数
#pragma mark 解法一：常规解法
void print1ToMaxOfNDigits(int n){
    for(int i = 1; i <= pow(10, n) - 1; ++i){
        printf("%d ", (int)i);
    }
    printf("\n");
}
#pragma mark 解法二：大数问题，用字符出啊解决
/*
 1.两数之和
 2.字符串表达数字
 */
bool Increment(char *number);
void PrintNumeber(char *number);
void print1ToMaxOfNDigits1(int n){
    if (n < 0) {
        return;
    }
    char *number = new char[n+1];
    memset(number, '0', n+1);
    number[n] = '\0';
    while(!Increment(number)) {
        PrintNumeber(number);
    }
}

bool Increment(char *number){
    bool isOverFlow = false;
    int nTakeOver = 0;
    int length = (int)strlen(number);
    for(int i = length-1; i >= 0; --i){
        int sum = number[i] - '0' + nTakeOver;
        if(i == length - 1) sum++;
        if (sum >= 10) {
            if (i == 0) {
                isOverFlow = true;
            }
            sum -= 10;
            nTakeOver = 1;
            number[i] = '0' + sum;
        }else{
            number[i] = '0' + sum;
            break;
        }
    }
    return isOverFlow;
}

void PrintNumeber(char *number){
    bool bBeginning = true;
    int length = (int)strlen(number);
    for(int i = 0; i < length; ++i){
        if (bBeginning && number[i] != '0') {
            bBeginning = false;
        }
        if (!bBeginning) {
            printf("%c", number[i]);
        }
    }
    printf("\t");
}

#pragma mark 解法三：递归解决
void print1ToMaxOfNDigits2Core(char *number, int length, int index){
    if (index == length-1) {
        PrintNumeber(number);
        return;
    }
    for(int i = 0; i < 10; i++){
        number[index+1] = i + '0';
        print1ToMaxOfNDigits2Core(number, length, index+1);
    }
}
void print1ToMaxOfNDigits2(int n){
    if (n < 0) {
        return;
    }
    char *number = new char[n+1];
    memset(number, '0', n+1);
    number[n] = '\0';
    for(int i = 0; i < 10; ++i){
        number[0] = i + '0';
        print1ToMaxOfNDigits2Core(number, n, 0);
    }
    delete [] number;
}

#pragma mark 19 正则表达式匹配
#pragma mark 题目描述：换一种思考方式，这也是在提醒你，你现在在动脑子
/*
 请实现一个函数用来匹配用来匹配包含"."和"*"的正则表达式。
 模式中的"."表示任意一个字符，
 而"*"表示他前面的字符可以出现任意次(含0次)，
 在本题中，匹配是指字符串的所有字符匹配整个模式。
 例如，字符串"aaa"与模式“a.a”和"ab*ac*a"匹配，
 但与“aa.a”和"ab*a"都不匹配
 */
#pragma mark  题目解析
/*
 1.compare 相同比较下一位 不同看pattent的下一位的情况
 */
bool matchCore(const char *str, const char *pattern);
bool match(const char *str, const char *pattern){
    if (str == nullptr || pattern == nullptr) {
        return false;
    }
    return matchCore(str, pattern);
}
bool matchCore(const char *str, const char *pattern){
    if (*str == '\0' && *pattern == '\0') {
        return true;
    }
    if (*str != '\0' && *pattern == '\0') {
        return false;
    }
    if (*(pattern+1) == '*') {
        if (*pattern == *str || (*pattern == '.'&&*str != '\0')) {
            return matchCore(str, pattern+2) ||
            matchCore(str+1, pattern) ||
            matchCore(str+1, pattern+2);
        }else{
           return matchCore(str, pattern+2);
        }
    }
    if ((*str != '\0' && *pattern == '.') || *str == *pattern) {
        return matchCore(str+1, pattern+1);
    }
    return false;
}

void Test(const char *method,const char *src,const char *dest, bool m){
    printf("%s %s match %s \n", src, match(src, dest)?"":"not", dest);
}

#pragma mark 20 判断一个字符串是否可以表示有效数字
/*
 如果一个字符串表达的事有效的数据，那么他应该遵守如下模式
 A[.[B]][e|EC]
 A:表示整数部分(+/-)(0~9)
 B:表示小数部分(0~9)
 C:表示指数部分(+/-)(0~9)
 */
//注意只有地址是可以++/--计算的
bool scanNumeric(const char **str);
bool scanUnsignedNumeric(const char **str);
bool isNumeric(const char *str){
    //str指向字符串第一个字符的地址
    if (str == nullptr) {
        return false;
    }
    bool numeric = scanNumeric(&str);//整数部分
    if (*str == '.') {//小数部分
        ++str;
        numeric = scanUnsignedNumeric(&str) || numeric;
    }
    if (*str == 'e' || *str == 'E') {//指数部分
        ++str;
        numeric = scanNumeric(&str) && numeric;
    }
    return numeric && *str == '\0';
}

//**str表示子字符串
bool scanNumeric(const char **str){
    if (**str == '+' || **str == '-') {
        ++(*str);
    }
    return scanUnsignedNumeric(str);
}

bool scanUnsignedNumeric(const char **str){
    const char *before = *str;
    while (**str != '\0' && **str >= '0' && **str <= '9') {
        ++(*str);
    }
    return *str > before;
}

void isNumericTest(const char *name, char *str, bool expected){
    printf("%s %s Numeric \n", str, isNumeric(str)?"is":"is not");
}


#pragma mark 38 字符串全排列
void printAllStrCore(char *str, char *begin){
    if (*begin == '\0') {
        printf("%s\n", str);
    }else{
        for(char *pCh = begin; *pCh != '\0'; pCh++){
            char temp = *pCh;
            *pCh = *begin;
            *begin = temp;
            printAllStrCore(str, begin+1);
            temp = *pCh;
            *pCh = *begin;
            *begin = temp;
        }
    }
}
void printAllStr(char *str){
    if (str == nullptr ) {
        return;
    }
    printAllStrCore(str, str);
}

#pragma mark 字符串的所有组合
/*
 1.情况1:组合包含当前的字符，下一步就要在剩余的字符中寻找m-1个字符
 2.情况2:组合中不包含当前的字符，下一步就要在剩余的字符中寻找m-1个字符
 */
void combination(char* str, int subLength, std::vector<char> &rs){
    if (subLength == 0) {
        vector<char>::iterator iter=rs.begin();
        for(;iter!=rs.end();iter++){
            printf("%c", *iter);
        }
        printf("\n");
        return;
    }
    if (*str == '\0') {
        return;
    }
    rs.push_back(*str);
    //情况1
    combination(str+1, subLength-1, rs);
    rs.pop_back();
    //情况2
    combination(str+1, subLength, rs);
}
void combination(char *str){
    if (str == nullptr) {
        return;
    }
    int length = (int)strlen(str);
    std::vector<char> rs;
    for(int i = 1; i <= length; ++i)
        combination(str, i, rs);
}

#pragma mark 使正方形3组相对的面的顶点和相等
void printMyArray(int *square, int length){
    for(int i = 0; i < length; i++)
        printf("%d ", square[i]);
    printf("\n");
}

bool myEqual(int *square, int length){
    return (square[0]+square[1]+square[2]+square[3] ==          square[4]+square[5]+square[6]+square[7]) && (square[0]+square[3]+square[4]+square[7] == square[1]+square[2]+square[5]+square[6]) && (square[2]+square[3]+square[6]+square[7] == square[0]+square[1]+square[4]+square[5]);
}

bool squarePlanEquelCore(int *square, int *square1, int index, int length){
    if (index == length) {
        if(myEqual(square, length)){
            printMyArray(square, length);
            return true;
        }
    }else{
        for(int cur = index; cur < length; cur++){
            int temp = square1[cur];
            square1[cur] = square1[index];
            square1[index] = temp;
            squarePlanEquelCore(square, square1, ++index, length);
            --index;
            temp = square1[cur];
            square1[cur] = square1[index];
            square1[index] = temp;
        }
    }
    return false;
}
bool squarePlanEqual(int *square, int length){
    if (square == nullptr) {
        return false;
    }
    int index = 0;
    return squarePlanEquelCore(square, square, index, length);
}

#pragma mark 国际象棋皇后问题
bool check(int **Chesshold, int length, int row, int col){
    if(row == 0) return true;
    //每列只能放一个皇后
    for(int i = 0; i != row; ++i){
        if(Chesshold[i][col] == 1)
            return false;
    }
    //每行只能放一个皇后
    for(int j = 0; j != col; ++j){
        if (Chesshold[row][j] == 1)
            return false;
    }
    //左上角
    for(int i = row-1, j = col-1; i>=0&&j>=0; --i, --j){
        if (Chesshold[i][j] == 1) {
            return false;
        }
    }
    //右上角
    for(int i = row-1, j = col+1; i>=0&&j!=length; --i, ++j){
        if (Chesshold[i][j] == 1) {
            return false;
        }
    }
    return true;
}

static int myCount = 0;
void printChesshold(int **Chesshold, int length){
    printf("%d\n", ++myCount); 
}

void solve(int **Chesshold, int length, int row){
    int col = 0;
    for (; col != length; ++col) {
        Chesshold[row][col] = 1;
        if (check(Chesshold, length, row, col)) {
            if (row == length-1) {
                printChesshold(Chesshold, length);
                printf("\n");
            }else{
                solve(Chesshold, length, (row+1));
            }
        }
        Chesshold[row][col] = 0;
    }
}

void nqueen(int **Chesshold, int length){
    if (Chesshold == nullptr) {
        return;
    }
    int row = 0;
    solve(Chesshold, length, row);
}


#pragma mark - 21 调整数组使奇数位于偶数前面
#pragma mark 时间复杂度O(n)，空间复杂度O(1)
bool isOdd(int *data, unsigned int length, int index);
void ReorderOddEvent(int *data, unsigned int length){
    if (data == nullptr || length < 0) {
        return;
    }
    int front = 0;
    int back  = length - 1;
    while (front < back) {
        
        while (front < back && !isOdd(data, length, front)){
            front++;
        }
        while (front < back && isOdd(data, length, back)){
            back--;
        }
        if (front < back){
            Swap(&data[front], &data[back]);
        }
    }
}

bool isOdd(int *data, unsigned int length, int index){
    return (data[index]%2) == 0;
}

void printArray(int *data, int length){
    for(int i = 0; i < length; ++i)
        printf("%d", data[i]);
    printf("\n");
}
void ReorderOddEventTest(int *data, int length){
    ReorderOddEvent(data, length);
    printArray(data, length);
}


#pragma mark - 29 顺时针打印矩阵
void printMatrixInCircle(int **numbers, int rows, int cols, int start);
void printMatrixInClock(int ** numbers, int rows, int cols){
    if (numbers == nullptr || rows <= 0 ||cols <= 0) {
        return;
    }
    int start = 0;
    while (rows > start * 2 && cols > start * 2) {
        printMatrixInCircle(numbers, rows, cols, start);
        ++start;
    }
}
void printMatrixInCircle(int **numbers, int rows, int cols, int start){
    int endX = cols - 1 - start;
    int endY = rows - 1 - start;

    //print left to right
    for(int currentCol = start; currentCol <= endX; ++currentCol){
        int number = numbers[start][currentCol];
        printf("%d ",number);
    }

    //print top to bottom
    if(start < endY){
        for(int currentRow = start+1; currentRow <= endY; ++currentRow){
            int number = numbers[currentRow][endX];
            printf("%d ", number);
        }
    }
    
    //print right to left
    if (start < endX && start < endY) {
        for(int currenttRtL = endX-1; currenttRtL >= start; --currenttRtL){
            int number = numbers[endY][currenttRtL];
            printf("%d ", number);
        }
    }

    if (start < endX && start < endY-1) {
        //print bottom to top
        for(int i = endY-1; i >= start+1; --i){
            int number = numbers[i][start];
            printf("%d ", number);
        }
    }


}

#pragma mark - 包含min函数的栈，使用模版类
template <typename T> class StackWithMin{
public:
    StackWithMin(){}
    virtual ~StackWithMin(){}
    
    T& top();
    const T& top() const;
    
    void push(const T& value);
    void pop();
    
    const T& min() const;
    
    bool empty() const;
    size_t size() const;
    
private:
    std::stack<T> m_data;
    std::stack<T> m_min;
};

template <typename T> void StackWithMin<T>::push(const T& value){
    m_data.push(value);
    if (m_min.size() == 0 || value < m_min.top()) {
        m_min.push(value);
    }else{
        m_min.push(m_min.top());
    }
}

template <typename T> void StackWithMin<T>::pop(){
    assert(m_data.size()>0 && m_min.size() > 0);
    m_data.pop();
    m_min.pop();
}

template <typename T> const T& StackWithMin<T>::min() const{
    assert(m_data.size() > 0 && m_min.size() > 0);
    return m_min.top();
}

template <typename T> T& StackWithMin<T>::top(){
    return m_data.top();
}

template <typename T> const T& StackWithMin<T>::top() const
{
    return m_data.top();
}

template <typename T> bool StackWithMin<T>::empty() const
{
    return m_data.empty();
}

template <typename T> size_t StackWithMin<T>::size() const
{
    return m_data.size();
}

#pragma mark - 栈的压入、弹出序列
bool isPopOrder(const int *push, const int *pop, int length){
    if (push == nullptr || pop == nullptr || length < 0) {
        return false;
    }
    const int *nextPush = push;
    const int *nextPop = pop;
    
    std::stack<int> stack;
    
    while (nextPop - pop < length) {
        while (stack.empty() || *nextPop != stack.top()) {
            if (nextPush - push == length) {
                break;
            }
            stack.push(*nextPush);
            nextPush++;
        }
        
        if (*nextPop != stack.top()) {
            break;
        }
        
        stack.pop();
        nextPop++;
    }
    
    if (stack.empty() && nextPop - pop == length) {
        return true;
    }
    return false;
}

#pragma mark - 数组中出现次数超过一半的数字
/*
 题目分析：既然是超过一半那么数组的length必须为奇数
 题目解析：
 方法一：
 1.排序
 2.找出中位数
 方法二：
 遍历数组，如果相等count++，不想等--，
 */

int myRandom(int start, int end){
    return rand()%(end-start+1)+start;
}

int myPartition(int *data, int length, int start, int end){
    int index = myRandom(start, end);
    swap(data[index], data[end]);
    int small = start-1;
    for(int index = start; index < length; index++){
        if (data[index] < data[end]) {
            small++;
            if (small != index) {
                swap(data[index], data[small]);
            }
        }
    }
    small++;
    swap(data[small], data[end]);
    return small;
}

void myQuickSort(int *data, int length, int start, int end){
    if (data == NULL || length < 0) {
        return;
    }
    if (start > end) {
        return;
    }
    int index = myPartition(data, length, start, end);
    if (index > start) {
        myQuickSort(data, length, start, index-1);
    }
    if (index < end) {
        myQuickSort(data, length, index+1, end);
    }
}

void getTheMoreThenHalfNumber(int *data, int length){
    if (data == NULL || length < 0) {
        return;
    }
    myQuickSort(data, length, 0, length-1);
    printf("getTheMoreThenHalfNumber is %d \n", data[(int)floor((length-0)/2)]);
}

void getTheMoreThanHalfNumber2(int *data, int length){
    if (data == NULL || length < 0) {
        return;
    }
    int cur = data[0];
    unsigned int count = 1;
    for(int i = 1; i < length; ++i){
        if (cur == data[i]) {
            count++;
        }else{
            count--;
            if (count == 0) {
                cur = data[i];
                count = 1;
            }
        }
    }
    printf("getTheMoreThanHalfNumber2  %d \n", count>0?cur:-1);
}

#pragma mark - 40 最小的k个数
/*
 堆排序
 */

struct Node{
    int x,y;
    Node(int a = 0,int b = 0): x(a), y(b){};
};
bool operator> (Node a, Node b){
    if (a.x == b.x) {
        return a.y > b.y;
    }
    return a.x > b.x;
}

vector<Node> getTheKNumber(vector<Node> &data, int k){
    vector<Node> res;
    if (data.size() <= 0) {
        return res;
    }
    //使用优先级队列，启底层试用对来实现的
    //大顶堆
    priority_queue<Node, vector<Node>, greater<Node>> kths;
    for(int i = 0; i < k; ++i){
        kths.push(data[i]);
    }
    for(int i = k; i < data.size(); ++i){
        if (data[i] > kths.top()) {
            kths.pop();
            kths.push(data[i]);
        }
    }
    for(int i = 0; i<k; ++i){
        res.push_back(kths.top());
        kths.pop();
    }
    
    return  res;
}

#pragma mark - 41 数据流中的中位数，思路同上利用推排序
/*
 细节讨论：
 1.首先要保证的是数据要平均分配max.size()-min.size()<=1
 2.当 (min.size()+max.size())&1==0时，将数据放入min中，否则放入max中
 */
template<typename T> class dynamicArray{
public:
    void insert(T num){
        if (((min.size()+max.size())&1)==0) {//偶数个
            if (max.size()>0&&num<max.top()) {
                max.push(num);
                num = max.top();
                max.pop();
            }
            min.push(num);
        }else{
            if (min.size()>0&&num>min.top()) {
                min.push(num);
                num = min.top();
                min.pop();
            }
            max.push(num);
        }
    }
    
    T getMedia(){
        int size = min.size()+max.size();
        if (size == 0) {
            @throw [NSException exceptionWithName:@"nil" reason:@"number is invalid" userInfo:nil];
        }
        T media = 0.0;
        if ((size&1) == 1) {
            media = min.top();
        }else{
            media = (min.top()+max.top())/2;
        }
        return media;
    }
private:
    priority_queue<T, vector<T>, greater<T>> min;
    priority_queue<T, vector<T>, less<T>> max;
};

#pragma mark - Test
void FindKthToTailTest();
void middleOfListTest();
void revertListTest();
void mergeTwoSortListTest();
void subTreeTest();
void startNodeOfLoopTest();
void mirrorBinaryTreeTest();
void isSymmetricalTest();
void verifySequenceOfBSTTest();
void pathOfBinaryTreeTest();
void convertNodeToListTest();
void serializeOrDeserializeTest();
void printMatrixTest();
void stackWitMinTest();
void isPopOrderTest();
void complexListCopyTest();
void printAllStrTest();
void printAllStr1Test();
void squarePlanEqualTest();
void nqueenTest();
void getTheMoreThanHalfNumber2Test();
void getTheKNumberTest();
void getMediaTest();

#pragma mark - main
int main(int argc, const char * argv[]) {
    @autoreleasepool {
        // insert code here...
        NSLog(@"Hello, World!");
        
        //数组中出现多次的数据：解法一
        int data[6] = {1, 2, 3, 4, 2, 3};
        std::vector<int> res = appearMoreThanOnceNum(data, 6);
        for(std::vector<int>::iterator ret = res.begin(); ret != res.end(); ret++){
            NSLog(@"appear more than once %d", *ret);
        }
        //数组中出现多次的数据：解法二
        int m_dupli = -1;
        if (duplicate(data, 6, &m_dupli)) {
            NSLog(@"duplicate numern %d", m_dupli);
        }
        //数组中出现多次的数字：解法三
        NSLog(@"duplicate numern function 3 %d", duplicate2(data, 6));
        
        //正整数数组中，重复出现的数字
        int dataDuplicate[8] = {2,3,4,5,2,6,7,8};
        int temp = findNumAppearMoreThanOnce(dataDuplicate, 8);
        printf("duplicate numern function 4 %d\n", temp);
        printf("duplicate number funcinot 4 %d\n", findNumAppearMoreThanOnce1(dataDuplicate, 8));
        
        //二维数组中查找数字
        int matrix[][4] = {{1,2,8,9},{2,4,9,12},{4,7,10,13},{6,8,11,15}};
        bool finded = findNumInMatrix((int *)matrix, 4, 4, 20);
        NSLog(@"find in matrix is %d", finded);
        
        //替换字符串中的空格
        const int strLen = 100;
        char string[strLen] = "I'm a student";
        replaceBlank(string, (int)strlen(string));
        NSLog(@"string is %s", string);
        
        //从尾到头打印列表
        ListNode *head = createListWithNumber(5);
        printListFromTrail(head);
        printListFromTrail_1(head);
        
        //重建二叉树
        int preOrder[8] = {1,2,4,7,3,5,6,8};
        int  inOrder[8] = {4,7,2,1,5,3,8,6};
        
        BinaryTreeNode *root = Construct(preOrder, inOrder, 8);
        printBinaryTree(root);
        printBinaryTreeLevel(root);
        printBinaryTreeWithZ(root);

        //二叉树的下一个节点
        BinaryTreeNode * node = getNext(root);
        printf("get Next node %d \n", node->m_nValue);
        node = getNext(root->m_pLeft->m_pLeft->m_pRight);
        printf("get Next node %d \n", node->m_nValue);
        node = getNext(root->m_pRight->m_pRight);
        printf("get Next node %d \n", node?node->m_nValue:0);
        
        //双栈实现队列
        CQueue<char> queue;
        queue.appendTail('a');
        queue.appendTail('b');
        queue.appendTail('c');
        printf("queue head %c \n", queue.deleteHead());
        printf("queue head %c \n", queue.deleteHead());
        printf("queue head %c \n", queue.deleteHead());
        
        //求斐波那契数列的第n项
        double start = CFAbsoluteTimeGetCurrent();
        printf("Fibonacci %d %lld\n ", 45, Fibonacci2(45));//1134903170
        double end = CFAbsoluteTimeGetCurrent();
        printf("cost time %f ms\n", (end - start) * 1000);
        
        //快速排序
        int quickData[8] = {3,1,2,7,6,5,4,0};
        QuickSort(quickData, 8, 0, 7);
        printf("queickData \n");
        for(int i = 0; i < 8; i++){
            printf("%d", quickData[i]);
        }
        printf("\nqueickData \n");
        
        //二分查找
        int halfData[10] = {1,3,7,9,11,23,44,55,79,88};
        printf("haleData %d \n", halfFind(halfData, 10, 3));
        
        //旋转数组
        int minData[5] = {3,4,5,1,2};
        printf("rotate data array min %d \n", Min(minData, 5));
        
        //圆圈中最后剩下的数
        int lastRemainData[3] = {1,2,3};
        printf("lastRemainData is %d \n", lastRemainNum(lastRemainData, 3, 3));
        printf("the lastRemainData is %d \n", theLastRemainNum(6, 3));
        
        
        //矩阵中的路径
        const char* findMatrix = "ABTGCFCSJDEH";
        const char* str = "BFCEF";
        printf("hasPath %d \n", hasPath(findMatrix, 3, 4, str));
        
        //机器人可能走到的格子
        printf("the sum of Robot %d \n", roboot(1, 10, 10));
        
        //解绳子
        double start_1 = CFAbsoluteTimeGetCurrent();
        printf("the max multy %d \n", maxProduct(20));
        double end1_1 = CFAbsoluteTimeGetCurrent();
        printf("cost time %f ms\n", (end1_1 - start_1) * 1000);
        
        printf("the max multy %d \n", maxProduct1(20));
        double end2_1 = CFAbsoluteTimeGetCurrent();
        printf("cost time %f ms\n", (end2_1 - end1_1) * 1000);
        
        //the number of 1
        double start_2 = CFAbsoluteTimeGetCurrent();
        printf("the number of 1 %d \n", countOf1_function1(999999999));
        double end_2 = CFAbsoluteTimeGetCurrent();
        printf("cost time %f ms\n", (end_2 - start_2) * 1000);
        printf("the number of 1 %d \n", countOf1_function2(999999999));
        double end_3 = CFAbsoluteTimeGetCurrent();
        printf("cost time %f ms\n", (end_3 - end_2) * 1000);
        
        //find the number apper once
        int appearOnceData[7] = {1,1,2,2,4,5,5};
        printf("find the number appear once %d \n", findNumAppearOnce(appearOnceData, 7));
        
        //find the nums appear once
        int appearNumsAppearOnce[6] = {4, 6, 1, 1, 1, 1};
        int num1 = 0;
        int num2 = 0;
        findNumsAppearOnce(appearNumsAppearOnce, 6, &num1, &num2);
        printf("appearNumsAppearOnce %d %d \n", num1, num2);
        
        //不用加减乘除做加法
        printf("Add %d \n", Add(8, 9));
        
        //数据的整数次方
        printf("MyPower %f \n", MyPower(9, 3));
        
        //打印从1到最大的n位数
        print1ToMaxOfNDigits(3);
        print1ToMaxOfNDigits1(3);
        print1ToMaxOfNDigits2(3);
        printf("\n");
        
        //delete Node
        ListNode *head_1 = createNode(1);
        ListNode *node1 = createNode(2);
        ListNode *node2 = createNode(3);
        ListNode *node3 = createNode(4);
        
        connectList(head_1, node1);
        connectList(node1, node2);
        connectList(node2, node3);
        
//        deleteNode(&head_1, head_1);
        deleteNode(&head_1, node2);
//        deleteNode(&head_1, node3);
        
        ListNode *head_2 = createNode(1);
        ListNode *node2_1 = createNode(2);
        ListNode *node2_2 = createNode(2);
        ListNode *node2_3 = createNode(3);
        ListNode *node2_4 = createNode(4);
        ListNode *node2_5 = createNode(4);
        ListNode *node2_6 = createNode(5);
        
        connectList(head_2, node2_1);
        connectList(node2_1, node2_2);
        connectList(node2_2, node2_3);
        connectList(node2_3, node2_4);
        connectList(node2_4, node2_5);
        connectList(node2_5, node2_6);
        
        deleteDeplication(&head_2);
        ListNode *current = head_2;
        while (current) {
            printf("%d ", current->value);
            current = current->next;
        }
        
        char matchStr[]    = "aaa";
        char patternStr1[] = "aa*a";
        char patternStr2[] = "a.a";
        char patternStr3[] = "ab*ab*a";
        printf("pattentStr1 match %d \n",match(matchStr, patternStr1));
        printf("pattentStr1 match %d \n",match(matchStr, patternStr2));
        printf("pattentStr1 match %d \n",match(matchStr, patternStr3));
        
        //正则表达式
        Test("Test01", "", "", true);
        Test("Test02", "", ".*", true);
        Test("Test03", "", ".", false);
        Test("Test04", "", "c*", true);
        Test("Test05", "a", ".*", true);
        Test("Test06", "a", "a.", false);
        Test("Test07", "a", "", false);
        Test("Test08", "a", ".", true);
        Test("Test09", "a", "ab*", true);
        Test("Test10", "a", "ab*a", false);
        Test("Test11", "aa", "aa", true);
        Test("Test12", "aa", "a*", true);
        Test("Test13", "aa", ".*", true);
        Test("Test14", "aa", ".", false);
        Test("Test15", "ab", ".*", true);
        Test("Test16", "ab", ".*", true);
        Test("Test17", "aaa", "aa*", true);
        Test("Test18", "aaa", "aa.a", false);
        Test("Test19", "aaa", "a.a", true);
        Test("Test20", "aaa", ".a", false);
        Test("Test21", "aaa", "a*a", true);
        Test("Test22", "aaa", "ab*a", false);
        Test("Test23", "aaa", "ab*ac*a", true);
        Test("Test24", "aaa", "ab*a*c*a", true);
        Test("Test25", "aaa", ".*", true);
        Test("Test26", "aab", "c*a*b", true);
        Test("Test27", "aaca", "ab*a*c*a", true);
        Test("Test28", "aaba", "ab*a*c*a", false);
        Test("Test29", "bbbba", ".*a*a", true);
        Test("Test30", "bcbbabab", ".*a*a", false);
        
        //有效数字
        isNumericTest("Test1", "100", true);
        isNumericTest("Test2", "123.45e+6", true);
        isNumericTest("Test3", "+500", true);
        isNumericTest("Test4", "5e2", true);
        isNumericTest("Test5", "3.1416", true);
        isNumericTest("Test6", "600.", true);
        isNumericTest("Test7", "-.123", true);
        isNumericTest("Test8", "-1E-16", true);
        isNumericTest("Test9", "1.79769313486232E+308", true);
        isNumericTest("Test10", "12e", false);
        isNumericTest("Test11", "1a3.14", false);
        isNumericTest("Test12", "1+23", false);
        isNumericTest("Test13", "1.2.3", false);
        isNumericTest("Test14", "+-5", false);
        isNumericTest("Test15", "12e+5.4", false);
        isNumericTest("Test16", ".", false);
        isNumericTest("Test17", ".e1", false);
        isNumericTest("Test18", "e1", false);
        isNumericTest("Test19", "+.", false);
        isNumericTest("Test20", "", false);
        isNumericTest("Test21", nullptr, false);
        
        int numbers1[] = {1, 2, 3, 4, 5, 6, 7};
        int numbers2[] = {2, 4, 6, 1, 3, 5, 7};
        int numbers3[] = {1, 3, 5, 7, 2, 4, 6};
        int numbers4[] = {1};
        int numbers5[] = {2};
        ReorderOddEventTest(numbers1,7);
        ReorderOddEventTest(numbers2,7);
        ReorderOddEventTest(numbers3,7);
        ReorderOddEventTest(numbers4,1);
        ReorderOddEventTest(numbers5,1);
        
        
        FindKthToTailTest();
        
        middleOfListTest();
        
        revertListTest();
        
        mergeTwoSortListTest();
        
        subTreeTest();
        
        startNodeOfLoopTest();
        
        mirrorBinaryTreeTest();
        
        isSymmetricalTest();
        
        verifySequenceOfBSTTest();
        
        pathOfBinaryTreeTest();
        
        convertNodeToListTest();
        
        printMatrixTest();
        
        stackWitMinTest();
        
        isPopOrderTest();
        
        complexListCopyTest();
        
        printAllStrTest();
        
        printAllStr1Test();
        
        squarePlanEqualTest();
        
        nqueenTest();
        
        getTheMoreThanHalfNumber2Test();
        
        getTheKNumberTest();
        
        getMediaTest();
    }
    
    return 0;
}

void printList(ListNode *head){
    while (head != nullptr) {
        printf("%d ", head->value);
        head = head->next;
    }
    printf("\n");
}

void FindKthToTailTest(){
    ListNode* pNode1 = createNode(1);
    ListNode* pNode2 = createNode(2);
    ListNode* pNode3 = createNode(3);
    ListNode* pNode4 = createNode(4);
    ListNode* pNode5 = createNode(5);

    connectList(pNode1, pNode2);
    connectList(pNode2, pNode3);
    connectList(pNode3, pNode4);
    connectList(pNode4, pNode5);
    
    ListNode *pNode = FindKthToTail(pNode1, 1);
    printf("pNode %d \n", pNode->value);
    ListNode *pNode_1 = FindKthToTail(pNode1, 5);
    printf("pNode %d \n", pNode_1->value);
    ListNode *pNode_2 = FindKthToTail(pNode1, 100);
    printf("pNode %d \n", pNode_2?pNode_2->value:-1);
    ListNode *pNode_3 = FindKthToTail(pNode1, 0);
    printf("pNode %d \n", pNode_3?pNode_3->value:-1);
}

void middleOfListTest(){
    ListNode* pNode1 = createNode(1);
    ListNode* pNode2 = createNode(2);
    ListNode* pNode3 = createNode(3);
    ListNode* pNode4 = createNode(4);
    ListNode* pNode5 = createNode(5);
    ListNode* pNode6 = createNode(6);

    connectList(pNode1, pNode2);
    connectList(pNode2, pNode3);
    connectList(pNode3, pNode4);
    connectList(pNode4, pNode5);
    connectList(pNode5, pNode6);

    ListNode *node_1 = middleOfList(pNode1);
    printf("pNode %d \n", node_1?node_1->value:-1);
}


void revertListTest(){
    ListNode* pNode1 = createNode(1);
    ListNode* pNode2 = createNode(2);
    ListNode* pNode3 = createNode(3);
    ListNode* pNode4 = createNode(4);
    ListNode* pNode5 = createNode(5);
    ListNode* pNode6 = createNode(6);

    connectList(pNode1, pNode2);
    connectList(pNode2, pNode3);
    connectList(pNode3, pNode4);
    connectList(pNode4, pNode5);
    connectList(pNode5, pNode6);

    revertList(pNode1);
    printList(pNode6);
}

void mergeTwoSortListTest(){
    ListNode* pNode1_1 = createNode(1);
    ListNode* pNode1_2 = createNode(3);
    ListNode* pNode1_3 = createNode(5);
    ListNode* pNode1_4 = createNode(7);
    ListNode* pNode1_5 = createNode(9);
    ListNode* pNode1_6 = createNode(11);

    connectList(pNode1_1, pNode1_2);
    connectList(pNode1_2, pNode1_3);
    connectList(pNode1_3, pNode1_4);
    connectList(pNode1_4, pNode1_5);
    connectList(pNode1_5, pNode1_6);
    
    
    ListNode* pNode2_1 = createNode(2);
    ListNode* pNode2_2 = createNode(3);
    ListNode* pNode2_3 = createNode(4);
    ListNode* pNode2_4 = createNode(6);
    ListNode* pNode2_5 = createNode(7);
    ListNode* pNode2_6 = createNode(8);

    connectList(pNode2_1, pNode2_2);
    connectList(pNode2_2, pNode2_3);
    connectList(pNode2_3, pNode2_4);
    connectList(pNode2_4, pNode2_5);
    connectList(pNode2_5, pNode2_6);
    
    mergeTwoSortList(pNode1_1, pNode2_1);
    printList(pNode1_1);
}

void subTreeTest(){
    BinaryTreeNode *root = createBinaryTree(1);
    BinaryTreeNode *left1 = createBinaryTree(2);
    BinaryTreeNode *right1 = createBinaryTree(3);
    BinaryTreeNode *left1_1 = createBinaryTree(4);
    BinaryTreeNode *right1_1 = createBinaryTree(5);
    BinaryTreeNode *right1_2 = createBinaryTree(6);
    
    connectBinaryTree(root, left1, right1);
    connectBinaryTree(left1, left1_1, nullptr);
    connectBinaryTree(right1, right1_1, right1_2);
    
    BinaryTreeNode *root2 = createBinaryTree(3);
    BinaryTreeNode *left2_1 = createBinaryTree(5);
    BinaryTreeNode *right2_1 = createBinaryTree(6);
    connectBinaryTree(root2, left2_1, right2_1);
    
    printf("has sub tree %d \n", HasSubTree(root, root2));
}
void startNodeOfLoopTest(){
    ListNode *head = createNode(1);
    ListNode *node1 = createNode(2);
    ListNode *node2 = createNode(3);
    ListNode *node3 = createNode(4);
    ListNode *node4 = createNode(5);
    ListNode *node5 = createNode(6);
    ListNode *node6 = createNode(7);
    ListNode *node7 = createNode(8);
    ListNode *node8 = createNode(9);
    node8->next = node3;
    
    connectList(head, node1);
    connectList(node1, node2);
    connectList(node2, node3);
    connectList(node3, node4);
    connectList(node4, node5);
    connectList(node5, node6);
    connectList(node6, node7);
    connectList(node7, node8);
    connectList(node8, node4);
    
    printf("start node %d \n", startNodeOfLoop(head)->value);
}

void mirrorBinaryTreeTest(){
    BinaryTreeNode *root = createBinaryTree(1);
    BinaryTreeNode *left1 = createBinaryTree(2);
    BinaryTreeNode *right1 = createBinaryTree(3);
    BinaryTreeNode *left1_1 = createBinaryTree(4);
    BinaryTreeNode *right1_1 = createBinaryTree(5);
    BinaryTreeNode *right1_2 = createBinaryTree(6);
    
    connectBinaryTree(root, left1, right1);
    connectBinaryTree(left1, left1_1, nullptr);
    connectBinaryTree(right1, right1_1, right1_2);
    
    printBinaryTreeLevel(root);
    MirrorBinaryTree(root);
    printBinaryTreeLevel(root);
}

void isSymmetricalTest(){
    BinaryTreeNode *root = createBinaryTree(1);
    BinaryTreeNode *node61 = createBinaryTree(6);
    BinaryTreeNode *node62 = createBinaryTree(6);
    BinaryTreeNode *node51 = createBinaryTree(5);
    BinaryTreeNode *node71 = createBinaryTree(7);
    BinaryTreeNode *node72 = createBinaryTree(7);
    BinaryTreeNode *node52 = createBinaryTree(5);

    connectBinaryTree(root, node61, node62);
    connectBinaryTree(node61, node51, node71);
    connectBinaryTree(node62, node72, node52);
    
    printf("tree is %s Symmetrical tree \n", isSymmetrical(root)?"":"not");
}

void verifySequenceOfBSTTest(){
    int data[7] = {5,7,6,9,11,10,8};
    printf("sequence is %s BST of tree \n", verifySequenceOfBST(data, 7)?"":"not");
}

void pathOfBinaryTreeTest(){
    BinaryTreeNode *root = createBinaryTree(1);
    BinaryTreeNode *node61 = createBinaryTree(2);
    BinaryTreeNode *node62 = createBinaryTree(3);
    BinaryTreeNode *node51 = createBinaryTree(4);
    BinaryTreeNode *node71 = createBinaryTree(5);

    connectBinaryTree(root, nullptr, node61);
    connectBinaryTree(node61, nullptr, node62);
    connectBinaryTree(node62, nullptr, node51);
    connectBinaryTree(node51, nullptr, node71);
    
    pathOfBinaryTree(root, 15);
    printf("\n");
}

void convertNodeToListTest(){
    BinaryTreeNode *root = createBinaryTree(10);
    
    BinaryTreeNode *left1 = createBinaryTree(6);
    BinaryTreeNode *right1 = createBinaryTree(14);
    
    BinaryTreeNode *left1_1 = createBinaryTree(4);
    BinaryTreeNode *left1_2 = createBinaryTree(8);
    
    BinaryTreeNode *right1_1 = createBinaryTree(12);
    BinaryTreeNode *right1_2 = createBinaryTree(16);

    connectBinaryTree(root, left1, right1);
    connectBinaryTree(left1, left1_1, left1_2);
    connectBinaryTree(right1, right1_1, right1_2);

    BinaryTreeNode *List = convertNotToList(root);
    while (List) {
        printf("%d ", List->m_nValue);
        List=List->m_pRight;
    }
    printf("\n");
}

void TestPrintMatrix(int columns, int rows)
{
    printf("Test Begin: %d columns, %d rows.\n", columns, rows);

    if(columns <= 0 || rows <= 0)
        return;

    int** numbers = new int*[rows];
    for(int i = 0; i < rows; ++i)
    {
        numbers[i] = new int[columns];
        for(int j = 0; j < columns; ++j)
        {
            numbers[i][j] = i * columns + j + 1;
        }
    }

    printMatrixInClock(numbers, rows, columns);
    printf("\n");

    for(int i = 0; i < rows; ++i)
        delete[] (int*)numbers[i];

    delete[] numbers;
}
void printMatrixTest(){
    TestPrintMatrix(5,5);
    TestPrintMatrix(2,2);
    TestPrintMatrix(3,3);
    TestPrintMatrix(1,1);
    TestPrintMatrix(1,5);
}

void stackWitMinTest(){
    StackWithMin<int> stack;
    
    stack.push(3);
    printf("%d ", stack.min());
    
    stack.push(4);
    printf("%d ", stack.min());
    
    stack.push(5);
    printf("%d ", stack.min());
    
    stack.push(2);
    printf("%d ", stack.min());
    
    stack.push(6);
    printf("%d ", stack.min());
    
    printf("\n");
}

void isPopOrderTest(){
    int push[5] = {1,2,3,4,5};
    int pop1[5] = {4,5,3,2,1};
    int pop2[5] = {4,3,5,1,2};
    printf("isPopOrder %d \n", isPopOrder(push, pop1, 5));
    printf("isPopOrder %d \n", isPopOrder(push, pop2, 5));
}

void Test1(){
    ListNode *node0 = createNode(0);
    ListNode *node1 = createNode(1);
    ListNode *node2 = createNode(2);
    ListNode *node3 = createNode(3);
    ListNode *node4 = createNode(4);
    ListNode *node5 = createNode(5);
    ListNode *node6 = createNode(6);
    
    connectList(node0, node1); node0->m_pSibling = node3; //(0,1,3)
    connectList(node1, node2); node1->m_pSibling = node5; //(1,2,5)
    connectList(node2, node3); node2->m_pSibling = node5; //(2,3,5)
    connectList(node3, node4); node3->m_pSibling = node5; //(3,4,5)
    connectList(node4, node5); node4->m_pSibling = node2; //(4,5,2)
    connectList(node5, node6); node5->m_pSibling = node3; //(5,6,3)
                               node6->m_pSibling = node3; //(6,0,3)
    

    ListNode *cpNode = complexListCopy(node0);
    while (cpNode != nullptr) {
        printf("%d %d %d \n", cpNode->value, cpNode->next?cpNode->next->value:0, cpNode->m_pSibling->value);
        cpNode = cpNode->next;
    }
}

void Test2(){
    
    ListNode *node0 = createNode(0);
    ListNode *node1 = createNode(1);
    ListNode *node2 = createNode(2);
    ListNode *node3 = createNode(3);
    ListNode *node4 = createNode(4);
    
    connectList(node0, node1);  //(0,1,0)
    connectList(node1, node2); node1->m_pSibling = node3; //(1,2,3)
    connectList(node2, node3);  //(2,3,0)
    connectList(node3, node4); node3->m_pSibling = node2; //(3,4,2)
                                                          //(4,0,0)
    
    ListNode *cpNode = complexListCopy(node0);
    while (cpNode != nullptr) {
        printf("%d %d %d \n", cpNode?cpNode->value:0, cpNode->next?cpNode->next->value:0, cpNode->m_pSibling?cpNode->m_pSibling->value:0);
        cpNode = cpNode->next;
    }
}

void Test3(){
    ListNode *node0 = nullptr;
    ListNode *cpNode = complexListCopy(node0);
    while (cpNode != nullptr) {
        printf("%d %d %d \n", cpNode?cpNode->value:0, cpNode->next?cpNode->next->value:0, cpNode->m_pSibling?cpNode->m_pSibling->value:0);
        cpNode = cpNode->next;
    }
}

void Test4(){
    ListNode *node0 = createNode(0);
    connectList(node0, nullptr); node0->m_pSibling = node0;  //(0,0,0)
    ListNode *cpNode = complexListCopy(node0);
    while (cpNode != nullptr) {
        printf("%d %d %d \n", cpNode?cpNode->value:0, cpNode->next?cpNode->next->value:0, cpNode->m_pSibling?cpNode->m_pSibling->value:0);
        cpNode = cpNode->next;
    }
}

void complexListCopyTest(){
 
    Test1();
    printf("\n");
    Test2();
    printf("\n");
    Test3();
    printf("\n");
    Test4();
}

void printAllStrTest(){
    char str1[] = "abcd";
    printAllStr(str1);
}


void printAllStr1Test(){
    char str[4] = "abc";
    combination(str);
}

void squarePlanEqualTest(){
    int square[8] = {2,4,6,8,1,3,5,7};
    squarePlanEqual(square, 8);
}


void nqueenTest(){
    const int N = 8;
    int **rows = new int*[N];
    for(int i = 0; i < N; ++i){
        rows[i] = new int[N];
        for(int j = 0; j < N; ++j)
        {
            rows[i][j] = 0;
        }
    }
    nqueen(rows, N);
    for(int i = 0; i < N; ++i)
        delete [] (int *)rows[i];
    delete [] rows;
}

void getTheMoreThanHalfNumber2Test(){
    int data[9] = {2,3,4,5,2,2,2,2,4};
    getTheMoreThanHalfNumber2(data, 8);
    getTheMoreThenHalfNumber(data, 8);
}

void getTheKNumberTest(){
    vector<Node> data;
    for(int i = 0; i < 100; i++){
        Node node;
        node.x = myRandom(1, 100); node.y = myRandom(1, 100);
        data.push_back(node);
    }
    vector<Node> cur = getTheKNumber(data, 5);
    vector<Node>::iterator ite = cur.begin();
    for(;ite != cur.end(); ite++){
        printf("%d ", (*ite).x);
    }
    printf("\n");
}

void getMediaTest(){
    dynamicArray<double> numbsers;
//    try {
//        numbsers.getMedia();
//        printf("FAILED. \n");
//    } catch (const exception&) {
//        printf("Passed.\n");
//    }
    numbsers.insert(5);
    printf("median %.2f \n", numbsers.getMedia());
    numbsers.insert(2);
    printf("median %.2f \n", numbsers.getMedia());
    numbsers.insert(3);
    printf("median %.2f \n", numbsers.getMedia());
    numbsers.insert(4);
    printf("median %.2f \n", numbsers.getMedia());
    numbsers.insert(1);
    printf("median %.2f \n", numbsers.getMedia());
    numbsers.insert(6);
    printf("median %.2f \n", numbsers.getMedia());
    numbsers.insert(7);
    printf("median %.2f \n", numbsers.getMedia());
    numbsers.insert(0);
    printf("median %.2f \n", numbsers.getMedia());
    numbsers.insert(8);
    printf("median %.2f \n", numbsers.getMedia());
}
