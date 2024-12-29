using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace UnionFind
{
    public class UnionFind_QU_Size : UnionFind_QU
    {
        private int[] size;
        public UnionFind_QU_Size(int capacity) : base(capacity)
        {
            size = new int[capacity];
            for(int i = 0; i < capacity; i++)
            {
                size[i] = 1;
            }
        }

        public override void Union(int v1, int v2)
        {
            int p1 = Find(v1);
            int p2 = Find(v2);
            if (p1 == p2) return;
            if (size[p1] < size[p2])
            {
                parents[p1] = p2;
                size[p2]++;

            }
            else
            {
                parents[p2] = p1;
                size[p1]++;
            }
        }
    }
}
