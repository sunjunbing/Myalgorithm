using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace UnionFind
{
    public class UnionFind_QF : UnionFind
    {
        public UnionFind_QF(int capacity) : base(capacity)
        { 
        }

        public override int Find(int v)
        {
            RangeCheck(v);
            return parents[v];
        }

        /// <summary>
        /// 将v1所在结合的所有元素的父节点都嫁接到v2上
        /// </summary>
        /// <param name="v1"></param>
        /// <param name="v2"></param>
        public override void Union(int v1, int v2)
        {
            int p1 = Find(v1);
            int p2 = Find(v2);
            if (p1 == p2) return;
            for(int i = 0; i < parents.Length; i++)
            {
                if (parents[i] == p1)
                {
                    parents[i] = p2;
                }
            }
        }
    }
}
