//
//  main.cpp
//  C++_Sort
//
//  Created by sunjian on 2024/11/5.
//
/*
 数据结构与算法。提现的是编程的思想，一切以数据说话
 我爱写程序，写程序很有意思。
 1.电脑开机，会有系统引导程序，启动操作系统，加载操作系统程序，开始执操作系统指令。
 2.启动应用程序，开启进程，以XNU为例，加载 Mach-O 文件，加载静态库、动态链接器。开始执行指令
 3.发生异常，抛出错误信号。就这么有意思，要有一个系统的了解
 4.算法很有意思 ASCII、unicode
 */


#include <iostream>
#include <vector>

using namespace std;

struct Display{
public:
    void operator()(int a){
        cout << a << " ";
    }
};


void swap(int& a, int& b){
    int temp = a; a = b; b = temp;
}
/*
 bubble的思路，两两相比，大的放后边，
 多次循环，Time:O(n^2), Space:O(n)
 */
void bubbleSort1(vector<int>& array){
    if(array.empty()) return;
    //逆序
    for(auto itr = array.rbegin(); itr != array.rend(); itr++){
        for (auto it = array.begin() + 1; it != array.end(); it++) {
            if(*it < *(it - 1)){
                swap(*it, *(it - 1));
            }
        }
    }
}

//bubbleSort2
/*
 优化如果数组已经提前有序了，就可以提前退出了
 增加一个标识： sorted
 */
void bubbleSort2(vector<int>& array){
    if(array.empty()) return;
    for(auto itr = array.rbegin(); itr != array.rend(); itr++){
        bool sorted = false;
        for (auto it = array.begin() + 1; it != array.end(); it++) {
            if(*it < *(it - 1)){
                swap(*it, *(it - 1));
            }else{
                sorted = true;
            }
        }
        if (sorted) {
            break;
        }
    }
}

/*
 优化3：
 如果尾部已经部分有序，那下次循环的开始就以这个位置开始
 */
void bubbleSort3(vector<int>& array){
    if(array.empty()) return;
    int i = static_cast<int>(array.size() - 1);
    for(; i > 0; i--){
        int sortedIndex = 1;
        for (int j = 1; j <= i; j++) {
            if(array[j] < array[j - 1]){
                swap(array[j], array[j - 1]);
                sortedIndex = j;
            }
        }
        i = sortedIndex;
    }
}

/*
 选择排序，顾名思义，就是要选择那个最大的数据，放在最后，然后进行下一轮循环
 1.第一层循环还是逆序的
 2.第二层循环找到那个最大元素的索引
 3.将最大的元素和最后一个元素交换
 */
void selectionSort(vector<int>& array){
    if(array.empty()) return;
    for (int i = static_cast<int>(array.size() - 1); i > 0; i--) {
        int maxIndex = 0;
        for (int j = 1; j <= i; j++) {
            if (array[maxIndex] <= array[j]) {
                maxIndex = j;
            }
        }
        swap(array[i], array[maxIndex]);
    }
}
/*
 堆排序：是对选择排序的一种优化
 堆也是一种数据结构，能够进行自动排序，大顶堆、小顶堆
 这里有几个重要的知识点：
 左子节点的 index
 leftIndex = (index << 1) + 1;
 rightIndex = leftIndex + 1;
 
 1.原地建堆(大顶堆)，array[0]是最大值
 2.交换array[0]、array[index]的值
 3.回复大顶堆的性质
 
 建堆的过程：
 1.获取元素
 2.对比左右子节点和父节点大小进行交换
 3.因为做过所以对这里很有印象
 */
void shiftDown(vector<int>& array, int heapSize, int index);
void heapSort(vector<int>& array){
    if(array.size() == 0) return;
    int heapSize = (int)array.size();
    //原地创建一个大顶堆 maxIndex = 0;
    for (int index = (heapSize >> 1) - 1; index >= 0; index--) {
        shiftDown(array, heapSize, index);
    }
    while (heapSize > 1) {
        swap(array[0], array[--heapSize]);
        shiftDown(array, heapSize, 0);
    }
}
void shiftDown(vector<int>& array, int heapSize, int index){
    int ele = array[index];
    int half = heapSize >> 1;
    while (index < half) {//index必须是非叶子节点
        int childIndex = (index << 1) + 1;
        int child = array[childIndex];
        int rightIndex = childIndex + 1;
        if (rightIndex < heapSize) {
            int rightChild = array[rightIndex];
            if(child < rightChild){
                child = rightChild;
                childIndex = rightIndex;
            }
        }
        if(ele > child) break;
        //这里先不交换
        array[index] = child;
        index = childIndex;
    }
    array[index] = ele;
}

/*
 插入排序：选择一个数据放到前面排序的序列中
 */
void insertSort(vector<int>& array){
    if(array.size() <= 0) return;
    for (int begin = 1; begin < (int)array.size(); begin++) {
        int cur = begin;
        while (cur > 0 && array[cur] < array[cur-1]) {
            swap(array[cur], array[cur-1]);
            cur--;
        }
    }
}
/*
 插入排序优化，将交换变为挪动
 */
