using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

public class SkipList<KType, VType>
{
    private static int MAX_LAYER = 32;
    private int size;

    private Node<KType, VType> first;

    private Func<KType, KType, int> Comparator;

    private int level;//有效层数

    public SkipList(Func<KType, KType, int> comparetor)
    {
        this.Comparator = comparetor;
        this.first = new Node<KType, VType>(default, default, MAX_LAYER) ;
    }
    public SkipList() : this(null)
    {

    }

    public int GetSize()
    {
        return size;
    }

    public bool isEmpty()
    {
        return size == 0;
    }

    public VType put(KType key, VType value)
    {
        KeyCheck(key);
        Node<KType, VType> node = first;
        Node<KType, VType>[] nodes = new Node<KType, VType>[level];
        for (int layer = level - 1; layer >= 0; layer--)
        {
            int cmp = -1;
            while (node.nexts[layer] != null && (cmp = compare(key, node.nexts[layer].key)) > 0)
            {
                node = node.nexts[layer];
            }
            if (cmp == 0)
            {
                VType oldv = node.nexts[layer].value;
                node.nexts[layer].value = value;
                return oldv;
            }
            nodes[layer] = node;
        }

        //new node
        int newLayer = randomLayer();
        Node<KType, VType> newNode = new Node<KType, VType>(key, value, newLayer);
        for(int i = 0; i < newLayer; i++)
        {
            if(i >= level)
            {
                first.nexts[i] = newNode;
            }
            else
            {
                newNode.nexts[i] = nodes[i].nexts[i];
                nodes[i].nexts[i] = newNode;
            }
        }

        size++;

        level = Math.Max(level, newLayer);

        return default;
    }

    public VType get(KType key)
    {
        KeyCheck(key);
        Node<KType, VType> node = first;
        for(int layer = level - 1; layer >= 0; layer--)
        {
            int cmp = -1;
            while (node.nexts[layer] != null && (cmp = compare(key, node.nexts[layer].key)) > 0)
            {
                node = node.nexts[layer];
            }
            if (cmp == 0) return node.nexts[layer].value;
        }
        return default(VType);
    }

    public VType remove(KType key)
    {
        //确定要删除的节点
        Node<KType, VType> node = first;
        Node<KType, VType>[] pre = new Node<KType, VType>[level];
        bool exit = false;
        for(int i = level - 1; i >= 0; i--)
        {
            int cmp = -1;
            while (node.nexts[i] != null && (cmp = compare(key, node.nexts[i].key)) > 0)
            {
                node = node.nexts[i];
            }
            pre[i] = node;
            if (cmp == 0) exit = true;
        }

        if (!exit) return default;

        var removeNode = node.nexts[0];

        //更新层数
        size--;

        //更新 list
        for (int i = 0; i < removeNode.nexts.Length; i++)
        {
            pre[i].nexts[i] = removeNode.nexts[i];
        }

        int newLayer = level;
        while (--newLayer >= 0 && first.nexts[newLayer] == null)
        {
            level = newLayer;
        }

        return removeNode.value;
    }

    private void KeyCheck(KType key)
    {
        if (key == null)
        {
            throw new ArgumentNullException("key is null"); 
        }
    }

    private int randomLayer()
    {
        int layer = 0;
        Random random = new Random();
        while(random.Next(0, 1) < 0.25 && layer < MAX_LAYER)
        {
            layer++;
        }
        return layer;
    }

    private int compare(KType key1, KType key2)
    {
        return Comparator != null ? Comparator(key1, key2) : ((IComparable<KType>)key1).CompareTo(key2);
    }

    public class Node<KType, VType>{
        public KType key;
        public VType value;
        public Node<KType, VType>[] nexts;

        public Node(KType key, VType value, int count)
        {
            this.key = key;
            this.value = value;
            this.nexts = new Node<KType, VType>[count];
        }
    }
}
