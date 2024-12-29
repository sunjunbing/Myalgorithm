//
//  main.cpp
//  C++_Algorithm_Array
//
//  Created by sunjian on 2024/11/6.
//

#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

struct Display{
    void operator()(int a){
        cout << a << " ";
    }
};

/*
 找出数组中重复的数字:
 在一个长度为 n 的数组中的所有数字都是在0～n-1的范围内，数组中的某些数字是重复的，
 但是不知道有几个数字重复了，也不知道每个数字重复了几次，请找出数组中任意重复的数字。
 */
void Array1(){

    //解法一：先排序，再找
    vector<int> array{0, 1, 5, 5, 3, 3, 4};
    auto findRepeatNumber = [](vector<int>& array){//传递的是引用
        //使用最简单的排序算法bubblesort
        for(int end = (int)(array.size() - 1); end > 0; end--){
            for (int begin = 1; begin <= end; begin++) {
                if (array[begin] < array[begin-1]) {
                    int temp = array[begin];
                    array[begin] = array[begin-1];
                    array[begin-1] = temp;
                }
            }
        }
        for (auto it = array.begin()+1; it != array.end(); it++) {
            if (*it == *(it - 1)) {
                cout << *it << ' ';
            }
        }
    };
    findRepeatNumber(array);
    cout << endl;
    //解法二：涉及到重复性问题直接用 HashMap
    vector<int> array1{0, 1, 5, 5, 3, 3, 4};
    auto findRepeatNum2 = [](vector<int>& array) {
        map<int, int> map;
        for (int i = 0; i < array.size(); i++) {
            if(map[array[i]] == 0){
                map[array[i]]++;
            }else{
                cout << array[i] << ' ';
            }
        }
    };
    findRepeatNum2(array1);
    cout << endl;
    //解法三：原地交换
    /* eing     这个题目有一个特点就是，给定的数组的元素范围【0，n-1】
     1.cmp(i, m) = 0, i++
     2.cmp(m, array[m]) == 0, 找到了一个重复的
     3.swap(m, array[m])
     4.continue
     */
    auto findRepeatNum3 = [](vector<int>& array) -> set<int>{
        set<int> set;
        for (int i = 0; i < (int)array.size(); i++) {
            while (i != array[i]) {
                int m = array[i];
                if (m == array[m]) {
                    set.insert(m);
                    break;
                }else{
                    int temp = array[m];
                    array[m] = m;
                    array[i] = temp;
                }
            }
        }
        return std::set<int>(set);
    };
    set<int> set = findRepeatNum3(array1);
    if(set.size() > 0){
        for (auto it = set.begin(); it != set.end(); it++) {
            cout << *it << " ";
        }
    }
    cout << endl;
}

/*
 不修改数组找出重复的数字
 在一个长度为 n+1 的数组中所有的数字都是 1～n的范围内，所有数字中至少有一个数字是重复的。
 请找出数组中任意重复的数字，但不能修改输入的数组。
 */
void Array2(){
    //首先想到的肯定是用 Map，但是上面已经用过了，这里就不用了
    //解法 1：利用辅助数组
    vector<int> array{2,3,5,4,3,2,6,7};
    auto findRepeatNum1 = [](vector<int>& array){
        int len = (int)array.size() + 1;
        vector<int> curArra(len, 0);
        for(auto it = array.begin(); it != array.end(); it++){
            if (curArra[*it] != 0) {
                cout << *it << ' ';
            }else{
                curArra[*it] = *it;
            }
        }
    };
    findRepeatNum1(array);
    cout << endl;
    
    /*
     解法 2：BinarySearch
     */
    auto findRepeatNum2 = [](vector<int>& array) -> int{
        int start = 1, end = (int)array.size() - 1;
        while (start <= end) {
            int middle = (end - start)/2 + start;
            auto filter = [](vector<int>&vec, int start, int middle) -> int {
                int ret = 0;
                for (auto it = vec.begin(); it != vec.end(); it++) {
                    if (*it >= start && *it <= middle ) {
                        ret++;
                    }
                }
                return ret;
            };
            int count = filter(array, start, middle);
            if (start == end) {
                if (count > 1) {
                    return start;
                }else{
                    break;
                }
            }
            if (count > middle - start + 1) {//重复的数字在左边
                end = middle;
            }else{//重复的数字在右边
                start = middle + 1;
            }
        }
        return -1;
    };
    cout << findRepeatNum2(array) << endl;
}

/*
 二维数组中的查找
 在一个二维数组中，
 每一行都按从左到右递增的顺序排序，
 每一列都按从上到下递增的顺序排序，
 输入一个二维数组和一个整数，判断二维数组中是否包含这个整数
 */
