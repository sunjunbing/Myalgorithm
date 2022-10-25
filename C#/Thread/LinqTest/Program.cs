// See https://aka.ms/new-console-template for more information
using LinqTest;
using System.Diagnostics.Metrics;

Console.WriteLine("Hello, World!");

var gaoshou = new List<Wulingaoshou>()
{
    new Wulingaoshou()
    {
        Id = 1, Name = "黄蓉", Age = 18, Menpai = "丐帮", Kongfu = "打狗棍法", Level = 9
    },
    new Wulingaoshou()
    {
        Id = 2, Name = "洪七公", Age = 70, Menpai = "丐帮", Kongfu = "打狗棍法", Level = 10
    },
    new Wulingaoshou()
    {
        Id = 3, Name = "郭靖", Age = 22, Menpai = "丐帮", Kongfu = "降龙十八掌", Level = 10
    },
    new Wulingaoshou()
    {
        Id = 4, Name = "任我行", Age = 50, Menpai = "明教", Kongfu = "葵花宝典", Level = 1
    },
    new Wulingaoshou()
    {
        Id = 5, Name = "东方不败", Age = 35, Menpai = "明教", Kongfu = "葵花宝典", Level = 10
    },
    new Wulingaoshou()
    {
        Id = 6, Name = "令狐冲", Age = 23, Menpai = "华山", Kongfu = "独孤九剑", Level = 10
    },
    new Wulingaoshou()
    {
        Id = 7, Name = "梅超风", Age = 23, Menpai = "桃花岛", Kongfu = "九阴真经", Level = 8
    },
    new Wulingaoshou()
    {
        Id = 7, Name = "黄药师", Age = 100, Menpai = "桃花岛", Kongfu = "弹指神功", Level = 5
    },
};

var kongfu = new List<Kongfu>
{
    new Kongfu(){ Id = 1, Name = "打狗棍法", Power = 90},
    new Kongfu(){ Id = 2, Name = "降龙十八掌", Power = 95},
    new Kongfu(){ Id = 3, Name = "葵花宝典", Power = 90},
    new Kongfu(){ Id = 4, Name = "独孤九剑", Power = 100},
    new Kongfu(){ Id = 4, Name = "九阴真经", Power = 100},
    new Kongfu(){ Id = 4, Name = "弹指神功", Power = 100},
};

//查询所有level > 8的武林高手
var res = from m in gaoshou         //frome  :  从哪个集合中操作
          where m.Level > 8 && m.Menpai == "丐帮"     //where  :  条件限制
          select m.Name;            //select :  返回的集合
foreach (var temp in res)
{
    Console.WriteLine(temp);
}

var res1 = gaoshou.Where(m => m.Level > 8 && m.Menpai == "华山");
foreach (var temp in res1)
{
    Console.WriteLine(temp);
}

//Linq之联合查询
var res2 = from m in gaoshou
           from k in kongfu
           where m.Kongfu == k.Name && m.Level > 8
           orderby m.Age
           select new { master = m, kf = k };
foreach (var temp in res2)
{
    Console.WriteLine(temp);
}

var res3 = gaoshou.SelectMany(m => kongfu, (m, k) => new { master = m, kf = k }).Where(x => x.master.Kongfu == x.kf.Name && x.master.Level > 90);
foreach (var temp in res3)
{
    Console.WriteLine(temp);
}

//Linq之排序
var res4 = from m in gaoshou
           where m.Level > 8 && m.Menpai == "丐帮"
           orderby m.Age
           select m;
foreach (var temp in res4)
{
    Console.WriteLine(temp);
}

var res5 = gaoshou.Where(m => m.Level > 8 && m.Menpai == "丐帮").OrderBy(m => m.Age).ThenBy(m => m.Id);
foreach (var temp in res5)
{
    Console.WriteLine(temp);
}

//Linq之分组操作
var res6 = from k in kongfu
           join m in gaoshou on k.Name equals m.Kongfu
           into groups
           orderby groups.Count()
           select new {kongfu = k, count = groups.Count()};
foreach (var temp in res6)
{
    Console.WriteLine(temp);
}

var res7 = from master in gaoshou
           group master by master.Menpai
           into g
           select new { count = g.Count(), key = g.Key };
foreach (var temp in res7)
{
    Console.WriteLine(temp);
}