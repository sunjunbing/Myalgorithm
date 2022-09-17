using System.Collections;
using System.Collections.Generic;


// See https://aka.ms/new-console-template for more information
Console.WriteLine("Hello, World!");

digui.FIB fIB = new digui.FIB();
int n = 40; 

int res = 0;
digui.Times.cost("Fib", () => {
    Console.Write($"{fIB.Fib(n)}");
});

digui.Times.cost("Fib2", () => {
    Console.Write($"{fIB.Fib2(n)}");
});

digui.Times.cost("Fib3", () => {
    Console.Write($"{fIB.Fib3(n)}");
});

digui.Times.cost("Fib4", () => {
    Console.Write($"{fIB.Fib4(n)}");
});
