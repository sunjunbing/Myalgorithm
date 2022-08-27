using System;
using System.Collections.Generic;
using System.Text;

class InsertSort3<T> : Sort<T>
{

    /**
     * Time  : O(n)
     * Space : O(n)
     */
    protected override void sort()
    {
        for (int i = 1; i < array.Length; i++)
        {
            int index = search(i);
            int cur = i;
            T v = array[i];
            while (cur > index)
            {
                array[cur] = array[cur - 1];
                cur--;
            }
            array[index] = v;
        }
    }

    private int search(int index)
    {
        int begin = 0;
        int end = index;
        while (begin < end)
        {
            int mid = (begin + end) >> 1;
            if (compare(array[index], array[mid]) < 0)
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
