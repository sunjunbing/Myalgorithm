using System.Collections;


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
            edges.Add(edge);
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
            return kruskal();
        }


        private HashSet<EdgeInfo<V, E>> prim()
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

        private HashSet<EdgeInfo<V, E>> kruskal()
        {
            int edgeSize = vertices.Count - 1;
            if (edgeSize == -1) return null;
            HashSet<EdgeInfo<V, E>> edgeInfo = new HashSet<EdgeInfo<V, E>>();
            BinaryHeap<Edge<V, E>> minHeap = new BinaryHeap<Edge<V, E>>(edges, (Edge<V, E> e1, Edge<V, E> e2) => weightManager.compare(e1.weight, e2.weight));
            UnionFind<Vertex<V, E>> uf = new UnionFind<Vertex<V, E>>();
            foreach(var vertex in vertices.Values)
            {
                uf.makeSet(vertex);
            }
            while (!minHeap.isEmpty() && edgeInfo.Count < edgeSize)
            {
                Edge<V, E> edge = minHeap.remove();
                if (uf.isSampe(edge.start, edge.end)) continue;
                edgeInfo.Add(edge.info());
                uf.union(edge.start, edge.end);
            }
            return edgeInfo;
        }

        private DictionaryEntry minPath(Dictionary<Vertex<V, E>, PathInfo<V,E>> paths)
        {
            //通过迭代器找到最短的哪一个路径
            DictionaryEntry res = new DictionaryEntry();
            Dictionary<Vertex<V, E>, PathInfo<V, E>>.Enumerator it = paths.GetEnumerator();
            while (it.MoveNext())
            {
                if(res.Key == null || weightManager.compare(it.Current.Value.weight, ((PathInfo<V, E>)res.Value).weight) < 0)
                { 
                    res.Key = it.Current.Key;
                    res.Value = it.Current.Value;
                }
            }
            return res;
        }

        private void relexDijkstra(Edge<V, E> edge, PathInfo<V, E> pathInfo, Dictionary<Vertex<V, E>, PathInfo<V, E>> paths)
        {
            //新的权值
            var newWeight = weightManager.add(pathInfo.weight, edge.weight);
            //获取可用信息
            PathInfo<V, E> oldPath = default(PathInfo<V, E>);
            paths.TryGetValue(edge.end, out oldPath);
            //如何新的权值比旧权值还要大
            if (oldPath != null && weightManager.compare(newWeight, oldPath.weight) >= 0) return;
            if (oldPath == null)
            {
                oldPath = new PathInfo<V, E>();
                paths[edge.end] = oldPath;
            }
            else
            {
                oldPath.edges.Clear();
            }
            foreach (var temp in pathInfo.edges)
            {
                oldPath.edges.AddLast(temp);
            }
            oldPath.edges.AddLast(edge.info());
            oldPath.weight = newWeight;
        }

        public override Dictionary<V, PathInfo<V, E>> ShortestPath(V origin)
        {
            return dijkstr(origin);// bellmanFord(origin);//dijkstr(origin);
        }

        private Dictionary<V, PathInfo<V, E>> dijkstr(V origin)
        {
            //从顶点中找到对应的顶点
            Vertex<V, E> start = null;
            vertices.TryGetValue(origin, out start);
            if (start == null) return null;

            //用来放置所有的顶点
            var paths = new Dictionary<Vertex<V, E>, PathInfo<V, E>>();
            paths.Add(start, new PathInfo<V, E>(weightManager.zero()));
            //用来存放返回值
            var selectedPath = new Dictionary<V, PathInfo<V, E>>();


            while (paths.Count != 0)
            {
                //找到接下来第一个被提起来的顶点
                DictionaryEntry minEntry = minPath(paths);
                Vertex<V, E> next = (Vertex<V, E>)minEntry.Key;
                PathInfo<V, E> pathInfo = (PathInfo<V, E>)minEntry.Value;
                //将接下来可能被提起来的点放入到返回集合中
                selectedPath.Add(next.value, pathInfo);
                //删除被踢起来的点
                paths.Remove(next);
                //计算下一个可能被提起来的点
                foreach (Edge<V, E> edge in next.outEdges)
                {
                    //如何已经包含了这个顶点
                    if (selectedPath.ContainsKey(edge.end.value)) continue;
                    relexDijkstra(edge, pathInfo, paths);
                }
            }
            selectedPath.Remove(start.value);
            return selectedPath;
        }


        private bool relexBellmanFord(Edge<V, E> edge, PathInfo<V, E> fromPath, Dictionary<V, PathInfo<V, E>> paths)
        {
            //新的权值
            var newWeight = weightManager.add(fromPath.weight, edge.weight);
            //获取可用信息
            PathInfo<V, E> oldPath = default(PathInfo<V, E>);
            paths.TryGetValue(edge.end.value, out oldPath);
            //如何新的权值比旧权值还要大
            if (oldPath != null && weightManager.compare(newWeight, oldPath.weight) >= 0) return false;
            if (oldPath == null)
            {
                oldPath = new PathInfo<V, E>();
                paths[edge.end.value] = oldPath;
            }
            else
            {
                oldPath.edges.Clear();
            }
            foreach (var temp in fromPath.edges)
            {
                oldPath.edges.AddLast(temp);
            }
            oldPath.edges.AddLast(edge.info());
            oldPath.weight = newWeight;

            return true;
        }

        private Dictionary<V, PathInfo<V, E>> bellmanFord(V origin)
        {
            //从顶点中找到对应的顶点
            Vertex<V, E> start = null;
            vertices.TryGetValue(origin, out start);
            if (start == null) return null;

            //用来存放返回值
            var selectedPath = new Dictionary<V, PathInfo<V, E>>();
            PathInfo<V, E> path = new PathInfo<V, E>(weightManager.zero());
            selectedPath[origin] = path;

            //循环次数
            int count = vertices.Count - 1;
            //对所有的边进行n-1次松弛操作
            for (int i = 0; i < count; i++)
            {
                foreach(var edge in edges)
                {
                    PathInfo<V, E> pathInfo = null;
                    selectedPath.TryGetValue(edge.start.value, out pathInfo);
                    if (pathInfo == null) continue;
                    relexBellmanFord(edge, pathInfo, selectedPath);
                }
            }

            for (int i = 0; i < count; i++)
            {
                foreach (var edge in edges)
                {
                    PathInfo<V, E> pathInfo = null;
                    selectedPath.TryGetValue(edge.start.value, out pathInfo);
                    if (pathInfo == null) continue;
                    if(relexBellmanFord(edge, pathInfo, selectedPath))
                    {
                        Console.WriteLine("有负权环");
                        return null;
                    }
                }
            }
            selectedPath.Remove(start.value);
            return selectedPath;
        }

        public override Dictionary<V, Dictionary<V, PathInfo<V, E>>> ShortestPath()
        {
            Dictionary<V, Dictionary<V, PathInfo<V, E>>> res = new Dictionary<V, Dictionary<V, Graph<V, E>.PathInfo<V, E>>>();

            //把所有的边都添加进入
            foreach(Edge<V, E> edge in edges)
            {

                Dictionary<V, PathInfo<V, E>> value = null;
                res.TryGetValue(edge.start.value, out value);
                if (value == null)
                {
                    value = new Dictionary<V, PathInfo<V, E>>();
                    res[edge.start.value] = value;
                }

                PathInfo<V, E> pathInfo = new PathInfo<V, E>(edge.weight);
                pathInfo.edges.AddLast(edge.info());
                value.Add(edge.end.value, pathInfo);
            }

            foreach(Vertex<V, E> v2 in vertices.Values)
            {
                foreach (Vertex<V, E> v1 in vertices.Values)
                {
                    foreach (Vertex<V, E> v3 in vertices.Values)
                    {
                        if (v1.Equals(v2) || v1.Equals(v3) || v2.Equals(v3)) continue;
                        //v1 -> v2
                        PathInfo<V, E> path12 = GetPathInfo(v1, v2, res);
                        if (path12 == null) continue;
                        //v2 -> v3
                        PathInfo<V, E> path23 = GetPathInfo(v2, v3, res);
                        if(path23 == null) continue;
                        //v1 -> v3
                        PathInfo<V, E> path13 = GetPathInfo(v1, v3, res);

                        E newWeight = weightManager.add(path12.weight, path23.weight);
                        if (path13 != null && weightManager.compare(newWeight, path13.weight) >= 0) continue;

                        if(path13 == null)
                        {
                            path13 = new PathInfo<V, E>();
                            res[v1.value][v3.value] = path13;
                        }
                        else
                        {
                            path13.edges.Clear();
                        }
                        path13.weight = newWeight;
                        foreach(var path in path12.edges)
                        {
                            path13.edges.AddLast(path);
                        }
                        foreach (var path in path23.edges)
                        {
                            path13.edges.AddLast(path);
                        }
                    }
                }
            }
            return res;
        }

        private PathInfo<V, E> GetPathInfo(Vertex<V, E> from, Vertex<V, E> to, Dictionary<V, Dictionary<V, PathInfo<V, E>>> paths)
        {
            Dictionary<V, PathInfo<V, E>> value = null;
            paths.TryGetValue(from.value, out value);
            if (value == null) return null;
            PathInfo<V, E> path = null;
            value.TryGetValue(to.value, out path);
            return  path;
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
