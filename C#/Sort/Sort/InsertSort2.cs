using System;
using System.Collections.Generic;
using System.Text;

class InsertSort2<T> : Sort<T>
{
    protected override void sort()
    {
        sort2();
    }

    private void sort2()
    {
        for (int i = 1; i < array.Length; i++)
        {
            int j = i;
            T v = array[j];
            while (j > 0 && compare(v, array[j - 1]) < 0)
            {
                array[j] = array[j - 1];
                j--;
            }
            array[j] = v;
        }
    }
}
