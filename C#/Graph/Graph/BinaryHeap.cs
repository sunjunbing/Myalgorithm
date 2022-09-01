using System;
using System.Collections.Generic;
using System.Text;


/*
    * 完全二叉树的基本性质
    * 1.当 i = 0 ，节点为根节点
    * 2.当 i > 0 , 其父节点的索引 floor((i - 1) / 2)
    * 3.当 2i + 1 <= n - 1 时，其左子节点的索引为 2i + 1
    * 4.当 2i + 2 <= n - 1 时，其右子节点的索引为 2i + 2
    * 5.完全二叉树的叶子节点的个数 floor((n+1)/2) celling(n/2)
    * 6.完全二叉是的非叶子节点的个数 为 floor(n/2)
    * 7.最后一个非叶子节点的索引为 (index >> 1) - 1
    * 8.第一个叶子节点的索引为 index >> 1
    */
class BinaryHeap<E>
{
    private E[] array;
    private int Count;
    private static int CAPACITY = 10;
    private Func<E, E, int> Comparator;

    public BinaryHeap(ICollection<E> elements, Func<E, E, int> Comparactor)
    {
        this.Comparator = Comparactor;

        Count = elements == null ? 0 : elements.Count;
        if (Count == 0)
        {
            array = new E[CAPACITY];
        }
        else
        {
            int capacity = Math.Max(elements.Count, CAPACITY);
            array = new E[capacity];
            for(int i = 0; i < elements.Count; i++)
            {
                array[i] = elements.ToArray()[i];
            }
            heapify();
        }
    }

    public BinaryHeap(E[] elements) : this(elements, null)
    {

    }

    public BinaryHeap() : this(null, null)
    {

    }

    public BinaryHeap(Func<E, E, int> Comparactor) : this(null, Comparactor)
    {

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
        Count = 0;
    }

    public void add(E element)
    {
        nullCheck(element);
        ensureCapacity(Count + 1);
        array[Count++] = element;
        shiftUp(Count-1);
    }

    public void addAll(ICollection<E> elements)
    {
        if (elements.Count == 0) return;
        foreach(E element in elements)
        {
            add(element);
        }
    }


    public E get()
    {
        emptyCheck();
        return array[0];
    }

    public E remove()
    {
        emptyCheck();
        E res = array[0];
        array[0] = array[Count - 1];
        array[Count - 1] = default(E);
        Count--;
        shiftDown(0);
        return res;
    }

    public E replace(E element)
    {
        nullCheck(element);
        E res = default(E);
        if(Count == 0)
        {
            array[0] = element;
            Count++;
        }
        else
        {
            res = array[0];
            array[0] = element;
            shiftDown(0);
        }
        return res;
    }

    private void heapify()
    {
        //自上而下的上滤
        //for (int i = 1; i < Count; i++)
        //{
        //    shiftUp(i);
        //}

        //自下而上的下滤
        for (int i = (Count >> 1) - 1; i >= 0; i--)
        {
            shiftDown(i);
        }
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

    private void shiftUp(int index)
    {
        E element = array[index];
        while(index > 0)
        {
            int pIndex = (index - 1) >> 1;
            E pElement = array[pIndex];
            if (compare(element, pElement) >= 0) break;
            array[index] = pElement;
            index = pIndex;
        }
        array[index] = element;
    }

    private void shiftDown(int index)
    {
        E element = array[index];
        int half = Count >> 1;
        // 第一个叶子节点的索引 == 非叶子节点的数量
        // index < 第一个叶子节点的索引
        // 必须保证index位置是非叶子节点
        while (index < half)
        {
            // index的节点有2种情况
            // 1.只有左子节点
            // 2.同时有左右子节点

            // 默认为左子节点跟它进行比较
            int childIndex = (index << 1) + 1;
            E child = array[childIndex];

            // 右子节点
            int rightIndex = childIndex + 1;

            // 选出左右子节点最小的那个
            if (rightIndex < Count && compare(array[rightIndex], child) < 0)
            {
                child = array[childIndex = rightIndex];
            }

            if (compare(element, child) <= 0) break;

            // 将子节点存放到index位置
            array[index] = child;
            // 重新设置index
            index = childIndex;
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
