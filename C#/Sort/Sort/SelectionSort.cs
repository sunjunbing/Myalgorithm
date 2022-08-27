using System;
using System.Collections.Generic;
using System.Text;

class SelectionSort<T> : Sort<T>
{
    protected override void sort()
    {
        for(int i = array.Length - 1; i > 0; i--)
        {
            int maxIndex = 0;
            for(int j = 1; j <= i; j++)
            {
                if (cmp(maxIndex, j) < 0) maxIndex = j;
            }
            swap(maxIndex, i); 
        }
    }
}
