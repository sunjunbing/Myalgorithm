using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Graph
{
    public interface  Graph<V, E>
    {
        int VertexSize();
        int EdgeSize();
        void AddVertex(V value);
        void AddEdge(V start, V end);
        void AddEdge(V start, V end, object weight);
        void RemoveVertex(V value);
        void RemoveEdge(V start, V end);
        void BFS(V start);
        void DFS(V start);
    }
}
