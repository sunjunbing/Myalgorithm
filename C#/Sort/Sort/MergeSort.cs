using System;
using System.Collections.Generic;
using System.Text;

class MergeSort<IComparable> : Sort<IComparable>
{
    private IComparable[] leftArray;
    protected override void sort()
    {
        leftArray = new IComparable[array.Length >> 1];
        devide(0, array.Length);
    }

    private void devide(int begin, int end)
    {
        if (end - begin < 2) return;
        //mid
        int mid = (begin + end) >> 1;//自动向下取整的
        devide(begin, mid);
        devide(mid, end);
        merge(begin, mid, end);
    }

    private void merge(int begin, int mid, int end)
    {
        int li = 0, le = mid - begin;
        int ri = mid, re = end;
        int ai = begin;

        //备份leftArray
        for(int i = li; i < le; i++)
        {
            leftArray[i] = (IComparable)array[i + begin];
        }
        //进行merge
        while(li < le)
        {
            if (ri< re && compare(array[ri], leftArray[li]) < 0)
            {
                array[ai++] = array[ri++];
            }
            else
            {
                array[ai++] = leftArray[li++];
            }
        }
    }
}
