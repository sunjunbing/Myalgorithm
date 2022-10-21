// See https://aka.ms/new-console-template for more information
Console.WriteLine("Hello, World!");

//MYThread.CreateThread();

//MYThread.ThreadParam();

//ThreadLock.Test();

/*
 * CPU的上下文切换，线程调度器，当线程切换的时候，
 * 线程调度器会保存当前等待线程的状态，并切换到另外一个线程
 * 而要回复等待线程的状态，需要消耗相当多的资源
 *
 * 内核模式
 * 线程的状态：执行、阻塞 切换会占用很多CPU的时间
 * 
 * 用户模式
 * 线程只是简单的等待，此时会浪费cpu的时间，但是
 * 相对于切换上下文效率会更高，
 * 
 * 混合模式
 * 先使用用户模式，如果等待时间很长就会切换到阻塞状态，
 * 以节省cpu资源
 * 
 */

//Semaphore.test();

//MyAutoResetEvent.test();

//MyReaderWriterLock.test();

Concurrent.ConcurrentDictionaryTest();