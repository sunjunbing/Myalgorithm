//
//  main.cpp
//  C++_Algorithm_top55
//
//  Created by sunjian on 2024/12/27.
//

#include <iostream>
#include <vector>
#include <map>
#include <deque>
#include <list>
#include <unordered_set>
#include <unordered_map>

using namespace std;

template <typename T>
struct Display{
    void operator()(T& element){
        cout << element << " ";
    }
};

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
    
    static void display(ListNode *node){
        auto temp = node;
        while (temp != nullptr) {
            cout << temp->val << " ";
            temp = temp->next;
        }
    }
};

/*
 1. 两数之和
 给定一个整数数组 nums 和一个整数目标值 target，
 请你在该数组中找出 和为目标值 target  的那 两个 整数，
 并返回它们的数组下标。
 你可以假设每种输入只会对应一个答案，并且你不能使用两次相同的元素。
 你可以按任意顺序返回答案
 */

vector<int> twoSum(vector<int>& nums, int target) {
    int len = (int)nums.size();
    if(len <= 0) return {};
    for(int i = 1; i < len; i++){
        for(int j = 0; j < i; j++){
            if(nums[i] + nums[j] == target){
                return {i,j};
            }
        }
    }
    return {};
}
void test1(){
    cout << "---------test1-----------" << endl;
    vector<int> nums{2,7,11,15}; int target = 9;
    nums = {3,2,4}; target = 6;
    nums = {3,3}; target = 6;
    auto ret = twoSum(nums, target);
    for_each(ret.begin(), ret.end(), Display<int>());
    cout << endl;
}

/*
 2. 两数相加
 给你两个 非空 的链表，表示两个非负的整数。
 它们每位数字都是按照 逆序 的方式存储的，并且每个节点只能存储 一位 数字。
 请你将两个数相加，并以相同形式返回一个表示和的链表。
 你可以假设除了数字 0 之外，这两个数都不会以 0 开头。
 解法：遍历，如果有进位，保留住等下相加
 */
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    return nullptr;
}
void test2(){
    cout << "---------test2-----------" << endl;
    addTwoNumbers(nullptr, nullptr);
}


/*
 3. 无重复字符的最长子串
 给定一个字符串 s ，请你找出其中不含有重复字符的 最长子串的长度。
 解法：滑动窗口，通过hashMap记录，char 和 index
 */
int lengthOfLongestSubstring(string s) {
    int len = (int)s.length();
    if(len == 0) return 0;
    int Max = 1;
    int i = -1;//左边揭界
    unordered_map<char, int> chars;
    for(int j = 0; j < len; j++){
        if (chars.find(s[j]) != chars.end()) {
            i = max(i, chars[s[j]]);
        }
        chars[s[j]] = j;
        Max = max(Max, j - i);
    }
    return Max;
}
void test3(){
    cout << "---------test3-----------" << endl;
    string str = "abcabcbb";
    str = "bbbbb";
    str = "pwwkew";
    cout << lengthOfLongestSubstring(str) << endl;
}

/*
 5. 最长回文子串
 给你一个字符串 s，找到 s 中最长的回文子串
 解法：中心扩展法，根据回文串的特点
 分为两种情况：
 1.以单个字符为中心，向两边扩展
 2.以当前字符和下一个字符为中心，向两边扩展
 */
string subString(string& s, int left, int right){
    while(left >= 0 && right < s.length() && s[left] == s[right]){
        left--; right++;
    }
    return s.substr(left + 1, right - left - 1);
}
string longestPalindrome(string s) {
    if(s.empty()) return "";
    string longestStr = "";
    for(int i = 0; i < s.length(); i++){
        //以单个字符为中心
        auto sub = subString(s, i, i);
        if(sub.length() > longestStr.length()){
            longestStr = sub;
        }
        sub = subString(s, i, i+1);
        if(sub.length() > longestStr.length()){
            longestStr = sub;
        }
    }
    return longestStr;
}
void test4(){
    cout << "---------test4-----------" << endl;
    cout << longestPalindrome("ababa") << endl;
}

/*
 42. 接雨水
 给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。
 解法一：双指针法

 */
int trap(vector<int>& height) {
    if(height.empty()) return 0;
    int left = 0, right = (int)height.size() - 1, leftMax = 0, rightMax = 0, total = 0;
    while (left < right) {
        if (height[left] <= height[right]) {
            if (height[left] > leftMax) {
                leftMax = height[left];
            }else{
                total += leftMax - height[left];
            }
            left++;
        }else{
            if (height[right] > rightMax) {
                rightMax = height[right];
            }else{
                total += rightMax - height[right];
            }
            right--;
        }
    }
    return total;
}
void test5(){
    cout << "---------test5-----------" << endl;
    vector<int> height{0,1,0,2,1,0,1,3,2,1,2,1};
    cout << trap(height) << endl;
}

