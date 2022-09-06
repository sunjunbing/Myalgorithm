using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


public class UnionFind<E>
{
    Dictionary<E, Node<E>> nodes = new Dictionary<E, Node<E>> ();

    public void makeSet(E value)
    {
        if (nodes.ContainsKey(value)) return;
        nodes.Add(value, new Node<E>(value));
    }

    private Node<E> findNode(E e)
    {
        Node<E> node = null;
        nodes.TryGetValue(e, out node);
        if (node == null) return null;
        //这里使用路径分裂
        while (!Object.Equals(node.value, node.parent.value))
        {
            node.parent = node.parent.parent;
            node = node.parent;
        }
        return node;
    }

    public E find(E value)
    {
        Node<E> node = findNode(value);
        return node == null ? default : node.value;
    }

    private void union(E e1, E e2)
    {
        Node<E> p1 = findNode(e1);
        Node<E> p2 = findNode(e2);
        if (p1 == null || p2 == null) return;
        if (Object.Equals(p1.value, p2.value)) return;
        if(p1.rank < p2.rank)
        {
            p1.parent = p2;
        }
        else if(p1.rank > p2.rank)
        {
            p2.parent = p1;
        }
        else
        {
            p1.parent = p2;
            p1.rank++;
        }
    }

    public Boolean isSampe(E e1, E e2)
    {
        return Object.Equals(find(e1), find(e2));
    }

    public class Node<E>
    {
        public E value;
        public Node<E> parent;
        public int rank = 1;
        public Node(E value)
        {
            this.value = value;
            this.parent = this;
        }
    }
}
