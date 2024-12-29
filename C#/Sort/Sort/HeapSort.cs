using System;
using System.Collections.Generic;
using System.Text;

class HeapSort<T> : Sort<T>
{
    protected int heapSize;
    
    protected override void sort()
    {
        //原地建堆
        heapify();
        
        while(heapSize > 1)
        {
            swap(0, --heapSize);
            shiftDown(0);
        }
    }

    private void heapify()
    {

        //自下而上的下滤
        //叶子节点的个数为 n = size / 2;
        //第一个叶子节点的索引 index = n - 1;
        //复杂度:O(n)
        heapSize = array.Length;
        for (int i = (heapSize >> 1) - 1; i >=0; i--)
        {
            shiftDown(i);
        }
    }

    private void shiftDown(int index)
    {
        T element = array[index];
        int half = heapSize >> 1;
        while(index < half)
        {
            //左子节点
            int leftIndex = (index << 1) + 1;
            T leftChild = array[leftIndex];

            int rightIndex = (index << 1) + 2;

            T child = leftChild;
            int childIndex = leftIndex;
            if (rightIndex < heapSize && compare(leftChild, array[rightIndex]) < 0)
            {
                child = array[rightIndex];
                childIndex = rightIndex;
            }
            if (compare(element, child) >= 0) break;
            array[index] = child;
            index = childIndex;
        }
        array[index] = element;
    }
}