/*
 翻转列表
 */
ListNode* reverseList(ListNode* head) {
    if(head == nullptr) return nullptr;
    ListNode *pre = nullptr;
    while (head) {
        ListNode* next = head->next;
        head->next = pre;
        pre = head;
        head = next;
    }
    return pre;
}
void test6(){
    cout << "---------test6-----------" << endl;
    ListNode *head = new ListNode(1);
    ListNode *node1 = new ListNode(2);
    ListNode *node2 = new ListNode(3);
    ListNode *node3 = new ListNode(4);
    ListNode *ndoe4 = new ListNode(5);
    head->next = node1;
    node1->next = node2;
    node2->next = node3;
    node3->next = ndoe4;
    auto newHead = reverseList(head);
    ListNode::display(newHead);
    cout << endl;
}

/*
 4. 寻找两个正序数组的中位数
 给定两个大小分别为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。
 请你找出并返回这两个正序数组的 中位数。
 算法的时间复杂度应该为 O(log (m+n)) 。
 解法一：先合并，在查找
 */
double findMedianSortedArrays(vector<int>& nums){
    if(nums.size() == 0) return 0;
    int len = (int)nums.size();
    if(!(len % 2)) {
        int media = len / 2;
        int v1 = nums[media];
        int v2 = nums[media-1];
        return (v1 + v2) / 2.0;
    }else{
        int media = len / 2;
        return nums[media] * 1.0;
    }
}

double findMedianSortedArrays1(vector<int>& nums1, vector<int>& nums2) {
    //合并两个有序的数组 merge sort
    if (nums1.size() == 0) return findMedianSortedArrays(nums2);
    if (nums2.size() == 0) return findMedianSortedArrays(nums1);
    int l1 = (int)nums1.size();
    vector<int> total(nums1.begin(), nums1.end());
    total.insert(total.end(), nums2.begin(), nums2.end());
    int l2 = (int)total.size();
    int l = 0, r = (int)nums1.size(), t = 0;
    while (l < l1 || r < l2) {
        if (r < l2) {
            if (nums1[l] < total[r]) {
                total[t++] = nums1[l++];
            }else{
                total[t++] = total[r++];
            }
        }else if(l < l1){
            total[t++] = nums1[l++];
        }
    }
    return findMedianSortedArrays(total);
}

double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    //合并两个有序的数组 merge sort
    if (nums1.size() == 0) return findMedianSortedArrays(nums2);
    if (nums2.size() == 0) return findMedianSortedArrays(nums1);
    int l1 = (int)nums1.size();
    vector<int> total(nums1.begin(), nums1.end());
    total.insert(total.end(), nums2.begin(), nums2.end());
    int l2 = (int)total.size();
    int l = 0, r = (int)nums1.size(), t = 0;
    while (l < l1 || r < l2) {
        if (r < l2) {
            if (nums1[l] < total[r]) {
                total[t++] = nums1[l++];
            }else{
                total[t++] = total[r++];
            }
        }else if(l < l1){
            total[t++] = nums1[l++];
        }
    }
    return findMedianSortedArrays(total);
}
void test7(){
    cout << "---------test7-----------" << endl;
    vector<int> nums1 = {5}, nums2 = {};
    cout << findMedianSortedArrays(nums1, nums2) << endl;
}

/*
 11. 盛最多水的容器
 给定一个长度为 n 的整数数组 height 。有 n 条垂线，
 第 i 条线的两个端点是 (i, 0) 和 (i, height[i]) 。
 找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。
 返回容器可以储存的最大水量。
 解法：双指针
 */
int maxArea(vector<int>& height) {
    if(height.size() <= 1) return 0;
    int left = 0, right = (int)height.size() - 1;
    int MAX = 0;
    while (left < right) {
        if(height[left] < height[right]){
            MAX = max(MAX, height[left] * (right - left));
            left++;
        }else{
            MAX = max(MAX, height[right] * (right - left));
            right--;
        }
    }
    return MAX;
}
void test8(){
    cout << "---------test8-----------" << endl;
    vector<int> nums1 = {1,8,6,2,5,4,8,3,7};
    cout << maxArea(nums1) << endl;
}


