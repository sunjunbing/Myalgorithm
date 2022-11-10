// See https://aka.ms/new-console-template for more information
using System.Runtime.InteropServices;

Console.WriteLine("Hello, World!");
convertStrTest();

void convertStrTest()
{
    Console.WriteLine(convertStr("  Hellow world!      "));
    Console.WriteLine(convertStr("     "));
    Console.WriteLine(convertStr(""));
    Console.WriteLine(convertStr("ab good    example"));
}


//字符串消除空格
string convertStr(string str)
{
    if(str == null || str.Length == 0)
    {
        Console.WriteLine("input str is empty");
        return "";
    }
    char[] chars = str.ToCharArray();
    if(chars.Length == 0)
    {
        Console.WriteLine("chars count is 0");
        return "";
    }
    int cur = 0;
    int len = 0;
    bool space = true;
    for(int i = 0; i < chars.Length; i++)
    {
        if (chars[i] != ' ')//当前字符不是空字符
        {
            chars[cur++] = chars[i];
            space = false;
        }
        else if(space == false)//当前字符是空字符，并且上一个字符不是空字符
        {
            chars[cur++] = ' ';
            space = true;
        }
    }
    len = space ? cur - 1 : cur;
    if (cur <= 0) return "";
    reverseStr(chars, 0, len);

    int begin = 0;
    for(int i = 0; i < len; i++) 
    {
        if (chars[i] == ' ')
        {
            reverseStr(chars, begin, i);
            begin = i+1;
        }
    }
    reverseStr(chars, begin, len);

    return new string(chars, 0, len);
}

void reverseStr(char[] chars, int li, int ri)
{
    ri--;
    while(li < ri)
    {
        char temp = chars[li];
        chars[li] = chars[ri];
        chars[ri] = temp;
        li++;ri--; 
    }
}

int lengthOfLongestNoRepeatSubString(string str)
{
    if (str == null) return 0;
    char[] chars = str.ToCharArray();
    if (chars.Length == 0) return 0;
    Dictionary<char, Integer> dict = new Dictionary<char, Integer>();
    dict.Add(chars[0], new Integer(0));

    int max = 1;
    int li = 0;
    for (int i = 1; i < chars.Length; i++)
    {
        dict.TryGetValue(chars[i], out Integer pi);
        if(pi != null && li < pi.index)
        {
            li = pi.index + 1;
        }
        dict.Add(chars[i], new Integer(i));
        max = Math.Max(max, i - li + 1);
    }
    return max;
}

class Integer
{
    public int index;
    public Integer(int i)
    {
        index = i;
    }
};

