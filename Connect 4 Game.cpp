#include <iostream>
#include <cstring>
#include <string>
using namespace std;
string decoration(8,'-');
int row[7]={5,5,5,5,5,5,5};
void print (char[][8]);
bool Insert (char[][8],char,int);
char IsWinnig (char[0][8]);
bool valid (int);
int main ()
{
    int col;
/////////////////////////////////////////
    char board[6][8];
    for (int i=0;i<6;i++)
        for (int j=0;j<7;j++)
            board[i][j]=' ';
    for (int i=0;i<6;i++)
        board[i][7]='\0';
/////////////////////////////////////////
    do
    {
        cout<<"The first player turn (X)\nChoose the column (from 1 to 7): ";
        cin>>col;
        while (!valid (col-1))
        {
            cout<<"Enter the column again please: ";
            cin>>col;
        }
        while (!Insert (board,'X',col-1))
        {
            cout<<"Enter another column: ";
            cin>>col;
        }
        print (board);
        if (IsWinnig (board)!='\0')
            break;
        cout<<"The second player turn (O)\nChoose the column (from 1 to 7): ";
        cin>>col;
        while (!valid (col-1))
        {
            cout<<"Enter the column again please: ";
            cin>>col;
        }
        while (!Insert (board,'O',col-1))
        {
            cout<<"Enter another column: ";
            cin>>col;
        }
        print (board);
        if (IsWinnig (board)!='\0')
            break;
    }while(1);
    cout<<"The winner is player ("<<IsWinnig (board)<<") WOOHOO!";
    return 0;
}
void print (char board[][8])
{
    cout<<decoration<<endl;
    for (int i=0;i<6;i++)
    {
        cout<<board[i];
        cout<<endl;
    }
    cout<<decoration<<endl;
}
bool Insert (char board[][8],char player,int col)/*col is between 0 and 6*/
{
    if (row[col]>=0)
    {
        board[row[col]][col]=player;
        row[col]--;
        return true;
    }
    else
        return false;
}
char IsWinnig (char board[][8])
{
    //check the X-axis
    for (int i=0;i<6;i++)
    {
        if (strstr (board[i],"XXXX")!= NULL)
            return 'X';

        else if (strstr (board[i],"OOOO")!= NULL)
            return 'O';
    }
    //Rotate the matrix then check the X-axis "the Y-axis previously"
    char boardR[7][7];
    for (int i=0;i<6;i++)
        for (int j=0;j<7;j++)
            boardR[j][i]=board[i][j];

    for (int i=0;i<7;i++)
        board[i][6]='\0';

    for (int i=0;i<7;i++)
    {
        if (strstr (boardR[i],"XXXX")!= NULL)
            return 'X';

        else if (strstr (boardR[i],"OOOO")!= NULL)
            return 'O';
    }
    //Check the main diagonal
    int x,y,counterx=0,countery=0;
    for (int row=0;row<=2;row++)
    {
        for (int col=0;col<=3;col++)
        {
            x=row,y=col;
            for (int i=0;i<3;i++)
            {
                if (board[x][y]!=board[++x][++y])
                    break;
                else if (board[x][y]=='X')
                    counterx++;
                else if (board[x][y]=='O')
                    countery++;
            }
            if (counterx==3)
                return 'X';
            else if (countery==3)
                return 'O';
            else
                counterx=0,countery=0;
        }
    }
    counterx=0,countery=0;
    for (int row=3;row<=5;row++)
    {
        for (int col=0;col<=3;col++)
        {
            x=row,y=col;
            for (int i=0;i<3;i++)
            {
                if (board[x][y]!=board[--x][++y])
                    break;
                else if (board[x][y]=='X')
                    counterx++;
                else if (board[x][y]=='O')
                    countery++;
            }
            if (counterx==3)
                return 'X';
            else if (countery==3)
                return 'O';
            else
                counterx=0,countery=0;
        }
    }
    return '\0';
}
bool valid (int col)
{
    if (col>=0 && col<=6)
        return true;
    else
        return false;
}
