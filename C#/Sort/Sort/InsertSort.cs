using System;
using System.Collections.Generic;
using System.Text;

class InsertSort<T> : Sort<T>
{
    protected override void sort()
    {
        for (int i = 1; i < array.Length; i++)
        {
            int j = i;
            while (j > 0 && cmp(j, j - 1) < 0)
            {
                swap(j, j - 1);
                j--;
            }
        }
    }
}
