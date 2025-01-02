//
//  main.cpp
//  C++_Algorithm_top55
//
//  Created by sunjian on 2024/12/27.
//

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <deque>
#include <list>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <numeric>

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

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
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
 25. K 个一组翻转链表
 给你链表的头节点 head ，每 k 个节点一组进行翻转，请你返回修改后的链表。
 k 是一个正整数，它的值小于或等于链表的长度。如果节点总数不是 k 的整数倍，
 那么请将最后剩余的节点保持原有顺序。
 你不能只是单纯的改变节点内部的值，而是需要实际进行节点交换。
 */
pair<ListNode *, ListNode*> reverseKGroup(ListNode* head, ListNode *tail){
    ListNode *pre = tail->next;
    ListNode *cur = head;
    while (tail != pre) {
        ListNode *next = cur->next;
        cur->next = pre;
        pre = cur;
        cur = next;
    }
    return make_pair(tail, head);
}
ListNode* reverseKGroup(ListNode* head, int k) {
    if (head == nullptr || k < 0) return nullptr;
    ListNode *dummyHead = new ListNode(-1);
    dummyHead->next = head;
    ListNode *pre = dummyHead;
    while (head) {
        auto tail = pre;
        
        for(int i = 0; i < k; i++){
            tail = tail->next;
            if (!tail) {
                return dummyHead->next;
            }
        }
        
        ListNode *next = tail->next;
        
        tie(head, tail) = reverseKGroup(head, tail);
        
        pre->next = head;
        pre = tail;
        
        head = next;
    }
    return dummyHead->next;
}
void test13(){
    cout << "---------test13-----------" << endl;
    ListNode *head1 = new ListNode(1);
    ListNode *node1_1 = new ListNode(2);
    ListNode *node1_2 = new ListNode(3);
    ListNode *node1_3 = new ListNode(4);
    ListNode *node1_4 = new ListNode(5);
    ListNode *node1_5 = new ListNode(6);
    head1->next = node1_1;
    node1_1->next = node1_2;
    node1_2->next = node1_3;
    node1_3->next = node1_4;
    node1_4->next = node1_5;
    
    ListNode *head =  reverseKGroup(head1, 3);
    ListNode::display(head);
    cout << endl;
}

/*
 14. 买卖股票的最佳时机
 给定一个数组 prices ，它的第 i 个元素 prices[i] 表示一支给定股票第 i 天的价格。
 你只能选择 某一天 买入这只股票，并选择在 未来的某一个不同的日子 卖出该股票。
 设计一个算法来计算你所能获取的最大利润。返回你可以从这笔交易中获取的最大利润。如果你不能获取任何利润，返回 0 。
 解法：动态规划
 */
int maxProfit(vector<int>& prices) {
    int len = (int)prices.size();
    if(len <= 0) return 0;
    vector<int> dp(len, 0);
    dp[0] = 0;
    int minPrice = prices[0];
    for(int i = 1; i < len; i++){
        minPrice = min(minPrice, prices[i]);
        dp[i] = max(dp[i-1], prices[i] - minPrice);
    }
    return dp[len-1];
}
void test14(){
    cout << "---------test14-----------" << endl;
    vector<int> prices{7,6,4,3,1};
    cout << maxProfit(prices) << endl;
}

/*
 15. 分发糖果
 n 个孩子站成一排。给你一个整数数组 ratings 表示每个孩子的评分。
 你需要按照以下要求，给这些孩子分发糖果：
 每个孩子至少分配到 1 个糖果。
 相邻两个孩子评分更高的孩子会获得更多的糖果。
 请你给每个孩子分发糖果，计算并返回需要准备的 最少糖果数目 。
 */
int candy(vector<int>& ratings) {
    int len = (int)ratings.size();
    if(len <= 0) return 0;
    vector<int> candies(len, 1);
    for(int  i = 1; i < len; i++){
        if (ratings[i] > ratings[i-1]) {
            candies[i] = candies[i-1] + 1;
        }
    }
    for(int  i = len-2; i >= 0; i--){
        if (ratings[i] > ratings[i+1]) {
            candies[i] = max(candies[i], candies[i+1] + 1);
        }
    }
    return accumulate(candies.begin(), candies.end(), 0);
}

void test15(){
    cout << "---------test15-----------" << endl;
    vector<int> ratings{1,3,4,5,2};
    cout << candy(ratings) << endl;
}

