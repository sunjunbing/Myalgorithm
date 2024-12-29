using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace UnionFind
{
    public class UnionFind_QU : UnionFind
    {
        public UnionFind_QU(int capacity) : base(capacity)
        {

        }

        public override int Find(int v)
        {
            RangeCheck(v);
            while(v != parents[v])
            {
                v = parents[v];
            }
            return v;
        }

        /// <summary>
        /// 将v1的父节点嫁接到v2的父节点上
        /// </summary>
        /// <param name="v1"></param>
        /// <param name="v2"></param>
        public override void Union(int v1, int v2)
        {
            int p1 = Find(v1);
            int p2 = Find(v2);
            if (p1 == p2) return;
            parents[p1] = p2;
        }
    }
}