/*
 15. 三数之和
 给你一个整数数组 nums ，判断是否存在三元组 [nums[i], nums[j],
 nums[k]] 满足 i != j、i != k 且 j != k ，
 同时还满足 nums[i] + nums[j] + nums[k] == 0 。请你返回所有和为 0 且不重复的三元组。
 注意：答案中不可以包含重复的三元组。
 */
vector<vector<int>> threeSum(vector<int>& nums) {
    if(nums.size() == 0) return {};
    //排序
    sort(nums.begin(), nums.end());
    //3指针
    int left = 0, right = (int)nums.size() - 1;
    vector<vector<int>> ret = {};
    while (left < right) {
        if(nums[left] + nums[right] > 0){
            int mid = left + 1;
            while (nums[mid] < 0) {
                if(nums[left] + nums[right] + nums[mid] == 0){
                    vector<int> temp = {nums[left], nums[right], nums[mid]};
                    ret.emplace_back(temp);
                    break;
                }
                mid++;
            }
            right--;
        }else if(nums[left] + nums[right] < 0){
            int mid = right - 1;
            while (nums[mid] > 0) {
                if(nums[left] + nums[right] + nums[mid] == 0){
                    vector<int> temp = {nums[left], nums[right], nums[mid]};
                    ret.emplace_back(temp);
                    break;
                }
                mid--;
            }
            left++;
        }else{
            int mid = left + 1;
            while (nums[mid] != 0 && mid < nums.size()) {
                mid++;
            }
            if (nums[mid] == 0 && mid != left && mid != right) {
                vector<int> temp = {nums[left], nums[right], nums[mid]};
                int needInser = true;
                for(auto vec : ret){
                    if (vec[0] == temp[0] && vec[1] == temp[1] && vec[2] == temp[2]) {
                        needInser = false;
                        break;
                    }
                }
                if(needInser) ret.emplace_back(temp);
            }
            left++;
        }
    }
    return ret;
}
void test9(){
    cout << "---------test9-----------" << endl;
    vector<int> nums = {-1,0,1,2,-1,-4};
    nums = {0,1,1};
    nums = {0,0,0};
    nums = {1,2,-2,-1};
    vector<vector<int>> ret = threeSum(nums);
    for(auto vec : ret){
        for_each(vec.begin(), vec.end(), Display<int>());
        cout << endl;
    }
}

/*
 21. 合并两个有序链表
 将两个升序链表合并为一个新的 升序 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。
 */
ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    if (list1 == nullptr) return list2;
    if (list2 == nullptr) return list1;
    
    
    ListNode* l1 = new ListNode(list1->val);
    ListNode *ret = l1;
    
    ListNode *list1_1 = list1->next;
    while (list1_1) {
        ListNode* temp = new ListNode(list1_1->val);
        l1->next = temp;
        l1 = l1->next;
        list1_1 = list1_1->next;
    }
    
    ListNode *temp = ret;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = list2;
    
    ListNode *l2 = temp->next;
    l1 = ret;
    while (list1 || l2) {
        if (l2 && list1) {
            if (list1->val > l2->val) {
                l1->val = l2->val;
                l1 = l1->next;
                l2 = l2->next;
            }else{
                l1->val = list1->val;
                l1 = l1->next;
                list1 = list1->next;
            }
        }else{
            if(list1){
                l1->val = list1->val;
                l1 = l1->next;
                list1 = list1->next;
            }
            if(l2){
                l1->val = l2->val;
                l1 = l1->next;
                l2 = l2->next;
            }
        }
    }
    
    return ret;
}
void test10(){
    cout << "---------test10-----------" << endl;
    ListNode *head1 = new ListNode(2);
    ListNode *node1_1 = new ListNode(3);
    ListNode *node1_2 = new ListNode(5);
    head1->next = node1_1;
    node1_1->next = node1_2;
    
    ListNode *head2 = new ListNode(1);
    ListNode *node2_1 = new ListNode(4);
    ListNode *node2_2 = new ListNode(6);
    head2->next = node2_1;
    node2_1->next = node2_2;
    
    ListNode *newHead = mergeTwoLists(head1, head2);
    ListNode::display(newHead);
    cout << endl;
}

/*
 53. 最大子数组和
 给你一个整数数组 nums ，请你找出一个具有最大和的连续子数组（子数组最少包含一个元素），
 返回其最大和。子数组是数组中的一个连续部分。
 解法：动态规划
 dp[i][j]表示以i开始，以j结束的
 */