/*
 16. 搜索旋转排序数组
 整数数组 nums 按升序排列，数组中的值 互不相同 。
 在传递给函数之前，nums 在预先未知的某个下标 k（0 <= k < nums.length）上进行了 旋转，使数组变为 [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]]（下标 从 0 开始 计数）。例如， [0,1,2,4,5,6,7] 在下标 3 处经旋转后可能变为 [4,5,6,7,0,1,2] 。

 给你 旋转后 的数组 nums 和一个整数 target ，如果 nums 中存在这个目标值 target ，则返回它的下标，否则返回 -1 。

 你必须设计一个时间复杂度为 O(log n) 的算法解决此问题。
 解法：二分查找
 */
int search(vector<int>& nums, int target) {
    int len = (int)nums.size();
    if(len <= 0) return -1;
    if(len == 1) return nums[0] == target ? 0 : -1;
    int start = 0, end = len - 1;
    while (start <= end) {
        int mid = start + (end - start)/2;
        if (target == nums[mid]) return mid;
        if (nums[start] <= nums[mid]) {//左边递增序列
            if (nums[start] <= target && target < nums[mid]) {
                end = mid - 1;
            }else{
                start = mid + 1;
            }
        }else{//右边递增序列
            if (nums[mid] < target && target <= nums[end]) {
                start = mid + 1;
            }else{
                end = mid - 1;
            }
        }
    }
    return -1;
}
void test16(){
    cout << "---------test16-----------" << endl;
    vector<int> nums = {4,5,6,7,0,1,2};
    nums = {1,3,5};
    cout << search(nums, 5) << endl;
}

/*
 17.有效括号
 */
bool isRight(char ch){
    return ch == ')' || ch == '}' || ch == ']';
}
bool isLeft(char ch){
    return ch == '(' || ch == '{' || ch == '[';
}
bool isValid(string s) {
    if (s.length() <= 1) return false;
    stack<char> chars;
    stack<char> right;
    for(auto ch : s){
        chars.push(ch);
    }
    char ch = chars.top();
    if(isLeft(ch)) return false;
    while (!chars.empty()) {
        if (isRight(chars.top())) {
            right.push(chars.top());
            chars.pop();
        }else{
            if (right.empty()) return false;
            switch (right.top()) {
                case ')':
                    if (chars.top() != '(') {
                        return false;
                    }
                    chars.pop();
                    right.pop();
                    break;
                case ']':
                    if (chars.top() != '[') {
                        return false;
                    }
                    chars.pop();
                    right.pop();
                    break;
                case '}':
                    if (chars.top() != '{') {
                        return false;
                    }
                    chars.pop();
                    right.pop();
                    break;
            }
        }
    }
    return chars.empty() && right.empty();
}
void test17(){
    cout << "---------test17-----------" << endl;
    cout << isValid("()") << endl;
    //()[]{}
    cout << isValid("()[]{}") << endl;
    //(]
    cout << isValid("(]") << endl;
    //([])
    cout << isValid("([)]") << endl;
    //([])
    cout << isValid("([])") << endl;
    
    cout << isValid(")(){}") << endl;
    
    cout << isValid("([]") << endl;
}

/*
 18. 合并 K 个升序链表
 给你一个链表数组，每个链表都已经按升序排列。
 请你将所有链表合并到一个升序链表中，返回合并后的链表。
 */
ListNode* mergeKLists(ListNode* l1, ListNode* l2) {
    if(!l1 || !l2) return l1 ? l1 : l2;
    ListNode head, *tail = &head; ListNode * head1 = l1; ListNode * head2 = l2;
    while (head1 && head2) {
        if (head1->val > head2->val) {
            tail->next = head2; head2 = head2->next;
        }else{
            tail->next = head1; head1 = head1->next;
        }
        tail = tail->next;
    }
    tail->next = head1 ? head1 : head2;
    return head.next;
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
    ListNode* dummyHead = nullptr;
    for(auto node : lists){
        dummyHead = mergeKLists(dummyHead, node);
    }
//    ListNode::display(dummyHead);
    return dummyHead;
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
//    lists = {};
//    lists = {{}};
//    lists = {nullptr, head1, nullptr, head3};
    mergeKLists(lists);
}
/*
 19. 合并区间
 以数组 intervals 表示若干个区间的集合，其中单个区间为 intervals[i] = [starti, endi] 。请你合并所有重叠的区间，并返回 一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间 。
 解法一:1.sort 2.merge
 解法二：1.sort 2.merge
 */
