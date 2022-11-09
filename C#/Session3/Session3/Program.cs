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