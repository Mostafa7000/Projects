#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <limits>
using namespace std;

struct account
{
    int account_number;
    char first_name[10];
    char last_name[10];
    float total_Balance;
};
struct link
{
    account data;
    link* next;
};
class Records
{
private:
    link* start;
public:
    Records( )
    { start = NULL; }
    void write_rec( );
    void read_rec( );
    void fwrite( );
    void fbinarywrite( );
    void fbinaryread( );
    void search_rec( );
    void update_rec( );
    void delete_rec( );
};
void write(link* newlink)
{
    cout<<"Enter account number: "; cin>>newlink->data.account_number;
    while (!cin.good())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout<<"Enter account number: "; cin>>newlink->data.account_number;
    }
    cin.ignore();//To ignore the '\n' character
    cout<<"Enter first name: "; cin.getline(newlink->data.first_name,10);
    while (!cin.good())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }
    cout<<"Enter last name: "; cin.getline(newlink->data.last_name,10);
    while (!cin.good())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }
    cout<<"Enter the balance: "; cin>>newlink->data.total_Balance;
    while(!cin.good())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout<<"Enter the balance: "; cin>>newlink->data.total_Balance;
    }

}
void read (link* current)
{
    cout<<"------------------------------------------------\n";
    cout<<"Account number: "; cout<<current->data.account_number<<endl;
    cout<<"First name: "; cout<<current->data.first_name<<endl;
    cout<<"Last name: "; cout<<current->data.last_name<<endl;
    cout<<"Balance: $"; cout<<current->data.total_Balance<<endl;
    cout<<"------------------------------------------------\n";
}
void Records::write_rec()
{
    link* newlink=new link;
    newlink->next=start;
    start=newlink;
    write(newlink);
}
void Records::read_rec()
{
    if (start==NULL)
    {
        cout<<"There is no records.";
        return;
    }
    link* current=start;
    while(current!=NULL)
    {
        read(current);
        current=current->next;
    }
}
void Records::search_rec()
{
    int num;
    cout<<"Enter account number: "; cin>>num;
    if (start==NULL)
    {
        cout<<"There is no records.";
        return;
    }
    link* current=start;
    while(current!=NULL)
    {
        if(current->data.account_number==num)
        {
            cout<<"Record Found: \n";
            read(current);
            return;
        }
        current=current->next;
    }
    cout<<"Account not found.";
}
void Records::update_rec()
{
    int num;
    cout<<"Enter account number: "; cin>>num;
    if (start==NULL)
    {
        cout<<"There is no records.";
        return;
    }
    link* current=start;
    while(current!=NULL)
    {
        if(current->data.account_number==num)
        {
            cout<<"Enter the new data: \n";
            write(current);
            return;
        }
        current=current->next;
    }
    cout<<"Account not found.";
}
void Records::delete_rec()
{
    int num;
    cout<<"Enter account number: "; cin>>num;
    if (start==NULL)
    {
        cout<<"There is no records to delete.";
        return;
    }
    link* current=start;
    if (current->data.account_number==num)
    {
        start=current->next;
        delete current;
        current=0;
        cout<<"Account deleted.\n";
        return;
    }
    while(current->next!=NULL)
    {
        if(current->next->data.account_number==num)
        {
            link* deletable=current->next; //To be able to delete the pointer
            current->next=current->next->next;
            delete deletable;
            deletable=0;
            cout<<"Account deleted.\n";
            return;
        }
        current=current->next;
    }
    cout<<"Account not found.";
}
void Records::fwrite()
{
    if (start==NULL)
    {
        cout<<"There is no records.";
        return;
    }
    link* current=start;
    ofstream outstream("Log.txt");
    if (outstream)
    {
        cout<<"Writing has been done successfully.\n";
    }
    while(current!=NULL)
    {
        outstream<<"------------------------------------------------\n";
        outstream<<"Account number: "; outstream<<current->data.account_number<<endl;
        outstream<<"First name: "; outstream<<current->data.first_name<<endl;
        outstream<<"Last name: "; outstream<<current->data.last_name<<endl;
        outstream<<"Balance: $"; outstream<<current->data.total_Balance<<endl;
        outstream<<"------------------------------------------------\n";
        current=current->next;
    }
}
void Records::fbinarywrite()
{
    if (start==NULL)
    {
        cout<<"There is no records.";
        return;
    }
    link* current=start;
    ofstream outstream;
    outstream.open("Binary log.dat",ios::binary);
    while (current!=NULL)
    {
        outstream.write(reinterpret_cast<char*>(current),sizeof(account));
        current=current->next;
    }
    cout<<"Record has been written successfully";
}
void Records::fbinaryread()
{
    ifstream instream;
    instream.open("Binary log.dat",ios::binary);
    if (instream.seekg(0,ios::end) && instream.tellg()==0)
    {
        cout<<"File is empty.";
        return;
    }
    if (!instream)
    {
        cout<<"Cant't open file.";
        return;
    }
    while(instream.peek()!=EOF)
    {
        link* newlink=new link;
        newlink->next=start;
        start=newlink;
        instream.read(reinterpret_cast<char*>(newlink),sizeof(account));
    }
    cout<<"Record has been read successfully";
}
int main()
{
    int choice;
    Records record;
    cout<<"Account information system.\n\n";
    while(1)
    {
        cout<<"Select one option below:\n";
        cout<<"\t1-->Add record to the system\n";
        cout<<"\t2-->Show record from the system\n";
        cout<<"\t3-->Search record from the system\n";
        cout<<"\t4-->Update record from the system\n";
        cout<<"\t5-->Delete record from the system\n";
        cout<<"\t6-->Write the record to file\n";
        //cout<<"\t7-->Write the record to file (binary)\n";
        //cout<<"\t8-->Get the record from file (binary)\n";
        cout<<"\t9-->Quit the system\n";
        cout<<"Enter your choice: ";    cin>>choice;
        while (!cin.good())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout<<"Enter your choice: ";    cin>>choice;
        }
        cout<<endl;
        switch(choice)
        {
            case 1:record.write_rec(); break;
            case 2:record.read_rec(); break;
            case 3:record.search_rec(); break;
            case 4:record.update_rec(); break;
            case 5:record.delete_rec(); break;
            case 6:record.fwrite(); break;
            //case 7:record.fbinarywrite(); break;
            //case 8:record.fbinaryread(); break;
            case 7:exit(1);
            default: cout<<"Invalid choice.\n\n";
        }
        cout<<endl;
    }
    return 0;
}
