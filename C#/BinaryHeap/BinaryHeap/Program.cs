using System;
using System.Collections.Generic;

namespace BinaryHeap
{

    class Program
    {
        static void Main(string[] args)
        {
            //test2();
            //test3();
            topK();
        }

        static void test1()
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
            Console.WriteLine("------");
            //heap.remove();
            //heap.print();
            Console.WriteLine("------");
            Console.WriteLine(heap.replace(70));
            heap.print();
        }

        static void test2()
        {
            int[] elements = { 88, 44, 53, 41, 16, 6, 70, 18, 85, 98, 81, 23, 36, 43, 37 };
            BinaryHeap<int> heap = new BinaryHeap<int>(elements, null);
            heap.print();
        }
        static void test3()
        {
            int[] elements = { 88, 44, 53, 41, 16, 6, 70, 18, 85, 98, 81, 23, 36, 43, 37 };
            //Action : 无返回值
            //Func   : 有返回值
            BinaryHeap<int> heap = new BinaryHeap<int>(elements, (int a, int b) => b - a);
            heap.print();
        }

        static void topK()
        {
            int[] elements = { 88, 44, 53, 41, 16, 6, 70, 18, 85, 98, 81, 23, 36, 43, 37 };
            //Action : 无返回值
            //Func   : 有返回值
            //小顶堆
            BinaryHeap<int> heap = new BinaryHeap<int>(null, (int a, int b) => a - b);
            int top = 3;
            for(int i = 0; i < elements.Length; i++)
            {
                if(heap.size() < top)
                {
                    heap.add(elements[i]);
                }
                else if(elements[i] < heap.get())
                {
                    heap.replace(elements[i]);
                }
            }
            heap.print();
        }
    }
}
