using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using BinaryHeap2;

namespace Graph
{
    public class ListGraph<V, E> : Graph<V, E>
    {
        public ListGraph() { }
        public ListGraph(WeightManager<E> weightManager) : base(weightManager)
        {
            
        }
        
        Dictionary<V, Vertex<V, E>> vertices =  new Dictionary<V, Vertex<V, E>>();
        HashSet<Edge<V, E>> edges = new HashSet<Edge<V, E>>();

        public void print()
        {

            foreach ((V key, Vertex<V, E> value) in vertices)
            {
                Console.WriteLine(key);
                Console.WriteLine("out  ----------------------");
                foreach (Edge<V, E> e in value.outEdges)
                {
                    Console.WriteLine(e);
                }
                Console.WriteLine("in   ----------------------");
                foreach (Edge<V, E> e in value.inEdges)
                {
                    Console.WriteLine(e);
                }
                vertices.Remove(key);
            }

            foreach (var e in edges)
            {
                Console.WriteLine(e);
            }
        }

        public override int VertexSize()
        {
            return vertices.Count;
        }
        public override int EdgeSize()
        {
            return edges.Count;
        }
        public override void AddVertex(V value)
        {
            if (!vertices.ContainsKey(value))
            {
                vertices.Add(value, new Vertex<V, E>(value));
            }
        }
        public override void AddEdge(V start, V end)
        {
            AddEdge(start, end, null);
        }

        public override void AddEdge(V start, V end, object? weight)
        {
            Vertex<V, E> VertexStart = null;
            vertices.TryGetValue(start, out VertexStart);
            if(VertexStart == null)
            {
                VertexStart = new Vertex<V, E>(start);
                vertices.Add(start, VertexStart);
            }
            Vertex<V, E> VertexEnd = null;
            vertices.TryGetValue(end, out VertexEnd);

            if (VertexEnd == null)
            {
                VertexEnd = new Vertex<V, E>(end);
                vertices.Add(end, VertexEnd);
            }
            //是否需要添加边
            Edge<V,E> edge = new Edge<V, E>(VertexStart, VertexEnd);
            edge.weight = (E)weight;
            if (VertexStart.outEdges.Remove(edge))
            {
                VertexEnd.inEdges.Remove(edge);
            }
            VertexStart.outEdges.Add(edge);
            VertexEnd.inEdges.Add(edge);
        }

        public override void RemoveVertex(V value)
        {
            Vertex<V, E> vertex = null;
            vertices.Remove(value, out vertex);
            if (vertex == null) return;

            //循环遍历outEdges/inEdges
            foreach(Edge<V, E> edge in vertex.outEdges)
            {
                edge.end.inEdges.Remove(edge);
                edges.Remove(edge);
            }
            vertex.outEdges.Clear();

            foreach (Edge<V, E> edge in vertex.inEdges)
            {
                edge.start.outEdges.Remove(edge);
                edges.Remove(edge);
            }
            vertex.inEdges.Clear();
        }
 
        public override void RemoveEdge(V start, V end)
        {
            Vertex<V, E> startVertex = null;
            vertices.TryGetValue(start, out startVertex);
            if (startVertex == null) return;
            Vertex<V, E> endVertex = null;
            vertices.TryGetValue(end, out endVertex);
            if (endVertex == null) return;
            Edge<V, E> edge = new Edge<V, E>(startVertex, endVertex);
            if (startVertex.outEdges.Remove(edge))
            {
                endVertex.inEdges.Remove(edge);
                edges.Remove(edge);
            }
        }

        public override void BFS(V start)
        {
            Vertex<V, E> vertex = null;
            vertices.TryGetValue(start, out vertex);
            if (vertex == null) return;
            LinkedList<Vertex<V, E>> queue = new LinkedList<Vertex<V, E>>();
            HashSet<Vertex<V, E>> set = new HashSet<Vertex<V, E>>();
            queue.AddLast(vertex);
            set.Add(vertex);
            while (queue.Count > 0)
            {
                Vertex<V, E> current = queue.First(); queue.RemoveFirst();
                Console.WriteLine(current.value);
                foreach(Edge<V, E> edge in current.outEdges)
                {
                    if (set.Contains(edge.end)) continue;
                    queue.AddLast(edge.end);
                    set.Add(edge.end);
                }
            }
        }

        public override void DFS(V start)
        {
            HashSet<Vertex<V, E>> set = new HashSet<Vertex<V, E>>();
            DFS(start, set);
        }

        private void DFS(V start, HashSet<Vertex<V, E>> set)
        {
            Vertex<V, E> startVertex = null;
            vertices.TryGetValue(start, out startVertex);
            if (startVertex == null) return;
            Console.WriteLine(startVertex.value);
            foreach (Edge<V, E> temp in startVertex.outEdges)
            {
                if(set.Contains(temp.end)) continue;
                set.Add(temp.end);
                DFS(temp.end.value, set);
            }
        }


