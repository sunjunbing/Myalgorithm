using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;

namespace QuickSort
{
    class Times
    {
        static public void test(string methodName, Action action)
        {
            DateTime beforeDT = System.DateTime.Now;//执行前时间
            action();
            DateTime afterDT = System.DateTime.Now;//执行后时间
            TimeSpan timespan = afterDT.Subtract(beforeDT);//时间间隔
            Console.WriteLine("{0} 程序耗时:'{1}'秒", methodName, timespan);

        }
    }
}
