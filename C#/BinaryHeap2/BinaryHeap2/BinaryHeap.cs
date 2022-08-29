using System;
using System.Collections.Generic;
using System.Text;

namespace BinaryHeap2
{
    class BinaryHeap<E> : Heap<E>
    {
        private E[] array;
        private int Count;
        private static int CAPACITY = 10;
        private Func<E, E, int> Comparator;

        public BinaryHeap() : this(null)
        {

        }

        public BinaryHeap(Func<E, E, int> Comparator)
        {
            array = new E[CAPACITY];
            this.Comparator = Comparator;
        } 

        public int size()
        {
            return Count;
        }

        public bool isEmpty()
        {
            return Count == 0;
        }

        public void clear()
        {
            nullCheck();
            for(int i = 0; i < Count; i++)
            {
                array[i] = default(E);
            }
        }

        public void add(E element)
        {

        }

        public E get()
        {
            return default(E);
        }

        public E remove(E element)
        {
            return default(E);
        }

        private void nullCheck()
        {
            if (array.Length == 0) throw new IndexOutOfRangeException("heap is empty");
        }

        private int compare(E e1, E e2)
        {
            return Comparator != null ? Comparator(e1, e2) : ((IComparable<E>)e1).CompareTo(e2);
        }
    }
}
