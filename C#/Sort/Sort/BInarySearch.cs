using System;
using System.Collections.Generic;
using System.Text;


class BInarySearch
{
   
    static public int search(int[] array, int value)
    {
        if (array == null || array.Length == 0) return -1;
        int begin = 0;
        int end = array.Length;
        while(begin < end)
        {
            int mid = (begin + end) >> 1;
            if(value < array[mid])
            {
                end = mid;
            }
            else if(value > array[mid])
            {
                begin = mid + 1;
            }
            else
            {
                return mid;
            }
        }
        return -1;
    }

    static public int searchIndex(int[] array, int value)
    {
        if (array == null || array.Length == 0) return -1;
        int begin = 0;
        int end = array.Length;
        while (begin < end)
        {
            int mid = (begin + end) >> 1;
            if (value < array[mid])
            {
                end = mid;
            }
            else
            {
                begin = mid + 1;
            }
        }
        return begin;
    }
}
