using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace UnionFind
{
    public class UninoFind_QU_Rank_PH : UnionFind_QU
    {
        private int[] Rank;
        public UninoFind_QU_Rank_PH(int capacity) : base(capacity)
        {
            Rank = new int[capacity];
            for (int i = 0; i < capacity; i++)
            {
                Rank[i] = 1;
            }
        }

        public override int Find(int v)
        {
            RangeCheck(v);
            while(v != parents[v])
            {
                parents[v] = parents[parents[v]];
                v = parents[v]; 
            }
            return v;
        }

        public override void Union(int v1, int v2)
        {
            int p1 = Find(v1);
            int p2 = Find(v2);
            if (p1 == p2) return;
            if(Rank[p1] < Rank[p2])
            {
                parents[p1] = p2;
            }
            else if(Rank[p1] > Rank[v2])
            {
                parents[p2] = p1;
            }
            else
            {
                parents[p1] = p2;
                Rank[p2]++;
            }
        }
    }
}
