// See https://aka.ms/new-console-template for more information
Console.WriteLine("Hello, World!");

Console.WriteLine($"{MaxSubArray()}");

int MaxSubArray()
{
    int[] nums = { -2, 1, -3, 4, -1, 2, 1, -5, 4 };
    return MaxSubArray3(nums);
}

//使用遍历的方法
int MaxSubArray1(int[] array)
{
    if(array == null || array.Length == 0) return 0;
    int max = int.MinValue;
    for(int begin = 0; begin < array.Length; begin++)
    {
        for(int end  = begin; end < array.Length; end++)
        {
            int sum = 0;
            for(int i = begin; i < end; i++)
            {
                sum += array[i];
            }
            if(max < sum) max = sum;
        }
    }
    return max;
}

int MaxSubArray2(int[] array)
{
    if (array == null || array.Length == 0) return 0;
    int max = int.MinValue;
    for (int begin = 0; begin < array.Length; begin++)
    {
        int sum = 0;
        for (int end = begin; end < array.Length; end++)
        {
            sum += array[end];
            if (max < sum) max = sum;
        }
    }
    return max;
}

int MaxSubArray3(int[] array)
{
    if (array == null || array.Length == 0) return 0;
    return MaxSubArray4(array, 0, array.Length); 
}

int MaxSubArray4(int[] array, int begin, int end)
{
    if (end - begin < 2) return array[begin];
    int mid = (begin + end) >> 1;

    int leftMax = int.MinValue;
    int leftSum = 0;
    for(int i = mid-1; i >= begin; i--)
    {
        leftSum += array[i];
        leftMax = Math.Max(leftMax, leftSum);
    }

    int rightMax = int.MinValue;
    int rightSum = 0;
    for(int i = mid; i < end; i++)
    {
        rightSum += array[i];
        rightMax = Math.Max(rightMax, rightSum);
    }

    int max = leftMax + rightMax;

    return Math.Max(max, 
                    Math.Max(MaxSubArray4(array, begin, mid), 
                             MaxSubArray4(array, mid, end)));
}

