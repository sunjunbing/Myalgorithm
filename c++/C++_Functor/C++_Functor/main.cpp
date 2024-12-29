//
//  main.cpp
//  C++_Functor
//
//  Created by sunjian on 2024/11/4.
//

#include <iostream>
#include <algorithm>

using namespace std;

template<class T>
inline bool mySort(T const& a, T const&  b){
    return a < b;
}

template<class T>
inline void Display(T const&  a){
    cout << a << " ";
}

struct SortF{
    bool operator()(int a, int b){
        return a < b;
    }
};

struct DisplayF{
    void operator()(int a){
        cout << a << " ";
    }
};

template<class T>
struct SortFT{
    bool operator()(T const&  a, T const&  b){
        return a > b;
    }
};

template<class T>
struct DisplayFT{
    void operator()(T const&  a){
        cout << a << " ";
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    //模板函数
    int array[] = {2,5,1,4,7};
    sort(array, array+5, mySort<int>);
    for_each(array, array+5, Display<int>);
    cout << endl;
    
    //仿函数
    int array1[] = {2,5,1,4,7};
    sort(array1, array1+5, SortF());
    for_each(array1, array1+5, DisplayF());
    cout << endl;
    
    //模板仿函数
    int array2[] = {2,5,1,4,7};
    sort(array2, array2+5, SortFT<int>());
    for_each(array2, array2+5, DisplayFT<int>());
    cout << endl;
    return 0;
}
