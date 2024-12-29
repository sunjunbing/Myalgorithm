using System;
using System.Linq;
using System.Diagnostics;

int capacity = 1000000;

UnionFind.UnionFind_QU_Size qus = new UnionFind.UnionFind_QU_Size(capacity);
UnionFind.UninoFind_QU_Rank qur = new UnionFind.UninoFind_QU_Rank(capacity);
UnionFind.UninoFind_QU_Rank_PC qurpc = new UnionFind.UninoFind_QU_Rank_PC(capacity);
UnionFind.UninoFind_QU_Rank_PS qurps = new UnionFind.UninoFind_QU_Rank_PS(capacity);
UnionFind.UninoFind_QU_Rank_PH qurph = new UnionFind.UninoFind_QU_Rank_PH(capacity);
test(qus, capacity);
test(qur, capacity);
test(qurpc, capacity);
test(qurps, capacity);
test(qurph, capacity);

void test(UnionFind.UnionFind uf, int capacity)
{

    Times.test(uf.GetType().Name, () => {
        Random randow = new Random();
        for (int i = 0; i < capacity; i++)
        {
            uf.Union(randow.Next(0, capacity), randow.Next(0, capacity));
        }

        for(int i = 0; i < capacity; i++)
        {
            uf.isSame(randow.Next(0, capacity), randow.Next(0, capacity));
        }
    });
}