int maxSubArray(vector<int>& nums) {
    int len = (int)nums.size();
    if(len == 0) return 0;
    if(len == 1) return nums[0];
    vector<int> dp(nums.begin(), nums.end());
    dp[0] = nums[0]; int ret = dp[0];
    for (int i = 1; i < len; i++) {
        dp[i] = max(nums[i], dp[i-1] + nums[i]);
        ret = max(dp[i], ret);
    }
    return ret;
}
void test11(){
    cout << "---------test11-----------" << endl;
    vector<int> nums{-2,1,-3,4,-1,2,1,-5,4};
    nums = {1};
    nums = {5,4,-1,7,8};
    cout << maxSubArray(nums) << endl;
}

/*
 146. LRU 缓存
 */
class LRUCache {
public:
    class LRUCacheNode {
    public:
        LRUCacheNode* pre;
        LRUCacheNode* next;
        int key;
        int val;
        LRUCacheNode(int key, int value):key(key),val(value),pre(nullptr),next(nullptr){
            
        }
    };
public:
    unordered_map<int, LRUCacheNode*> hashMap = {};
    LRUCacheNode* dummmyHead;
    LRUCacheNode* tail;
    int capacity = 0;
    LRUCache(int capacity):capacity(capacity),tail(nullptr){
        dummmyHead = new LRUCacheNode(-1, -1);
    }
    
    int get(int key){
        if (hashMap.find(key) == hashMap.end())
            return -1;
        LRUCacheNode* node = hashMap[key];
        bringNodeToHead(node);
        return node->val;
    }
    
    void put(int key, int value){
        if (hashMap.find(key) == hashMap.end()){
            LRUCacheNode* node = new LRUCacheNode(key, value);
            hashMap[key] = node;
            inserNodeToHead(node);
            if (hashMap.size() > capacity) {
                hashMap.erase(tail->key);
                tail->pre->next = nullptr;
                tail = tail->pre;
            }
        }else{
            LRUCacheNode* node = hashMap[key];
            node->val = value;
            bringNodeToHead(node);
        }
    }
    
    void display(){
        LRUCacheNode *head = dummmyHead->next;
        while (head) {
            cout << head->val << " ";
            head = head->next;
        }
        cout << endl;
    }
private:
    void bringNodeToHead(LRUCacheNode *node){
        if (node == tail && node->pre) {
            LRUCacheNode *next = dummmyHead->next;
            node->next = next; next->pre = node;
            node->pre->next = nullptr;
            tail = node->pre;
            dummmyHead->next = node;
        }else{
            if (node == dummmyHead->next) return;
            node->pre->next = node->next;
            node->next->pre = node->pre;
            LRUCacheNode *next = dummmyHead->next;
            node->next = next; next->pre = node;
            dummmyHead->next = node;
        }
    }
    void inserNodeToHead(LRUCacheNode *node){
        if (dummmyHead->next == nullptr) {
            dummmyHead->next = node;
            tail = node;
        }else{
            LRUCacheNode *next = dummmyHead->next;
            node->next = next;
            next->pre = node;
            dummmyHead->next = node;
        }
    }
};

void test12(){
    cout << "---------test12-----------" << endl;
//    LRUCache *cache = new LRUCache(2);
//    cache->put(1,1); cache->display();
//    cache->put(2,2); cache->display();
//    cout << cache->get(1) << endl;cache->display();
//    cache->put(3, 3);cache->display();
//    cout << cache->get(2) << endl;cache->display();
//    cache->put(4, 4);cache->display();
//    cout << cache->get(1) << endl;cache->display();
//    cout << cache->get(3) << endl;cache->display();
//    cout << cache->get(4) << endl;cache->display();
    
    //[[2],[2],[2,6],[1],[1,5],[1,2],[1],[2]]
//    LRUCache *cache = new LRUCache(2);
//    cout << cache->get(2) << endl;cache->display();
//    cache->put(2, 6);cache->display();
//    cout << cache->get(1) << endl;cache->display();
//    cache->put(1, 5);cache->display();
//    cache->put(1, 2);cache->display();
//    cout << cache->get(1) << endl;cache->display();
//    cout << cache->get(2) << endl;cache->display();
    
//    [[3],[1,1],[2,2],[3,3],[4,4],[4],[3],[2],[1],[5,5],[1],[2],[3],[4],[5]]
    LRUCache *cache = new LRUCache(3);
    cache->put(1, 1);cache->display();
    cache->put(2, 2);cache->display();
    cache->put(3, 3);cache->display();
    cache->put(4, 4);cache->display();
    cout << cache->get(4) << endl;cache->display();
    cout << cache->get(3) << endl;cache->display();
    cout << cache->get(2) << endl;cache->display();
    cout << cache->get(1) << endl;cache->display();
    cache->put(5, 5);cache->display();
    cout << cache->get(1) << endl;cache->display();
    cout << cache->get(2) << endl;cache->display();
    cout << cache->get(3) << endl;cache->display();
    cout << cache->get(4) << endl;cache->display();
    cout << cache->get(5) << endl;cache->display();

}


