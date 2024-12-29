//
//  main.cpp
//  C++_Algorithm
//
//  Created by sunjian on 2024/11/4.
//

#include <iostream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <vector>

using namespace std;

void swap(char* a, char* b){
    char temp = *a;
    *a = *b;
    *b = temp;
}

//全排列问题
void permutation(char* pStr, char* pPos){//递归问题
    if(*pPos == '\0'){
        cout << pStr << endl;
    }else{
        for (char *pChar = pPos; *pChar != '\0'; pChar++) {
            swap(pChar, pPos);
            permutation(pStr, pPos+1);
            swap(pPos, pChar);
        }
    }
}

void test(){
    int ones[] = {1,2,3,4};
    int twos[] = {2,3,4,5};
    int result[5];
    transform(ones, ones+5, twos, result, std::plus<int>());//将两个数组相加
    for_each(result, result+4, [](int a) -> void {
        cout << a << " ";
    });
    cout << endl;
    
    //查找
    int arra[] = {0,1,3,4,55,5,6,6,7,8};
    cout << count(arra, arra+sizeof(arra)/sizeof(arra[0]), 6) << endl;//统计数量
    cout << count_if(arra, arra+sizeof(arra)/sizeof(arra[0]), bind2nd(less<int>(), 7)) << endl;//统计数量
    cout << count_if(arra, arra+sizeof(arra)/sizeof(arra[0]), bind1st(less<int>(), 7)) << endl;//统计数量
    cout << binary_search(arra, arra+sizeof(arra)/sizeof(arra[0]), 9) << endl;
    
    
    
    vector<int> iA(arra+3, arra+4);
    cout << *search(arra, arra+sizeof(arra)/sizeof(arra[0]), iA.begin(), iA.end()) << endl;
    
    
    char str[] = {"123"};
    permutation(str, str);
    
    cout << endl;
    
    do{
        cout << str[0] << str[1] << str[2] << endl;
    }while (next_permutation(str, str+3));//需要有序
}

void bubbleSort(vector<int>& array){
    if(array.empty()) return;
    //逆向遍历
    //begin：从左到右，rbegin：从右到左
    for(auto itr = array.rbegin(); itr != array.rend(); itr++){
        for(auto it = array.begin()+1; it != array.end(); it++){
            if ((*it) < (*(it - 1))) {
                auto temp = *it;
                *it = *(it - 1);
                *(it-1) = temp;
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
//    test();
    
    int Array[] = {2, 4, 5, 3, 1};
    
    vector<int> vec1(Array, Array+5);
    bubbleSort(vec1);
    
    return 0;
}