void insertSort2(vector<int>& array){
    if(array.size() <= 0) return;
    for (int begin = 1; begin < (int)array.size(); begin++) {
        int cur = begin;
        int inserValue = array[cur];
        while (cur > 0 && array[cur] < array[cur-1]) {
            //swap(array[cur], array[cur-1]);
            array[cur] = array[cur-1];
            cur--;
        }
        array[cur] = inserValue;
    }
}
/*
 插入排序继续优化，使用二分查找优化
 */
int binarySearch(vector<int>& array, int index);
void insert(vector<int>& array, int sorce, int desc);
void insertSort3(vector<int>& array){
    if(array.size() <= 0) return;
    for (int begin = 1; begin < (int)array.size(); begin++) {
        insert(array, begin, binarySearch(array, begin));
    }
}
/*
 二分查找的前提带插入的序列已经是有序的
 */
int binarySearch(vector<int>& array, int index){
    //二分查找首先确定 begin 和 end,
    /*
     begin = 0;
     end = index / array.size() - 1;
     这块很重要
     */
    int begin = 0;
    int end = index;
    while (begin < end) {
        int mid = (begin + end) >> 1;
        if (array[mid] > array[index]) {
            end = mid;
        }else{
            begin = mid + 1;
        }
    }
    return begin;
}
void insert(vector<int>& array, int sorce, int desc){
    int insertValue = array[sorce];
    for (int i = sorce; i > desc; i--) {
        array[i] = array[i-1];
    }
    array[desc] = insertValue;
}

/*
 归并排序：就是将序列打散，然后重新合并，再合并的过程中，完成排序
 具体操作：
 1.将数组分我左右两个
 2.备份左边的数组
 3.然后比较填充数据
 */
class MergeSort{
public:
    MergeSort(vector<int>& vec):curArray(vec){
        length = (int)curArray.size();
        leftArray = vector<int>(curArray.begin(), curArray.begin() + (curArray.size() >> 1));
    }
    
    void mergerSort(){
        sort(0, length);
    }
    
    void sort(int begin, int end){//这里使用递归进行 devide
        if(end - begin < 2) return;
        
        int mid = (begin + end) >> 1;
        sort(begin, mid);
        sort(mid, end);
        merge(begin, mid, end);
    }
    
    void merge(int begin, int mid, int end){
        int li = 0, le = mid - begin;
        int ri = mid, re = end, len = end - mid + 1;
        int ai = begin;
        
        //备份左边的数据
        for (int i = li; i < le; i++) {
            leftArray[i] = curArray[begin + i];
        }
        
        while (li < le) {
            if (ri < re && curArray[ri] < leftArray[li]) {
                curArray[ai++] = curArray[ri++];
                count++;
            }else{
                if (ri == re) {
                    count += len;
                }
                curArray[ai++] = leftArray[li++];
            }
        }
    }
    
private:
    int length = 0;
    int count = 0;
    vector<int> leftArray;
    vector<int>& curArray;//这里也需要一个引用
};

/*
 QuickSort:
 1.获取轴点元素，然后进行比较，
 */

class QuickSort{
public:
    QuickSort(vector<int>& vec):array(vec){}
    void sort(){
        if(array.size() <= 0) return;
        sort(0, (int)array.size());
    }
private:
    void sort(int begin, int end){
        if(end - begin < 2) return;
        int mid = pivotIndex(begin, end);
        sort(begin, mid);
        sort(mid+1, end);
    }
    
    int pivotIndex(int begin, int end){
        swap(array[begin], array[begin+(rand()%(end-begin))]);
        int value = array[begin];
        end--;
        while (begin < end) {
            while (begin < end) {
                if (value < array[end]) {
                    end--;
                }else{
                    array[begin++] = array[end];
                    break;
                }
            }
            while (begin < end) {
                if (value > array[begin]) {
                    begin++;
                }else{
                    array[end--] = array[begin];
                    break;
                }
            }
        }
        array[begin] = value;
        return begin;
    }
    vector<int>& array;
};



int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    int array[] = {7,6,5,4};
    vector<int> vec(array, array+4);
//    bubbleSort1(vec);
//    bubbleSort2(vec);
//    bubbleSort3(vec);
//    selectionSort(vec);
//    heapSort(vec);
//    insertSort(vec);
//    insertSort2(vec);
//    insertSort3(vec);
    auto mergeSort = MergeSort(vec);
    mergeSort.mergerSort();
//    auto quickSort = QuickSort(vec);
//    quickSort.sort();
    for_each(vec.begin(), vec.end(), Display());
    cout << endl;
    
//    //斐波那契数
//    auto fib = [](int arg)->int{
//        //通过ret1 和 ret2 来保存计算结果
//        int ret1 = 0, ret2 = 1, sum = 0;
//        for(int i = 0; i < arg; i++){
//            sum = ret1 + ret2; ret1 = ret2; ret2 = sum;
//        }
//        return ret1;
//    };
//    cout << fib(45) << endl;
//
//    //爬楼梯
//    auto climbStairs = [](int n) -> int{
//        if(n <= 2) return n;
//        int first = 1, second = 2;
//        for (int i = 3; i <= n; i++) {
//            second += first;
//            first = second - first;
//        }
//        return second;
//    };
//    cout << climbStairs(20) << endl;
    return 0;
}
