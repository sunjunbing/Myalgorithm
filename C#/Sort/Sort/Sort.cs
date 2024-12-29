using System;
using System.Collections.Generic;
using System.Text;
using System.Linq;

public abstract class  Sort<T> :  IComparable<Sort<T>>
{
    protected T[] array;
    private int compareCount;
    private int swappedCount;
    private double time; 

    public void sort(T[] array)
    {
        if (array == null || array.Length == 0 || array.Length < 2) return;
        this.array = array;
        DateTime start = DateTime.Now;
        sort();
        time = ((DateTime.Now - start).TotalMilliseconds) / 1000;
    }

    public int CompareTo(Sort<T> s)
    {
        if (time - s.time < 0) 
            return -1;
        else if (time - s.time < 0.00001) 
            return 0;
        else
            return 1;
    }

    protected abstract void sort();
    /*
     * ret = 0; array[i1] = array[i2]
     * ret > 0; array[i1] > array[i2]
     * ret < 0; array[i1] < array[i2]
     */
    protected int cmp(int i1, int i2)
    {
        compareCount++;
        return ((IComparable<T>)array[i1]).CompareTo(array[i2]);
    }

    protected int compare(T v1, T v2)
    {
        compareCount++;
        return ((IComparable<T>)v1).CompareTo(v2);
    }

    protected void swap(int i1, int i2)
    {
        swappedCount++;
        T temp = array[i1];
        array[i1] = array[i2];
        array[i2] = temp;
    }

    public override string ToString()
    {
        StringBuilder sb = new StringBuilder();
        sb.Append("名字:" + this.GetType().Name  + " ");
        sb.Append("耗时:" + String.Format("{0:0.000}", time) + " ");
        sb.Append("交换:" + swappedCount + " ");
        sb.Append("比较:" + compareCount + "\n");
        //sb.Append("稳定:" + isStable() + "\n");
        sb.Append("-------------------------------------");
        return sb.ToString();
    }

    //private bool isStable()
    //{
    //    int count = 20;
    //    Student[] students = new Student[count];
    //    for(int i = 0; i < count; i++)
    //    {
    //        students[i] = new Student(i * 10, 10);
    //    }

    //    for (int i = 1; i < count; i++)
    //    {
    //        int score = students[i].score;
    //        int preScore = students[i - 1].score;
    //        if (score != preScore + 10) return false;
    //    }
    //    return true;
    //}
}
