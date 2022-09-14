using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Graph
{
    public abstract class Graph<V, E>
    {
        protected WeightManager<E> weightManager;
        public Graph(WeightManager<E> weightManager)
        {
            this.weightManager = weightManager;
        }
        public Graph() { }
        public abstract int VertexSize();
        public abstract int EdgeSize();
        public abstract void AddVertex(V value);
        public abstract void AddEdge(V start, V end);
        public abstract void AddEdge(V start, V end, object weight);
        public abstract void RemoveVertex(V value);
        public abstract void RemoveEdge(V start, V end);
        public abstract void BFS(V start);
        public abstract void DFS(V start);

        /*
         * 最小生成树
         * 就是根据权值最小的边，将图中所有的顶点连接起来
         */
        public abstract HashSet<EdgeInfo<V, E>> mst();

        /*
         * 单源最短路径，从一个点出发找到最短路径
         */
        public abstract Dictionary<V, PathInfo<V, E>> ShortestPath(V origin);


        public interface WeightManager<E>
        {
            int compare(E e1, E e2);
            E add(E e1, E e2);
            E zero();
        }


        public class PathInfo<V, E>
        {
            public E weight;
            public LinkedList<EdgeInfo<V, E>> edges = new LinkedList<EdgeInfo<V, E>>();

            public override string ToString()
            {
                StringBuilder sb = new StringBuilder();
                sb.Append(this.weight.ToString());
                sb.Append(' ');
                foreach(var item in edges)
                {
                    sb.Append(item.ToString());
                    sb.Append(' ');
                }
                return sb.ToString();
            }
        }

        public class EdgeInfo<V, E>
        {
            public V start;
            public V end;
            public E weight;
            public EdgeInfo(V start, V end, E weight)
            {
                this.start = start; 
                this.end = end; 
                this.weight = weight;
            }

            public override string ToString()
            {
                return  "[start = " + start + " end = " + end + " weight = " + weight + "]";
            }
        }
    }
}
