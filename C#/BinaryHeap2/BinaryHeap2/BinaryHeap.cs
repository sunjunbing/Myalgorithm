using System;
using System.Collections.Generic;
using System.Text;

namespace BinaryHeap2
{

    /*
     * 完全二叉树的基本性质
     * 1.当 i = 0 ，节点为根节点
     * 2.当 i > 0 , 其父节点的索引 floor((i - 1) / 2)
     * 3.当 2i + 1 <= n - 1 时，其左子节点的索引为 2i + 1
     * 4.当 2i + 2 <= n - 1 时，其右子节点的索引为 2i + 2
     */
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
            array =  new E[CAPACITY];
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
            for(int i = 0; i < Count; i++)
            {
                array[i] = default(E);
            }
        }

        public void add(E element)
        {
            nullCheck(element);
            ensureCapacity(Count + 1);
            array[Count++] = element;
            shiftup(Count-1);
        }

        public E get()
        {
            emptyCheck();
            return array[0];
        }

        public E remove(E element)
        {
            return default(E);
        }

        private void emptyCheck()
        {
            if (array.Length == 0) throw new IndexOutOfRangeException("heap is empty");
        }

        private void nullCheck(E element)
        {
            if(element == null)
            {
                throw new NullReferenceException("element is null");
            }
        }

        private int compare(E e1, E e2)
        {
            return Comparator != null ? Comparator(e1, e2) : ((IComparable<E>)e1).CompareTo(e2);
        }

        private void ensureCapacity(int capacity)
        {
            int oldCapacity = array.Length;
            if (oldCapacity > capacity) return;

            int newCapacity = oldCapacity + (oldCapacity >> 1);
            E[] elements = new E[newCapacity];
            Array.Copy(array, 0, elements, 0, Count);
            array = elements;
        }

        private void shiftup(int index)
        {
            E element = array[index];
            while(index > 0)
            {
                int pIndex = (index - 1) >> 1;
                E pElement = array[pIndex];
                if (compare(pElement, element) >= 0) break;
                array[index] = pElement;
                index = pIndex;
            }
            array[index] = element;
        }

        public void print()
        {
            emptyCheck();
            for(int i = 0; i < Count; i++)
            {
                Console.WriteLine(array[i]);
            }
        }
    }
}
