using System;

namespace BinaryHeap2
{
    class Program
    {
        static void Main(string[] args)
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
        }
    }
}
