using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;

class Times
{
    static public void test(string methodName, Action action)
    {
        DateTime beforeDT = System.DateTime.Now;//执行前时间
        action();
        DateTime afterDT = System.DateTime.Now;//执行后时间
        Console.WriteLine("{0} 程序耗时:'{1}'秒", methodName, ((afterDT - beforeDT).TotalMilliseconds)/1000);

    }
}
