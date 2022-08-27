using System;
using System.Collections.Generic;
using System.Text;

class Integers
{
    static public int[] random(int count, int min, int max)
    {
        if (count < 0 || min > max) return null;
        int[] array = new int[count];
        Random random = new Random();
        for (int i = 0; i <  count; i++)
        {
            array[i] = random.Next(min, max);
        }
        return array;
    }

    static public bool isAsyncSorder(int[] array)
    {
        if (array == null || array.Length == 0) return false;
        for(int i = 1; i < array.Length; i++)
        {
            if (array[i - 1] > array[i]) return false;
        }
        return true;
    }
}

