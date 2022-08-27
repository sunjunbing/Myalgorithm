using System;
using System.Collections.Generic;
using System.Text;

class QuickSort<T> : Sort<T>
{
    protected override void sort()
    {
        sort(0, array.Length);
    }

    private void sort(int begin, int end)
    {
        if (end - begin < 2 ) return;
        int mid = devide(begin, end);
        sort(begin, mid);
        sort(mid+1, end);
    }

    private int devide(int begin, int end)
    {
        Random random = new Random();
        swap(begin, begin + random.Next(0, end - begin));
        T pivot = array[begin];
        end--;
        while (begin < end)
        {
            while (begin < end)
            {
                if(compare(pivot, array[end]) < 0)
                {
                    end--;
                }
                else
                {
                    array[begin++] = array[end];
                    break;
                }
            }

            while (begin < end)
            {
                if (compare(pivot, array[begin]) > 0)
                {
                    begin++;
                }
                else
                {
                    array[end--] = array[begin];
                    break;
                }
            }
        }
        array[begin] = pivot;
        return begin;
    }
}
