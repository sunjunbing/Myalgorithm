using System;
using System.Collections.Generic;
using System.Text;

namespace BinaryHeap2
{
    public interface  Heap <E>
    {
        public int size();

        public bool isEmpty();

        public void clear();

        public void add(E element);

        public E get();

        public E remove(E element);
    }
}
