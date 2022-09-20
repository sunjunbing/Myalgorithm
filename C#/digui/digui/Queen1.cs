using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace digui
{
    public class Queen1
    {
        bool[] cols;

        bool[] leftTop;

        bool[] rightTop;

        int ways = 0;

        public void PlaceXQueen(int n)
        {
            if(n < 1) return;
            cols = new bool[n];
            leftTop = new bool[2 * n - 1];
            rightTop = new bool[leftTop.Length];
            place(0);
            Console.WriteLine($"{n} 皇后一共有 {ways} 放法！！！");
        }

        private void place(int row)
        {
            if(row == cols.Length) {
                ways++;
                show();
                return;
            }
            for(int col = 0; col < cols.Length; col++){
                if (cols[col]) continue;
                int leftTopIndex = col - row + cols.Length - 1;
                if (leftTop[leftTopIndex]) continue;
                int rightTopIndex = row + col;
                if (rightTop[rightTopIndex]) continue;

                cols[col] = true;
                leftTop[leftTopIndex] = true;
                rightTop[rightTopIndex] = true;

                place(row + 1);

                cols[col] = false;
                leftTop[leftTopIndex] = false;
                rightTop[rightTopIndex] = false;

            }
        }  

        private void show()
        {
            //for(int row = 0; row < cols.Length; row++){
            //    for(int col = 0; col < cols.Length; col++){
            //        if(cols[row] == col) {
            //            Console.Write("1 ");
            //        }else
            //        {
            //            Console.Write("0 ");
            //        }
            //    }
            //    Console.WriteLine();
            //}
            //Console.WriteLine("--------------------");
        }
    }
}
