using System;


namespace QuickSort
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");
            int[] array = Integers.random(10000, 1, 1000000);
            int[] array1 = new int[array.Length];
            Array.Copy(array, array1, array.Length);
            int[] array2 = new int[array.Length];
            Array.Copy(array, array2, array.Length);
            Times.test("bubbleSort", () =>
            {
                bubbleSort(array);
            });
            Times.test("bubbleSort2", () =>
            {
                bubbleSort2(array1);
            });

            Times.test("bubbleSort3", () =>
            {
                bubbleSort3(array2);
            });

            Times.test("selectionSort", () =>
            {
                selectionSort(array2);
            });
        }

        static void bubbleSort(int[] array)
        {
            bool swapped = false;
            do
            {
                swapped = false;
                for (int i = 0; i < array.Length - 1; i++)
                {
                    if (array[i] > array[i + 1])
                    {
                        int temp = array[i];
                        array[i] = array[i + 1];
                        array[i + 1] = temp;
                        swapped = true;
                    }
                }
            } while (swapped);
        }

        static void bubbleSort2(int[] array)
        {
            for(int i = array.Length - 1; i > 0; i--)
            {
                bool swapped = true;
                for(int j = 1; j <= i; j++)
                {
                    if(array[j] < array[j - 1])
                    {
                        int temp = array[j];
                        array[j] = array[j - 1];
                        array[j - 1] = temp;
                        swapped = false;
                    }
                }
                if (swapped) break;
            }
        }

        static void bubbleSort3(int[] array)
        {
            for (int i = array.Length - 1; i > 0; i--)
            {
                int sortedIndex = 1;
                for (int j = 1; j <= i; j++)
                {
                    if (array[j] < array[j - 1])
                    {
                        int temp = array[j];
                        array[j] = array[j - 1];
                        array[j - 1] = temp;
                        sortedIndex = j;
                    }
                }
                i = sortedIndex;
            }
        }

        static void selectionSort(int[] array)
        {
            for(int i = array.Length - 1; i > 0; i--)
            {
                int maxIndex = 0;
                for (int j = 1; j <= i; j++)
                {
                    if(array[maxIndex] <= array[j])
                    {
                        maxIndex = j;
                    }
                }
                int temp = array[maxIndex];
                array[maxIndex] = array[i];
                array[i] = temp;
            }
        }
    }
}
