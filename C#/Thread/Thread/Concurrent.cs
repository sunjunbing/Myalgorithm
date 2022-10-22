using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections.Concurrent;
using System.Diagnostics;
using System.Threading;

public class Concurrent
{
    public static void ConcurrentDictionaryTest()
    {
        var concurrentDictionary = new ConcurrentDictionary<int, string>();
        var dictionary = new Dictionary<int, string>();

        var sw = new Stopwatch();
        sw.Start();

        for(int i = 0; i < 1000000; i++)
        {
            lock (dictionary)
            {
                dictionary[i] = i.ToString();
            }
        }

        sw.Stop();
        Console.WriteLine("writing to dicionary with a lock: {0}", sw.Elapsed);


        sw.Restart();

        for (int i = 0; i < 1000000; i++)
        {
            concurrentDictionary[i] = i.ToString();
        }

        sw.Stop();
        Console.WriteLine("writing to dicionary with a lock: {0}", sw.Elapsed);

        sw.Restart();
        for (int i = 0; i < 1000000; i++)
        {
            lock (dictionary)
            {
                string item = dictionary[i];
            }
        }
        sw.Stop();
        Console.WriteLine("Reading from dictionary with a lock: {0}", sw.Elapsed);

        sw.Restart();
        for (int i = 0; i < 1000000; i++)
        {
            string item = concurrentDictionary[i];
        }
        sw.Stop();
        Console.WriteLine("Reading from a concurrent dictionary: {0}", sw.Elapsed);

        Console.ReadKey();
    }
}
