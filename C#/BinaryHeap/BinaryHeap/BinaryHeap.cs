using System;
using System.Collections.Generic;
using System.Diagnostics.CodeAnalysis;
using System.Text;

namespace BinaryHeap
{
    /*
     * 完全二叉堆 
     * 底层的数据结构使用数组来实现：
     * 索引i的规律：
     *  1.i = 0， 它是根节点
     *  2.i > 0,  它的父节点的编号为floor((i - 1) / 2)
     *  3.2i + 1 <= n - 1; 它的左子节点编号为2i+1
     *  4.2i + 1 > n - 1;它无左子节点
     *  5.2i + 2 <= n - 1; 它的右子节点编号为2i+2
     *  6.2i + 2 > n - 1; 他没有右子节点
     *  7.叶子节点的数量：n = floor((n+1)/2) = ceiling(n/2)
     *  8.非叶子节点个数：n = floor(n/2) = ceiling((n-1)/2) 
     *  计算机默认向下取正
     */
    class BinaryHeap<E> : Heap<E>
    {
        private E[] elements;
        private int count;
        private static int DEFAUL_CAPACITY = 10;
        private Func<E, E, int> comparetor;
        public BinaryHeap(E[] elements, Func<E, E, int> comparetor)
        {
            this.comparetor = comparetor;
            if(elements == null || elements.Length == 0)
            {
                this.elements = new E[DEFAUL_CAPACITY];
            }
            else
            {
                int capacity = Math.Max(elements.Length, DEFAUL_CAPACITY);
                this.elements = new E[capacity];
                count = elements.Length;
                for (int i = 0; i < count; i++)
                {
                    this.elements[i] = elements[i];
                }
                heapify();
            }
        }

        public BinaryHeap():this(null, null)
        {

        }

        public int size()
        {
            return count;
        }

        public Boolean isEmpty()
        {
            return count == 0;
        }

        public void clear()
        {
            for(int i = 0; i < count; i++)
            {
                elements[i] = default;
            }
            count = 0;
        }

        public void add(E element)
        {
            elementNotNullCheck(element);
            ensureCapacity(count + 1);
            elements[count++] = element;
            shiftUp(count-1);
        }

        public E get()
        {
            emptyCheck();
            return elements[0];
        }

        /*
         * remove特指删除堆顶元素
         * 1.交换数组首元素和尾元素
         * 2.清空尾元素
         * 3.shiftDown
         */
        public E remove()
        {
            emptyCheck();  
            int lastIndex = --count;
            E ret = elements[0];
            elements[0] = elements[lastIndex];
            elements[lastIndex] = default;
            shiftDown(0);
            return ret;
        }

        public E replace(E element)
        {
            elementNotNullCheck(element);
            E ret = default;
            if (count == 0)
            {
                elements[0] = element;
                count++;
            }
            else
            {
                ret = elements[0];
                elements[0] = element;
                shiftDown(0);
            }
            return ret;
        }

        private void heapify()
        {
            //自上而下的上滤 == add
            //for(int i = 1; i < count; i++)
            //{
            //    //找打它的父节点进行对比，然后进行交换
            //    //父节点的计算方法
            //    //floor((i - 1) >> 1)
            //    shiftUp(i);
            //}
            //自下而上的下滤 == remove
            for(int i = (count >> 1) - 1; i >= 0; i--)
            {
                //找打它的子节点进行对比，然后进行交换
                //左子树：2i + 1
                //右子树：2i + 2;
                //叶子节点个数  childCount = ceiling(n / 2) == n >> 1;
                //非叶子节点的个数 childCount = floor(n / 2) 
                //第一个叶子节点的index = n / 2 - 1;
                shiftDown(i);
            }
        }
        private void shiftUp(int index)
        {
            //E e = elements[index];
            ////获取父节点的索引
            //while (index > 0)
            //{
            //    int pIndex = (index - 1) >> 1;
            //    E p = elements[pIndex];
            //    if (compare(e, p) <= 0) return;
            //    //交换位置
            //    E temp = elements[index];
            //    elements[index] = elements[pIndex];
            //    elements[pIndex] = temp;
            //    index = pIndex;
            //    ;
            //}
           //优化
            E e = elements[index];
            while(index > 0)
            {
                int pIndex = (index - 1) >> 1;
                E p = elements[pIndex];
                if (compare(e, p) <= 0) break;
                elements[index] = p;
                index = pIndex;
            }
            elements[index] = e;
        }

        private void shiftDown(int index)
        {
            //1.必须非叶子节点
            int half = count >> 1;
            E element = elements[index];
            while(index < half)//必须是非叶子节点
            {
                int leftChildIndex = (index << 1) + 1;
                int childIndex = leftChildIndex;
                int rightChildIndex = leftChildIndex + 1;
                if(rightChildIndex < count && compare(elements[leftChildIndex], elements[rightChildIndex]) < 0)
                {
                    childIndex = rightChildIndex;
                }
                E child = elements[childIndex];
                if (compare(element, child) >= 0) break;
                elements[index] = child; 
                index = childIndex;
            }
            elements[index] = element;
        }
        
        private int compare(E e1, E e2)
        {
            return comparetor != null ? comparetor(e1, e2) : ((IComparable<E>)e1).CompareTo(e2);
        }

        private void emptyCheck()
        {
            if(count == 0)
            {
                throw new IndexOutOfRangeException("Heap is empty");
            }
        }

        private void elementNotNullCheck(E element)
        {
            if(element == null)
            {
                throw new ArgumentNullException("element must not be null");
            }
        }

        /*
         * 扩容逻辑
         */
        private void ensureCapacity(int capacity)
        {
            int oldLength = elements.Length;
            if (oldLength >= capacity) return;

            int newCapacity = oldLength + (oldLength >> 1);
            E[] newElements = new E[newCapacity];
            for(int i = 0; i < oldLength; i++)
            {
                newElements[i] = elements[i];
            }
            elements = newElements;
        } 

        public void print()
        {
            for(int i = 0; i < count; i++)
            {
                Console.WriteLine(elements[i]);
            }
        }
    }
}
