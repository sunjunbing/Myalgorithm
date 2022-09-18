using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace digui
{
    //爬楼梯：现有n阶台阶，可以一次走1步，也可以一次走2步，那么一共有多少种方法，
    public class Queen
    {
        int[] cols;
        int ways = 0;

        public void PlaceXQueen(int n)
        {
            if(n < 1) return;
            cols = new int[n];
            place(0);
            Console.WriteLine($"{n} 皇后一共有 {ways} 放法！！！");
        }

        private void place(int row){
            if(row == cols.Length) {
                ways++;
                show();
                return;
            }
            for(int col = 0; col < cols.Length; col++){
                if(isValid(row, col)){
                    cols[row] = col;
                    place(row + 1);
                }
            }
        }

        private bool isValid(int row, int col){
            for(int i = 0; i < row; i++){
                if(cols[i] == col) return false;
                if(row - i == Math.Abs(col - cols[i])) return false;
            }
            return true;
        }

        private void show(){
            for(int row = 0; row < cols.Length; row++){
                for(int col = 0; col < cols.Length; col++){
                    if(cols[row] == col) {
                        Console.Write("1 ");
                    }else
                    {
                        Console.Write("0 ");
                    }
                }
                Console.WriteLine();
            }
            Console.WriteLine("--------------------");
        }
    }
}
