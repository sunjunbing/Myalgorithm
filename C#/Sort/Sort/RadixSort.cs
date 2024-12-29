using System;
using System.Collections.Generic;
using System.Text;

//基数排序
//对数据的每一位做一次计数排序

class STNumber
{
    public int num;
    public int baseNum;
}

 class RadixSort : Sort<int>
{
    
    STNumber[] numbsers;

    protected override void sort()
    {
        //计算每一位的基数
        int baseNum = 10;
        numbsers = new STNumber[array.Length];
        for (int i = 0; i < array.Length; i++)
        {
            STNumber sTNumber = new STNumber();
            sTNumber.num = array[i];
            numbsers[i] = sTNumber;
        }
        while (true)
        {
            int needSort = 0;
            for (int i = 0; i < numbsers.Length; i++)
            {
                numbsers[i].baseNum = numbsers[i].num % baseNum / (baseNum / 10);
                needSort += numbsers[i].baseNum;
            }
            if (needSort == 0) break;
            sortBase(numbsers);
            baseNum *= baseNum;
        }
        for (int i = 0; i < numbsers.Length; i++)
        {
            array[i] = numbsers[i].num;
        }
    }

    private void sortBase(STNumber[] nums)
    {
        //get min and max
        int min = 0, max = 0;
        for(int i = 0; i < nums.Length; i++)
        {
            if (nums[i].baseNum > max) max = nums[i].baseNum;
            if (nums[i].baseNum < min) min = nums[i].baseNum;
        }
        //array count max - min + 1
        int[] counts = new int[max - min + 1];
        for(int i = 0; i < nums.Length; i++)
        {
            counts[nums[i].baseNum]++;
        }
        for (int i = 1; i < counts.Length; i++)
        {
            counts[i] += counts[i-1];
        }
        STNumber[] result = new STNumber[nums.Length];
        for (int i = nums.Length - 1; i >= 0; i--)
        {
            result[--counts[nums[i].baseNum - min]] = nums[i];
        }
        for (int i = 0; i < nums.Length; i++)
        {
             nums[i] = result[i];
        }
    }
}
