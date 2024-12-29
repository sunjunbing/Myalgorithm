//
//  main.cpp
//  C++_Algorithm_Other
//
//  Created by sunjian on 2024/11/14.
//

#include <iostream>
#include <stack>
#include <vector>
#include <deque>
#include <map>
#include <unordered_set>
#include <tuple>
#include <unordered_map>
#include <sstream>
#include <regex>
#include <string>

using namespace std;

template <typename T>
struct Display{
    void operator()(T& a){
        cout << a << ' ';
    }
};

/*
 锻炼自己的程序员思维，遇到问题解决方法的能力
 用两个栈实现队列，能够实现 appendTail 和 deleteHead
 move和右值引用的目的就是介绍不必要的拷贝
 */
template <typename T>
class StackQueue{
public:
    void appendTail(const T& element){
        stack1.push(element);
    }
    void deleteHead(){
        if (stack1.empty()) {
            while (!stack1.empty()) {
                stack2.push(stack1.top());
                stack1.pop();
            }
        }
        stack2.pop();
    }
private:
    stack<T> stack1 = stack<T>();
    stack<T> stack2 = stack<T>();
};
void test1(){
    
}

/*
 合并两个有序的数组
 */

void myMerge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    int li = 0, le = m;
    int ri = 0, re = n;
    int ai = 0;
    vector<int> leftArray(nums1.begin(),nums1.begin()+m);
    while(li < le){
        if(ri < re && nums2[ri] < leftArray[li]){
            nums1[ai++] = nums2[ri++];
        }else{
            nums1[ai++] = leftArray[li++];
        }
    }
    while(ri < re) {
        nums1[ai++] = nums2[ri++];
    }
}
void test2(){
    vector<int> num1 = {1,2,3,0,0,0};
    vector<int> num2 = {2,5,6};
    int m = 3, n = 3;
    myMerge(num1, m, num2, n);
    for_each(num1.begin(), num1.end(), Display<int>());
    cout << endl;
}

/*
 颜色分类
 */
void swap(int& n1, int& n2){
    auto temp = n1; n1 = n2; n2 = temp;
}
void sortColors(vector<int>& colors){
    if(colors.size() <= 0) return;
    int red = 0, white = 0, blue = (int)colors.size()-1;
    while (red <= blue) {
        if (colors[red] == 1) {
            red++;
        }else if(colors[red] == 0){
            swap(colors[red++], colors[white++]);
        }else if(colors[red] == 2){
            swap(colors[red], colors[blue--]);
        }
    }
}
void test3(){
    vector<int> colors{1,2,0};
    sortColors(colors);
    for_each(colors.begin(), colors.end(), Display<int>());
    cout << endl;
}

/*
 不分排序
 双指针
 */
vector<int> partSort(vector<int>& nums){
    if(nums.size() <= 1) return vector<int>{-1,-1};
    int begin = 0;
    int end = 0;
    int min = nums[(int)nums.size() - 1], max = nums[begin];
    for(int i = 1; i < (int)nums.size(); i++){
        if(nums[i] >= max){
            max = nums[i];
        }else{
            end = i;
        }
    }
    for(int i = (int)nums.size() - 2; i >= 0; i--){
        if(nums[i] <= min){
            min = nums[i];
        }else{
            begin = i;
        }
    }
    if(begin == end) return vector<int>{-1,-1};
    return vector<int>{begin, end};
}
void test4(){
    vector<int> nums = {1,2,4,7,10,11,7,12,6,7,16,18,19};
    nums = {1,3,9,7,5};
    auto ret = partSort(nums);
    for_each(ret.begin(), ret.end(), Display<int>());
    cout << endl;
}

/*
 两数相加
 给定两个列表，用来表示两个数，逆序表示，计算两个列表的和，放到一个新的列表中
 */
class ListNode{
public:
    int value;
    shared_ptr<ListNode> next;
    ListNode(int value):value(value), next(nullptr){}
    static void Display(shared_ptr<ListNode> node){
        while (node != nullptr) {
            cout << node->value << ' ';
            node = node->next;
        }
        cout << endl;
    }
};
inline void myCaculate(int& value, int& come){
    if (come > 0) {
        value += come; come = 0;
    }
    if (value >= 10) {
        come = 1;
        value = value%10;
    }
}
shared_ptr<ListNode> sum(shared_ptr<ListNode>& node1, shared_ptr<ListNode>& node2){
    if(node1 == nullptr) return node2;
    if(node2 == nullptr) return node1;
    auto sum = make_shared<ListNode>(-1);
    auto ret = sum;
    auto dummyNode1 = make_shared<ListNode>(-1);
    auto dummyNode2 = make_shared<ListNode>(-1);
    dummyNode1->next = node1;
    dummyNode2->next = node2;
    int come = 0;
    while (dummyNode1->next != nullptr) {
        if (dummyNode2->next != nullptr) {
            auto value = dummyNode1->next->value + dummyNode2->next->value;
            myCaculate(value, come);
            sum->next = make_shared<ListNode>(value);
            sum = sum->next;
            dummyNode2->next = dummyNode2->next->next;
            dummyNode1->next = dummyNode1->next->next;
        }else{
            if (dummyNode1->next != nullptr) {
                int value = dummyNode1->next->value;
                myCaculate(value, come);
                sum->next = make_shared<ListNode>(value);
                sum = sum->next;
            }
            dummyNode1->next = dummyNode1->next->next;
        }
    }
    while (dummyNode2->next != nullptr) {
        int value = dummyNode2->next->value;
        myCaculate(value, come);
        sum->next = make_shared<ListNode>(value);
        sum = sum->next;
        dummyNode2->next = dummyNode2->next->next;
    }
    if (come > 0) {
        sum->next = make_shared<ListNode>(come);
        come = 0;
    }
    return ret->next;
}
void test5(){
    auto node1 = make_shared<ListNode>(8);
    auto node2 = make_shared<ListNode>(9);
    auto node3 = make_shared<ListNode>(9);
    node1->next = node2;
    node2->next = node3;
    ListNode::Display(node1);
    
    auto node4 = make_shared<ListNode>(5);
    auto node5 = make_shared<ListNode>(6);
    auto node6 = make_shared<ListNode>(4);
    node4->next = node5;
    node5->next = node6;
    ListNode::Display(node4);
    
    auto ret = sum(node1, node4);
    ListNode::Display(ret);
}

/*
 最小栈
 */
class MinStack{
public:
    MinStack():normal(stack<int>()), min(stack<int>()){};
    
    void push(int val){
        normal.push(val);
        if (min.empty()) {
            min.push(val);
        }else{
            min.push(std::min(val, min.top()));
        }
    }
    
    void pop(){
        normal.pop();
        min.pop();
    }
    
    int top(){
        return normal.top();
    }
    
    int GetMin(){
        return min.top();
    }
    
private:
    stack<int> normal;
    stack<int> min;
};

/*
 滑动窗口的最大值
 */
void test6(){
    vector<int> nums= {14,2,27,-5,28,13,39};
    nums= {1,7,5,3,-3,-1,8,2};
    nums= {7,2,4};
    int k = 3;
    auto maxSlidingWindow = [](vector<int> nums, int k)->vector<int>{
        if(nums.size() == 0 || k < 1) return vector<int>();
        if(k == 1) return nums;
        vector<int> ret;//value
        deque<int> deque = {0};//index
        for(int i = 1; i < (int)nums.size(); i++){
            while (!deque.empty() && nums[deque.back()] <= nums[i]) {
                deque.pop_back();
            }
            deque.push_back(i);
            int w = i - k + 1;
            if(w < 0) continue;
            if (deque.front() < w) {
                deque.pop_front();
            }
            ret.push_back(nums[deque.front()]);
        }
        return ret;
    };
    vector<int> value = maxSlidingWindow(nums, k);
    for_each(value.begin(), value.end(), Display<int>());
    cout << endl;
}

/*
 字符串轮转
 */
