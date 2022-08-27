using System;
using System.Collections.Generic;
using System.Text;

namespace QuickSort
{
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
    }
}
