//
//  main.m
//  Myalgorithm
//
//  Created by sunjian on 2020/8/21.
//  Copyright © 2020 sjuinan. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <vector>
#import <queue>
#include <cstdio>
#include <algorithm>
#include <functional>
#include <exception>
#include <list>
#include <map>
#include <stack>

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

#pragma mark - 从尾到头打印列表
struct ListNode{
    int value;
    ListNode *next;
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
#pragma mark 有关二叉搜索树的题目33、36
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
void connectBinaryTree(BinaryTreeNode *root, BinaryTreeNode *left, BinaryTreeNode *right){
    if (root) {
        root->m_pLeft = left;
        root->m_pRight = right;
    }
}
BinaryTreeNode* ConstructCore(int* startPreorder, int* endPreorder, int* startInorder, int* endInorder);

#pragma mark - 重建二叉树，通过给定的前序遍历序列和中序遍历序列，重建二叉树，并输出根节点
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

#pragma mark - 不分行打印二叉树
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

#pragma mark - 分行打印二叉树(双向队列)
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

#pragma mark - 之字形打印二叉树(双栈)
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

#pragma mark - 二叉树的下一个节点
#pragma mark 给定一个二叉树和其中一个节点，请找出中序遍历的下一个节点
/*
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
    if (index < start) {
        QuickSort(data, length, index + 1, length);
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
    }
    
    return 0;
}