bool merge(vector<int>& v1, vector<int>& v2){
    if (v1[1] >= v2[0]) {
        v1[1] = max(v1[1], v2[1]);
        return true;
    }
    return false;
}
vector<vector<int>> merge(vector<vector<int>>& intervals) {
    if(intervals.size() == 0) return {};
    vector<vector<int>> ret = {};
    //1.sort
    sort(intervals.begin(), intervals.end());
    //2.merge
    vector<int> temp = intervals[0];
    for(int i = 1; i < intervals.size(); i++){
        if (!merge(temp, intervals[i])) {
            ret.push_back(temp);
            temp = intervals[i];
        }
    }
    ret.push_back(temp);
    return ret;
}
vector<vector<int>> merge1(vector<vector<int>>& intervals) {
    if(intervals.size() == 0) return {};
    vector<vector<int>> ret = {};
    //1.sort
    sort(intervals.begin(), intervals.end(), [](vector<int> l, vector<int> r){
        return l[0] < r[0];
    });
    //2.双指针
    for(int i = 0; i < intervals.size(); ){
        int j = i + 1;
        int t = intervals[i][1];
        while (j < intervals.size() && intervals[j][0] <= t) {
            t = max(intervals[j][1], t);
            j++;
        }
        ret.push_back({intervals[i][0], t});
        i = j;
    }
    return ret;
}
void test19(){
    cout << "---------test19-----------" << endl;
    vector<vector<int>> lists{{1,3},{2,6},{8,10},{15,18}};
    auto ret = merge(lists);
    for(auto& vec : ret){
        for_each(vec.begin(), vec.end(), Display<int>());
        cout << endl;
    }
}

/*
 20. 整数反转
 给你一个 32 位的有符号整数 x ，返回将 x 中的数字部分反转后的结果。
 如果反转后整数超过 32 位的有符号整数的范围 [−231,  231 − 1] ，就返回 0。
 假设环境不允许存储 64 位整数（有符号或无符号）。
 */
int reverse(int x) {
    int reversed = 0;
    
    while (x != 0) {
        int digit = x % 10;  // 获取当前的个位数字
        x /= 10;  // 删除个位数字
        
        // 溢出检查：如果反转后的数字超出 32 位有符号整数的范围
        if (reversed > INT_MAX / 10 || (reversed == INT_MAX / 10 && digit > 7)) {
            return 0;  // 超过 INT_MAX，溢出
        }
        if (reversed < INT_MIN / 10 || (reversed == INT_MIN / 10 && digit < -8)) {
            return 0;  // 小于 INT_MIN，溢出
        }
        
        reversed = reversed * 10 + digit;  // 将数字添加到反转结果中
    }
    
    return reversed;
}
void test20(){
    cout << "------------test20-----------" << endl;
    cout << reverse(-2147483412) << endl;
}

/*
 21. 字典序的第K小数字
 给定整数 n 和 k，返回  [1, n] 中字典序第 k 小的数字。
 */
int count_steps(int cur, int n){
    int ret = 0;
    int first = cur, last = cur;
    while (first <= n) {
        ret += min(n, last) - first + 1;
        first *= 10;
        last  *= 10 + 9;
    }
    return ret;
}
int findKthNumber(int n, int k) {
    int cur = 1;
    k--;
    while (k > 0) {
        int steps = count_steps(cur, n);
        //这里是跳跃的过程
        if(steps <= k){
            cur++;
            k -= steps;
        }else{
            cur = cur * 10;
            k--;
        }
    }
    return cur;
}
void test21(){
    cout << "--------------test21-------------" << endl;
    cout << findKthNumber(25, 5) << endl;
}

/*
 22. 回文数
 给你一个整数 x ，如果 x 是一个回文整数，返回 true ；否则，返回 false 。
 回文数
 是指正序（从左向右）和倒序（从右向左）读都是一样的整数。
 例如，121 是回文，而 123 不是。
 */
bool isPalindrome(int x) {
    if(x < 0) return false;
    if(x > 0 && x < 10) return true;
    string xStr = to_string(x);
    int i = 0, j = (int)xStr.length() - 1;
    while (i < j) {
        if(xStr[i] != xStr[j]) return false;
        i++; j--;
    }
    return true;
}
void test22(){
    cout << "--------------test22-------------" << endl;
    cout << isPalindrome(121) << endl;
}

/*
 23. 数组中的第K个最大元素
 给定整数数组 nums 和整数 k，请返回数组中第 k 个最大的元素。
 请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。
 你必须设计并实现时间复杂度为 O(n) 的算法解决此问题。
 */
