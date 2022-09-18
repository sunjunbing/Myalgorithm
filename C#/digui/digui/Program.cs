using System.Collections;
using System.Collections.Generic;


// See https://aka.ms/new-console-template for more information
Console.WriteLine("Hello, World!");

digui.FIB fIB = new digui.FIB();
int n = 10; 
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


digui.ClimbStairs stairs = new digui.ClimbStairs();
digui.Times.cost("func1", () => {
    Console.Write($"{stairs.func1(n)}");
});

digui.Times.cost("func2", () => {
    Console.Write($"{stairs.func2(n)}");
});

digui.Times.cost("func4", () => {
    Console.Write($"{stairs.func4(n)}");
});


Console.WriteLine($"---------------------- ");

digui.Hanoi hanoi = new digui.Hanoi();
hanoi.hanoi(3, "A", "B", "C");

digui.Queen quees = new digui.Queen();
quees.PlaceXQueen(8);