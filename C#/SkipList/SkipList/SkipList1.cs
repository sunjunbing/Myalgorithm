using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection.Metadata.Ecma335;
using System.Text;
using System.Threading.Tasks;

public class SkipList1<KType, VType>
{
    public static int MAX_LAYER = 32;
    private Func<KType, KType, int> comperator;

    //虚拟头节点
    private Node<KType, VType> first;

    private int size;

    private int level;

    public SkipList1() : this(null)
    {

    }
    public SkipList1(Func<KType, KType, int> comperator)
    {
        this.comperator = comperator;
        this.first = new Node<KType, VType>(default, default, MAX_LAYER);
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
        keyCheck(key);

        var node = first;
        var pre = new Node<KType, VType>[level];
        for (int layer = level - 1; layer >= 0; layer--)
        {
            int cmp = -1;
            while (node.next[layer] != null && (cmp = compare(key, node.next[layer].key)) > 0)
            {
                node = node.next[layer];
            }
            if (cmp == 0)//如果找到相等的就直接替换
            {
                var oldV = node.next[layer].value;
                node.next[layer].value = value;
                return oldV;
            }

            //证明没有相等的，要添加
            pre[layer] = node;
        }

        //如何添加
        /*
         * 随机产生一个层数
         */
        int newLayer = randomLayer();
        var addNode = new Node<KType, VType>(key, value, newLayer);
        for (int i = 0; i < newLayer; i++)
        {
            if (i >= level)
            {
                first.next[i] = addNode;
            }
            else 
            {
                //更新next节点
                addNode.next[i] = pre[i].next[i];
                pre[i].next[i] = addNode;
            }
        }

        //更新层数
        level = Math.Max(level, newLayer);

        size++;

        return default;
    }

    public VType get(KType key)
    {
        keyCheck(key);
        var node = first;

        for (int layer = level - 1; layer >= 0; layer--)
        {
            int cmp = -1;
            while (node.next[layer] != null && (cmp = compare(key, node.next[layer].key)) > 0)
            {
                node = node.next[layer];
            }
            if (cmp == 0) return node.next[layer].value;
        }

        return default;
    }

    public VType remove(KType key)
    {
        keyCheck(key);
        var node = first;
        bool exit = true;
        var pre = new Node<KType, VType>[level];
        for (int layer = level - 1; layer >= 0; layer--)
        {
            int cmp = -1;
            while (node.next[layer] != null && (cmp = compare(key, node.next[layer].key)) > 0)
            {
                node = node.next[layer];
            }
            if (cmp == 0)//获得了要删除的节点
            {
                exit = false;
            }
            //证明没有相等的，要添加
            pre[layer] = node;
        }
        if (exit) return default;

        var removeNode = node.next[0];

        size--;

        for(int i = 0; i < removeNode.next.Length; i++)
        {
            pre[i].next[i] = removeNode.next[i];
        }

        var newLayer = level;
        while (--newLayer >= 0 && first.next[newLayer] == null)
        {
            level = newLayer;
        }

        return removeNode.value;
    }

    private int randomLayer()
    {
        int newLayer = 0;
        Random random = new Random();
        while (newLayer < MAX_LAYER && random.Next(0, 1) < 0.25)
        {
            newLayer++;
        }
        return newLayer;
    }

    private void keyCheck(KType key)
    {
        if(key == null) throw new NullReferenceException("key is null");
    }

    private int compare(KType key1, KType key2)
    {
        return comperator != null ? comperator(key1, key2) : ((IComparable<KType>)key1).CompareTo(key2);
    }

    public class Node<KType, VType>
    {
        public KType key;
        public VType value;
        public Node<KType, VType>[] next;

        public Node(KType key, VType value, int count)
        {
            this.key = key;
            this.value = value;
            this.next = new Node<KType, VType>[count];
        }
    }
}
