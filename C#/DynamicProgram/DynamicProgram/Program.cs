using System;

namespace DynamicProgram
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");
            //最少的硬币数量
            Console.WriteLine($"最少的硬币数量 {DP2(41)}");
            //最长上升子序列
            Console.WriteLine($"最长上升子序列 {LongestSubArray2(new int[] {10, 9, 2, 5, 3, 7, 101, 18})}");
            //最长公共子序列
            Console.WriteLine($"最长公共子序列 {MaxSubArray3(new int[] { 1, 3, 4, 6, 7},new int[] { 1, 4, 5, 6})}");
            //最长公共子串
            Console.WriteLine($"最长公共子串 {MaxSubString("D", "ABCD")}");
            //0-1背包问题
            Console.WriteLine($"背包最大价值 {SnapsackExactly(new int[] { 6,3,5,4,6}, new int[] { 2,2,6,5,4}, 20)}");
        }

        /*
         * 0-1背包问题
         */
        static int SnapsackExactly(int[] values, int[] weights, int capacity)
        {
            if (values == null || values.Length == 0) return 0;
            if (weights == null || weights.Length == 0) return 0;
            if (capacity == 0) return 0;
            /*
             * dp[i,j] 重量不超过j的，前i个可选物品的最大价值
             * 两个情况
             * i) j > weights[i]时，说明可以选第i件物品
             *  dp[i, j] = Math.Max(dp[i - 1, j], dp[i - 1, j - weight[i]] + value(i))
             * ii) j <= weights[i]时，已经没有空间了，不能选
             *  dp[i, j] = dp[i-1,j]; //总价值相等
             */
            int[] dp = new int[capacity + 1];
            for(int i = 1; i <= capacity; i++)
            {
                dp[i] = int.MinValue;
            }
            for (int i = 1; i <= weights.Length; i++)
            {
                for (int j = capacity; j >= weights[i - 1]; j--)
                {
                    dp[j] = Math.Max(dp[j], dp[j - weights[i - 1]] + values[i - 1]);
                }
            }
            return dp[capacity] < 0 ? -1 : dp[capacity];
        }
        static int Snapsack2(int[] values, int[] weights, int capacity)
        {
            if (values == null || values.Length == 0) return 0;
            if (weights == null || weights.Length == 0) return 0;
            if (capacity == 0) return 0;
            /*
             * dp[i,j] 重量不超过j的，前i个可选物品的最大价值
             * 两个情况
             * i) j > weights[i]时，说明可以选第i件物品
             *  dp[i, j] = Math.Max(dp[i - 1, j], dp[i - 1, j - weight[i]] + value(i))
             * ii) j <= weights[i]时，已经没有空间了，不能选
             *  dp[i, j] = dp[i-1,j]; //总价值相等
             */
            int[] dp = new int[capacity + 1];
            for (int i = 1; i <= weights.Length; i++)
            {
                for (int j = capacity; j >= weights[i - 1]; j--)
                {
                    dp[j] = Math.Max(dp[j], dp[j - weights[i - 1]] + values[i - 1]);
                }
            }
            return dp[capacity];
        }
        static int Snapsack1(int[] values, int[] weights, int capacity)
        {
            if (values == null || values.Length == 0) return 0;
            if (weights == null || weights.Length == 0) return 0;
            if (capacity == 0) return 0;
            /*
             * dp[i,j] 重量不超过j的，前i个可选物品的最大价值
             * 两个情况
             * i) j > weights[i]时，说明可以选第i件物品
             *  dp[i, j] = Math.Max(dp[i - 1, j], dp[i - 1, j - weight[i]] + value(i))
             * ii) j <= weights[i]时，已经没有空间了，不能选
             *  dp[i, j] = dp[i-1,j]; //总价值相等
             */
            int[] dp = new int[capacity + 1];
            for (int i = 1; i <= weights.Length; i++)
            {
                for (int j = capacity; j >= 1; j--)
                {
                    if (j <= weights[i - 1])
                    {
                        dp[j] = dp[j];
                    }
                    else
                    {
                        dp[j] = Math.Max(dp[j], dp[j - weights[i - 1]] + values[i - 1]);
                    }
                }
            }
            return dp[capacity];
        }
        static int Snapsack(int[] values, int[] weights, int capacity)
        {
            if (values == null || values.Length == 0) return 0;
            if (weights == null || weights.Length == 0) return 0;
            if (capacity == 0) return 0;
            /*
             * dp[i,j] 重量不超过j的，前i个可选物品的最大价值
             * 两个情况
             * i) j > weights[i]时，说明可以选第i件物品
             *  dp[i, j] = Math.Max(dp[i - 1, j], dp[i - 1, j - weight[i]] + value(i))
             * ii) j <= weights[i]时，已经没有空间了，不能选
             *  dp[i, j] = dp[i-1,j]; //总价值相等
             */
            int[,] dp = new int[weights.Length + 1,capacity + 1];
            for (int i = 1; i <= weights.Length; i++)
            {
                for(int j = 1; j <= capacity; j++)
                {
                    if(j <= weights[i - 1])
                    {
                        dp[i,j] = dp[i - 1,j];
                    }
                    else
                    {
                        dp[i, j] = Math.Max(dp[i-1,j],dp[i - 1, j - weights[i - 1]] + values[i - 1]);
                    }
                }
            }
            return dp[weights.Length,capacity];
        }

        /*
        * 最长公共字串
        *1.状态转移方程
        * str1[i] = str2[j]
        * dp[i, j] = dp[i-1, j-1] + 1;
        * str1[i] != str2[j]
        * dp[i,j] = 0;
        * 
        * 2.初始值
        * dp[0,0] = 0;
        * 
        * 3.最终解
        * dp[i, j]
        */ 
        static int MaxSubString(string str1, string str2)
        {
            if (str1 == null || str1.Length == 0) return 0;
            if (str2 == null || str2.Length == 0) return 0;
            char[] str1Arr = str1.ToCharArray();
            char[] str2Arr = str2.ToCharArray();
            return MaxSubString_1(str1Arr, str2Arr);
        }
        static int MaxSubString_1(char[] str1Arr, char[] str2Arr)
        {
            int[] dp = new int[str2Arr.Length + 1];
            int max = 0;
            for(int i = 1; i <= str1Arr.Length; i++)
            {
                int cur = 0;
                for(int j = 1; j <= str2Arr.Length; j++)
                {
                    int leftTop = cur;
                    cur = dp[j];
                    if (str1Arr[i - 1] == str2Arr[j - 1])
                    {
                        dp[j] = leftTop + 1;
                        max = Math.Max(dp[j], max);
                    }
                    else
                    {
                        dp[j] = 0;
                    }
                }
            }
            return max;
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

        /*
        * 动态规划：
        * 1.又穷子任务
        * 2.判断每一种可能的情况
        */
        //利用递推自底向上
        static int DP2(int money)
        {
            if (money < 1) return int.MaxValue;
            int[] dp = new int[money + 1];
            int[] coins = new int[money + 1];
            for (int i = 1; i <= money; i++)
            {
                int min = int.MaxValue;
                if (i >= 1 && dp[i - 1] < min)
                {
                    min = dp[i - 1];
                    coins[i] = 1;
                }
                if (i >= 5 && dp[i - 5] < min)
                {
                    min = dp[i - 5];
                    coins[i] = 5;
                }
                if (i >= 20 && dp[i - 20] < min)
                {
                    min = dp[i - 20];
                    coins[i] = 20;
                }
                if (i >= 25 && dp[i - 25] < min)
                {
                    min = dp[i - 25];
                    coins[i] = 25;
                }
                dp[i] = min + 1;
            }
            print(coins, money);
            return dp[money];
        }

        static void print(int[] coins, int money)
        {
            while (money > 0)
            {
                Console.WriteLine($"{coins[money]}");
                money = money - coins[money];
            }
            Console.WriteLine("---------------------");
        }

        //记忆搜索，减少调用次数
        static int DP1(int money)
        {
            if (money < 1) return int.MaxValue;
            int[] conis = new int[money + 1];
            int[] subCons = { 1, 5, 20, 25 };
            foreach (int i in subCons)
            {
                conis[i] = 1;
            }
            return DP1_1(money, conis);
        }

        static int DP1_1(int money, int[] coins)
        {
            if (money < 1) return int.MaxValue;
            if (coins[money] == 0)
            {
                int min1 = Math.Min(DP1_1(money - 25, coins), DP1_1(money - 20, coins));
                int min2 = Math.Min(DP1_1(money - 5, coins), DP1_1(money - 1, coins));
                coins[money] = Math.Min(min1, min2) + 1;
            }
            return coins[money];
        }

        //暴力穷举
        static int DP(int money)
        {
            if (money < 1) return int.MaxValue;
            if (money == 25 || money == 20 || money == 5 || money == 1) return 1;
            int min1 = Math.Min(DP(money - 25), DP(money - 20));
            int min2 = Math.Min(DP(money - 5), DP(money - 1));
            return Math.Min(min1, min2) + 1;
        }


        //最长上升子序列
        static int LongestSubArray(int[] nums)
        {
            if (nums == null || nums.Length == 0) return 0;
            int[] dp = new int[nums.Length];
            int max = dp[0] = 1;
            for (int i = 1; i < nums.Length; i++)
            {
                dp[i] = 1;
                for (int j = 0; j < i; j++)
                {
                    if (nums[i] <= nums[j]) continue;
                    dp[i] = Math.Max(dp[i], dp[j] + 1);
                }
                max = Math.Max(max, dp[i]);
            }
            return max;
        }
    }

}
