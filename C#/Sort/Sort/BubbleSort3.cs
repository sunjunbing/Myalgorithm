using System;
using System.Collections.Generic;
using System.Text;

class BubbleSort3<T> : Sort<T>
{
    protected override void sort()
    {
        for(int i = array.Length - 1; i > 0; i--)
        {
            int maxIndex = 0;
            for(int j = 1; j <= i; j++)
            {
                if(cmp(j, j-1) < 0)
                {
                    swap(j - 1, j);
                    maxIndex = j;
                }
            }
            i = maxIndex;
        }
    }
}