int findKthLargest(vector<int>& nums, int k) {
    if(nums.size() == 0) return 0;
    if(k > nums.size()) return 0;
    if(nums.size() == 1 && k == 1) return nums[0];
    sort(nums.begin(), nums.end(), [](int l, int r){
        return l > r;
    });
    return nums[k-1];
}
void test23(){
    cout << "---------test23-----------" << endl;
    vector<int> nums{3,2,1,5,6,4}; int k = 2;
    nums = {3,2,3,1,2,4,5,5,6}; k = 4;
//    nums = {2,1}; k = 1;
    cout << findKthLargest(nums, k) << endl;
}

/*
 24. 全排列
 给定一个不含重复数字的数组 nums ，返回其 所有可能的全排列 。你可以 按任意顺序 返回答案。
 */
void permute(vector<int>& nums, int start, vector<vector<int>>& ret) {
    if(start == nums.size()){
        ret.push_back(nums);
        return;
    }
    for(int i = start; i < nums.size(); i++){
        swap(nums[i], nums[start]);
        permute(nums, start+1, ret);
        swap(nums[i], nums[start]);
    }
}

vector<vector<int>> permute(vector<int>& nums) {
    if(nums.size() == 0) return {};
    vector<vector<int>> ret = {};
    permute(nums, 0, ret);
    return ret;
}
void test24(){
    cout << "---------test24-----------" << endl;
    vector<int> nums = {1,2,3};
    auto ret = permute(nums);
    for (auto& vec : ret) {
        for_each(vec.begin(), vec.end(), Display<int>());
        cout << endl;
    }
}

/*
 25. 删除链表的倒数第 N 个结点
 给你一个链表，删除链表的倒数第 n 个结点，并且返回链表的头结点。
 */
ListNode* removeNthFromEnd(ListNode* head, int n) {
    if (head == nullptr) return head;
    ListNode *dummy = new ListNode(-1);
    dummy->next = head;
    ListNode *slow = dummy, *fast = dummy;
    
    while (n-- >= 0) {
        fast = fast->next;
    }

    while (fast) {
        slow = slow->next;
        fast = fast->next;
    }
    
    if (slow->next) {
        slow->next = slow->next->next;
    }
    
    return dummy->next;
}
void test25(){
    cout << "-------------test25-----------" << endl;
    ListNode *head1 = new ListNode(1);
    ListNode *node1_1 = new ListNode(2);
    ListNode *node1_2 = new ListNode(6);
    ListNode *node1_3 = new ListNode(5);
    ListNode *node1_4 = new ListNode(4);
    ListNode *node1_5 = new ListNode(3);
//    head1->next = node1_1;
//    node1_1->next = node1_2;
//    node1_2->next = node1_3;
//    node1_3->next = node1_4;
//    node1_4->next = node1_5;
    auto ret = removeNthFromEnd(head1, 1);
    ListNode::display(ret);
    cout << endl;
}

/*
 26.下一个排列
 1.从右到左，找到第一个 nums[i] < nums[i+1]。
 2.如果没有找到，说明当前排列已经是最大排列，直接反转整个数组。
 3.否则，找到从右侧开始大于 nums[i] 的第一个的元素，并与 nums[i] 交换。
 4.最后，反转 i+1 之后的部分，得到下一个排列。
 */
void nextPermutation(vector<int>& nums) {
    int len = (int)nums.size();
    if(len <= 0) return;
    int begin = 0;
    for(int i = len - 2; i >= 0; i--){
        if (nums[i] < nums[i + 1]) {
            int j = len - 1;
            while (nums[j] <= nums[i]) {
                j--;
            }
            swap(nums[i], nums[j]);
            begin = i + 1;
            break;
        }
    }
    reverse(nums.begin()+begin, nums.end());
}

void test26(){
    cout << "---------test26-----------" << endl;
    vector<int> nums{2,3,1,3,3};
    nums = {4,7,5,3,2};
    nextPermutation(nums);
    for_each(nums.begin(), nums.end(), Display<int>());
    cout << endl;
}

/*
 27. 编辑距离
 给你两个单词 word1 和 word2， 请返回将 word1 转换成 word2 所使用的最少操作数  。
 你可以对一个单词进行如下三种操作：
 插入一个字符
 删除一个字符
 替换一个字符
 解法一：动态规划
 dp[i][j] : 从 s1[0][i] 转换到 s2[0][j]所有需要的最少操作
 */
