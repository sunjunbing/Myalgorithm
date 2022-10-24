﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

class MyAwait
{
    public static void test()
    {
        callMethod();
        Console.ReadKey();
    }

    public static async void callMethod()
    {
        Task<int> task = Method1();
        Method2();
        int count = await task;
        Method3(count);
    }

    //异步执行，不阻塞主线程
    public static async Task<int> Method1()
    {
        int count = 0;
        await Task.Run(() =>
        {
            for (int i = 0; i < 100; i++)
            {
                Console.WriteLine(" Method 1");
                count += 1;
            }
        });
        return count;
    }

    public static void Method2()
    {
        for (int i = 0; i < 5; i++)
        {
            Console.WriteLine(" Method 2");
        }
    }

    //必须等待第一个任务完成后，才能执行
    public static void Method3(int count)
    {
        Console.WriteLine("Total count is " + count);
    }
}
