// See https://aka.ms/new-console-template for more information
Console.WriteLine("Hello, World!");

Console.WriteLine(indexOf2("Hello World!!!", "or"));
Console.WriteLine(indexOf2("China", "ia"));

Console.WriteLine(KMP("Hello World!!!", "or"));
Console.WriteLine(KMP("China", "ia"));


static int indexOf(string text, string pattern)
{
    if (text == null || text.Length == 0 ||
        pattern == null || pattern.Length == 0) return -1;
    char[] texts = text.ToCharArray();
    char[] parrents = pattern.ToCharArray();
    int tLen = texts.Length;
    int pLen = parrents.Length;
    if (tLen  < pLen) return -1;
    int ti = 0, pi = 0;
    while(pi < pLen && ti - pi <= tLen - pLen)
    {
        if(texts[ti] == parrents[pi])
        {
            pi++; 
            ti++;
        }
        else
        {
            ti -= pi - 1;
            pi = 0;
        }
    }
    return (pi == pLen) ? ti - pi : -1;
}

static int indexOf2(string text, string pattern)
{
    if (text == null || text.Length == 0 ||
        pattern == null || pattern.Length == 0) return -1;
    char[] texts = text.ToCharArray();
    char[] parrents = pattern.ToCharArray();
    int tLen = texts.Length;
    int pLen = parrents.Length;
    if (tLen < pLen) return -1;
    int ti = 0, pi = 0;
    for(; ti <= tLen - pLen; ti++)
    {
        for(pi = 0; pi < pLen; pi++)
        {
            if (texts[ti + pi] != parrents[pi]) break;
        }
        if (pi == pLen) return ti;
    }
    return -1;
}

static int KMP(string text, string pattern)
{
    if (text == null || text.Length == 0 ||
        pattern == null || pattern.Length == 0) return -1;
    char[] texts = text.ToCharArray();
    char[] parrents = pattern.ToCharArray();
    int tLen = texts.Length;
    int pLen = parrents.Length;
    if (tLen < pLen) return -1;

    int[] next = nexts2(pattern);

    int ti = 0, pi = 0;
    while (pi < pLen && ti - pi <= tLen - pLen)
    {
        if (pi < 0 || texts[ti] == parrents[pi])
        {
            pi++;
            ti++;
        }
        else
        {
            pi = next[pi];
        }
    }
    return (pi == pLen) ? ti - pi : -1;
}

static int[] nexts(string pattern)
{
    char[] pattens = pattern.ToCharArray();
    int[] next = new int[pattens.Length];
    int i = 0;
    int n = -1;
    next[0] = -1;
    int iMax = pattens.Length - 1;
    while (i < iMax)
    {
        if (n < 0 || pattens[i] == pattens[n])
        {
            next[++i] = n++;
        }
        else
        {
            n = next[n];
        }
    }
    return next;
}

static int[] nexts2(string pattern)
{
    char[] pattens = pattern.ToCharArray();
    int[] next = new int[pattens.Length];
    int i = 0;
    int n = -1;
    next[0] = -1;
    int iMax = pattens.Length - 1;
    while (i < iMax)
    {
        if (n < 0 || pattens[i] == pattens[n])
        {
            ++i; ++n;
            if(pattens[i] == pattens[n])
            {
                next[i] = next[n];
            }
            else
            {
                next[i] = n;
            }
        }
        else
        {
            n = next[n];
        }
    }
    return next;
}