int minDistance(string word1, string word2) {
    int l1 = (int)word1.length(), l2 = (int)word2.length();
    vector<vector<int>> dp(l1+1, vector<int>(l2+1, 0));
    dp[0][0] = 0;
    for(int i = 1; i <= l1; i++){
        dp[i][0] = i;
    }
    for(int i = 1; i <= l2; i++){
        dp[0][i] = i;
    }
    for(int row = 1; row <= l1; row++){
        for(int col = 1; col <= l2; col++){
            if (word1[row - 1] == word2[col - 1]) {
                dp[row][col] = dp[row-1][col-1];
            }else{
                dp[row][col] = min({dp[row-1][col] + 1,dp[row][col-1] + 1, dp[row-1][col-1] + 1});
            }
        }
    }
    return dp[l1][l2];
}
void test27(){
    cout << "---------test27-----------" << endl;
    cout << minDistance("horse", "ros") << endl;
}


/*
 30. 爬楼梯
 */

int climbStairs(int n) {
    if(n <= 2) return n;
    vector<int> dp = vector<int>(n, 0);
    dp[0] = 0;
    dp[1] = 1;
    dp[2] = 2;
    for(int i = 3; i <= n; i++){
        dp[i] = dp[i-1] + dp[i-2];
    }
    return dp[n];
}
void test30(){
    cout << "---------test30-----------" << endl;
    cout << climbStairs(3) << endl;
}

/*
 32. 相交链表
 给你两个单链表的头节点 headA 和 headB ，请你找出并返回两个单链表相交的起始节点。
 如果两个链表不存在相交节点，返回 null 。
 解法：将两个链表相加
 */
ListNode *getIntersectionNode(ListNode *A, ListNode *B) {
    if(!A || !B) return A ? A : B;
    ListNode *headA = A, *headB = B;
    
    ListNode* dummyA = new ListNode(headA->val); ListNode* dummyA_ = dummyA;
    headA = headA->next;
    while (headA) {
        ListNode* temp = new ListNode(headA->val);
        dummyA_->next = temp;
        dummyA_ = dummyA_->next;
        headA = headA->next;
    }
    ListNode* dummyB = new ListNode(headB->val); ListNode* dummyB_ = dummyB;
    headB = headB->next;
    while (headB) {
        ListNode* temp = new ListNode(headB->val);
        dummyB_->next = temp;
        dummyB_ = dummyB_->next;
        headB = headB->next;
    }

    ListNode *ret = nullptr;
    dummyA_ = dummyA; dummyB_ = dummyB;
    while (dummyB_->next) {
        dummyB_ = dummyB_->next;
    }
    while (dummyA_->next) {
        dummyA_ = dummyA_->next;
    }
    
    dummyB_->next = A; dummyA_->next = B;
    
    while (dummyA && dummyB) {
        if (dummyA == dummyB) {
            return dummyB;
        }
        dummyA = dummyA->next;
        dummyB = dummyB->next;
    }
    
    return ret;
}
void test32(){
    cout << "---------test32-----------" << endl;
    ListNode *head1 = new ListNode(1);
    ListNode *node1_1 = new ListNode(2);
    ListNode *node1_2 = new ListNode(3);
    ListNode *node1_3 = new ListNode(4);
    
    head1->next = node1_1;
    node1_1->next = node1_2;
    node1_2->next = node1_3;
    
    ListNode *head2 = new ListNode(2);
    head2->next = node1_2;
    
    ListNode *node = getIntersectionNode(head1, head2);
    ListNode::display(node);
    cout << endl;
}

/*
 中序遍历
 */
void inorderTraversal(vector<int>& vec,TreeNode* root){
    if(root == nullptr) return;
    inorderTraversal(vec, root->left);
    vec.push_back(root->val);
    inorderTraversal(vec, root->right);
}
vector<int> inorderTraversal(TreeNode* root) {
    vector<int> ret;
    inorderTraversal(ret, root);
    return ret;
}
void test33(){
    cout << "---------test33-----------" << endl;
    TreeNode *root = new TreeNode(1);
    TreeNode *left = new TreeNode(2);
    TreeNode *right = new TreeNode(3);
    
    root->right = left;
    left->left = right;
    
    auto vec = inorderTraversal(root);
    for_each(vec.begin(), vec.end(), Display<int>());
    cout << endl;
}

/*
 层序遍历
 */
void levelTraversal(vector<vector<int>>& vec,TreeNode* root){
    if(root == nullptr) return;
    deque<TreeNode *> deque;
    deque.push_back(root);
    while (!deque.empty()) {
        int size = (int)deque.size();
        vec.push_back(vector<int>());
        for(int i = 0; i < size; i++){
            auto node = deque.front();
            vec.back().push_back(node->val);
            deque.pop_front();
            if(node->left) deque.push_back(node->left);
            if(node->right) deque.push_back(node->right);
        }
    }
}
vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> ret;
    levelTraversal(ret, root);
    return ret;
}
void test34(){
    cout << "---------test34-----------" << endl;
    TreeNode *root = new TreeNode(1);
    TreeNode *left = new TreeNode(2);
    TreeNode *right = new TreeNode(3);
    
    root->right = left;
    left->left = right;
    
    vector<vector<int>> vec = levelOrder(root);
    for(auto& vec : vec){
        for_each(vec.begin(), vec.end(), Display<int>());
        cout << endl;
    }
}

