/*******************************************
* 01076582 - Assignment 3                  *
* Members:                                 *
* 1.55010006 Kanokporn   Chuangcham        *
* 2.55010977 Maturose    Kappako           *
* 3.55011362 Suratchanan Kraidech          *
*******************************************/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;
namespace AIAssignment3
{
    class pzstate : ICloneable
    {
        public char []sol = new char[500];
        public char[][] cappz = { new char[3], new char[3], new char[3] };
        public int sollen;
        public int fn;
        public object Clone()
        {
            int i, j;
            pzstate temp = new pzstate();
            for (i = 0; i < sollen; i++)
                temp.sol[i] = this.sol[i];
            //sol.CopyTo(temp.sol, 0);
            for (i = 0; i < 3; i++)
                for (j = 0; j < 3; j++)
                    temp.cappz[i][j] = cappz[i][j];
            temp.sollen = sollen;
            temp.fn = fn;
            return temp;
        }
    }

    class arrpos
    {
        public int r;
        public int c;
    }


    class Program
    {
        public static Random gen = new Random();
        public static int brow = 2, bcol = 2;
        public static char[] sol = new char[2000];
        public static char[][] puzzle = { new char[] { '1', '2', '3' }, new char[] { '4', '5', '6' }, new char[] { '7', '8', ' ' } };
        public static char[][] goal = {new char[]{'1','2','3'},new char[]{'4','5','6'},new char[]{'7','8',' '}};
        public static char[][] start = {new char[3],new char[3],new char[3] };
        public static char[] direction = { 'U', 'L', 'D', 'R' };
        static bool mvblank(char dir)
        {
            if (dir == 'U')
            {
                if (brow > 0)
                {
                    puzzle[brow][bcol] = puzzle[brow - 1][bcol];
                    brow--;
                    puzzle[brow][bcol] = ' ';
                    return true;
                }
                return false;
            }
            else if (dir == 'L')
            {
                if (bcol > 0)
                {
                    puzzle[brow][bcol] = puzzle[brow][bcol - 1];
                    bcol--;
                    puzzle[brow][bcol] = ' ';
                    return true;
                }
                return false;
            }
            else if (dir == 'D')
            {
                if (brow < 2)
                {
                    puzzle[brow][bcol] = puzzle[brow + 1][bcol];
                    brow++;
                    puzzle[brow][bcol] = ' ';
                    return true;
                }
                return false;
            }
            else
            {
                if (bcol < 2)
                {
                    puzzle[brow][bcol] = puzzle[brow][bcol + 1];
                    bcol++;
                    puzzle[brow][bcol] = ' ';
                    return true;
                }
                return false;
            }

        }

        static void randomPuzzle()
        {
            int i;
            for (i = 0; i < 10000; i++)
            {
                mvblank(direction[Convert.ToInt32(Math.Floor(gen.NextDouble() * 4))]);
            }
        }

        static char findOppositeDir(char d)
        {
            if (d == 'U') return 'D';
            else if (d == 'L') return 'R';
            else if (d == 'D') return 'U';
            else if (d == 'R') return 'L';
            else return ' ';
        }
        static arrpos findPos(int type, char ch)
        {
            int i, j;
            arrpos ans = new arrpos();
            ans.r = 0;
            ans.c = 0;
            if (type == 0)
            {
                for (i = 0; i < 3; i++)
                {
                    for (j = 0; j < 3; j++)
                    {
                        if (puzzle[i][j] == ch)
                        {
                            ans.r = i;
                            ans.c = j;
                            return ans;
                        }
                    }
                }
            }
            else
            {
                for (i = 0; i < 3; i++)
                {
                    for (j = 0; j < 3; j++)
                    {
                        if (goal[i][j] == ch)
                        {
                            ans.r = i;
                            ans.c = j;
                            return ans;
                        }
                    }
                }
            }
            return ans;
        }
        static int mhtdis()
        {
            int i, j, sum = 0;
            arrpos pos1, pos2;
            for (i = 0; i < 3; i++)
            {
                for (j = 0; j < 3; j++)
                {
                    pos1 = findPos(0, puzzle[i][j]);
                    pos2 = findPos(1, puzzle[i][j]);
                    sum = sum + Math.Abs(pos1.r - pos2.r) + Math.Abs(pos1.c - pos2.c);
                }
            }

            return sum;
        }

