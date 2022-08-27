using System;
using System.Collections.Generic;
using System.Text;

class BubbleSort2<T> : Sort<T> 
{
    protected override void sort()
    {
        for(int i = array.Length - 1; i > 0; i--)
        {
            bool sorted = true;
            for(int j = 1; j <= i; j++)
            {
                if(cmp(j, j - 1) < 0)
                {
                    sorted = false;
                    swap(j, j - 1);
                }
            }
            if (sorted) break; 
        }
    }
}
