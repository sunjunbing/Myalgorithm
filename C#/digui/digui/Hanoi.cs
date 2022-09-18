using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace digui
{
    //汉诺塔
    public class Hanoi
    {
        /*
        n: n个盘子
        p1 : 起点
        p2 : 中间盘子
        p3 : 终点
        */
        public void hanoi(int n, string p1, string p2, string p3){
            if(n == 1){
                move(n, p1, p3);
                return;
            }
            hanoi(n-1, p1, p3, p2);
            move(n, p1, p3);
            hanoi(n-1, p2, p1, p3);
        }

        static int i = 1;
        private void move(int n, string from, string to){
            Console.WriteLine($"第 {i++} 步 将 {n} 从 {from} 移动到 {to}");
        }
    }
}
