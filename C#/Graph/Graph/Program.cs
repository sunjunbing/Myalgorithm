﻿using System;
using System.Collections.Generic;

Console.WriteLine("Hello world");

//Graph.ListGraph<string, int> gp = new Graph.ListGraph<string, int>();
//gp.AddEdge("V1", "V0", 9);
//gp.AddEdge("V1", "V2", 3);
//gp.AddEdge("V2", "V0", 2);
//gp.AddEdge("V2", "V3", 5);
//gp.AddEdge("V3", "V4", 1);
//gp.AddEdge("V0", "V4", 6);

//gp.RemoveVertex("V3");

////gp.print();

//Console.WriteLine("--------------BFS---------------");
//gp.BFS("V1");
//Console.WriteLine("--------------DFS---------------");
//gp.DFS("V1");
//Console.WriteLine("--------------DFSStack---------------");
//gp.DFSStack("V1");

//Console.WriteLine("--------------TopologicalSort---------------");

//Graph.ListGraph<string, int> gp1 = new Graph.ListGraph<string, int>();
//gp1.AddEdge("0", "2", 0);
//gp1.AddEdge("1", "0", 0);
//gp1.AddEdge("2", "5", 0); gp1.AddEdge("2", "6", 0);
//gp1.AddEdge("3", "1", 0); gp1.AddEdge("3", "5", 0); gp1.AddEdge("3", "7", 0);
//gp1.AddEdge("5", "7", 0);
//gp1.AddEdge("6", "4", 0);
//gp1.AddEdge("7", "6", 0);
//List<string> list = gp1.TopologicalSort();
//foreach (string v in list)
//{
//    Console.WriteLine(v);
//}

Graph.ListGraph<string, int> gp2 = new Graph.ListGraph<string, int>(new SubWeightManager());
gp2.AddEdge("A", "B", 17); gp2.AddEdge("A", "F", 1); gp2.AddEdge("A", "E", 16);
gp2.AddEdge("B", "A", 17); gp2.AddEdge("F", "A", 1); gp2.AddEdge("E", "A", 16);

gp2.AddEdge("B", "C", 6); gp2.AddEdge("B", "D", 5); gp2.AddEdge("B", "F", 11);
gp2.AddEdge("C", "B", 6); gp2.AddEdge("D", "B", 5); gp2.AddEdge("F", "B", 11);

gp2.AddEdge("C", "D", 10);
gp2.AddEdge("D", "C", 10);

gp2.AddEdge("D", "E", 4); gp2.AddEdge("D", "F", 14);
gp2.AddEdge("E", "D", 4); gp2.AddEdge("F", "D", 14);

gp2.AddEdge("E", "F", 33);
gp2.AddEdge("F", "E", 33);

HashSet<Graph.Graph<string, int>.EdgeInfo<string, int>> set = gp2.mst();
foreach(Graph.Graph<string, int>.EdgeInfo<string, int> info in set)
{
    Console.WriteLine(info);
}


Graph.ListGraph<string, int> gp3 = new Graph.ListGraph<string, int>(new SubWeightManager());
gp3.AddEdge("A", "B", 10); gp3.AddEdge("A", "D", 30); gp3.AddEdge("A", "E", 100);
gp3.AddEdge("B", "C", 50);
gp3.AddEdge("C", "E", 10);
gp3.AddEdge("D", "C", 20); gp3.AddEdge("D", "E", 60);

Dictionary<string, Graph.Graph<string, int>.PathInfo<string, int>> res = gp3.ShortestPath("A");
Dictionary<string, Graph.Graph<string, int>.PathInfo<string, int>>.Enumerator it = res.GetEnumerator();
while (it.MoveNext())
{
    Console.WriteLine($" {it.Current.Key} = {it.Current.Value}");
}

Dictionary<string, Dictionary<string, Graph.Graph<string, int>.PathInfo<string, int>>> paths = gp3.ShortestPath();
Dictionary<string, Dictionary<string, Graph.Graph<string, int>.PathInfo<string, int>>>.Enumerator pathIt = paths.GetEnumerator();
while (pathIt.MoveNext())
{
    Console.WriteLine($" {pathIt.Current.Key} ----------------------------------");
    Dictionary<string, Graph.Graph<string, int>.PathInfo<string, int>>.Enumerator itt = pathIt.Current.Value.GetEnumerator();
    while (itt.MoveNext())
    {
        Console.WriteLine($" {itt.Current.Key} {itt.Current.Value}");
    }

}


Graph.ListGraph<int, int> gp4 = new Graph.ListGraph<int, int>(new SubWeightManager1());
gp4.AddEdge(0, 1, 1);
gp4.AddEdge(1, 2, 7); 
gp4.AddEdge(1, 0, -2);

Dictionary<int, Graph.Graph<int, int>.PathInfo<int, int>> res1 = gp4.ShortestPath(1);
if (res1 != null)
{
    Dictionary<int, Graph.Graph<int, int>.PathInfo<int, int>>.Enumerator it1 = res1.GetEnumerator();
    while (it.MoveNext())
    {
        Console.WriteLine($" {it.Current.Key} = {it.Current.Value}");
    }
}


//现在类型已经定了
class SubWeightManager : Graph.Graph<string, int>.WeightManager<int>
{
    public int compare(int e1, int e2)
    {
        //比较器
        return e1.CompareTo(e2);
    }

    public int add(int e1, int e2)
    {
        return e1 + e2;
    }

    public int zero()
    {
        return 0;
    }
}

class SubWeightManager1 : Graph.Graph<int, int>.WeightManager<int>
{
    public int compare(int e1, int e2)
    {
        //比较器
        return e1.CompareTo(e2);
    }

    public int add(int e1, int e2)
    {
        return e1 + e2;
    }

    public int zero()
    {
        return 0;
    }
}