        public void DFSStack(V start)
        {
            Vertex<V, E> startVertex = null;
            vertices.TryGetValue(start, out startVertex);
            if (startVertex == null) return;
            Console.WriteLine(startVertex.value);
            Stack<Vertex<V, E>> stack = new Stack<Vertex<V, E>>();
            stack.Push(startVertex);
            HashSet<Vertex<V, E>> set = new HashSet<Vertex<V, E>>();
            set.Add(startVertex);
            while (stack.Count > 0)
            {
                Vertex<V, E> temp = stack.Pop();
                foreach(var edge in temp.outEdges)
                {
                    if(set.Contains(edge.end)) continue;
                    stack.Push(temp);
                    stack.Push(edge.end);
                    set.Add(edge.end);
                    Console.WriteLine(edge.end.value);
                    break;
                }
            }
        }

        public List<V> TopologicalSort()
        {
            List<V> list = new List<V>();
            Queue<Vertex<V, E>> queue = new Queue<Vertex<V, E>>();
            Dictionary<Vertex<V, E>, int> dict = new Dictionary<Vertex<V, E>, int>();

            foreach(Vertex<V, E> v in vertices.Values)
            {
                int count = v.inEdges.Count;
                if (count == 0)
                {
                    queue.Enqueue(v);
                }
                else
                {
                    dict.Add(v, count);
                }
            }

            while (queue.Count > 0)
            {
                Vertex<V, E> v = queue.Dequeue();
                list.Add(v.value);
                foreach(Edge<V, E> edge in v.outEdges)
                {
                    int inDe = dict[edge.end] - 1;
                    if (inDe == 0)
                    {
                        queue.Enqueue(edge.end);
                    }
                    else
                    {
                        dict[edge.end] = inDe;
                    }
                }
            }

            return list;
        }

        public override HashSet<EdgeInfo<V, E>> mst()
        {
            return prim();
        }

        public HashSet<EdgeInfo<V, E>> prim()
        {
            //遍历获取所有的顶点
            var enu = vertices.Values.GetEnumerator();
            if (!enu.MoveNext()) return default;
            Vertex<V, E> vertex = enu.Current;
            //返回值
            HashSet<EdgeInfo<V, E>> res = new HashSet<EdgeInfo<V, E>>();
            //避免重复
            HashSet<Vertex<V, E>> addedVertexs = new HashSet<Vertex<V, E>>();
            //利用小顶堆获取最小值
            BinaryHeap<Edge<V, E>> minHeap = new BinaryHeap<Edge<V, E>>(vertex.outEdges, (Edge<V,E> e1, Edge<V, E> e2) => weightManager.compare(e1.weight, e2.weight));
            addedVertexs.Add(vertex);
            int verticesSize = vertices.Count;
            while (!minHeap.isEmpty() && addedVertexs.Count < verticesSize)
            {
                Edge<V, E> top = minHeap.remove();
                if (addedVertexs.Contains(top.end)) continue;
                res.Add(top.info());
                addedVertexs.Add(top.end);
                minHeap.addAll(top.end.outEdges);
            }
            return res;
        }

        private class Vertex<V, E>
        {
            public V value;
            public HashSet<Edge<V, E>> inEdges = new HashSet<Edge<V, E>>();
            public HashSet<Edge<V, E>> outEdges = new HashSet<Edge<V, E>>();
            public Vertex(V value)
            {
                this.value = value; 
            }

            public override bool Equals(object? obj)
            {
                return object.Equals(value, ((Vertex<V,E>)obj).value);
            }

            public override int GetHashCode()
            {
                return value.GetHashCode();
            }

            public override string ToString()
            {
                return value.ToString();
            }
        }

        private class Edge<V, E>
        {
            public Vertex<V, E> start;
            public Vertex<V, E> end;
            public E weight;
            public Edge(Vertex<V, E> start, Vertex<V, E> end)
            {
                this.start = start;
                this.end = end;
            }

            public EdgeInfo<V, E> info()
            {
                return new EdgeInfo<V, E>(start.value, end.value, weight);
            }

            public override bool Equals(object? obj)
            {
                Edge<V, E> edge = obj as Edge<V, E>;
                return object.Equals(start, edge.start) && object.Equals(end, edge.end);
            }

            public override int GetHashCode()
            {
                return start.GetHashCode() * 31 + end.GetHashCode();
            }

            public override string ToString()
            {
                return "Edge [ start = " + start.ToString() + ", end = " + end.ToString() + ", weight =" + weight.ToString() + "]";
            }


        }
    }
}
