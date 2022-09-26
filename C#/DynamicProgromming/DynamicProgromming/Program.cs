// See https://aka.ms/new-console-template for more information
Console.WriteLine("Hello, World!");

Console.WriteLine($"{DP2(41)}");

Console.WriteLine($"{LongestSubArray(new int[]{10, 2, 2, 5, 1, 7, 101, 18})}");


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
    for(int i = 1; i <= money; i++)
    {
        int min = int.MaxValue;
        if(i >= 1 && dp[i - 1] < min)
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
    if(coins[money] == 0)
    {
        int min1 = Math.Min(DP1_1(money - 25, coins), DP1_1(money - 20, coins));
        int min2 = Math.Min(DP1_1(money - 5, coins), DP1_1(money - 1, coins));
        coins[money] =  Math.Min(min1, min2) + 1;
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


static int LongestSubArray(int[] nums)
{
    if (nums == null || nums.Length == 0) return 0;
    int[] dp = new int[nums.Length];
    int max = dp[0] = 1;
    for(int i = 1; i < nums.Length; i++)
    {
        dp[i] = 1;
        for(int j = 0; j < i; j++)
        {
            if (nums[i] <= nums[j]) continue;
            dp[i] = Math.Max(dp[i], dp[j] + 1);
        }
        max = Math.Max(max, dp[i]);
    }
    return max;
}