void test7(){
    string s1 = "aa"; string s2 = "aba";
    auto isFlipedString = [](string s1, string s2)->bool{
        if(s1.length() < 0 || s2.length() < 0) return false;
        if(s1.length() == 0 && s2.length() == 0) return true;
        if(s1.length() > 0 && s2.length() == 0) return false;
        string temp = s1 + s1;
        auto pos = temp.find(s2);
        return pos == string::npos ? false : true;
    };
    cout << isFlipedString(s1, s2) << endl;
}

/*
 另一棵树的子树
 在剑指 offer 做过这道题
 1.两种方法，先序列化，在判断s2是否是s1的子数组
 2.递归，通过前序或中序判断是否相同
 */
class TreeNode {
public:
    int val;
    shared_ptr<TreeNode> left;
    shared_ptr<TreeNode> right;
    TreeNode(int val):val(val),left(nullptr),right(nullptr){}
};
bool dfs(TreeNode* s1, TreeNode* s2);
//bool check(TreeNode* s1, TreeNode* s2){//深度优先
//    if (s2 == nullptr && s1 == nullptr) {
//        return true;
//    }
//    if ((!s1 && s2) || (s1 && !s2) || s1->val != s2->val) {
//        return false;
//    }
//    return dfs(s1->left, s2->left) && dfs(s1->right, s2->right);
//}
//bool dfs(TreeNode* s1, TreeNode* s2){
//    if(!s2) return false;
//    return check(s1, s2) || dfs(s1->left, s2);// || dfs(s1->right, s2);
//}
//bool isSubtree(TreeNode* s1, TreeNode* s2) {
//    return dfs(s1, s2);
//}
string dfs1(shared_ptr<TreeNode> node){
    if(node==nullptr) return "#!";
    string str = "";
    auto temp = node->val;
    str += to_string(temp);
    str += "!";
    str += dfs1(node->left);
    str += dfs1(node->right);
    return str;
}

bool isSubTree2(shared_ptr<TreeNode>& s1, shared_ptr<TreeNode>& s2){
    string str1 = dfs1(s1);
    string str2 = dfs1(s2);
    auto pos = str1.find(str2);
    return pos != string::npos ? true : false;
}
void test8(){
    auto node1 = make_shared<TreeNode>(3);
    auto node2 = make_shared<TreeNode>(4);
    auto node3 = make_shared<TreeNode>(5);
    auto node4 = make_shared<TreeNode>(1);
    auto node5 = make_shared<TreeNode>(12);
    auto node5_1 = make_shared<TreeNode>(0);
    node1->left = node2;
    node1->right = node3;
    node2->left = node4;
    node2->right = node5;
//    node5->left = node5_1;

    auto node6 = make_shared<TreeNode>(2);
//    auto node7 = make_shared<TreeNode>(1);
//    auto node8 = make_shared<TreeNode>(2);
    
//    node6->left = node7;
//    node6->right= node8;

//    cout << isSubTree(node1, node6) << endl;
//    cout << isSubTree2(node1, node6) << endl;
}

/*
 有效的字符异位词
 这道题和 第一个只出现一次的字母相同
 题目的意思：
 组成单词字母的数量是相同的，但是位置不一定相同
 解法一：hash
 解法二：sort、 比较
 部分排序
 */
bool isAnagram(string s, string t){
    if(s.length() <= 0 || t.length() <= 0 || s.length() != t.length()) return false;
    map<int, int> map;
    int idx = 0; auto c = s[idx];
    while (c !=  '\0') {
        c = s[idx++];map[c-'a']++;
    }
    c = t[--(--idx)];
    while (c !=  '\0') {
        c = t[idx--];
        if(map[c-'a']>0)map[c-'a']--;
    }
    int sum = 0;
    for (auto it = map.begin(); it != map.end(); it++) {
        sum+= it->second;
    }
    return sum == 0;
}
void test9(){
    string s("anagram");
    string t("nagaram");
    cout << isAnagram(s, t) << endl;
}

/*
 无重复字符的最长子串:
 c++/python
 滑动窗口+hash
 */
int lenOfLongestSubStr(string s){
    if(s.length() == 0) return 0;
    int len = 0, left = 0;
    unordered_set<int> window;//底层实现是 hashTable
    for(int i = 0; i < s.length(); i++){
        while (window.find(s[i]) != window.end()) {
            window.erase(s[left]);
            left++;
        }
        len = max(len, i - left + 1);
        window.insert(s[i]);
    }
    return len;
}
void test10(){
    string s = "abcabcbb";
    s = "bbbbb";
    s = "pwwkew";
    s = "nfpdmpi";
    cout << lenOfLongestSubStr(s) << endl;
}

/*
 45.跳跃游戏2，这道题是55.跳跃游戏的升级版
 给定一个整数数组，从nums[0]开始，每次能跳跃nums[i]，
 返回到达nums[n-1]的最少跳跃次数
 */
int jump(vector<int>& nums){
    int maxPos = 0, n = (int)nums.size(), end = 0, step = 0;
    for (int i = 0; i < n - 1; ++i) {
        if (maxPos >= i) {
            maxPos = max(maxPos, i + nums[i]);
            if (i == end) {//到这就必须要往前跳了，这会明白了
                end = maxPos;
                ++step;
            }
        }
    }
    return step;
}
void test11(){
    vector<int> nums{2,3,1,2,4,2,3};
    cout <<  jump(nums) << endl;
}

/*
 H指数，至少有H篇论文被引用了不少于H次
 解法一：
    1.先排序，确定一共发表论文数量
    2.倒序 nums[i] > i
 */
int hIndex(vector<int>& citations) {
    if(citations.size() == 0) return 0;
    sort(citations.begin(), citations.end());
    int h = 0, i = (int)citations.size() - 1;
    while (i >= 0 && citations[i] > h) {
        h++;
        i--;
    }
    return h;
}
void test12(){
    vector<int> nums{3,0,6,1,5};
    cout <<  hIndex(nums) << endl;
}

/*
 O(1)时间插入、删除和获取随机元素，这不就是HastTable，
 1.hash函数
 2.扩容的问题
 */
class RandomizedSet{
public:
    RandomizedSet(){
    }
    bool insert(int val) {
        if(nums.find(val) == nums.end()) {
            nums.insert(val);
            return true;
        }
        return false;
    }
    
    bool remove(int val) {
        if (nums.find(val) != nums.end()) {
            nums.erase(val);
            return true;
        }
        return false;
    }
    
    int getRandom() {
        vector<int> temp(nums.begin(), nums.end());
        return temp.size() > 0 ? temp[rand()%temp.size()] : 0;
    }
private:
    vector<int> array;
    unordered_set<int> nums;
};
void test13(){
    RandomizedSet set;
    cout << set.insert(-1) << " "
         << set.remove(-2) << " "
         << set.insert(-2) << " "
         << set.getRandom() << " "
         << set.remove(-1) << " "
         << set.insert(-2) << " "
         << set.getRandom() << " "
         << endl;
}

/*
 除自身以外数组的乘积，在O(n)的时间复杂度内完成，也可以是多次循环
 那肯定需要借助额外的数据结构：
 1.两个数据结构，一个放前面的乘积，一个放后面的乘积
 */
vector<int> productExceptSelf(vector<int>& nums) {
    if(nums.size() == 0) return {};
    auto len = (int)nums.size();
    vector<int> left(len, 0), right(len, 0);
    left[0] = 1;
    for(int i = 1; i < len; i ++){
        left[i] = nums[i-1] * left[i-1];
    }
    right[len-1] = 1;
    for(int i = len-2; i >= 0; i--){
        right[i] = nums[i+1] * right[i+1];
    }
    vector<int> ret(len);
    for(int i = 0; i < len; i++){
        ret[i] = left[i] * right[i];
    }
    return ret;
}
void test14(){
    vector<int> nums{1,2,3,4};
    auto ret = productExceptSelf(nums);
    for_each(ret.begin(), ret.end(), Display<int>());
    cout << endl;
}


/*
 反转列表
 */
