using System;
using System.Collections.Generic;
using System.Text;


public class Student : IComparable<Student>
{
    public int score;
    public int age;

    public Student(int score, int age)
    {
        this.score = score;
        this.age = age;
    }

    public int CompareTo(Student o)
    {
        return age - o.age;
    }
}
