using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace digui
{
    public class FIB
    {
        //方法一：
        public int Fib(int n)
        {
            if (n <= 1) return n;
            return Fib(n - 1) + Fib(n - 2);
        }

        //方法二：
        public int Fib2(int n)
        {
            if (n <= 2) return n;
            int[] array = new int[n + 1];
            array[2] = array[1] = 1;
            return Fib2(n, array);
        }

        public int Fib2(int n, int[] array)
        {
            if (array[n] == 0)
            {
                array[n] = Fib2(n-1, array) + Fib2(n - 2, array);
            }
            return array[n];
        }

        public int Fib3(int n)
        {
            if (n <= 2) return n;
            int[] array = new int[2];
            array[0] = array[1] = 1;
            for(int i = 3; i <= n; i++)
            {
                array[i & 1] = array[(i - 1) & 1] + array[(i - 2) & 1];
            }
            return array[n & 1];
        }

        public int Fib4(int n)
        {
            if (n <= 2) return n;
            int first = 1, second = 1;
            for (int i = 3; i <= n; i++)
            {
                second = first + second;
                first = second - first;
            }
            return second;
        }

    }
}