void reverseList(){
    shared_ptr<ListNode> head = make_shared<ListNode>(1);
    shared_ptr<ListNode> node1 = make_shared<ListNode>(2);
    shared_ptr<ListNode> node2 = make_shared<ListNode>(3);
    shared_ptr<ListNode> node3 = make_shared<ListNode>(4);
    shared_ptr<ListNode> node4 = make_shared<ListNode>(5);
    
    head->next = node1; node1->next = node2;
    node2->next = node3; node3->next = node4;
    
    ListNode::Display(head);
    
    shared_ptr<ListNode> pre = nullptr;
    auto cur = head;
    while (cur != nullptr) {
        auto next = cur->next; cur->next = pre; pre = cur; cur = next;
    }
    ListNode::Display(pre);
}
/*
 给你单链表的头指针 head 和两个整数 left 和 right ，其中 left <= right 。
 请你反转从位置 left 到位置 right 的链表节点，返回 反转后的链表 。
 */
shared_ptr<ListNode> reverseBetween(shared_ptr<ListNode> head, int left, int right){
    //先遍历一边，记录下left和right节点
    auto temp = head;
    int  i = 0;
    shared_ptr<ListNode> leftNode = nullptr;
    shared_ptr<ListNode> rightNode = nullptr;
    
    int leftPreIndex = left - 1;
    shared_ptr<ListNode> leftPreNode = nullptr;
    shared_ptr<ListNode> rightNextNode = nullptr;
    
    while (temp != nullptr && i++ <= right) {
        if(i == leftPreIndex) leftPreNode = temp;
        if(i == left) leftNode = temp;
        if(i == right) rightNode = temp;
        temp = temp->next;
    }
    
    rightNextNode = rightNode->next;

    shared_ptr<ListNode> pre = rightNextNode;
    shared_ptr<ListNode> cur = leftNode;
    int begin = left;
    while (begin++ <= right) {
        auto next = cur->next;
        cur->next = pre;
        pre = cur;
        cur = next;
    }
    if(leftPreNode != nullptr)
        leftPreNode->next = pre;
    
    return left >= 2 ? head : pre;
}

class Node {
public:
    int m_value;
    Node* next;
    Node(int value):m_value(value),next(nullptr){
        
    }
};
Node* reverseBetween(Node* head, int left, int right) {
    if(left > right) return nullptr;
    auto temp = head;
    int  i = 0;
    Node* leftNode = nullptr;
    Node* rightNode = nullptr;
    
    int leftPreIndex = left - 1;
    Node* leftPreNode = nullptr;
    Node* rightNextNode = nullptr;
    
    while (temp != nullptr && i++ <= right) {
        if(i == leftPreIndex) leftPreNode = temp;
        if(i == left) leftNode = temp;
        if(i == right) rightNode = temp;
        temp = temp->next;
    }
    
    rightNextNode = rightNode->next;

    Node* pre = rightNextNode;
    Node* cur = leftNode;
    while (left++ <= right) {
        auto next = cur->next;
        cur->next = pre;
        pre = cur;
        cur = next;
    }
    leftPreNode->next = pre;
    
    return head;
}

void test15(){
    shared_ptr<ListNode> head = make_shared<ListNode>(1);
    shared_ptr<ListNode> node1 = make_shared<ListNode>(2);
    shared_ptr<ListNode> node2 = make_shared<ListNode>(3);
    shared_ptr<ListNode> node3 = make_shared<ListNode>(4);
    shared_ptr<ListNode> node4 = make_shared<ListNode>(5);
    
    head->next = node1;
//    node1->next = node2;
//    node2->next = node3;
//    node3->next = node4;
    
    ListNode::Display(head);
    
    auto ndoe = reverseBetween(head, 1, 2);
    
    ListNode::Display(ndoe);
    
}

/*
 给你链表的头节点 head ，每 k 个节点一组进行翻转，请你返回修改后的链表。
 k 是一个正整数，它的值小于或等于链表的长度。如果节点总数不是 k 的整数倍，
 那么请将最后剩余的节点保持原有顺序。
 你不能只是单纯的改变节点内部的值，而是需要实际进行节点交换。
 
 这里就不能从前往后了，就要从后向前的
 */

pair<shared_ptr<ListNode> , shared_ptr<ListNode>> myReverse(shared_ptr<ListNode> head, shared_ptr<ListNode> tail) {
    auto prev = tail->next;
    auto p = head;
    while (prev != tail) {
        auto nex = p->next;
        p->next = prev;
        prev = p;
        p = nex;
    }
    return {tail, head};
}

shared_ptr<ListNode> reverseKGroup(shared_ptr<ListNode> head, int k) {
    //设置一个dummyNode太有用了，这个思想太重要了
    shared_ptr<ListNode> dummyNode = make_shared<ListNode>(-1);
    dummyNode->next = head;
    shared_ptr<ListNode> pre = dummyNode;
    
    while (head) {
        auto tail = pre;
        
        for(int i = 0; i < k; i++){
            tail = tail->next;
            if (!tail) {
                return dummyNode->next;
            }
        }
        
        auto next = tail->next;
        tie(head, tail) = myReverse(head, tail);
        
        pre->next = head;
        tail->next = next;
        
        pre = tail;
        head = tail->next;
    }
    return dummyNode->next;
}
void test16(){
    shared_ptr<ListNode> head = make_shared<ListNode>(1);
    shared_ptr<ListNode> node1 = make_shared<ListNode>(2);
    shared_ptr<ListNode> node2 = make_shared<ListNode>(3);
    shared_ptr<ListNode> node3 = make_shared<ListNode>(4);
    shared_ptr<ListNode> node4 = make_shared<ListNode>(5);
    
    head->next = node1;
    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
    
    ListNode::Display(head);
    
    auto ret = reverseKGroup(head, 2);
    
    ListNode::Display(ret);
}

/*
 LRU 算法
 */
class CacheNode{
public:
    int key;
    int val;
    shared_ptr<CacheNode> pre;
    shared_ptr<CacheNode> next;
    CacheNode(int key, int val):key(key),val(val),pre(nullptr),next(nullptr){}
    virtual ~CacheNode(){}
};

class LRUCache{
private:
    void bringNodeToHead(shared_ptr<CacheNode> node){
        if (head == node) return;
        if (tail == node){
            tail = node->pre;
            if(tail) tail->next = nullptr;
        }else{
            if(node->pre) node->pre->next = node->next;
            if(node->next) node->next->pre = node->pre;
        }
        node->next = head;
        node->pre = nullptr;
        head->pre = node;
        head = node;
    }
    void insertNodeToHead(shared_ptr<CacheNode> node){
        LRUDic[node->key] = node;
        if (head == nullptr) {
            head = node; tail = node;
        }else{
            node->next = head;
            head->pre = node;
            head = node;
        }
    }
    void trimCost(){
        while (LRUDic.size() > capacity) {
            if (tail == nullptr) break;
            LRUDic.erase(tail->key);
            tail = tail->pre;
            if(tail) tail->next = nullptr;
        }
    }
public:
    LRUCache(int capacity):capacity(capacity){
    }
    
    int get(int key) {
        auto it = LRUDic.find(key);
        if(it == LRUDic.end()) return -1;
        bringNodeToHead(it->second);
        return it->second->val;
    }
    
    void put(int key, int value) {
        auto it = LRUDic.find(key);
        if (it != LRUDic.end()) {//update
            it->second->val = value;
            bringNodeToHead(it->second);
        }else{//insert
            auto node = make_shared<CacheNode>(key,value);
            insertNodeToHead(node);
        }
        if (LRUDic.size() > capacity) {
            trimCost();
        }
    }

private:
    shared_ptr<CacheNode> head = nullptr;
    shared_ptr<CacheNode> tail = nullptr;
    int size = 0;
    int capacity;
    map<int, shared_ptr<CacheNode>> LRUDic = map<int, shared_ptr<CacheNode>>();
};

