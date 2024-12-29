using System;
using System.Collections.Generic;
using System.Text;

namespace BinaryHeap
{
    public interface Heap<E>
    {
        int size();

        Boolean isEmpty();

        void clear();

        void add(E element);

        E get();

        E remove();

        E replace(E element);
    }
}