void Array3(){

    vector<vector<int>> matrix(4, vector<int>(4));
    int stride = 4;
    int origin = 5;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matrix[i][j] = stride * i + j + origin;
        }
    }
    
    auto findNumIn2DArray = [](vector<vector<int>>& array, int target) -> bool {
        int rows = (int)array.size();
        int cols = (int)array[0].size();
        int row = 0;
        int col = cols - 1;
        while (row < rows && col >= 0) {
            if (array[row][col] == target) {
                return true;
            }else if(array[row][col] < target){
                row++;
            }else{
                col--;
            }
        }
        return false;
    };
    cout << findNumIn2DArray(matrix, 21) << endl;
}

/*
 旋转数组最小的数字：
 数组的旋转：将一个数组中最开始的几个元素移动到数组的末尾
 [3,4,5,1,2] 旋转之后 [1,2,3,4,5] 最小的元素是 1
 解法：直接排序，输出array[0]就好了呀。
 应该这样描述，给定一个递增数组的旋转数组，获取这个数组的最小值
 */
void Array4(){
    vector<int> array{9, 10, 11, 4, 5};
    auto minArray = [](vector<int>& array) -> int {
        int start = 0;
        int end = (int)array.size() - 1;
        while (start < end) {
            int middle = (end - start)/2 + start;
            if (array[middle] < array[end]) {//最小值在前面
                end = middle;
            }else{//最小值在后边
                start = middle + 1;
            }
        }
        return array[start];
    };
    cout << minArray(array) << endl;
}

/*
 调整数组顺序使得奇数位于偶数的前面
 解法一：统计数组中所有的奇数和偶数分别放在两个数组中，然后重新在放回到原始数组中
 解法二：扫描数组发现偶数在奇数前面就交换,有点类似于bubbleSort
 解法三：双指针
 */
void Array5(){
    vector<int> array{1,2,3,4,5};
    auto exchange1 = [](vector<int>& array){
        for(auto it = array.begin(); it != array.end(); it++){
            if (*it % 2 == 0) {//发现偶数
                auto cur = it;
                while (++cur != array.end()) {
                    if (*cur % 2  != 0) {//发现奇数
                        int temp = *it; *it = *cur; *cur = temp;
                        break;
                    }
                }
            }
        }
        for_each(array.begin(), array.end(), Display());
        cout << endl;
    };
    exchange1(array);
    
    vector<int> array1{2,3,4,5,6};
    auto exchange2 = [](vector<int>& array){
        int l = 0, r = (int)array.size() - 1;
        while (l < r) {
            if (array[l] % 2 == 0 && array[r] % 2 != 0) {//偶数
                int temp = array[l]; array[l] = array[r]; array[r] = temp;
                l++;r--;
            }else{
                if(array[l] % 2 != 0){//奇数
                    l++;
                }
                if(array[r] % 2 == 0){//偶数
                    r--;
                }
            }
        }
        for_each(array.begin(), array.end(), Display());
        cout << endl;
    };
    exchange2(array1);
}

/*
 数组中出现次数超过一半的数字
 解法一：hash，记录每个数字出现的的次数
 解法二：排序找到中位数
 解法三：投票法，记录次数，相同加一，不同减一，
 */
void Array6(){
    vector<int> array{1,2,3,2,2,2,5,4,2};
    auto majorityElement = [](vector<int>& array) -> int{
        int cur = array[0];
        int count = 1;
        for (auto it = array.begin()+1; it != array.end(); it++) {
            if (cur == *it) {
                count++;
            }else{
                count--;
                if (count == 0) {
                    cur = *it;
                    count = 1;
                }
            }
        }
        return count > 0 ? cur : -1;
    };
    cout << majorityElement(array) << endl;
}

/*
 连续子数组的最大和，一看到最大就要想到 “动态规划”
 解法一：暴力法，列出所有的子数组，然后计算出最大的和，但这肯定不是最优的解法
 解法二：如果前n个数字的和 < 第n个数，那么就重新开始计算，如果 加上第n个数，变小了，那么最大值就 Max，如果继续求和，右边大了更新 Max
 解法三：动态规划，我就是要去最大值，最大和两个内容有关系，
 f(n) = max(data[n], f(n-1));
 res  = max(res, f(n));
 */
void Array7(){
    vector<int> array{1,-2,3,10,-4,7,2, -5};
    auto maxSubArray = [](vector<int>& array) -> int{
        int Max = 0, preMax = 0;
        for (auto it = array.begin(); it != array.end(); it++) {
            if (Max + *it < *it) {//重新开始
                Max = *it;
            }else if(Max + *it < Max){//先记录一下最大值
                preMax = Max;
                Max += *it;
            }else{
                Max += *it;
            }
        }
        return preMax > Max ? preMax : Max;
    };
    cout << maxSubArray(array) << endl;
    
    auto maxSubArray2 = [](vector<int>& array) -> int {
        vector<int> newArray(array);
        int max = newArray[0];
        for(int i = 1; i < (int)array.size(); i++){
            newArray[i] += std::max(0, newArray[i-1]);
            max = std::max(max, newArray[i]);
        }
        return max;
    };
    cout << maxSubArray2(array) << endl;
}

