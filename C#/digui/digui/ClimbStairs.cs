using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace digui
{
    //爬楼梯：现有n阶台阶，可以一次走1步，也可以一次走2步，那么一共有多少种方法，
    public class ClimbStairs
    {
        public int func1(int n)
        {
            if(n <= 2) return n;
            return func1(n - 1) + func1(n - 2);
        }

        public int func2(int n)
        {
            if(n <= 2) return n;
            int[] array = new int[n+1];
            array[2] = 2;
            array[1] = 1;
            return func2(n, array);
        }
        private int func2(int n, int[] array)
        {
            if(array[n] == 0){
                array[n] = func2(n-1, array) + func2(n-2, array);
            }
            return array[n];
        }

        //通过两个变量
        public int func4(int n)
        {
            if(n <= 2) return n;
            int first = 1; 
            int second = 2;
            for(int i = 3; i <= n; i++){
                second = first + second;
                first = second - first;
            }
            return second;
        }
    }
}