void test17(){
//    ["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
//    [[2],       [1, 1], [2, 2], [1],  [3, 3], [2],  [4, 4], [1],   [3],   [4]]
//    [null,      null,    null,   1,    null,  -1,    null,  -1,     3,     4]
    
    cout << "------------------" << endl;
    LRUCache cache(2);
    cache.put(1, 1);
    cache.put(2, 2);
    cout << cache.get(1) << " ";
    cache.put(3, 3);
    cout << cache.get(2) << " ";
    cache.put(4, 4);
    cout << cache.get(1) << " ";
    cout << cache.get(3) << " ";
    cout << cache.get(4) << " ";
    cout << endl;
    // 1  -1 -1 3 4
    
    LRUCache cache2(1);
    cache2.put(2, 1);
    cout << cache2.get(2) << endl;
    //1
    
    
//    [[1],[2,1],[2],[3,2],[2],[3]]
    
    LRUCache cache1(1);
    cache1.put(2, 1);
    cout << cache1.get(2) << " ";
    cache1.put(3, 2);
    cout << cache1.get(2) << " ";
    cout << cache1.get(3) << " ";
    cout << endl;
    //1 -1 2
    
    
    LRUCache cache3(2);
    cache3.put(2, 1);
    cache3.put(2, 2);
    cout << cache3.get(2) << " ";
    cache3.put(1, 1);
    cache3.put(4, 1);
    cout << cache3.get(2) << " ";
    cout << endl;
    //2 -1
    
//    [[2],[1,1],[2,2],[1],[3,3],[2],[4,4],[1],[3],[4]]
    LRUCache cache4(2);
    cache4.put(1, 1);
    cache4.put(2, 2);
    cout << cache4.get(1) << " ";
    cache4.put(3, 3);
    cout << cache4.get(2) << " ";
    cache4.put(4, 4);
    cout << cache4.get(1) << " ";
    cout << cache4.get(3) << " ";
    cout << cache4.get(4) << " ";
    cout << endl;
    //1 -1  -1  3  4
    
    
//    [[2],[2,1],[1,1],[2,3],[4,1],[1],[2]]
    
    LRUCache cache5(2);
    cache5.put(2, 1);
    cache5.put(1, 1);
    cache5.put(2, 3);
    cache5.put(4, 1);
    cout << cache5.get(1) << " ";
    cout << cache5.get(2) << " ";
    cout << endl;
    //-1 3
    
    
//    [[2],[2],[2,6],[1],[1,5],[1,2],[1],[2]]
    LRUCache cache6(2);
    cout << cache6.get(2) << " ";
    cache6.put(2, 6);
    cout << cache6.get(1) << " ";
    cache6.put(1, 5);
    cache6.put(1, 2);
    cout << cache6.get(1) << " ";
    cout << cache6.get(2) << " ";
    cout << endl;
    //-1 -1  2 6
    
//    [[2],[2,1],[3,2],[3],[2],[4,3],[2],[3],[4]]
    LRUCache cache7(2);
    cache7.put(2, 1);
    cache7.put(3, 2);
    cout << cache7.get(3) << " ";
    cout << cache7.get(2) << " ";
    cache7.put(4, 3);
    cout << cache7.get(2) << " ";
    cout << cache7.get(3) << " ";
    cout << cache7.get(4) << " ";
    cout << endl;
    // 2 1 1 -1 3
}


/*
 删除列表的第N个节点
 */
shared_ptr<ListNode> removeK(shared_ptr<ListNode> head, int k){
    if(head == nullptr || k <= 0) return head;
    auto dummyHead = make_shared<ListNode>(-1);
    dummyHead->next = head;
    int cur = 0, slowing = 0;
    auto fast = head, slow = head;
    while (fast) {
        if (cur++ == k) slowing = 1;
        if (slowing > 0) slow = slow->next;
        fast = fast->next;
    }
    if (slow->next) {
        slow->value = slow->next->value;
        slow->next = slow->next->next;
    }else{
        if (head->next == nullptr) {
            return nullptr;
        }else{
            while (head->next && head->next->next) {
                head = head->next;
            }
            head->next = nullptr;
        }
    }
    return dummyHead->next;
}
void test18(){
    shared_ptr<ListNode> head = make_shared<ListNode>(1);
    shared_ptr<ListNode> node1 = make_shared<ListNode>(2);
    shared_ptr<ListNode> node2 = make_shared<ListNode>(3);
    shared_ptr<ListNode> node3 = make_shared<ListNode>(4);
    shared_ptr<ListNode> node4 = make_shared<ListNode>(5);
    
    head->next = node1;
//    node1->next = node2;
//    node2->next = node3;
//    node3->next = node4;
    
    ListNode::Display(head);
    auto temp = removeK(head, 1);
    ListNode::Display(temp);
}

/*
 旋转链表
 */
shared_ptr<ListNode> rotateRight(shared_ptr<ListNode> head, int k){
    if(head == nullptr || k <= 0) return head;
    auto dummyHead = make_shared<ListNode>(-1);
    dummyHead->next = head;
    int len = 0;
    auto temp = head;
    while (temp) {
        len++;
        temp = temp->next;
    }
    temp = head;
    auto tail = head;
    while (tail->next) {
        tail = tail->next;
    }
    int joinLen = len;
    while (joinLen--) {
        tail->next = temp;
        temp = temp->next;
        tail = tail->next;
    }
    
    int count = k % len;
    int begin = len - count;
    auto beginNode = head;
    while (begin--) {
        beginNode = beginNode->next;
    }
    int tempLen = len;
    deque<shared_ptr<ListNode>> deque{};
    while (tempLen--) {
        deque.push_back(beginNode);
        beginNode = beginNode->next;
    }
    beginNode->next = nullptr;
    auto ret = make_shared<ListNode>(-1);
    ret->next = deque.front();
    while (!deque.empty()) {
        auto temp = deque.front();
        deque.pop_front();
        temp->next = deque.size() > 0 ? deque.front() : nullptr;
    }
    return ret->next;
}
void test19(){
    shared_ptr<ListNode> head = make_shared<ListNode>(1);
    shared_ptr<ListNode> node1 = make_shared<ListNode>(2);
    shared_ptr<ListNode> node2 = make_shared<ListNode>(3);
    shared_ptr<ListNode> node3 = make_shared<ListNode>(4);
    shared_ptr<ListNode> node4 = make_shared<ListNode>(5);
    
    head->next = node1;
    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
    
    ListNode::Display(head);
    auto temp = rotateRight(head, 6);
    ListNode::Display(temp);
}


class ListNode1{
public:
    int val;
    ListNode1 *next;
    ListNode1(int val):val(val),next(nullptr){}
};

ListNode1* rotateRight(ListNode1* head, int k) {
    if(head == nullptr || k <= 0) return head;
    ListNode1* dummyHead = new ListNode1(-1);
    dummyHead->next = head;
    dummyHead->next = head;
    int len = 0;
    auto temp = head;
    while (temp) {
        len++;
        temp = temp->next;
    }
    temp = head;
    auto tail = head;
    while (tail->next) {
        tail = tail->next;
    }
    int joinLen = len;
    while (joinLen--) {
        tail->next = temp;
        temp = temp->next;
        tail = tail->next;
    }
    
    int count = k % len;
    int begin = len - count;
    auto beginNode = head;
    while (begin--) {
        beginNode = beginNode->next;
    }
    int tempLen = len;
    deque<ListNode1*> deque{};
    while (tempLen--) {
        deque.push_back(beginNode);
        beginNode = beginNode->next;
    }
    beginNode->next = nullptr;
    auto ret = new ListNode1(-1);
    ret->next = deque.front();
    while (!deque.empty()) {
        auto temp = deque.front();
        deque.pop_front();
        temp->next = deque.size() > 0 ? deque.front() : nullptr;
    }
    return ret->next;
}
void test20(){
    ListNode1* head = new ListNode1(1);
    ListNode1* node1 = new ListNode1(2);
    ListNode1* node2 = new ListNode1(3);
    ListNode1* node3 = new ListNode1(4);
    ListNode1* node4 = new ListNode1(5);
    
    head->next = node1;
    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
    
    auto ret = rotateRight(head, 4);
}

/*
 删除列表中的重复元素
 方法比较多：
 2.原地删除
 */

