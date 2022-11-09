// See https://aka.ms/new-console-template for more information
Console.WriteLine("Hello, World!" + test());


int test()
{
    SkipList1<int ,int> list = new SkipList1<int, int> ();
    test1(list, 100, 10);
    test1(list, 20, 5);
    return 1;
}

void test1(SkipList1<int, int> list, int count, int delta)
{
    for(int i = 0; i < count; i++)
    {
        list.put (i, i + delta);
    }

    for(int i = 0; i < count; i++)
    {
        System.Diagnostics.Debug.Assert(list.get(i) == i + delta);
    }
    System.Diagnostics.Debug.Assert(list.GetSize() == count);


    for (int i = 0; i < count; i++)
    {
        System.Diagnostics.Debug.Assert(list.remove(i) == i + delta);
    }
    System.Diagnostics.Debug.Assert(list.GetSize() == 0);
}
