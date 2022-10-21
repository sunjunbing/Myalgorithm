using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

public class Semaphore
{

    static SemaphoreSlim _semaphroe = new SemaphoreSlim(4);
    public static void test()
    {
        for(int i = 0; i < 6; i++)
        {
            string threadName = "Thread" + i;
            int secondsWait = 2 + 2 * i;
            var t = new Thread(() => AccessDataBase(threadName, secondsWait));
            t.Start();
        }
    }

    static void AccessDataBase(string name, int seconds)
    {
        Console.WriteLine("{0} waits to access a database", name);
        _semaphroe.Wait();

        Console.WriteLine("{0} was granted an access to a database", name);
        Thread.Sleep(TimeSpan.FromSeconds(seconds));
        Console.WriteLine("{0} is completed", name);

        _semaphroe.Release();
    }
}