ListNode1* deleteDuplicates1(ListNode1* head) {
    if(head == nullptr) return head;
    auto dummyHead = new ListNode1(-1);
    dummyHead->next = head;
    auto temp = dummyHead;
    while (temp->next && temp->next->next) {
        if (temp->next->val == temp->next->next->val){
            int x = temp->next->val;
            while (temp->next && temp->next->val == x) {//这里还要与自己比一次，这挺难想的
                temp->next = temp->next->next;
            }
        }else{
            temp = temp->next;
        }
    }
    return dummyHead->next;
}

void test21(){
    ListNode1* head = new ListNode1(1);
    ListNode1* node1 = new ListNode1(2);
    ListNode1* node2 = new ListNode1(2);
    ListNode1* node3 = new ListNode1(3);
    ListNode1* node4 = new ListNode1(3);
    
    head->next = node1;
    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
    
    auto ret = deleteDuplicates1(head);
}

#pragma MARK HashTable
/*
 算法、算法、还是算法
 计算机、英语、英语、计算机
 赎金信:
 给你两个字符串：ransomNote 和 magazine ，判断 ransomNote 能不能由 magazine 里面的字符构成。
 如果可以，返回 true ；否则返回 false 。
 magazine 中的每个字符只能在 ransomNote 中使用一次。
 解法1:HastTable
 解法2:一共就26了个字母，创建一个26个字母的一维数组
 */
bool canConstruct(string ransomNote, string magazine) {
    if(magazine.length() <= 0) return false;
    int chs[26] = {};
    for(auto ch : magazine){
        chs[ch - 'a']++;
    }
    for(auto ch : ransomNote){
        if (chs[ch - 'a'] == 0) return false;
        chs[ch - 'a']--;
    }
    return true;
}
void test22(){
    cout << canConstruct("aa", "aab") << endl;
}

/*
 给定两个字符串 s 和 t ，判断它们是否是同构的。
 如果 s 中的字符可以按某种映射关系替换得到 t ，那么这两个字符串是同构的。
 每个出现的字符都应当映射到另一个字符，同时不改变字符的顺序。
 不同字符不能映射到同一个字符上，相同字符只能映射到同一个字符上，
 字符可以映射到自己本身。
 算法、算法、还是算法
 音视频、音视频、还是音视频
 解法一：最简单的方式就是，遍历s和t，记录每个字符出现的位置，然后进行对比，
 */
bool isIsomorphic(string s, string t) {
    //add pee, adef befc, hehe dada
    //顺序，必须相同
    unordered_map<char, char> hash1{};
    unordered_map<char, char> hash2{};
    int len = (int)s.length();
    for(int i = 0; i < len; i++){
        char x = s[i], y = t[i];
        if ((hash1.count(x) && hash1[x] != y) || (hash2.count(y) && hash2[y] != x)) {
            return false;
        }
        hash1[x] = y;
        hash2[y] = x;
    }
    return true;
}
void test23(){
    cout << isIsomorphic("qwertyuiop[]asdfghjkl;'\\zxcvbnm,./", "',.pyfgcrl/=aoeuidhtns-\\;qjkxbmwvz") << endl;
    cout << isIsomorphic("mm", "mv") << endl;
}


/*
 给定一种规律 pattern 和一个字符串 s ，判断 s 是否遵循相同的规律。
 这里的 遵循 指完全匹配，例如， pattern 里的每个字母和字符串 s
 中的每个非空单词之间存在着双向连接的对应规律。
 解法一：
 这个题相对简单一点：
 同时遍历pattern 和 s
 pattern的 char 作为key
 s的单词作为value，便利是否相同就OK
 算法 算法 还是算法
 */
/*
 c++从字符串中获取字符串:
 方法一：string getline
 方法二：regex
 方法三：substring
 */
/*
 学习c++一定要注意的是 值引用/地址引用
 class Person{
    int age;
    string name;
 }
 auto person = Person();
 Person function(){
    auto person = Person();//临时变量，因为处理了作用域，person就会被销毁
    return person;//在返回的时候要进行拷贝构造，先根据person拷贝构造出一个新的person对象，在返回
 }
 
 Person& function(){
     auto person = Person();//临时变量，因为处理了作用域，person就会被销毁
     return person;//直接返回person的地址，就会减少一步拷贝构造
 }
 */
vector<string> split1(string& s, char delimiter){
    vector<string> ret;
    stringstream ss(s);
    string token;
    while (getline(ss, token, delimiter)) {
        ret.push_back(token);
    }
    return ret;
}
vector<string> split2(string& s, string delimiter){
    regex reg(delimiter);
    sregex_token_iterator first{s.begin(), s.end(), reg, -1}, last;
    return {first, last};
}
vector<string> split3(string& s, char delimiter){
    vector<string> ret;
    size_t start = 0;
    size_t end = s.find(delimiter);
    
    while (end != string::npos) {
        ret.push_back(s.substr(start, end - start));
        start = end + 1;
        end = s.find(delimiter, start);
    }
    
    ret.push_back(s.substr(start, end));
    return ret;
}
bool wordPattern(string pattern, string s) {
    if(pattern.length() == 0 || s.length() == 0) return false;
    string strs[26];
    auto words = split1(s, ' ');
    for(int i = 0; i < pattern.length() || i < words.size(); i++){
        if ((i >= pattern.length() && i < words.size()) ||
            (i >= words.size() && i < pattern.length())) return false;
        auto ch = pattern[i];
        if(strs[ch - 'a'] != "" && strs[ch - 'a'] != words[i])
            return false;
        else{
            for (int j = 0; j < ch - 'a'; j++) {
                if(strs[j] == words[i]) return false;
            }
            strs[ch - 'a'] = words[i];
        }
    }
    return true;
}
void test24(){
    cout << wordPattern("abc", "dog cat dog") << endl;
}

/*
 给定两个字符串 s 和 t ，编写一个函数来判断 t 是否是 s 的
 字母异位词
 解法一：hash搞定
 */
bool isAnagram1(string s, string t){
    if(s.length() == 0 || t.length() == 0) return false;
    int chars[26] = {0};
    for (int i = 0; i < s.length() || i < t.length(); i++) {
        if((i < s.length() && i >= t.length()) ||
           (i < t.length() && i >= s.length())) return false;
        auto ch = s[i] - 'a';
        chars[ch]++;
    }
    for (auto it = t.begin(); it != t.end(); it++) {
        if(--chars[*it - 'a'] < 0) return false;
    }
    return true;
}
void test25(){
    cout << "-----test25--------" << endl;
    cout << isAnagram1("anagram", "nagaram") << endl;
    cout << isAnagram1("cat", "car") << endl;
    cout << isAnagram1("ab", "a") << endl;
}

/*
 给你一个字符串数组，请你将 字母异位词 组合在一起。可以按任意顺序返回结果列表。
 字母异位词 是由重新排列源单词的所有字母得到的一个新单词。
 解法一：
 1.双指针遍历
 2.hash判断是否是异构词
 这种方法会导致超过时间限制
 解法二：
 1.异构词，是由相同的字符组成的
 2.排序之后，作为key，具体元素作为value
 然后统计一下
 */
vector<vector<string>> groupAnagrams(vector<string>& strs) {
    vector<vector<string>> ret;
    if(strs.size() <= 1) {
        ret.push_back(strs);
        return ret;
    }
    unordered_map<string, vector<string>> temp{};
    for(int begin = 0; begin < strs.size(); begin++){
        string str = strs[begin];
        string key = str;
        sort(key.begin(), key.end());
        temp[key].emplace_back(str);
    }
    
    for(auto it = temp.begin(); it != temp.end(); it++){
        ret.emplace_back(it->second);
    }

    return ret;
}
void test26(){
    cout << "------test26--------" << endl;
    vector<string> strs{"eat", "tea", "tan", "ate", "nat", "bat"};
    auto ret = groupAnagrams(strs);
    for (int i = 0; i < ret.size(); i++) {
        for_each(ret[i].begin(), ret[i].end(), Display<string>());
        cout << endl;
    }
    vector<string> strs1{"",""};
    auto ret1 = groupAnagrams(strs1);
    for (int i = 0; i < ret1.size(); i++) {
        for_each(ret1[i].begin(), ret1[i].end(), Display<string>());
        cout << endl;
    }
    cout << endl;
}

