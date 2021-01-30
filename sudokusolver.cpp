/*
The program use brute force to solve a Sudoku Puzzle given as
an input text file named SUDOKU.TXT
It ignores white space, and the characters '|','.','+'

What should be left is eighty-one non-zero
digits and periods, which are entered into the initial grid.

create the SUDOKU.TXT file
in the same directory and run the exe in a command console window


 */

#include <stdio.h>
#include <stdlib.h>
#include<ctype.h>
#include<iostream>
#include<string.h>

using namespace std;
#define MAXSOLUTIONS 4
int grid[9][9], solutions;

//function to reset grid
static void resetgrid()
{
int i,j;
for (i=0;i<9;i++)
for (j=0;j<9;j++)
{
grid[i][j] = 0;
}
}

//function for checking the grid
static int ingrid(int i,int j, int val)
{
int k, m;
                                             // in  a row
for (k=0; k<9; k++)
{
if (k!=j)
if (grid[i][k]==val)
return 0;
}
                                            //  in a column
for (m=0; m<9; m++)
{
if (m!=i)
if (grid[m][j]==val)
return 0;
}
                                            //in sub grid
for (k=(i/3)*3; k<(i/3)*3+3; k++)
for (m=(j/3)*3; m<(j/3)*3+3; m++)
{
if ((k!=i)||(m!=j))
if (grid[k][m]==val)
return 0;
}
return 1;
}


//function to read grid
static int readgrid()
{
int i, j, ch;

resetgrid();
for (i=0;i<9;i++)
for (j=0;j<9;j++)
for (;;)
{
ch=getchar();
                                                  //printf("%c",ch);
if (ch==EOF)
return -1;
if (ch=='-')
break;
if (('1'<=ch )&&(ch<='9'))
{
if (ingrid(i,j,1+ch-'1'))
{
grid[i][j]=1+ch-'1';
break;
} else
{
return -1;
}
}
if (!isspace(ch) && ch!= '|' && ch!= '.' && ch!='+')
return -1;
}

for (;;)
{
int ch=getchar();
if (ch==EOF)
return 0;
if (!isspace(ch) && ch!= '|' && ch!= '.' && ch!='+')
return -1;
}
}


//function to display the solved sudoku grid
static void displaygrid()
{
int i,j;
for (i=0;i<9;i++)
{
if (i%3 == 0)
cout<<" # - - -  # - - -  # - - -  #\n";
for (j=0;j<9;j++)
{
if (j%3==0)
cout<<" | ";
cout<<grid[i][j]<<" ";
}
cout<<" | \n";
}
cout<<" # - - -  # - - -  # - - -  #\n";
}


static int SearchSolution(int i, int j)
{
int value;
if (j==9)
{
j=0;
i++;
}
if (i==9)
 {                                               //solution of given sudoku
  displaygrid();
  solutions++;

  cout<<"\nThe number of solutions found  "<<solutions<<endl;

                                                 //fprintf(stderr," %d solution(s) found !\n", solutions);
                                                 //return solutions >= MAXSOLUTIONS;
  return solutions;

}

if (grid[i][j]!=0)
{
if (SearchSolution(i, j+1))
return 1;
}
else
{
for (value=1;value<10;value++)
if (ingrid(i,j,value))
 {
grid[i][j]=value;
if (SearchSolution(i,j+1))
return 1;
}
grid[i][j]=0;
}
return 0;
}



static int solution()
{
if (readgrid()==-1)
{
cout<<"\n\nInvalid input matrix\n";
return 1;
}

solutions = 0;
cout<<"\n\n Given Matrix is :\n";
displaygrid();
cout<<"\n\n The solution is : \n\n";

SearchSolution(0,0);
if (solutions == 0)
{
cout<< "No solution found for the given matrix \n";
return 1;
}
return 0;
}

//main function

int main(int argc, char **argv)
{
    char user[15],pass[9];
    cout<<"*-*-*-* THE SUDOKU SOLVER *-*-*-*-*\n";
for(;;)
{int x;


    cout<<"****** MENU *******\n";
    cout<<" CHOICE 1:SOLVE THE PUZZLE\n";
    cout<<" CHOICE 2:EXIT\n";
    cout<<"\n\n-----------  NOTE  --------------------------------------------------------\n";
    cout<<"\n      ENTER YOUR SUDOKU TO BE SOLVED IN THE TEXT FILE 'SUDOKU.TXT'     ";
    cout<<"\n\n-----------  NOTE  --------------------------------------------------------\n";
    cout<<"\n\nenter your choice:";
    cin>>x;
    if(x==1)
            {

            char *output = 0;
               if (!freopen("sudoku.txt" , "r", stdin))
                 {
                     fprintf(stderr,"input file sudoku.txt does not exist.\n");
                      return 1;
                 }

               if (output && !freopen(output, "w", stdout))
                      {
                        perror(output);
                        return 1;
                      }

               return solution();
               break;
            }
            else
                {

                if(x==2)
                    return 0;
                else
                    cout<<"wrong choice\n"<<"\nchoose again";}


    }

    return 0;
}