/*
 把数组排列成最小的数：
 解法一：暴力获取所有的排列，然后获取到最最小，将他们转换成字符串来处理
 c++
 int2string : to_string(xxxx)
 string2int : stoi(xxxx)
 sort(vec.begin(), vec.begin() + len, [](a, b){ a > b;//降序  a < b;//升序})//默认升序
 */
void Array8(){
    vector<int> array = {3, 32, 321};
    auto printMinNum = [](vector<int>& array) -> string {
        int len = (int)array.size();
        vector<string> strArray;
        for (int i = 0; i < len; i++) {
            strArray.push_back(to_string(array[i]));
        }
        sort(strArray.begin(), strArray.begin()+len, [](string a, string b){return a > b;});
        string ret;
        for (auto it = strArray.begin(); it != strArray.end(); it++) {
            ret += *it;
        }
        return ret;
    };
    cout << printMinNum(array) << endl;
}

/*
 数组中的逆序对:
 其实就是再做一个 mergeSort
 原理：
 1.利用递归将数组分开单独的数据
 2.在合并，merge
 3.这里需要一个辅助的数组 leftArray
 */
struct Array9{
    vector<int> array{7,5,6,4};
    vector<int> leftArray;
    int count = 0;
    
    void sort(){
        leftArray = vector<int>(array.begin(), array.begin() + (array.size() >> 1));
        sort(0, (int)array.size());
        cout << count << endl;
    }
    
    void sort(int begin, int end){
        if(end - begin < 2) return;
        int middle = (end + begin ) >> 1;
        sort(begin, middle);
        sort(middle, end);
        merge(begin, middle, end);
    }
    
    void merge(int begin, int middle, int end){
        int li = 0, le = middle - begin;
        int ri = middle, re = end;
        int ai = begin;
        
        //备份左边的数据
        for (int i = li; i < le; i++) {
            leftArray[i] = array[begin + i];
        }
        
        while (li < le) {
            if (ri < re && array[ri] < leftArray[li]) {
                array[ai++] = array[ri++];
                count++;
            }else{//这里直接把左边全都拼接到原来的数组中
                if (ri == re && array[ri] < leftArray[li]) {//提前退出了
                    count += (end - middle + 1);
                }
                array[ai++] = leftArray[li++];
            }
        }
    }
};

int removeDuplicates(vector<int>& nums) {
    if(nums.size() == 0) return 0;
    map<int, int> map;
    vector<int> array;
    for(auto it = nums.begin(); it != nums.end(); it++){
        if(map[*it] == 0){
            map[*it]++;
            array.push_back(*it);
        }
    }
    nums = move(array);
    return (int)nums.size();
}
void test9(){
    vector<int> array = {0,0,1,1,1,2,2,3,3,4};
    cout << removeDuplicates(array) << endl;
}

void rotate(vector<int>& nums, int k) {
    vector<int> temp(nums);
    temp.insert(temp.end(), nums.begin(), nums.end());
    while (temp.size() - 1 <= k) {
        temp.insert(temp.end(), nums.begin(), nums.end());
    }
    int begin = (int)nums.size() - k;
    vector<int> ret = {};
    for(int i = begin; i < (int)nums.size()+begin; i++){
        ret.push_back(temp[i]);
    }
    nums = move(ret);
}
void test10(){
    vector<int> array = {1,2};
    int k = 3;
    rotate(array, k);
    for_each(array.begin(), array.end(), Display());
    cout << endl;
}

/*
 跳跃游戏：
 给你一个非负整数数组 nums ，你最初位于数组的
 第一个下标 。数组中的每个元素代表你在该位置可以跳跃的最大长度。你能跳的距离是 <= k的，
 也就是说，如何 k=3
 你可以挑 1 次，可以跳 2 次，也可以跳 3 次，
 因此说我每次就跳一次，前提是，我要跳的范围，要比你给我的范围大
 */
bool canJump(vector<int>& nums){
    int k = 0;
    for (int i = 0; i < nums.size(); i++) {
        if (i > k) return false;
        k = max(k, i + nums[i]);
    }
    return true;
}
void test11(){
    vector<int> array{2,3,1,1,4};
    array = {3,2,1,0,4};
    array = {0};
    array = {1,0};
    cout << canJump(array) << endl;
}

/*
 总结：
 1.对于数组问题，如果需要找某一规律的问题直接 Hash 解决，效率最好
 2.如果涉及到 大数 问题，就要尝试转换到 string 类型来解决
 3.要充分分析题目内容，利用、排序、hash等算法来解决。
 */

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";

    Array1();
    
    Array2();
    
    Array3();
    
    Array4();
    
    Array5();
    
    Array6();
    
    Array7();
    
    Array8();
    
    Array9 array9;
    array9.sort();
    
    test9();
    
    test10();
    
    test11();
    
    return 0;
}