/*
 35. 二叉树的锯齿形层序遍历
 给你二叉树的根节点 root ，返回其节点值的 锯齿形层序遍历 。
 （即先从左往右，再从右往左进行下一层遍历，以此类推，层与层之间交替进行）。
 */
vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    vector<vector<int>> ret = {};
    if(root == nullptr) return ret;
    queue<TreeNode *> q = {};
    q.push(root);
    bool dire = false;
    while (!q.empty()) {
        int size = (int)q.size();
        deque<int> dq = {};
        for(int i = 0; i < size; i++){
            auto node = q.front();
            q.pop();
            if (!dire) {
                dq.push_back(node->val);
            }else{
                dq.push_front(node->val);
            }
            if(node->left) q.push(node->left);
            if(node->right) q.push(node->right);
        }
        ret.emplace_back(vector<int>(dq.begin(), dq.end()));
        dire = !dire;
    }
    return ret;
}
void test35(){
    cout << "---------test35-----------" << endl;
    TreeNode *root = new TreeNode(1);
    TreeNode *left = new TreeNode(2);
    TreeNode *right = new TreeNode(3);
    
    root->left = left;
    root->right = right;
    
    TreeNode *left1 = new TreeNode(4);
    TreeNode *right1 = new TreeNode(5);
    
    left->left = left1;
    right->right = right1;
    
    
    auto ret = zigzagLevelOrder(root);
    for(auto vec : ret){
        for_each(vec.begin(), vec.end(), Display<int>());
        cout << endl;
    }
}

/*
 88. 合并两个有序数组
 给你两个按 非递减顺序 排列的整数数组 nums1 和 nums2，另有两个整数 m 和 n ，分别表示 nums1 和 nums2 中的元素数目。
 请你 合并 nums2 到 nums1 中，使合并后的数组同样按 非递减顺序 排列。
 注意：最终，合并后数组不应由函数返回，而是存储在数组 nums1 中。为了应对这种情况，nums1 的初始长度为 m + n，其中前 m 个元素表示应合并的元素，后 n 个元素为 0 ，应忽略。nums2 的长度为 n 。
 */
void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    for(int i = m; i < nums1.size(); i++){
        nums1[i] = nums2[i-m];
    }
    vector<int> leftCopy(nums1.begin(), nums1.begin()+m);
    int l = 0, t = 0, r = m, len = (int)nums1.size();
    while (l < m && r < len) {
        if (leftCopy[l] < nums1[r]) {
            nums1[t++] = leftCopy[l++];
        }else{
            nums1[t++] = nums1[r++];
        }
    }
    while (l < m) {
        nums1[t++] = leftCopy[l++];
    }
}
void test42(){
    cout << "-------------test42-----------" << endl;
    //输入：nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
    int m = 3;
    vector<int> num1(6, 0);
    for(int i = 1; i <= m; i++){
        num1[i-1] = i;
    }
    int n = 3;
    vector<int> num2{2,5,6};
    merge(num1, m, num2, n);
    for_each(num1.begin(), num1.end(), Display<int>());
    cout << endl;
}

/*
 43. 重排链表
 给定一个单链表 L 的头节点 head ，单链表 L 表示为：L0 → L1 → … → Ln - 1 → Ln
 请将其重新排列后变为：L0 → Ln → L1 → Ln - 1 → L2 → Ln - 2 → …
 不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。
 解法：求逆序
 */
