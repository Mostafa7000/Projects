#include <iostream>
#include <cctype>
using namespace std;

const int ROW=7,COL=8;
////////////////////////////////////////////////////////
bool authentic(char [][COL]);
int organisms(const char [][COL], int, int);
bool check(char,char[][COL], int, int);
void NextGeneration(char [][COL],char [][COL], int, int);
void print (char [][COL]);
void swaping (char [][COL], char [][COL]);
/////////////////////////////////////////////////////////
int main()
{
    char life[ROW][COL],life2[ROW][COL];
    int iterations;

    cout<<"Enter the 7x7 array (each line at a time)\n";
    for(int i=0;i<ROW;i++)
    {
        cin>>life[i];
    }
    while(!authentic(life))
    {
        cout<<"please enter another 7x7 array (each line at a time)\n";
        for(int i=0;i<ROW;i++)
        {
            cin>>life[i];
        }

    }
    cout<<"Enter the number of iterations: ";
    cin>>iterations;
    for(int row=0;row<ROW;row++)//print the Original array
    {
        cout<<"\n[";
        for(int col=0;col<COL-1;col++)
        {
                cout<<char (toupper(life[row][col]));
        }
        cout<<"]";
    }
    cout<<endl;
    for(int i=0;i<iterations;i++)
    {
        for(int row=0;row<ROW;row++)
        {
            for(int col=0;col<COL-1;col++)
            {
                NextGeneration(life2, life, row, col);
            }
        }
        cout<<endl;
        print(life2);
        swaping (life,life2);
    }
}
bool authentic(char life[][COL])//checks the correctness of the array
{
        for(int row=0;row<ROW;row++)
        {
            for(int col=0;col<COL-1;col++)
            {
                if(life[row][col]!='m' && life[row][col]!='M' && life[row][col]!='-')
                    return false;
            }
        }
        return true;
}
int organisms(const char life[][COL],int row,int col)//function to get the number of organisms nearby
{
    int top=row-1,bottom=row+1,right=col+1,left=col-1;
    int counter=0;
    if ((top)>=0 && (left)>=0)
        if (life[top][left]=='m' || life[top][left]=='M')//top left
            counter++;
    if ((top)>=0)
        if (life[top][col]=='m' || life[top][col]=='M')//top center
            counter++;
    if ((top)>=0 && (right)>=0)
        if (life[top][right]=='m' || life[top][right]=='M')//top right
            counter++;
    if ((left)>=0)
        if (life[row][left]=='m' || life[row][left]=='M')//center left
            counter++;
    if ((right)>=0)
        if (life[row][right]=='m' || life[row][right]=='M')//center right
            counter++;
    if ((bottom)>=0 && (left)>=0)
        if (life[bottom][left]=='m' || life[bottom][left]=='M')//bottom left
            counter++;
    if ((bottom)>=0)
        if (life[bottom][col]=='m' || life[bottom][col]=='M')//bottom center
            counter++;
    if ((bottom)>=0 && (right)>=0)
        if (life[bottom][right]=='m' || life[bottom][right]=='M')//bottom right
            counter++;
    return counter;
}
bool check(char ch, char life[][COL], int row, int col)//function to determine what this place will be in the next iteration
{
    int number=organisms(life,row,col);
    if(ch=='M' || ch=='m')
    {
        if(number>=4 || number<=1)
            return false;
        else
            return true;
    }
    else
    {
        if(number==3)
            return true;
        else
            return false;
    }
}
void NextGeneration(char life2[][COL], char life[][COL], int row, int col)//function to put the new generation in an array
{
    if(check(life[row][col], life, row, col))
    {
        life2[row][col]='M';
    }
    else
        life2[row][col]='-';
}
void print (char life2[][COL])//Print the new iteration
{
    for(int i=0;i<ROW;i++)
    {
        cout<<"["<<life2[i]<<"]\n";
    }
}
void swaping (char life[][COL], char life2[][COL])//put the new iteration in the original array
{
    for(int i=0;i<ROW;i++)
    {
        for(int j=0;j<COL-1;j++)
           {
             life[i][j]=life2[i][j];

           }
    }
}