/*
 23. 合并 K 个升序链表
 给你一个链表数组，每个链表都已经按升序排列。
 请你将所有链表合并到一个升序链表中，返回合并后的链表。
 */
ListNode* mergeKLists(ListNode* l1, ListNode* l2) {
    if(l1 == nullptr && l2 == nullptr) return nullptr;
    if(l1 == nullptr) return l2;
    if(l2 == nullptr) return l1;
    ListNode *fullHead = new ListNode(l1->val);
    ListNode *tempHead1 = l1;
    ListNode *tempFH = fullHead;
    while (tempHead1->next) {
        ListNode *temp = new ListNode(tempHead1->val);
        tempFH->next = temp;
        tempFH = tempFH->next;
        tempHead1 = tempHead1->next;
    }
    tempFH->next = l2;
    tempFH = fullHead;
    while (l1 || l2) {
        if (l1 && l2) {
            if (l1->val < l2->val) {
                tempFH->val = l1->val;
                tempFH = tempFH->next;
                l1 = l1->next;
            }else{
                tempFH->val = l2->val;
                tempFH = tempFH->next;
                l2 = l2->next;
            }
        }
        else if (l1) {
            tempFH->val = l1->val;
            tempFH = tempFH->next;
            l1 = l1->next;
        }
        else if (l2) {
            tempFH->val = l2->val;
            tempFH = tempFH->next;
            l2 = l2->next;
        }
    }
    return fullHead;
}
void mergeKLists(vector<ListNode*>& lists, ListNode* dummyHead) {
    lists.erase(std::remove(lists.begin(), lists.end(), nullptr), lists.end());
    int start = 0, end = (int)lists.size() - 1;
    ListNode* temp = new ListNode(-1);//同一个指针
    while (start < end) {
        temp->next = lists[start];
        ListNode* cur = mergeKLists(temp->next, lists[end]);
        if (!dummyHead->next) {
            dummyHead->next = cur;
        }
        temp = cur;
        while (temp && temp->next) {
            temp = temp->next;
        }
        start++; end--;
    }
    if (start == end) {//还剩下最后一个没有排序
        ListNode* cur = mergeKLists(dummyHead->next, lists[start]);
        dummyHead->next = cur;
    }
}

void mergeKLists1(vector<ListNode*>& lists, ListNode* dummyHead) {
    lists.erase(std::remove(lists.begin(), lists.end(), nullptr), lists.end());
    ListNode* temp = new ListNode(-1);
    int i = 1;
    for(; i < lists.size(); i++){
        temp->next = lists[i-1];
        ListNode* cur = mergeKLists(temp->next, lists[i]);
        if (!dummyHead->next) {
            dummyHead->next = cur;
        }
        temp = cur;
        while (temp && temp->next) {
            temp = temp->next;
        }
        i++;
    }
    if(i == lists.size()){
        ListNode* cur = mergeKLists(dummyHead->next, lists[i-1]);
        dummyHead->next = cur;
    }
}

ListNode* mergeKLists(vector<ListNode*>& lists) {
    if(lists.size() == 0) return nullptr;
    ListNode *dummyHead = new ListNode(-1);
    mergeKLists(lists, dummyHead);
    ListNode::display(dummyHead->next);
    cout << endl;
    return dummyHead->next;
}
void test18(){
    cout << "---------test18-----------" << endl;
    
//    lists = [[1,4,5],[1,3,4],[2,6]]
    
    ListNode *head1 = new ListNode(1);
    ListNode *node1_1 = new ListNode(4);
    ListNode *node1_2 = new ListNode(5);
    head1->next = node1_1;
    node1_1->next = node1_2;
    
    ListNode *head2 = new ListNode(1);
    ListNode *node2_1 = new ListNode(3);
    ListNode *node2_2 = new ListNode(4);
    head2->next = node2_1;
    node2_1->next = node2_2;
    
    ListNode *head3 = new ListNode(2);
    ListNode *node3_1 = new ListNode(6);
    head3->next = node3_1;
    
    vector<ListNode*> lists{head1, head2, head3};
    lists = {};
    lists = {{}};
    lists = {nullptr, head1, nullptr, head3};
    mergeKLists(lists);
}

int main(int argc, const char * argv[]) {
    test1();
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
    test12();
    test18();
    return 0;
}
