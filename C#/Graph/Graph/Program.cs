
Console.WriteLine("Hello world");

Graph.ListGraph<string, int> gp = new Graph.ListGraph<string, int>();
gp.AddEdge("V1", "V0", 9);
gp.AddEdge("V1", "V2", 3);
gp.AddEdge("V2", "V0", 2);
gp.AddEdge("V2", "V3", 5);
gp.AddEdge("V3", "V4", 1);
gp.AddEdge("V0", "V4", 6);

gp.RemoveVertex("V3");

//gp.print();

Console.WriteLine("--------------BFS---------------");
gp.BFS("V1");
Console.WriteLine("--------------DFS---------------");
gp.DFS("V1");
Console.WriteLine("--------------DFSStack---------------");
gp.DFSStack("V1");

Console.WriteLine("--------------TopologicalSort---------------");

Graph.ListGraph<string, int> gp1 = new Graph.ListGraph<string, int>();
gp1.AddEdge("0", "2", 0);
gp1.AddEdge("1", "0", 0);
gp1.AddEdge("2", "5", 0); gp1.AddEdge("2", "6", 0);
gp1.AddEdge("3", "1", 0); gp1.AddEdge("3", "5", 0); gp1.AddEdge("3", "7", 0);
gp1.AddEdge("5", "7", 0);
gp1.AddEdge("6", "4", 0);
gp1.AddEdge("7", "6", 0);
List<string> list = gp1.TopologicalSort();
foreach(string v in list)
{
    Console.WriteLine(v);
}