/*
 c++ 关于数组查找的方法
 find
 count
 Lambda结合any_of
 */
void test27(){
    vector<int> vec{1,2,3,4,5};
    int target = 4;
    if (any_of(vec.begin(), vec.end(), [target](int num){return target == num; })) {
        cout << "vec contain target" << endl;
    }
}
/*
 两数之和：
 给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出
 和为目标值 target  的那 两个 整数，并返回它们的数组下标。
 你可以假设每种输入只会对应一个答案，并且你不能使用两次相同的元素。
 解法一：暴力遍历
 解法二：二分查找
 */
vector<int> twoSum(vector<int>& nums, int target) {
    if(nums.size() < 2) return {};
    int start = 0, end = start;
    int size = (int)nums.size();
    for(;start < size; start++){
        end = start + 1;
        while (end < size) {
            if(nums[start] + nums[end] == target)
                return {start,end};
            end++;
        }
    }
    return {};
}
vector<int> twoSum1(vector<int>& nums, int target) {
    if(nums.size() < 2) return {};
    int size = (int)nums.size();
    int start = 0, end = size - 1;
    vector<pair<int, int>> pairs;
    int i = 0;
    for(auto num : nums){
        pairs.emplace_back(i++, num);
    }
    sort(pairs.begin(), pairs.end(), [](auto& l, auto& r) -> bool{
        return l.second < r.second;
    });
    while(start < end){
        auto sum = pairs[start].second + pairs[end].second;
        if(sum == target) {
            return {pairs[start].first,pairs[end].first};
        }else if (sum < target) {
            ++start;
        }else{
            --end;
        }
    }
    return {};
}
void test28(){
    cout << "------test28-------" << endl;
    vector<int> nums{3,2,4};
    auto vec = twoSum1(nums, 6);
    for_each(vec.begin(), vec.end(), Display<int>());
    cout << endl;
}

/*
 「快乐数」 定义为：
 对于一个正整数，每一次将该数替换为它每个位置上的数字的平方和。
 然后重复这个过程直到这个数变为 1，也可能是 无限循环 但始终变不到 1。
 如果这个过程 结果为 1，那么这个数就是快乐数。
 如果 n 是 快乐数 就返回 true ；不是，则返回 false 。
 */
bool isHappy(int n) {
    int q[10] = {0};
    for(int i = 0; i < 10; i++){
        q[i] = i * i;
    }
    int count = 10;
    for(; count-- > 0;){
        int sum = 0;
        while (n > 0) {
            sum += q[n%10];
            n /= 10;
        }
        if (sum == 1) {
            return true;
        }
        n = sum;
    }
    return false;
}
void test29(){
    cout << "------test29-------" << endl;
    cout << isHappy(19) << endl;
    cout << isHappy(2) << endl;
}

/*
 128.最长的连续序列
 给定一个未排序的整数数组 nums ，找出数字连续的最长序列（不要求序列元素在原数组中连续）的长度。
 请你设计并实现时间复杂度为 O(n) 的算法解决此问题。
 解法一：1.先排序 2.双指针
 解法二：hashTable
 */
int longestConsecutive(vector<int>& nums) {
    if (nums.size() <= 1) return (int)nums.size();
    sort(nums.begin(), nums.end());//默认生序
    int begin = 0, end = 1, maxL = 1, count = 1;
    while(begin < nums.size() && end < nums.size() && begin < end){
        if(nums[end] - nums[begin] <= 1){
            if (nums[end] - nums[begin] == 1) {
                maxL = max(maxL, ++count);
            }
            end++; begin++;
        }else{
            begin = end; end++; count = 1;
        }
    }
    return maxL;
}

int longestConsecutive1(vector<int>& nums) {
    if (nums.size() <= 1) return (int)nums.size();
    unordered_set<int> hash(nums.begin(), nums.end());
    int maxL = 0;
    for(auto& val : hash){
        if (hash.count(val - 1)) {
            continue;
        }
        int end = val + 1;
        while (hash.count(end)) {
            end++;
        }
        maxL = max(maxL, (end - val));
    }
    return maxL;
}
void test30(){
    cout << "------test30-------" << endl;
    vector<int> nums{100,4,200,1,3,2};
    vector<int> nums1{0,3,7,2,5,8,4,6,0,1};
    vector<int> nums2{0,0};
    vector<int> nums3{9,1,4,7,3,-1,0,5,8,-1,6};
    cout << longestConsecutive(nums) << endl;
    cout << longestConsecutive1(nums) << endl;
    cout << longestConsecutive(nums1) << endl;
    cout << longestConsecutive1(nums1) << endl;
    cout << longestConsecutive(nums2) << endl;
    cout << longestConsecutive1(nums2) << endl;
    cout << longestConsecutive(nums3) << endl;
    cout << longestConsecutive1(nums3) << endl;
    cout << endl;
}

//MARK: 回溯
/*
 17. 电话号码的字母组合
 给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。答案可以按 任意顺序 返回。
 给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。
 解法一：递归
 解法二：回溯
 */
void addSubStr(vector<string>& ret, string& str, int index, string digital, map<string, vector<char>> phoneNum)
{
    if (index == digital.length() - 1){
        auto key = digital[index];
        if (phoneNum.find(to_string(key - '0')) != phoneNum.end()){
            auto strVec = phoneNum[to_string(key - '0')];
            for(auto ch : strVec){
                auto temp = string(str);
                temp += ch; ret.push_back(string(temp));
            }
        }
    }else{
        if (index < digital.length()) {
            auto key = digital[index];
            if (phoneNum.find(to_string(key - '0')) != phoneNum.end()){
                auto strVec = phoneNum[to_string(key - '0')];
                for(auto ch : strVec){
                    auto temp = string(str); temp += ch;
                    addSubStr(ret, temp, index+=1, digital, phoneNum);
                    index -= 1;
                }
            }
        }
    }
}

vector<string> letterCombinations(string digits) {
    if(digits.length() == 0) return {};
    map<string, vector<char>> phoneNum;
    int current = 'a';
    for (int i = 2; i <= 9; i++) {
        vector<char> second{};
        if (i == 9 || i == 7) {
            int count = 4;
            while (count-- > 0) {
                second.push_back(current++);
            }
        }else{
            int count = 3;
            while (count-- > 0) {
                second.push_back(current++);
            }
        }
        cout << i << ": ";
        for_each(second.begin(), second.end(), Display<char>());
        cout << endl;
        auto key = to_string(i);
        phoneNum[key] = second;
    }
    
    int next = 0;
    vector<string> ret = {};
    string str = "";
    addSubStr(ret, str, next, digits, phoneNum);
    
    return ret;
}
void test31(){
    cout << "-------test31----------" << endl;
    auto ret = letterCombinations("7");
    for_each(ret.begin(), ret.end(), Display<string>());
    cout << endl;
}

/*
 77. 组合
 给定两个整数 n 和 k，返回范围 [1, n] 中所有可能的 k 个数的组合。
 你可以按 任何顺序 返回答案。
 输入：n = 4, k = 2
 输出：
 [
   [2,4],
   [3,4],
   [2,3],
   [1,2],
   [1,3],
   [1,4],
 ]
 示例 2：

 输入：n = 1, k = 1
 输出：[[1]]
 解法一：暴力
 解法二：回溯
 */
void combine(vector<vector<int>>& ret, vector<int> vec, int count, int begin, int n, int k){
    if (count == k) {//个数
        ret.push_back(vec);
        return;
    }else{
        for (int i = begin; i <= n; i++) {
            vec.push_back(i);
            int newCount = count+1;
            combine(ret, vec, newCount, i+1, n, k);
            vec.pop_back();
        }
    }
}
vector<vector<int>> combine(int n, int k) {
    if(n < k) return {};
    vector<int> nums(n, 0);
    vector<vector<int>> ret;
    vector<int> vec;
    int count = 0, begin = 1;
    combine(ret, vec, count, begin, n, k);
    return ret;
}
void test32(){
    cout << "-------test32----------" << endl;
    auto ret = combine(1, 1);
    for(auto vec : ret){
        for_each(vec.begin(), vec.end(), Display<int>());
        cout << endl;
    }
}

