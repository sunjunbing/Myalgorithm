using System;
using System.Collections.Generic;
using System.Text;

/*
 * 1.获取array的最小值min
 * 2.array中元素k对应的counts索引是k-min
 * 3.array中元素在有序序列中的索引counts[k-min] - p(倒数第几个k)
 */
class CountingSort : Sort<int>
{
    protected override void sort()
    {
        int min = array[0], max = array[0];
        for(int i = 0; i < array.Length; i++)
        {
           if(array[i] > max) max = array[i];
           if(array[i] < min) min = array[i];
        }

        int length = max - min + 1;
        int[] counts = new int[length];
        for(int i = 0; i < array.Length; i++)
        {
            counts[array[i] - min]++;
        }
 
        for (int i = 1; i < counts.Length; i++)
        {
            counts[i] += counts[i - 1];
        }

        int[] res = new int[array.Length];
        for(int i = array.Length - 1; i >= 0; i--)
        {
            int index = --counts[array[i] - min]; 
            res[index] = array[i]; 
        }

        for (int i = 0; i < array.Length; i++)
        {
            array[i] = res[i];
        }
    }
    
}
