using System;
using System.Collections.Generic;
using System.Text;

class ShellSort<T> : Sort<T>
{
    protected override void sort()
    {
        List<int> steps = getStep();//获取分列

        foreach(int step in steps)
        {
            sort(step);
            //TODO
            //insertSort(step);
        }
    }

    private List<int> getStep()
    {
        List<int> list = new List<int>();
        int step = array.Length;
        while(step > 0)
        {
            step >>= 1;
            list.Add(step);
        }
        return list;
    }
    private void sort(int step)
    {
        for (int col = 0; col < step; col++)//遍历每一列
        {
            for (int begin = col + step; begin < array.Length; begin += step)
            {
                int cur = begin;
                while (cur > col && cmp(cur, cur - step) < 0)
                {
                    swap(cur, cur - step);
                    cur -= step;
                }
            }
        }
    }

    //TODO
    private void insertSort(int step)
    {
        for(int col = 0; col < step; col++)
        {
            for (int begin = col+ step; begin < array.Length; begin += step)
            {
                T v = array[begin];
                int index = search(begin, step);
                int j = begin;
                while (j > index)
                {
                    array[j] = array[j - step];
                    j-=step;
                }
                array[j] = v;
            }
        }
    }

    private int search(int index, int step)
    {
        int begin = 0;
        int end = index;
        while (begin < end)
        {
            int mid = (begin + end) ;//这里有问题，mid必须是step的整数倍
            if (compare(array[end], array[mid]) < 0)
            {
                end = mid;
            }
            else
            {
                begin = mid +step;
            }
        }
        return begin;
    }
}