/*
 46. 全排列
 给定一个不含重复数字的数组 nums ，返回其 所有可能的全排列 。你可以 按任意顺序 返回答案。
 解法二：回溯
 */
void permute(vector<vector<int>>& ret, int begin, vector<int>& nums) {
    if (begin == nums.size()) {
        ret.push_back(nums);
        return;
    }else{
        for (int i = begin; i < nums.size(); i++) {
            swap(nums[i], nums[begin]);
            permute(ret, begin+1, nums);
            swap(nums[i], nums[begin]);
        }
    }
}
vector<vector<int>> permute(vector<int>& nums) {
    vector<vector<int>> ret = {};
    int begin = 0;
    permute(ret, begin, nums);
    return ret;
}
void test33(){
    cout << "-------test33----------" << endl;
    vector<int> nums{6,2,-1,8};
    auto ret = permute(nums);
    for(auto vec : ret){
        for_each(vec.begin(), vec.end(), Display<int>());
        cout << endl;
    }
}

/*
 39. 组合总和
 给你一个 无重复元素 的整数数组 candidates 和一个目标整数 target ，
 找出 candidates 中可以使数字和为目标数 target 的 所有 不同组合 ，
 并以列表形式返回。你可以按 任意顺序 返回这些组合。
 candidates 中的 同一个 数字可以 无限制重复被选取 。如果至少一个数字的被选数量不同，则两种组合是不同的。
 对于给定的输入，保证和为 target 的不同组合数少于 150 个。
 分析：这个无限使用就很扯，这道题不像之前就一个分支，现在有两个分支，
 1.使用index 和 index+1
 2.一直使用index
 
 结束的标志是
 1.sum = target
 2.index == candidates.size
 */

void combinationSum(vector<vector<int>>& ret, vector<int>& candidates, int target, int begin, int sum, vector<int>& nums){
    if(begin == candidates.size()) return;
    if(sum == target){
        ret.push_back(nums);
        return;
    }
    combinationSum(ret, candidates, target, begin+1, sum, nums);
    if((sum += candidates[begin]) <= target){
        nums.emplace_back(candidates[begin]);
        combinationSum(ret, candidates, target, begin, sum, nums);
        nums.pop_back();
    }
}

vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    if(candidates.size() == 0) return {};
    int begin = 0, sum = 0;
    vector<vector<int>> ret = {};
    vector<int> nums = {};
    combinationSum(ret, candidates, target, begin, sum, nums);
    return ret;
}

void test34(){
    cout << "-------test34----------" << endl;
    vector<int> nums{2,3,6,7}; int target = 7;
    auto vec = combinationSum(nums, target);
    for(auto ret : vec){
        for_each(ret.begin(), ret.end(), Display<int>());
    }
    cout << endl;
}

/*
 皇后问题
 */
class Solution {
public:
    vector<int> cols = {};
    int count = 0;
    int total = 0;
    vector<vector<int>> ret = {};
    int totalNQueens(int n) {
        total = n;
        cols = vector<int>(total, 0);
        place(0);
        return count;
    }
    
    void place(int row){
        if(row == total) {
            count++;
            return;
        }
        for(int col = 0; col < total; col++){
            if (isValid(row, col)) {
                cols[row] = col;
                place(row+1);
            }
        }
    }
    
    bool isValid(int row, int col){
        for(int i = 0; i < row; i++){
            if (cols[i] == col) return false;
            if (row - i == abs(col - cols[i])) return false;
        }
        return true;
    }
};

void test35(){
    cout << "-------test35----------" << endl;
    auto solution = Solution();
    cout << solution.totalNQueens(4) << endl;
}

/*
 22. 括号生成
 数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。

 示例 1：
 输入：n = 3
 输出：["((()))","(()())","(())()","()(())","()()()"]
 示例 2：

 输入：n = 1
 输出：["()"]
 
 解法：回溯
 1.结束的条件： str.length = 2 * n
 2.左括号 nl < n，就继续加左括号
 3.右括号 nr < nl, 就继续加右括号
 */
class Solution36 {
public:
    vector<string> ret; string str = "";
    int left = 0, right = 0;
    void place(int n, int left, int right){
        if(str.length() == 2 * n) {
            ret.emplace_back(str);
            return;
        }
        if (left < n) {
            str.push_back('(');
            place(n, left+1, right);
            str.pop_back();
        }
        if (right < left) {
            str.push_back(')');
            place(n, left, right+1);
            str.pop_back();
        }
    }
    vector<string> generateParenthesis(int n) {
        place(n, 0, 0);
        return ret;
    }
};
void test36(){
    cout << "-------test36----------" << endl;
    auto solution = Solution36();
    auto ret = solution.generateParenthesis(2);
    for_each(ret.begin(), ret.end(), Display<string>());
    cout << endl;
}

/*
 79. 单词搜索
 给定一个 m x n 二维字符网格 board 和一个字符串单词 word 。
 如果 word 存在于网格中，返回 true ；否则，返回 false 。
 单词必须按照字母顺序，通过相邻的单元格内的字母构成，
 其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。
 同一个单元格内的字母不允许被重复使用。
 解法：回溯
 */
bool check(vector<vector<char>>& board, vector<vector<bool>>& visit, int row, int col, string s, int k){
    if(board[row][col] != s[k]) return false;
    else if(k == s.length() - 1) return true;
    
    visit[row][col] = true;
    
    vector<pair<int, int>> dirs{{0,1}, {0, -1}, {1,0}, {-1,0}};
    bool result = false;
    for(auto& dir : dirs){
        int newR = row + dir.first, newC = col + dir.second;
        if(newR >= 0 && newR < board.size() && newC >= 0 && newC < board[0].size()){
            if (!visit[newR][newC]) {
                bool flag = check(board, visit, newR, newC, s, k+1);
                if (flag) {
                    result = true;
                    break;
                }
            }
        }
    }
    visit[row][col] = false;
    return result;
}
bool exist(vector<vector<char>>& board, string word) {
    auto rows = board.size(); auto cols = board[0].size();
    vector<vector<bool>> visi(rows, vector<bool>(cols));
    for(int row = 0; row < rows; row++){
        for(int col = 0; col < cols; col++){
            if(check(board, visi, row, col, word, 0)){
                return true;
            }
        }
    }
    return false;
}
void test37(){
    cout << "-------test36----------" << endl;
    //board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
    vector<vector<char>> board{{'A','B','C','E'}, {'S','F','C','S'}, {'A','D','E','E'}};
    string word = "ABCCED";
    word = "SEE";
//    word = "ABCB"
    cout << exist(board, word) << endl;
}

/*
 200. 岛屿数量
 给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量。
 岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成。
 此外，你可以假设该网格的四条边均被水包围。
 */
void isIland(vector<vector<string>>& grid, int row, int col){
    if(row < 0 || row >= grid.size() || col < 0 || col >= grid[row].size() || grid[row][col] == "0")  return;
    grid[row][col] = "0";
    vector<pair<int, int>> dirs{{-1, 0},{1, 0},{0, 1},{0, -1}};
    for(auto dir : dirs){
        int nR = row + dir.first, nC = col + dir.second;
        isIland(grid, nR, nC);
    }
}
int numIslands(vector<vector<string>>& grid) {
    if(grid.size() == 0) return 0;
    int ret = 0;
    int rows = (int)grid.size();
    for(int row = 0; row < rows; row++){
        for(int col = 0; col < grid[row].size(); col++){
            if(grid[row][col] == "1"){
                isIland(grid, row, col);
                ret++;
            }
        }
    }
    return ret;
}

void test38(){
    vector<vector<string>> grid = {
        {"1","1","1","1","0"},
        {"1","1","0","1","0"},
        {"1","1","0","0","0"},
        {"0","0","0","0","0"}
    };
    grid = {
        {"1","1","0","0","0"},
        {"1","1","0","0","0"},
        {"0","0","1","0","0"},
        {"0","0","0","1","1"}
    };

    cout << numIslands(grid) << endl;
}

