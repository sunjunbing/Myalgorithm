using System;

namespace BinaryHeap2
{
    class Program
    {
        static void Main(string[] args)
        {
            //test1();
            //test2();
            topK();
        }

        static void test()
        {
            BinaryHeap<int> heap = new BinaryHeap<int>();
            heap.add(68);
            heap.add(72);
            heap.add(43);
            heap.add(50);
            heap.add(38);
            heap.add(10);
            heap.add(90);
            heap.add(65);
            heap.print();
            Console.WriteLine("-------------------");
            //heap.remove();
            //heap.print();

            Console.WriteLine("-------------------");
            heap.replace(70);
            heap.print();
        }

        static void test1()
        {
            int[] data = { 88, 44, 53, 41, 16, 6, 70, 18, 85, 98, 81, 23, 36, 43, 37 };
            BinaryHeap<int> heap = new BinaryHeap<int>(data);
            heap.print();
            Console.WriteLine("-------------------");
            data[0] = 10;
            data[1] = 20;
            heap.print();
        }

        static void test2()
        {
            int[] data = { 88, 44, 53, 41, 16, 6, 70, 18, 85, 98, 81, 23, 36, 43, 37 };
            BinaryHeap<int> heap = new BinaryHeap<int>(data, (int a, int b) => b - a);
            heap.print();
            Console.WriteLine("-------------------");
            data[0] = 10;
            data[1] = 20;
            heap.print();
        }

        static void topK()
        {
            int[] data = { 51, 30, 39, 92, 74, 25, 16, 93, 91, 19,  54, 47, 73, 62, 76,
            63, 35, 18, 90, 6, 65, 49, 3, 26, 61, 21, 48};
            BinaryHeap<int> heap = new BinaryHeap<int>((int a, int b) => b - a);
            int k = 3;
            for (int i = 0; i < data.Length; i++)
            {
                if(heap.size() < k)
                {
                    heap.add(data[i]);
                }
                else if (data[i] > heap.get())
                {
                    heap.replace(data[i]);
                }
            }
            heap.print();
        }
    }
}