ListNode *reverseNode(ListNode *head){
    ListNode *pre = nullptr;
    ListNode *cur = head;
    while (cur) {
        ListNode *next = cur->next;
        cur->next = pre;
        pre = cur;
        cur = next;
    }
    return pre;
}
void reorderList(ListNode* head) {
    if (head == nullptr) return;
    ListNode *temp = head;
    ListNode *newHead = new ListNode(temp->val);
    temp = temp->next; ListNode *nnHead = newHead;
    int count = 1;
    while (temp) {
        ListNode *cur = new ListNode(temp->val);
        temp = temp->next;
        nnHead->next = cur;
        nnHead = nnHead->next;
        count++;
    }
    ListNode *reorderNode = reverseNode(newHead);
    ListNode *cur = head;
    ListNode *dummy = new ListNode(-1);
    ListNode *pre = dummy;
    int i = 0;
    while (count-- > 0) {
        if ((i++ & 1) == 0) {
            pre->next = cur;
            cur = cur->next;
        }else{
            pre->next = reorderNode;
            reorderNode = reorderNode->next;
        }
        pre = pre->next;
    }
    pre->next = nullptr;
    head = dummy->next;
}
void test43(){
    cout << "-------------test43-----------" << endl;
    ListNode *head1 = new ListNode(1);
    ListNode *node1_1 = new ListNode(2);
    ListNode *node1_2 = new ListNode(3);
    ListNode *node1_3 = new ListNode(4);
    ListNode *node1_4 = new ListNode(5);
    ListNode *node1_5 = new ListNode(6);
    head1->next = node1_1;
    node1_1->next = node1_2;
    node1_2->next = node1_3;
    node1_3->next = node1_4;
    node1_4->next = node1_5;
    
    ListNode::display(head1);
    cout << endl;
    reorderList(head1);
    ListNode::display(head1);
    cout << endl;
}

/*
 44. 最长公共前缀
 编写一个函数来查找字符串数组中的最长公共前缀。
 如果不存在公共前缀，返回空字符串 ""。
 */
string longestCommonPrefix(vector<string>& strs) {
    if (strs.size() == 0) return "";
    string str1 = strs[0];
    int index = 0; bool flag = false;
    for(; index < str1.length(); index++){
        for(int i = 1; i < strs.size(); i++){
            if (str1[index] != strs[i][index]) {
                flag = true;
                break;
            }
        }
        if(flag) break;
    }
    return string(str1.begin(), str1.begin()+index);
}
void test44(){
    cout << "-------------test44-----------" << endl;
    vector<string> strs = {"dog","racecar","car"};
    cout << longestCommonPrefix(strs) << endl;
}

/*
 48. 两两交换链表中的节点
 给你一个链表，两两交换其中相邻的节点，并返回交换后链表的头节点。
 你必须在不修改节点内部的值的情况下完成本题（即，只能进行节点交换）。
 解法： K个一组反转列表的特例
 */
pair<ListNode*, ListNode*> swapPairs(ListNode* head, ListNode *tail){
    ListNode *pre = tail->next;
    ListNode *cur = head;
    while (pre != tail) {
        ListNode *next = cur->next;
        cur->next = pre;
        pre = cur;
        cur = next;
    }
    return make_pair(tail, head);
}

ListNode *swapPairs(ListNode* head, int k){
    if(head == nullptr) return head;
    ListNode *dummy = new ListNode(-1);
    dummy->next = head;
    ListNode *pre = dummy;
    
    while (head) {
        auto tail = pre;
        for(int i = 0; i < k; i++){
            tail = tail->next;
            if(!tail) return dummy->next;
        }
        auto next = tail->next;
        
        tie(head, tail) = swapPairs(head, tail);
        
        pre->next = head;
        pre = tail;
        
        head = next;
    }
    return dummy->next;
}
ListNode* swapPairs(ListNode* head) {
    return swapPairs(head, 2);
}
void test48(){
    cout << "-------------test48-----------" << endl;
    ListNode *head1 = new ListNode(1);
    ListNode *node1_1 = new ListNode(2);
    ListNode *node1_2 = new ListNode(6);
    ListNode *node1_3 = new ListNode(5);
    ListNode *node1_4 = new ListNode(4);
    ListNode *node1_5 = new ListNode(3);
    head1->next = node1_1;
    node1_1->next = node1_2;
    node1_2->next = node1_3;
    node1_3->next = node1_4;
    node1_4->next = node1_5;
    
    ListNode::display(head1);
    cout << endl;
    auto head = swapPairs(head1);
    ListNode::display(head);
    cout << endl;
}

/*
 51. 排序链表
 给你链表的头结点 head ，请将其按 升序 排列并返回 排序后的链表 。
 要求：时间： nlogn 空间：常数
 直接使用mergeSort
 */
ListNode *merge(ListNode *l, ListNode *r){
    if(l == nullptr || r == nullptr) return l ? l : r;
    ListNode *dummy = new ListNode(0);
    ListNode *cur = dummy;
    while (l && r) {
        if(l->val < r->val){
            cur->next = l; l = l->next;
        }else{
            cur->next = r; r = r->next;
        }
        cur = cur->next;
    }
    if (l) cur->next = l;
    if (r) cur->next = r;
    return dummy->next;
}

