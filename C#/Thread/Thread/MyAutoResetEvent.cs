using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


/*
 * 使用AutoResetEvent类从一个线程向另外一个线程发送通知，
 * AutoResetEvent类可以通知等待的线程有某事情发生
 */
public class MyAutoResetEvent
{

    private static AutoResetEvent _workerEvent = new AutoResetEvent(false);
    private static AutoResetEvent _mainEvent = new AutoResetEvent(false);

    public static void test()
    {
        var t = new Thread(() => Process(10));
        t.Start();

        Console.WriteLine("Waiting for another thread to complete work");
        _workerEvent.WaitOne();
        Console.WriteLine("First operation is complete");
        Console.WriteLine("Performing an operation on a main thread");
        Thread.Sleep(TimeSpan.FromSeconds(5));
        _mainEvent.Set();
        Console.WriteLine("Now running the second operation on a second thread");
        _workerEvent.WaitOne();
        Console.WriteLine("Second operation is completed");

        Console.ReadKey();
    }

    static void Process(int seconds)
    {
        Console.WriteLine("Starting a long runing work...");
        Thread.Sleep(TimeSpan.FromSeconds(seconds));
        Console.WriteLine("Work is done");
        _workerEvent.Set();
        Console.WriteLine("Waiting for a main thread to complete...");
        _mainEvent.WaitOne();
        Console.WriteLine("Starting second operation...");
        Thread.Sleep(TimeSpan.FromSeconds(seconds));
        Console.WriteLine("Work is done");
        _workerEvent.Set();
    }
}
