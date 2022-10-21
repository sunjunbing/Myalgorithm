using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

internal class MYThread
{
    //Create Thread
    static public void CreateThread()
    {
        Thread t = new Thread(PrintNumbersWithDelay);
        t.Start();
        PrintNumbers();
        Console.WriteLine("这是主线程");
        Console.ReadKey();
    }
    static void PrintNumbers()
    {
        Console.WriteLine("Starting ...");
        for(int i = 0; i < 10; i++)
        {
            Console.WriteLine(i);
        }
    }

    static void PrintNumbersWithDelay()
    {
        Console.WriteLine("Starting ...");
        for (int i = 0; i < 10; i++)
        {
            Thread.Sleep(TimeSpan.FromSeconds(2));
            Console.WriteLine(i);
        }
    }

    //线程的优先级
    static public void ThreadPriority()
    {
        Console.WriteLine("Current thread priority: {0}", Thread.CurrentThread.Priority);
        Console.WriteLine("Running on all cores available");
        RunThreads();
        Thread.Sleep(TimeSpan.FromSeconds(2));
        Console.WriteLine("Running on a single core");
        Process.GetCurrentProcess().ProcessorAffinity = new IntPtr(1);
        RunThreads();
    }
   
    static void RunThreads()
    {
        var sample = new ThreadSample(1);
        var threadOne = new Thread(sample.CountNumbers1);
        threadOne.Name = "ThreadOne";
        var threaeTwo = new Thread(sample.CountNumbers1);
        threaeTwo.Name = "ThreadTwo";

        threadOne.Priority = System.Threading.ThreadPriority.Highest;
        threaeTwo.Priority = System.Threading.ThreadPriority.Lowest;

        threadOne.Start();
        threaeTwo.Start();

        Thread.Sleep(TimeSpan.FromSeconds(2));
        sample.stop();

        Console.ReadKey();
    }

    //向线程传递参数
    static public void ThreadParam()
    {
        var sample = new ThreadSample(10);

        var threadOne = new Thread(sample.CountNumbers1);
        threadOne.Name = "ThreadOne";
        threadOne.Start();
        threadOne.Join();

        Console.WriteLine("-------------------------");

        var threadTwo = new Thread(Count);
        threadTwo.Name = "ThreadTwo";
        threadTwo.Start(8);
        threadTwo.Join();

        Console.WriteLine("-------------------------------");

        var threadThree = new Thread(() => CountNumbers(12));
        threadThree.Name = "ThreadThree";
        threadThree.Start();
        threadThree.Join();
        Console.WriteLine("--------------------------");


        int i = 10;
        var threadFour = new Thread(() => PrintNumber(i));
        i = 20;
        var threadFive = new Thread(() => PrintNumber(i));
        threadFour.Start();
        threadFive.Start();
    }

    static void Count(object iterations)
    {
        CountNumbers((int)iterations);
    }

    static void CountNumbers(int iterations)
    {
        for(int i = 0; i <= iterations; i++)
        {
            Thread.Sleep(TimeSpan.FromSeconds(0.5));
            Console.WriteLine("{0} prints {1}", Thread.CurrentThread.Name, i);
        }
    }

    static void PrintNumber(int number)
    {
        Console.WriteLine(number);
    }
}

class ThreadSample
{
    private bool _isStopped = false;

    public void stop()
    {
        _isStopped = true;
    }

    //public void CountNumbers()
    //{
    //    long counter = 0;

    //    while (_isStopped)
    //    {
    //        counter++;
    //    }

    //    Console.WriteLine("{0} with { 1, 11 } priority" +
    //        "has a count = {2 ,13}", Thread.CurrentThread.Name, 
    //        Thread.CurrentThread.Priority, 
    //        counter.ToString("NO"));
    //}

    private readonly int _iterations;
    
    public ThreadSample(int iterations)
    {
        _iterations = iterations;
    }

    public void CountNumbers1()
    {
        for(int i = 0; i <= _iterations; i++)
        {
            Thread.Sleep(TimeSpan.FromSeconds(0.5));
            Console.WriteLine("{0} prints {1}", Thread.CurrentThread.Name, i);
        }
    }
}