ListNode *findMiddle(ListNode *head){
    if (head == nullptr) return head;
    ListNode *slow = head, *fast = head->next;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

ListNode *mergeSort(ListNode *head){
    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    ListNode *mid = findMiddle(head);
    ListNode *left = head;
    ListNode *right = mid->next;
    mid->next = nullptr;
    
    return merge(mergeSort(left), mergeSort(right));
}

ListNode* sortList(ListNode* head) {
    if(head == nullptr) return head;
    head = mergeSort(head);
    return head;
}

void test51(){
    cout << "-------------test51-----------" << endl;
    ListNode *head1 = new ListNode(1);
    ListNode *node1_1 = new ListNode(2);
    ListNode *node1_2 = new ListNode(6);
    ListNode *node1_3 = new ListNode(5);
    ListNode *node1_4 = new ListNode(4);
    ListNode *node1_5 = new ListNode(3);
    head1->next = node1_1;
    node1_1->next = node1_2;
    node1_2->next = node1_3;
    node1_3->next = node1_4;
    node1_4->next = node1_5;
    auto ret = sortList(head1);
    ListNode::display(ret);
    cout << endl;
}


/*
 55. 删除有序数组中的重复项
 给你一个 非严格递增排列 的数组 nums ，请你 原地 删除重复出现的元素，使每个元素 只出现一次 ，返回删除后数组的新长度。元素的 相对顺序 应该保持 一致 。然后返回 nums 中唯一元素的个数。

 考虑 nums 的唯一元素的数量为 k ，你需要做以下事情确保你的题解可以被通过：

 更改数组 nums ，使 nums 的前 k 个元素包含唯一元素，并按照它们最初在 nums 中出现的顺序排列。nums 的其余元素与 nums 的大小不重要。
 返回 k 。
 */
int removeDuplicates(vector<int>& nums) {
    if(nums.size() == 0) return 0;
    map<int, int> map = {};
    for(int i = 0; i < nums.size(); i++){
        map[nums[i]] = i;
    }
    nums.clear();
    for(auto& pair : map){
        nums.push_back(pair.first);
    }
    return (int)(nums.size());
}
void test55(){
    cout << "-------------test55-----------" << endl;
    vector<int> nums{0,0,1,1,1,2,2,3,3,4};
    nums = {1,1,2};
    nums = {0, 3};
    auto ret = removeDuplicates(nums);
    cout << ret << endl;
    for_each(nums.begin(), nums.end(), Display<int>());
    cout << endl;
}

/*
 56. 反转链表 II
 给你单链表的头指针 head 和两个整数 left 和 right ，其中 left <= right 。
 请你反转从位置 left 到位置 right 的链表节点，返回 反转后的链表 。
 */
pair<ListNode*, ListNode*> reverseBetween(ListNode* head, ListNode *tail) {
    auto pre = tail->next;
    auto cur = head;
    while (tail != pre) {
        auto next = cur->next;
        cur->next = pre;
        pre = cur;
        cur = next;
    }
    return make_pair(tail, head);
}
ListNode* reverseBetween(ListNode* head, int left, int right) {
    if(head == nullptr || right <= left) return head;
    ListNode *dummyHead = new ListNode(-1);
    dummyHead->next = head;
    ListNode *cur = head;
    ListNode *leftNodePre = nullptr;  ListNode *leftNode = nullptr; ListNode *rightNode = nullptr;
    int index = 1;
    while (cur) {
        if(index == left-1) leftNodePre = cur;
        if(index == left) leftNode = cur;
        if(index == right) rightNode = cur;
        cur = cur->next;
        index++;
    }
    tie(leftNode, rightNode) = reverseBetween(leftNode, rightNode);
    
    if(leftNodePre)
        leftNodePre->next = leftNode;
    else
        dummyHead->next = leftNode;

    return dummyHead->next;
}
void test56(){
    cout << "-------------test56-----------" << endl;
    ListNode *head1 = new ListNode(1);
    ListNode *node1_1 = new ListNode(2);
//    ListNode *node1_2 = new ListNode(3);
//    ListNode *node1_3 = new ListNode(4);
//    ListNode *node1_4 = new ListNode(5);
//    ListNode *node1_5 = new ListNode(6);
    head1->next = node1_1;
//    node1_1->next = node1_2;
//    node1_2->next = node1_3;
//    node1_3->next = node1_4;
//    node1_4->next = node1_5;
    ListNode *newHead = reverseBetween(head1, 1, 2);
    ListNode::display(newHead);
    cout << endl;
    
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
    test13();
    test14();
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
    test30();
    test32();
    test33();
    test34();
    test35();
    test42();
    test43();
    test44();
    test48();
    test51();
    test55();
    test56();
    return 0;
}
