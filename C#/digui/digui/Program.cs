using System.Collections;
using System.Collections.Generic;


// See https://aka.ms/new-console-template for more information
Console.WriteLine("Hello, World!");

digui.FIB fIB = new digui.FIB();
int n = 40; 

DateTime time = DateTime.Now;
int res = fIB.Fib(n);
DateTime after = DateTime.Now;
Console.WriteLine($" Fib cost {res} {(after - time).TotalMilliseconds}");

res = fIB.Fib2(n);
DateTime after1 = DateTime.Now;
Console.WriteLine($" Fib2 cost {res} {(after1 - after).TotalMilliseconds}");

res = fIB.Fib3(n);
DateTime after2 = DateTime.Now;
Console.WriteLine($" Fib3 cost {res} {(after2 - after1).TotalMilliseconds}");

res = fIB.Fib4(n);
DateTime after3 = DateTime.Now;
Console.WriteLine($" Fib4 cost {res} {(after3 - after2).TotalMilliseconds}");