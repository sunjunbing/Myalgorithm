using System;

namespace DynamicProgram
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");
            Console.WriteLine($" {MaxSubArray3(new int[] { 1, 3, 4, 6, 7},new int[] { 1, 4, 5, 6})}");
        }

        /*
         * 最长公共子序列
         * 两种做法
         */
        static int MaxSubArray3(int[] array1, int[] array2)
        {
            if (array1 == null || array1.Length == 0) return 0;
            if (array2 == null || array2.Length == 0) return 0;
            int[] dp = new int[array2.Length + 1];
            int cur = 0;
            for (int i = 1; i <= array1.Length; i++)
            {
                for (int j = 1; j <= array2.Length; j++)
                {
                    int leftTop = cur;
                    cur = dp[j];
                    if (array1[i - 1] == array2[j - 1])
                    {
                        dp[j] = leftTop + 1;
                    }
                    else
                    {
                        dp[j] = Math.Max(dp[j - 1], dp[j]);
                    }
                }
            }
            return dp[array2.Length];
        }

        static int MaxSubArray2(int[] array1, int[] array2)
        {
            if (array1 == null || array1.Length == 0) return 0;
            if (array2 == null || array2.Length == 0) return 0;
            int[,] dp = new int[2, array2.Length+1];
            for (int i = 1; i <= array1.Length; i++)
            {
                for (int j = 1; j <= array2.Length; j++)
                {
                    if (array1[i - 1] == array2[j - 1])
                    {
                        dp[i & 1, j] = dp[i&1, j - 1] + 1;
                    }
                    else
                    {
                        dp[i & 1, j] = Math.Max(dp[(i-1)&1, j], dp[i&1, j - 1]);
                    }
                }
            }
            return dp[array1.Length & 1, array2.Length];
        }
        static int MaxSubArray1(int[] array1, int[] array2)
        {
            if (array1 == null || array1.Length == 0) return 0;
            if (array2 == null || array2.Length == 0) return 0;
            int[,] dp = new int[array1.Length+1,array2.Length+1];
            for(int i = 1; i <= array1.Length; i++)
            {
                for(int j = 1; j <= array2.Length; j++)
                {
                    if(array1[i-1] == array2[j-1])
                    {
                        dp[i,j] = dp[i - 1,j - 1] + 1;
                    }
                    else
                    {
                        dp[i, j] = Math.Max(dp[i-1, j ], dp[i, j-1]);
                    }
                }
            }
            return dp[array1.Length, array2.Length];
        }
        static int MaxSubArray(int[] array1, int[] array2)
        {
            if (array1 == null || array1.Length == 0 ||
                array2 == null || array2.Length == 0)
                return 0;
           return MaxSubArray_1(array1, array1.Length-1, array2, array2.Length-1);
        }

        static int MaxSubArray_1(int[] array1, int index1, int[] array2, int index2)
        {
            if (index1 < 0 || index2 < 0) return 0;
            if(array1[index1] == array2[index2])
            {
                return MaxSubArray_1(array1, index1 - 1, array2, index2 - 1) + 1;
            }
            else
            {
                return Math.Max(MaxSubArray_1(array1, index1 - 1, array2, index2),
                                MaxSubArray_1(array1, index1, array2, index2-1));
            }
        }
    }
}