        static int wrongtiledis()
        {
            int i, j, sum = 0;
            for (i = 0; i < 3; i++)
                for (j = 0; j < 3; j++)
                    if (puzzle[i][j] != goal[i][j]) sum++;
            return sum;
        }

       
        static bool isFinalStates()
        {
            return puzzle[0][0] == '1' && puzzle[0][1] == '2' && puzzle[0][2] == '3' && puzzle[1][0] == '4' && puzzle[1][1] == '5' && puzzle[1][2] == '6' && puzzle[2][0] == '7' && puzzle[2][1] == '8' && puzzle[2][2] == ' ';
        }
        static void printPuzzle()
        {
            int i, j;
            for (i = 0; i < 3; i++)
            {
                Console.Write(" ");
                for (j = 0; j < 3; j++)
                {
                    Console.Write(puzzle[i][j]);
                    if (j + 1 < 3) Console.Write(" | ");
                }
                Console.WriteLine();
            }
            Console.WriteLine();
        }

        static void printStartPuzzle()
        {
            int i, j;
            for (i = 0; i < 3; i++)
            {
                Console.Write(" ");
                for (j = 0; j < 3; j++)
                {
                    Console.Write(start[i][j]);
                    if (j + 1 < 3) Console.Write(" | ");
                }
                Console.WriteLine();
            }
            Console.WriteLine();
        }
        static void findSolution()
        {
            int nextind, i, j, k, T = 1000000;
            arrpos ar;
            List<pzstate> list = new List<pzstate>();

            pzstate current = new pzstate(),next,temp;
            current.sollen = 0;  //sollen act as gn
            current.sol[0] = '\0';

            current.fn = mhtdis() + wrongtiledis();
            //Duplicate puzzle state
            for (i = 0; i < 3; i++)
                for (j = 0; j < 3; j++)
                   current.cappz[i][j] = puzzle[i][j];

            //Is it final state?
            if (isFinalStates())
            {
                //if yes
                //return that state snapshot as answer
                return;
            }

            //Start from start stage derive all possible move at t=0
            //Add all possible move (with state capture)
            for (i = 0; i < 4; i++)
            {
                if (mvblank(direction[i]))
                {
                    temp = (pzstate)current.Clone();
                    temp.sol[temp.sollen] = direction[i];
                    for (j = 0; j < 3; j++)
                        for (k = 0; k < 3; k++)
                            temp.cappz[j][k] = puzzle[j][k];
                    temp.sollen++;
                    temp.fn = mhtdis() + wrongtiledis(); //more hn value result in less expand node.
                    list.Add(temp);
                    mvblank(findOppositeDir(direction[i]));
                }
            }

            while (true)
            {
                
                if (T == 0)
                {
                    Console.WriteLine("Final State:");
                    printPuzzle();
                    //Console.WriteLine("Leng = " + sol.Length);
                    //for (i = 0; i < current.sollen; i++)
                    //Console.Write(current.sol[i]); return;
                    return;
                }
                nextind = Convert.ToInt32(Math.Floor(gen.NextDouble()*list.Count));
                next = list.ElementAt(nextind);
                list.RemoveAt(nextind);

                if(current.fn - next.fn > 0)
                {
                    current = (pzstate)next.Clone();
                    //When dequeue,set solution(length sollen),puzzle state with the position of blank char.
                    for (i = 0; i < current.sollen; i++)
                    {
                        sol[i] = current.sol[i];
                    }
                    sol[i] = '\0';
                    for (i = 0; i < 3; i++)
                        for (j = 0; j < 3; j++)
                            puzzle[i][j] = current.cappz[i][j];
                    ar = findPos(0, ' ');
                    brow = ar.r; bcol = ar.c;

                    //current changed find all possible move
                    //Track final state?
                    
                    for (i = 0; i < 4; i++)
                    {
                        if (direction[i] != findOppositeDir(current.sol[current.sollen - 1]))
                        {
                            if (mvblank(direction[i]))
                            {
                                temp = (pzstate)current.Clone();
                                temp.sol[temp.sollen] = direction[i];
                                for (j = 0; j < 3; j++)
                                    for (k = 0; k < 3; k++)
                                        temp.cappz[j][k] = puzzle[j][k];
                                temp.sollen++;
                                temp.fn = mhtdis() + wrongtiledis(); //more hn value result in less expand node.
                                list.Add(temp);
                                //temp.sollen--;
                                mvblank(findOppositeDir(direction[i]));
                            }
                        }
                    }
                }
                else
                {
                    double prob, target;
                    target = 1 / (Math.Pow(Math.E, (Math.Abs(current.fn - next.fn))*1.0 / (T/40000)));
                    prob = gen.NextDouble();
                    //Console.WriteLine( prob + " " + target);
                    if (prob < target)
                    {
                        current = (pzstate)next.Clone();

                        //When dequeue,set solution(length sollen),puzzle state with the position of blank char.
                        for (i = 0; i < current.sollen; i++)
                        {
                            sol[i] = current.sol[i];
                        }
                        sol[i] = '\0';
                        for (i = 0; i < 3; i++)
                            for (j = 0; j < 3; j++)
                                puzzle[i][j] = current.cappz[i][j];
                        ar = findPos(0, ' ');
                        brow = ar.r; bcol = ar.c;

                        //current changed find all possible move
                        //Track final state?
                        //temp = (pzstate)current.Clone();
                        for (i = 0; i < 4; i++)
                        {
                            if (direction[i] != findOppositeDir(current.sol[current.sollen - 1]))
                            {

                                if (mvblank(direction[i]))
                                {
                                    temp = (pzstate)current.Clone();
                                    temp.sol[temp.sollen] = direction[i];
                                    for (j = 0; j < 3; j++)
                                        for (k = 0; k < 3; k++)
                                            temp.cappz[j][k] = puzzle[j][k];
                                    temp.sollen++;
                                    temp.fn = mhtdis() + wrongtiledis(); //more hn value result in less expand node.
                                    list.Add(temp);
                                    //temp.sollen--;
                                    mvblank(findOppositeDir(direction[i]));
                                }
                            }
                        }

                    }
                }
                T--;
            }
        }
        public static int Main(string[] args)
        {
            int i, j, trials;
            char ch;

            for (trials = 0; trials < 1; trials++)
            {
                Console.WriteLine("[TRIAL " + (trials + 1)+"]");
                Console.WriteLine();
                randomPuzzle();
                for (i = 0; i < 3; i++)
                    for (j = 0; j < 3; j++)
                        start[i][j] = puzzle[i][j];
                Stopwatch timer = new Stopwatch();
                timer.Start();
                findSolution();
                timer.Stop();
                i = 0;
                while (sol[i] != '\0')
                    Console.Write(sol[i++]);
                if (i < 2)
                {
                    Console.WriteLine();
                    Console.Write(i + "move. ");
                }
                else
                {
                    Console.WriteLine();
                    Console.Write(i + "moves. ");
                }
                Console.WriteLine("Time used:" + (timer.ElapsedMilliseconds / 1000.0) + " seconds");
                for (i = 0; i < 3; i++)
                    for (j = 0; j < 3; j++)
                        puzzle[i][j] = start[i][j];
                arrpos ar = findPos(0, ' ');
                brow = ar.r; bcol = ar.c;

                Console.WriteLine("Start State:");
                printPuzzle();
                Console.WriteLine("==========================\n");
            }
            
            i = 0;
            Console.Write("Press R to move next\nPress L to move prev\nPress S to view start state\nPress T to view solution\n");
            Console.Write("Press Q to quit.\n");
            while (true)
            {
                ch = Console.ReadKey().KeyChar;
                Console.WriteLine();
                if (Char.ToUpper(ch) == 'L')
                {
                    if (i > 0)
                    {
                        Console.Write("UNDO STEP "+i+"\n");
                        mvblank(findOppositeDir(sol[--i]));
                        printPuzzle();
                    }
                }
                else if (Char.ToUpper(ch) == 'R')
                {
                    if (sol[i] != '\0')
                    {
                        Console.Write("STEP " + (i+1) + ":"+sol[i]+"\n");
                        mvblank(sol[i++]);
                        printPuzzle();
                    }
                }
                else if (Char.ToUpper(ch) == 'S')
                {
                    Console.Write("\nSTART STATE:\n");
                    printStartPuzzle();
                }
                else if (Char.ToUpper(ch) == 'T')
                {
                    j = 0;
                    while (sol[j] != '\0')
                        Console.Write(sol[j++]);
                    if (j < 2)
                        Console.Write("\n"+j+" move.\n");
                    else
                        Console.Write("\n"+j+" moves.\n");
                    Console.WriteLine();
                }
                else if (Char.ToUpper(ch) == 'Q')
                {
                    break;
                }
            }
            return 0;
        }
    }


    









}




