using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace UnionFind
{
    public abstract class UnionFind
    {
        protected int[] parents;

        public UnionFind(int capacity)
        {
            if (capacity <= 0)
            {
                throw new InvalidOperationException("capacity must >= 1");
            }
            parents = new int[capacity];
        }

        public abstract int Find(int v);

        public abstract void Union(int v1, int v2);

        public bool isSame(int v1, int v2)
        {
            return parents[v1] ==  parents[v2];
        }

        protected void RangeCheck(int v)
        {
            if(v < 0 || v > parents.Length)
            {
                throw new ArgumentOutOfRangeException(nameof(v));
            }
        }

    }
}