//MARK: 二维动态规划
/*
 120. 三角形最小路径和
 给定一个三角形 triangle ，找出自顶向下的最小路径和。
 每一步只能移动到下一行中相邻的结点上。相邻的结点 在这里指的是 下标 与
 上一层结点下标 相同或者等于 上一层结点下标 + 1 的两个结点。也就是说，
 如果正位于当前行的下标 i ，那么下一步可以移动到下一行的下标 i 或 i + 1 。
 解法一：回溯这样会超出限制
 解法二：动态规划
 dp[i][i]表示从三角形顶部走到[i][j]的最短路径和
 dp[i][j] = min(dp[i-1][j-1], dp[i-1][j]) + tri[i][j]
 主要有一些边界条件
 1.dp[0][0] = tri[0][0]
 2.dp[i][0] = dp[i-1][0] + c[i][0]
 3.dp[i][max] = dp[i-1][max] + c[i][max]
 */
int minimumTotal(vector<vector<int>>& triangle, int Min, int row, int col){
    if (row == triangle.size() || col == triangle[row].size()) {
        return 0;
    }
    Min += min(minimumTotal(triangle, Min, row+1, col), minimumTotal(triangle, Min, row+1, col+1));
    Min += triangle[row][col];
    return Min;
}
int minimumTotal1(vector<vector<int>>& triangle) {
    return minimumTotal(triangle, 0, 0, 0);
}
int minimumTotal(vector<vector<int>>& triangle) {
    int n = (int)triangle.size();
    vector<vector<int>> dp(n, vector<int>(n));
    dp[0][0] = triangle[0][0];
    for(int row = 1; row < n; row++){
        dp[row][0] = dp[row-1][0] + triangle[row][0];
        for(int col = 1; col < row; col++){
            dp[row][col] = min(dp[row-1][col-1], dp[row-1][col]) + triangle[row][col];
        }
        dp[row][row] = dp[row-1][row-1] + triangle[row][row];
    }
    
    return *min_element(dp[n-1].begin(), dp[n-1].end());
}


void test39(){
    cout << "----------test39---------------" << endl;
    vector<vector<int>> triangle{{2}, {3,4}, {6,5,7}, {4,1,8,3}};
    triangle = {{-10}};
    cout << minimumTotal(triangle) << endl;
}

/*
 64. 最小路径和
 给定一个包含非负整数的 m x n 网格 grid ，请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。
 说明：每次只能向下或者向右移动一步。
 解法一：动态规划
 */
int minPathSum(vector<vector<int>>& grid) {
    if(grid.size() == 0) return 0;
    if(grid.size() == 1) {
        int sum = 0;
        for_each(grid[0].begin(), grid[0].end(), [&sum](int num){
            sum += num;
        });
        return sum;
    }
    int rows = (int)grid.size(), cols = (int)grid[0].size();
    vector<vector<int>> dp(rows, vector<int>(cols));
    dp[0][0] = grid[0][0];
    for(int row = 1; row < rows; row++){
        dp[row][0] = dp[row-1][0] + grid[row][0];
        for(int col = 1; col < cols; col++){
            dp[0][col] = dp[0][col-1] + grid[0][col];
            dp[row][col] = min(dp[row - 1][col], dp[row][col-1]) + grid[row][col];
        }
    }
    return dp[rows-1][cols-1];
}
void test40(){
    cout << "----------test40---------------" << endl;
    vector<vector<int>> gird{{1,3,1},{1,5,1},{4,2,1}};
    gird = {{1,2,3},{4,5,6}};
    gird = {{9,1,4,8}};
    cout << minPathSum(gird) << endl;
}

/*
 63. 不同路径 II
 给定一个 m x n 的整数数组 grid。一个机器人初始位于 左上角（即 grid[0][0]）。
 机器人尝试移动到 右下角（即 grid[m - 1][n - 1]）。机器人每次只能向下或者向右移动一步。
 网格中的障碍物和空位置分别用 1 和 0 来表示。机器人的移动路径中不能包含 任何 有障碍物的方格。
 返回机器人能够到达右下角的不同路径数量。
 测试用例保证答案小于等于 2 * 109。
 解法：还是动态规划 回溯的问题其实挺难理解的
 */
int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
    if(obstacleGrid.size() == 0 || obstacleGrid[0][0]) return 0;
    int rows = (int)obstacleGrid.size();
    int cols = (int)obstacleGrid[0].size();
    vector<vector<int>> dp(rows, vector<int>(obstacleGrid[0].size(), 0));//表示能够到达grid[i][j]的路径数量
    for(int i=0;i < rows && obstacleGrid[i][0]==0;i++){
        dp[i][0]=1;
    }
    for(int j=0; j < cols && obstacleGrid[0][j]==0;j++){
        dp[0][j]=1;
    }
    for(int row = 1; row < rows; row++){
        for(int col = 1; col < cols; col++){
            if(obstacleGrid[row][col] == 1) continue;
            dp[row][col] = dp[row-1][col] + dp[row][col-1];
        }
    }
    return dp[rows-1][cols-1];
}
void test41(){
    cout << "----------test41---------------" << endl;
    vector<vector<int>> gird{{0,0,0},{0,1,0},{0,0,0}}; //2
    vector<vector<int>> gird1 = {{0,1},{0,0}};//1
    vector<vector<int>> gird2 = {{1}};//1
    vector<vector<int>> gird3 = {{0, 1}};//0
    vector<vector<int>> gird4 = {{1, 0}};//0
    vector<vector<int>> gird5 = {{0, 1, 0}};//0
    vector<vector<vector<int>>> test = {gird,  gird1, gird2, gird3, gird4, gird5};
    for_each(test.begin(), test.end(), [](auto& gird){
        cout << uniquePathsWithObstacles(gird) << endl;
    });
}

struct alignas(32) MyStruct {
    int a;
    double b;
    char c;
};

class alignas(16) MyClass {
    int a;
    float b;
};


void test42(){
    cout << "----------test42---------------" << endl;
    MyStruct s;
    std::cout << "Address of s: " << &s << std::endl;
    std::cout << "Size of MyStruct: " << sizeof(MyStruct) << std::endl;
    
    MyClass obj;
    std::cout << "Address of obj: " << &obj << std::endl;
    std::cout << "Size of MyStruct: " << sizeof(MyClass) << std::endl;
}

/*
 k个一组翻转列表
 */
pair<shared_ptr<ListNode>, shared_ptr<ListNode>> myReverseNode(shared_ptr<ListNode> head, shared_ptr<ListNode> tail){
    auto pre = tail->next;
    auto p = head;
    while (pre != tail) {
        auto next = p->next; p->next = pre; pre = p;  head = next;
    }
    return make_pair(head, tail);
}
shared_ptr<ListNode> reverseKGroup1(shared_ptr<ListNode> head, int k) {
    if(head == nullptr || k == 0) return head;
    auto dummyHead = make_shared<ListNode>(-1);
    dummyHead->next = head;
    auto pre = dummyHead;
    
    while (head) {
        
        auto tail = pre;
        
        int temp = k;
        while (temp-- > 0) {
            tail = tail->next;
            if (!tail) {
                return dummyHead->next;
            }
        }
        
        auto next = tail->next;
        tie(head, tail) = myReverseNode(head, tail);
        
        pre->next = head;
        tail->next = next;
        
        pre = tail;
        head = tail->next;
    }
    
    return dummyHead->next;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    string str = "123";
    int ret = stoi(str) + 321;
    cout << ret << endl;
    
    test2();

    test3();

    test4();

    test5();

    test6();

    test7();

    test8();

    test9();

    test10();

    test11();

    test13();

    test14();

    reverseList();

    test15();

    test16();

    test17();

    test18();

    test19();

    test20();

    test21();

    test22();

    test23();

    test24();

    test25();

    test26();

    test27();

    test28();

    test29();

    test30();

    test31();

    test32();
    
    test33();
    
    test34();
    
    test35();
    
    test36();
    
    test37();
    
    test38();
    
    test39();
    
    test40();
    
    test41();
    
    test42();
    
    return 0;
}
