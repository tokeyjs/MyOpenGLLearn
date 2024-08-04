using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace studyCS
{
    class Program
    {
        int? y = null;
        protected int opp;

        static int[] arr = new int[12];


        static void Main(string[] args)
        {
            GG g = new GG();
            Action atc = new Action(g.Test);
            atc.Invoke();

            _ = Console.ReadKey();
        }
    }

    struct GG
    {
        public int u;
        public void Test()
        {
            Console.WriteLine("test()");
        }
    }

     abstract class Fa
    {
        virtual public void func1()
        {

        }

        abstract public void func2();

    }

    class MyClass
    {
        public GG u;
        public double val;

        public MyClass()
        {

        }

        // 强转 MyClass->double
        public static implicit operator double(MyClass mc)
        {
            return mc.val;
        }
    }
}
