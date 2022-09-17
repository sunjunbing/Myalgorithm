using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace digui
{
    public class Times 
    {
        static public void cost(string name, Action action)
        {
            DateTime time = DateTime.Now;
            action();
            DateTime after = DateTime.Now;
            Console.WriteLine($" {name} cost {(after - time).TotalMilliseconds}");
        }
    }
}