using System;
using System.Linq;
using System.Diagnostics;
class Program
{
    static void Main(string[] args)
    {

        int[] array1 = { 20, 23, 5, 8, 8, 8, 10, 14 };
        //Debug.Assert(BInarySearch.searchIndex(array1, 2) == 1);
        //Debug.Assert(BInarySearch.searchIndex(array1, 8) == 6);
        //Debug.Assert(BInarySearch.searchIndex(array1, 11) == 7);
        //Debug.Assert(BInarySearch.searchIndex(array1, 15) == 8);

        RadixSort radixSort = new RadixSort();
        radixSort.sort(array1);
        Debug.Assert(Integers.isAsyncSorder(array1));
        return;

        int[] array = Integers.random(1000000, 1, 1000000);
        /*
         * C# 数组copy的两种方便方式
         * 1.Clone()
         * 2.LINQ查询
         */
        sort(new Sort<int>[] { 
                          //new HeapSort<int>(), 
                          //new InsertSort3<int>(), 
                          //new InsertSort2<int>(), 
                          //new BubbleSort3<int>(),
                          //new SelectionSort<int>(),
                          //new InsertSort<int>(),
                          new MergeSort<int>(),
                          new QuickSort<int>(),
                          new ShellSort<int>(),
                         new CountingSort()},
            new int[][] { 
                          //array,
                          //array.Select(a => a).ToArray(),
                          //array.Select(a => a).ToArray(),
                          //array.Select(a => a).ToArray(),
                          //array.Select(a => a).ToArray(), 
                          //array.Select(a => a).ToArray(),
                          array.Select(a => a).ToArray(),
                          array.Select(a => a).ToArray(),
                          array.Select(a => a).ToArray(),
                          array.Select(a => a).ToArray()});
                                      
        
    }

    static void sort(Sort<int>[] sorts, int[][] array)
    {
        for(int  i = 0; i < sorts.Length; i++)
        {
            sorts[i].sort(array[i]);
            //判断排序是否正确
            Debug.Assert(Integers.isAsyncSorder(array[i]));
        }
        Array.Sort<Sort<int>>(sorts);
        foreach (Sort<int> sort in sorts)
        {
            Console.WriteLine(sort);
        }
    }
}
