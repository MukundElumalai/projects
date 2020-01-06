//to create an interface for a mobile
#include<iostream>
#include<windows.h>
#include<conio.h>
#include<string.h>
#include<iomanip>
#include<time.h>
#include<fstream>
#include<stdio.h>
#include<cstdlib>
using namespace std;

struct node         //for messages, call log, memo
{
    char info[100];
    string times;
    string message;
    node *link;
};

class linkedlist        //to stack and maintain list
{
    node *start;
public:
    linkedlist()
    {
        start=NULL;
    }
    void insert_last(string val)
    {
        node *temp=new node;
        temp->message=val;
        temp->link=NULL;
        if(start==NULL)
            start=temp;
        else
        {
            node *ptr=start;
            while(ptr->link!=NULL)
            {
                ptr=ptr->link;
            }
            ptr->link=temp;
        }
    }
    void insert_first(char val[100],string val2)
    {
        node *temp=new node;
        strcpy(temp->info,val);
        temp->times=val2;
        if(start==NULL){start=temp;}
        else{
            temp->link=start;
            start=temp;
            }
    }
    void insert_first(char val[20],string val1,string val2)
    {
        node *temp=new node;
        strcpy(temp->info,val);
        temp->message=val1;
        temp->times=val2;
        if(start==NULL){start=temp;}
        else{
            temp->link=start;
            start=temp;
            }
    }
    bool delete_pos(int pos)
    {
        if(pos<1)return 0;
        int c=1;
        node *ptr=start,*prev;
        if(pos==1)
        {
            start=start->link;
            delete ptr;
        }
        else
        {
            while(c<pos)
            {
                prev=ptr;
                ptr=ptr->link;c++;
            }
            if(ptr==NULL)return 0;
            prev->link=ptr->link;
            delete ptr;
        }
        return 1;
    }
    node* get_start()
    {
        return start;
    }
    void display()      //call display
    {
        node *ptr=start;
        if(start==NULL)cout<<"\n\t\t\tEMPTY LOG";
        else
        {
            while(ptr->link!=NULL)
            {
                cout<<"\n\n\t\t"<<left<<setw(20)<<ptr->info<<"  "<<ptr->times;
                ptr=ptr->link;
            }
        }
    }
    void displayMessage()
    {
        node *ptr=start;
        if(start==NULL)cout<<"\n\t\t\tEMPTY LOG";
        else
        {
            while(ptr!=NULL)
            {
                cout<<"\n\n"<<"To:"<<ptr->info;
                cout<<endl<<"\t> "<<ptr->message;
                cout<<"\n\nSent at:"<<ptr->times<<endl;
                cout<<"\n\t----- * ------------ * ----------";
                ptr=ptr->link;
            }
        }
    }
};

class game
{
    int no_wins,no_losses;
public:
    game()
    {
        fstream f;
        f.open("scores.txt",ios::in);
        f>>no_wins>>no_losses;
        f.close();
    }
    void minesweeper(int p)
{
	system("CLS");
	printf("\n\t\t\t\tMINESWEEPER");
	char Q[8][8],A[8][8],swap,Choice;
	int a[64][2],i,j,x,choice,y,Win=1;
//mine setting prep and Q / A table prep
	for(i=0,x=0;i<8;i++)
		for(j=0;j<8;j++,x++)
		{
			a[x][0]=i;
			a[x][1]=j;
		}
	for(i=0;i<8;i++)
		for(j=0;j<8;j++)
		{
			Q[i][j]='0';
			A[i][j]='*';
		}

//mine setter
	time_t t;
	srand((unsigned)time(&t));
	x=64;
	while(x>56)
	{	choice=rand()%x;
		i=a[choice][0];
		j=a[choice][1];
		Q[i][j]='*';
		swap=a[choice][0];
		a[choice][0]=a[--x][0];
		a[x][0]=swap;
		swap=a[choice][1];
	        a[choice][1]=a[x][1];
	        a[x][1]=swap;
	}
	//number setter
		numberset(Q);
//game-play
	printf("\n\n\t\tDo you need instructions?( Y / N):");
	do
	{
		scanf("%c",&Choice);
	}while(Choice==10);
	if(Choice=='y' || Choice=='Y')
		printf("\n\tThe objective of the game is to display all tiles except mines. The numbers represent the number of mines surrounding them");
	displaym(A);
	while(win(Q,A))
	{
		n://valid position entry
			printf("\n\nEnter the position,\n\tRow:");
			scanf("%d",&x);
			printf("\tcolumn:");
			scanf("%d",&y);
			--x;--y;
			if(A[x][y]!='*' && x>=0 && x<=7 && y<=7 && y>=0)
			{
				printf("\n\tAlready identified position");
				goto n;
			}
			if(x>7 || x<0 || y>7 || y<0)
			{
				printf("Enter a valid position");
				goto n;
			}
	//checking for mines/numbers
		if(Q[x][y]=='*')
		{
			printf("\n\nYou triggered a mine.. You Lose");Win=0;
			no_losses++;
			break;
		}
		else if(Q[x][y]!='0')
			A[x][y]=Q[x][y];
		else if(Q[x][y]=='0')
		{
			A[x][y]=Q[x][y];
			codezero(Q,A,x,y);
		}
		system("CLS");
		displaym(A);
	}
	if(Win)
	{
		printf("\n\n\n\tYou WIN!!!");
		no_wins++;
	}
	cout<<"\n\nNUMBER OF WINS    :"<<no_wins;
	cout<<"\nNUMBER OF LOSSES  :"<<no_losses;
	cout<<endl;
	fstream f;
	f.open("scores.txt",ios::out);
	f<<no_wins<<" "<<no_losses;
	f.close();
	system("pause");
}
void numberset(char Q[8][8])
{
	int i,j,x,y;
//centered
	for(i=1;i<7;i++)
		for(j=1;j<7;j++)
	//looping the center
			if(Q[i][j]=='*')
				for(x=i-1;x<i+2;x++)
					for(y=j-1;y<j+2;y++)
			//8 possibiities
						if(Q[x][y]!='*')
							Q[x][y]+=1;
//edged
	for(i=0,j=1;j<7;j++)
	//top edge
		if(Q[i][j]=='*')
			for(x=i;x<i+2;x++)
				for(y=j-1;y<j+2;y++)
			//5 possibilities
					if(Q[x][y]!='*')
						Q[x][y]+=1;
	for(i=7,j=1;j<7;j++)
	//bottom edge
		if(Q[i][j]=='*')
			for(x=i-1;x<i+1;x++)
				for(y=j-1;y<j+2;y++)
					if(Q[x][y]!='*')
						Q[x][y]+=1;
	for(j=0,i=1;i<7;i++)
	//left edge
		if(Q[i][j]=='*')
			for(x=i-1;x<i+2;x++)
				for(y=j;y<j+2;y++)
					if(Q[x][y]!='*')
						Q[x][y]+=1;
	for(j=7,i=1;i<7;i++)
	//right edge
		if(Q[i][j]=='*')
			for(x=i-1;x<i+2;x++)
				for(y=j-1;y<j+1;y++)
					if(Q[x][y]!='*')
						Q[x][y]+=1;
//corners
	//top left
	if(Q[0][0]=='*')
		for(x=0;x<2;x++)
			for(y=0;y<2;y++)
				if(Q[x][y]!='*')
					Q[x][y]+=1;
	//bottom right
	if(Q[7][7]=='*')
		for(x=6;x<8;x++)
			for(y=6;y<8;y++)
				if(Q[x][y]!='*')
					Q[x][y]+=1;
	//top right
	if(Q[0][7]=='*')
		for(x=0;x<2;x++)
			for(y=6;y<8;y++)
				if(Q[x][y]!='*')
					Q[x][y]+=1;
	//bottom left
	if(Q[7][0]=='*')
		for(x=6;x<8;x++)
			for(y=0;y<2;y++)
				if(Q[x][y]!='*')
					Q[x][y]+=1;
}
void codezero(char Q[8][8],char A[8][8],int i,int j)
{
	int x,y;
//centered
	if(i<7 && i>0 && j>0 && j<7)
		for(x=i-1;x<i+2;x++)
			for(y=j-1;y<j+2;y++)
				if(A[x][y]=='*')
				{
					A[x][y]=Q[x][y];
					if(A[x][y]=='0')
						codezero(Q,A,x,y);
				}
//edged
	//top
        if(i==0 && j!=0 && j!=7)
		for(x=i;x<i+2;x++)
                	for(y=j-1;y<j+2;y++)
                        	if(A[x][y]=='*')
				{
					A[x][y]=Q[x][y];
					if(A[x][y]=='0')
						codezero(Q,A,x,y);
				}
	//bottom
	if(i==7 && j!=0 && j!=7)
		for(x=i-1;x<i+1;x++)
			for(y=j-1;y<j+2;y++)
				if(A[x][y]=='*')
				{
					A[x][y]=Q[x][y];
					if(A[x][y]=='0')
						codezero(Q,A,x,y);
				}
	//left
	if(j==0 && i!=0 && i!=7)
		for(x=i-1;x<i+2;x++)
                	for(y=j;y<j+2;y++)
                        	if(A[x][y]=='*')
				{
					A[x][y]=Q[x][y];
					if(A[x][y]=='0')
						codezero(Q,A,x,y);
				}
        //right
	if(j==7 && i!=0 && i!=7)
		for(x=i-1;x<i+2;x++)
                	for(y=j-1;y<j+1;y++)
                        	if(A[x][y]=='*')
				{
					A[x][y]=Q[x][y];
					if(A[x][y]=='0')
						codezero(Q,A,x,y);
				}
//corners
	//top left
        if(i==0 && j==0)
                for(x=i;x<i+2;x++)
                        for(y=j;y<j+2;y++)
                                if(A[x][y]=='*')
                                {
					A[x][y]=Q[x][y];
					if(A[x][y]=='0')
						codezero(Q,A,x,y);
				}
	//bottom right
        if(i==7 && j==7)
                for(x=i-1;x<i+1;x++)
                        for(y=j-1;y<j+2;y++)
                                if(A[x][y]=='*')
				{
                                        A[x][y]=Q[x][y];
					if(A[x][y]=='0')
						codezero(Q,A,x,y);
				}
	//top right
        if(i==0 && j==7)
                for(x=i;x<i+2;x++)
                        for(y=j-1;y<j+1;y++)
                                if(A[x][y]=='*')
                                {
				        A[x][y]=Q[x][y];
					if(A[x][y]=='0')
						codezero(Q,A,x,y);
				}
	//bottom left
        if(i==7 && j==0)
                for(x=i-1;x<i+1;x++)
                        for(y=j;y<j+2;y++)
                                if(A[x][y]=='*')
                                {
					A[x][y]=Q[x][y];
					if(A[x][y]=='0')
						codezero(Q,A,x,y);
				}
}
	//Checks whether only mines are left
int win(char Q[8][8],char A[8][8])
{
	int i,j;
	for(i=0;i<8;i++)
		for(j=0;j<8;j++)
			if(A[i][j]=='*')
				if(A[i][j]!=Q[i][j])
					return 1;
	return 0;
}
	//displaying the minesweeper table
void displaym(char A[8][8])
{
	int i,j;
	printf("\n\n\n\tcol 1\tcol 2\tcol 3\tcol 4\tcol 5\tcol 6\tcol 7\tcol 8");
	for(i=0;i<8;i++)
	{
		printf("\n\nrow %d",i+1);
		for(j=0;j<8;j++)
			printf("\t%c",A[i][j]);
	}
}

};

class memo
{
    linkedlist m;
    int no_memo;
public:
    memo()
    {
        string info;
        no_memo=0;
        fstream f;
        f.open("memo.txt",ios::in);         //reading old memo
        while(getline(f,info))
        {
            m.insert_last(info);
        }
    }
    void create()                           //file storage and adding in the linked list
    {
        no_memo++;
        string info;
        cout<<"\n\n\t\t\tEnter your information:\n\t\t\t";
        cin.ignore();
        getline(cin,info);
        m.insert_last(info);
        fstream f;
        f.open("memo.txt",ios::app|ios::out);
        f<<info<<endl;
        cout<<"\n\t\t\tMemo created!";
    }
    void view()
    {
        int counts=1;
        node *ptr;
        ptr=m.get_start();
        while(ptr!=NULL)
        {
            cout<<"\n\n\t\t\t"<<counts++<<". "<<ptr->message;
            ptr=ptr->link;
        }
    }
    void delete_memo()
    {
        int data;
        view();
        cout<<"\n\n\t\t\tEnter the memo# to be deleted:";
        cin>>data;
        bool check=m.delete_pos(data);
        if(check==1)                        //if success, rewriting the file
        {
            cout<<"\n\t\t\t--DELETION SUCCESSFUL--";
            no_memo--;
            fstream f;
            f.open("memo.txt",ios::out);
            node *ptr=m.get_start();
            while(ptr!=NULL)
            {
                f<<ptr->message<<endl;
                ptr=ptr->link;
            }
            f.close();
        }
        else
            cout<<"--DELETION UNSUCCESSFUL--";
    }
};

class contacts
{
    char name[20];
    char mob_no[15];
public:
    void createContact()
    {
        cout<<"\n\n\t\t\tEnter contact name: ";
        cin>>name;
        cout<<"\n\t\t\tEnter contact no. : ";
        cin>>mob_no;
        fstream f;
        f.open("contacts.txt",ios::app|ios::out);   //adding contact to file
        f<<" "<<name<<" "<<mob_no;
        cout<<"\n\n\t\t\tContact added!";
        f.close();
    }
    bool viewContact(char temp[20])
    {
        fstream f;bool flag=0;
        f.open("contacts.txt",ios::in);
        while(!f.eof())
        {
            f>>name;
            f>>mob_no;
            if(strcmp(temp,name)==0)
            {
                flag=1;
                cout<<"\n\n\t\t\tName: "<<name<<"\n\t\t\t"<<"Mobile number: "<<mob_no;
            }
        }
        if(flag==0)cout<<"\n\n\t\t\t--Contact not found--";
        f.close();
    }
    char* callContact()
    {
        char temp[20];
        char failret[1]="";
        cout<<"\n\t\t\tEnter the name of the contact: ";
        cin>>temp;
        if(viewContact(temp))
        {
            return temp;
        }
        else
            return failret;
    }
    void deleteContact()
    {
        char temp[20];
        cout<<"\n\n\t\t\tEnter the contact to be deleted: ";
        cin>>temp;
        fstream f;bool flag=0;
        f.open("contacts.txt",ios::in);
        fstream fc;
        fc.open("contactstemp.txt",ios::out);
        while(!f.eof())                     //copying the undeleted contacts to the file
        {
            f>>name;
            f>>mob_no;
            if(strcmp(name,temp)==0)
                flag=1;
            else
                fc<<" "<<name<<" "<<mob_no;
        }
        f.close();
        fc.close();
        if(flag==1)cout<<"\n\t\t\tContact deleted!";
        else cout<<"\n\n\t\t\tContact not found";
        remove("contacts.txt");
        rename("contactstemp.txt","contacts.txt");
    }
    void modifyContact()
    {
        char temp[20];
        cout<<"\n\n\t\t\tEnter the contact to be modified: ";
        cin>>temp;
        fstream f;bool flag=0;
        f.open("contacts.txt",ios::in);
        fstream fc;
        fc.open("contactstemp.txt",ios::out);           //after modification, writing file
        while(!f.eof())
        {
            f>>name;
            f>>mob_no;
            if(strcmp(name,temp)==0)
            {
                flag=1;
                cout<<"\n\t\t\tEnter the new name and mobile number :)";
                cout<<"\n\n\t\t\tName:";
                cin>>name;
                cout<<"\n\t\t\tMobile No.:";
                cin>>mob_no;
                fc<<" "<<name<<" "<<mob_no;
            }
            else
                fc<<" "<<name<<" "<<mob_no;
        }
        f.close();
        fc.close();
        if(flag==0)cout<<"\n\t\t\tContact not found";
        remove("contacts.txt");
        rename("contactstemp.txt","contacts.txt");
    }
    void displayContacts()
    {
        fstream f;
        f.open("contacts.txt",ios::in);
        cout<<setw(20)<<left<<"\n\n\t\t\tNAME"<<setw(20)<<left<<"\t    MOBILE NO."<<endl;
        while(!f.eof())
        {
            f>>name;
            f>>mob_no;
            cout<<"\n\n\t\t\t"<<setw(20)<<left<<name<<setw(20)<<mob_no;
        }
        f.close();
    }
};

class call
{
    linkedlist call_log;
    char name[20];
    string times;
    contacts *CONTACTS;
public:
    call(){}
    void get_contacts(contacts *x)
    {
        fstream f;
        CONTACTS=x;
        f.open("calllog.txt",ios::in);
        while(f>>name && getline(f,times))
        {
            call_log.insert_first(name,times);
        }
        f.close();
    }
    void makeCall()
    {
        char temp[20];
        int choice;
        cout<<"\n\n\t\t\t1.To a contact\n\t\t\t2.To a number";
        cout<<"\n\n\t\t\t> ";
        cin>>choice;
        if(choice==1)
        {
        strcpy(temp,CONTACTS->callContact());   //searching the contact
        }
        else
        {
            cout<<"\n\t\t\tEnter the number:";
            cin>>temp;
        }
        if(temp[0]!='\0')
        {//writing into the file and list
            time_t tim;
            time(&tim);
            times=ctime(&tim);
            fstream f;
            f.open("calllog.txt",ios::app | ios::out);
            f<<temp<<" ";
            f<<times<<endl;
            char *txt="Calling...";
            cout<<"\n\t\t\t";
            for(int i=0;txt[i]!='\0';i++)
            {
                cout<<txt[i];Sleep(250);
            }
            cout<<"\n\t\t\tHANG? (1):";
            int data;
            cin>>data;
            cout<<"\n\t\t\tCall Ended!";
            f.close();
            call_log.insert_first(temp,times);
        }
    }
    void display()
    {
        call_log.display();
    }
};

class message
{
    char name[20];
    string mess,times;
    linkedlist m;
    contacts *CONTACTS;
public:
    message(){}
    void get_contacts(contacts *x)
    {   //reading the old messages from the file
        fstream f;
        CONTACTS=x;
        f.open("message.txt",ios::in);

        while(f>>name && getline(f,mess) && getline(f,times))
        {
            m.insert_first(name,mess,times);
        }
        f.close();
    }
    void Create()
    {
        char temp[20];int choice;
        cout<<"\n\n\t\t\t1.To a Contact\n\t\t\t2.To a number";
        cout<<"\n\n\t\t\t> ";
        cin>>choice;
        if(choice==1)   //finding the contact
        {
            strcpy(temp,CONTACTS->callContact());
        }
        else
        {
            cout<<"\n\t\t\tEnter the number:";
            cin>>temp;
        }
        if(temp[0]!='\0')
        {   //writing into the file and the list
            cout<<"\n\t\t\tEnter message:";
            cin.ignore();
            getline(cin,mess);
            fstream f;
            time_t tim;
            time(&tim);
            string times=ctime(&tim);
            f.open("message.txt",ios::app|ios::out);
            f<<temp<<" ";
            f<<mess<<endl;
            f<<times<<endl;
            m.insert_first(temp,mess,times);
            cout<<"\n\t\t\tMessage sent!";
            f.close();
        }
    }
    void display()
    {
        m.displayMessage();
    }
};

class settings
{
    char pin[6];
public:
    settings()
    {   //to read the old password
        fstream f;
        f.open("password.txt",ios::in);
        f>>pin;
        f.close();
    }
    char* get_pin(){return pin;}    //for associating with lockscreen(class phone)
    void changePIN()
    {
        char temp[6],temp2[6];
        cout<<"\n\n\t\t\tEnter the old pin:";
        cin>>temp;
        if(strcmp(temp,pin)==0)
        {
            cout<<"\n\n\t\t\tEnter the new pin:";
            cin>>temp;
            cout<<"\t\t\tCONFIRM the new pin:";
            cin>>temp2;
            if(strcmp(temp,temp2)==0)
            {
                cout<<"\n\t\t\tPIN change successful!";
                strcpy(pin,temp);
                fstream f;
                f.open("password.txt",ios::out);
                f<<pin;
                f.close();
            }
            else
            {
                cout<<"\nConfirmation failed";
            }
        }
        else cout<<"\n--WRONG PIN--";
    }
};
int m,y;
time_t t = time(NULL);
tm* tptr= localtime(&t);
void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}
int dayNumber(int day,int month, int year)
{

    static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1,
                       4, 6, 2, 4 };
    year -= month < 3;
    return ( year + year/4 - year/100 +
             year/400 + t[month-day] + 1) % 7;
}

//string getMonthName(int monthNumber)
//{
    string months[] = {"January", "February", "March",
                       "April", "May", "June",
                       "July", "August", "September",
                       "October", "November", "December"
                      };

  //  return (months[monthNumber]);
//}

int numberOfDays (int monthNumber, int year)
{
    switch(monthNumber)
    {
        case 0:
        case 2:
        case 4:
        case 6:
        case 7:
        case 9:
        case 11:
            return (31);
            break;
        case 1:
            if (year % 400 == 0 ||(year % 4 == 0 && year % 100 != 0))
                return (29);
            else
                return (28);
            break;
        case 3:
        case 5:
        case 8:
        case 10:
            return (30);
            break;
    }
}

void printCalendarMonth(int month,int year)
{
    cout<<endl<<"           Year "<<year<<endl<<endl;
    int days;

    int current = dayNumber (1,1, year);

    int k=current;
    for (int i = 0; i < month; i++)
    {
        days = numberOfDays (i, year);
        for (int j = 1; j <= days; j++)
            if (++k > 6)
                k = 0;
        current = k;
    }
    days = numberOfDays (month, year);

    cout<<"\n  ------------"<<months[month]<<"-------------\n";
    cout<<"  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n";

    for (k = 0; k < current; k++)
        printf("     ");

    for (int j = 1; j <= days; j++)
    {
        printf("%5d", j);

        if (++k > 6)
        {
            k = 0;
            printf("\n");
        }
    }

    if (k)
        printf("\n");
    return;
}
int inrange(int d,int m,int y)
{
    int difference=(y - tptr->tm_year - 1900)*365;
    if(difference==0)
        difference+= (m - tptr->tm_mon)*10;
    if(difference<=10)
        return 1;
    return 0;
}
void prev(int &m,int &y)    //calculating prev month index
{
    if(m==0)
    {
        m=11;
        y--;
    }
    else
        m--;
}
void next(int &m,int &y)    //calculating next month index
{
    if(m==11)
    {
        m=0;
        y++;
    }
    else
        m++;
}
void printCalendar(int year)    //prints a whole year calender
{
    int ch=1;
    while(ch!=0)
    {
    system("cls");
    cout<<"         Calendar - "<<year<<endl<<endl;
    int days;

    int current = dayNumber (1,1, year);

    for (int i = 0; i < 12; i++)
    {
        days = numberOfDays (i, year);

        cout<<"\n  ------------"<<months[i]<<"-------------\n";

        cout<<"  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n";

        int k;
        for (k = 0; k < current; k++)
            printf("     ");

        for (int j = 1; j <= days; j++)
        {
            printf("%5d", j);

            if (++k > 6)
            {
                k = 0;
                printf("\n");
            }
        }

        if (k)
            printf("\n");

        current = k;
    }
    cout<<"\n(1) Previous Year\t(2) Next Year\n(3) Enter Year\t\t(0) Return to Menu\n:";
    cin>>ch;
    if(ch>3 || ch<0)
    {
        cout<<"\nThis option is availiable only for secret agents. *insert some cool emoji here*\n";
        system("pause");
    }
    else
    switch(ch)
    {
        case 1: prev(year,ch);
                break;
        case 2: next(year,ch);
                break;
        case 3: cout<<"\nEnter year\t";
                cin>>year;
                break;
        case 0: return;
    }
    }
}

int Check(int d,int m,int y)
{
    if(d<=numberOfDays(m,y)&& m<12 && m>=0 && y>=tptr->tm_year+1900 &&d>=0)
    {
        if(y==tptr->tm_year+1900)
        {
            if(m>tptr->tm_mon)
                return 1;
            else if(m==tptr->tm_mon)
            {
                if(d>=tptr->tm_mday)
                    return 1;
            }
        }
        else
            return 1;
    }
    return 0;
}
struct day
{
    bool rep;
    int d,m,y;
    string note;
    day* next;
};
class calender         //linkedlist
{
    int d,m,y;
    int tot,TOT;
    day* start;
    public:
    calender()
    {
        ifstream det;
        det.open("Details.txt",ios::in);
        det>>TOT;
        start=NULL;
        tot=0;
        det.close();
    }
    void InQ(day *temp)     //insertion
    {
        tot++;
        if(tot>=TOT)
                TOT=tot;
        day* ptr=start;
        day* prev;
        while(ptr!=NULL)
        {
            if(ptr->y == temp->y && ptr->m > temp->m)
                break;
            if(ptr->y == temp->y && ptr->m == temp->m && ptr->d > temp->d)
                break;
            if(ptr->y > temp->y)
                break;
            prev=ptr;
            ptr=ptr->next;
        }
        if(ptr==start)
        {
            temp->next=start;
            start=temp;
        }
        else if(ptr==NULL)
        {
            prev->next=temp;
            temp->next=NULL;
        }
        else
        {
            prev->next=temp;
            temp->next=ptr;
        }
    }
    day* DelQ(int no,int r=0)       //deleting and returning
    {
        int i=1;
        day* ptr=start;
        day* prev;
        while(i<no)
        {
            prev=ptr;
            ptr=ptr->next;
            i++;
        }
        if(r==0)
        {
            if(ptr->rep==true)
            {
                day* temp=new day;
                temp->d=ptr->d;
                temp->m=ptr->m;
                temp->y=(ptr->y)+1;
                temp->rep=true;
                temp->note=ptr->note;
                InQ(temp);
            }
        }
        if(ptr==start)
        {
            start=ptr->next;
        }
        else
        {
            prev->next=ptr->next;
        }
        --TOT;
        --tot;
        return ptr;
    }
    void Disp()
    {
        day* ptr=start;
        int no=1,i=1;
        cout<<"\nNo."<<setw(17)<<"Date"<<setw(23)<<"Event"<<setw(27)<<"Repetitive";
        while(ptr!=NULL)
        {
            if(Check(ptr->d,ptr->m,ptr->y)==false)
            {
                ptr=ptr->next;
                DelQ(i);
                i++;
            }
            else
            {
                i++;
                cout<<endl<<no++<<setw(14)<<ptr->d<<'-'<<setw(2)<<ptr->m+1<<'-'<<setw(4)<<ptr->y<<setw(19)<<ptr->note;
                if(ptr->rep==true)
                    cout<<setw(21)<<"\tYes";
                else
                    cout<<setw(21)<<"\tNo";
                ptr=ptr->next;
            }
        }
    }
    void upcoming()
    {
        day* ptr=start;
        int no=1,i=1;
        cout<<"\nUpcoming Events:\n";
        while(ptr!=NULL)
        {
            if(Check(ptr->d,ptr->m,ptr->y)==false)
            {
                ptr=ptr->next;
                DelQ(i);
                i++;
            }
            else
            {
                i++;
                if(inrange(ptr->d,ptr->m,ptr->y)==0)
                    return;
                cout<<endl<<no++<<setw(20)<<ptr->note<<setw(10)<<ptr->d<<'-'<<setw(2)<<ptr->m+1<<'-'<<setw(4)<<ptr->y;
                ptr=ptr->next;
            }
        }
    }
    void Delete()
    {
        int no;
        Disp();
        cout<<"\nEnter the event no. to be deleted:\t";
        cin>>no;
        if(no>tot || no<=0)
        {
            cout<<"\nEnter a valid no.\n";
            delay(1500);
            return;
        }
        DelQ(no);
        cout<<"\nDeleted.";
        delay(1000);
    }
    void Modify()
    {
        int no;
        Disp();
        cout<<"\nEnter the event no. to be modified:\t";
        cin>>no;
        if(no>tot || no<=0)
        {
            cout<<"\nEnter a valid no.\n";
            delay(1000);
            return;
        }
        int i;
        day* ptr;
        ptr=DelQ(no,1);
        cout<<"\nChange date?\t";
        cin>>i;
        if(i==1)
        {
            cout<<"\nEnter new date:\t";
            cin>>ptr->d>>ptr->m>>ptr->y;
            ptr->m = (ptr->m)-1;
        }
        cout<<"\nChange Event name?\t";
        cin>>i;
        if(i==1)
        {
            cout<<"\nEnter new event name:\t";
            cin>>ptr->note;
        }
        cout<<"\nChange repeatiton mode?\t";
        cin>>i;
        if(i==1)
        {
            cout<<"\nIs that a repeatative event?:\t";
            cin>>ptr->rep;
        }
        cout<<"\nModified";
        delay(1000);
        InQ(ptr);
    }
    void Add()
    {
        int ch;
        cout<<"\nContinue in the current month and year?\t";
        cin>>ch;
        if(ch!=1)
        {
                cout<<"\nEnter day, month, year:\t";
                cin>>d>>m>>y;
                m--;
        }
        else
        {
                cout<<"\nEnter day:\t";
                cin>>d;
                m=::m;
                y=::y;
        }
        if(!Check(d,m,y))
            {
                cout<<"\nThe date entered is either invalid or past.\n";
                delay(1500);
                return;
            }
        day* add=new day;
        add->d=d;
        add->m=m;
        add->y=y;
        cout<<"\nEnter event name:\t";
        cin>>add->note;
        cout<<"\nIs that a repeatative event?\t";
        cin>>add->rep;
        InQ(add);
        cout<<"\nAdded..\n";
        delay(1000);
    }
    void getfromfile()
    {
        if(TOT==0)
            return;
        ifstream file;
        int no=0;
        file.open("Events.txt",ios::in);
        while(no<TOT)
        {
            no++;
            day* temp=new day;
            file>>temp->d>>temp->m>>temp->y>>temp->note>>temp->rep;
            InQ(temp);
        }
        file.close();
    }
    void writetofile()
    {
        ofstream file,det;
        day *ptr= start;
        file.open("Events.txt",ios::out);
        while(ptr!=NULL)
        {
            file<<ptr->d<<"\t"<<ptr->m<<"\t"<<ptr->y<<"\t"<<ptr->note<<"\t"<<ptr->rep<<"\t";
            ptr=ptr->next;
        }
        file.close();
        det.open("Details.txt");
        det<<TOT;
    }
};

class menu
{
    call CALL;
    message MESSAGE;
    memo MEMO;
    game GAMES;
    settings *SETTINGS;
    contacts CONTACTS;
    calender Event;
public:
    menu()
    {
        Event.getfromfile();
        m=tptr->tm_mon,y=tptr->tm_year+1900 ;
    }
    void aggregate(settings &z)
    {
        SETTINGS=&z;
    }
    void aggregate()
    {
        CALL.get_contacts(&CONTACTS);
        MESSAGE.get_contacts(&CONTACTS);
    }
    void access()
    {
        int data,choice;char temp[30];
        do{
            system("CLS");
            time_t tim;
            time(&tim);
            cout<<"\n\n\t\t\t----------MENU----------\n\n";
            cout<<"\n\t\t\t"<<ctime(&tim);
            cout<<"\n\t\t\t1.CONTACTS\n\t\t\t2.CALL\n\t\t\t3.MESSAGE\n\t\t\t4.MEMO\n\t\t\t5.GAMES\n\t\t\t6.SETTINGS\n\t\t\t7.CALENDAR\n\t\t\t8.BACK";
            cout<<"\n\n\t\t\t> ";
            cin>>data;
            switch(data)
            {
            case 1: //CONTACTS
                    do
                    {
                        system("CLS");
                        cout<<"\n\t\t\t------CONTACTS------";
                        cout<<"\n\n\t\t\t1.Search Contact\n\t\t\t2.Add contact\n\t\t\t3.Display contacts\n\t\t\t4.Delete contact\n\t\t\t5.Edit contact\n\t\t\t6.BACK";
                        cout<<"\n\n\t\t\t> ";
                        cin>>choice;
                        switch(choice)
                        {
                        case 1:system("CLS");
                                cout<<"\n\t\t\t******SEARCH CONTACTS******";
                                cout<<"\n\n\t\t\tEnter the name of the contact: ";
                                cin>>temp;
                                CONTACTS.viewContact(temp);
                                break;
                        case 2: system("CLS");
                                cout<<"\n\t\t\t******ADD CONTACT******";
                                CONTACTS.createContact();
                                break;
                        case 3:system("CLS");
                                cout<<"\n\t\t\t******ALL CONTACTS******";
                                CONTACTS.displayContacts();
                                break;
                        case 4:system("CLS");
                                cout<<"\n\t\t\t******DELETE CONTACT******";
                                CONTACTS.deleteContact();
                                break;
                        case 5:system("CLS");
                                cout<<"\n\t\t\t******EDIT CONTACT******";
                                CONTACTS.modifyContact();
                                break;
                        }
                        cout<<"\n\n\t\t\t";
                        system("pause");
                    }while(choice!=6);break;
            case 2: //CALL
                    do
                    {
                        system("CLS");
                        cout<<"\n\t\t\t------CALL------";
                        cout<<"\n\n\t\t\t1.Call\n\t\t\t2.View Call Log\n\t\t\t3.BACK";
                        cout<<"\n\n\t\t\t> ";
                        cin>>choice;
                        if(choice==1)
                        {
                            system("CLS");
                            cout<<"\n\t\t\t******CALL******";
                            CALL.makeCall();
                            cout<<"\n\n\t\t\t";
                            system("pause");
                        }

                        else if(choice==2)
                        {
                            system("CLS");
                            cout<<"\n\t\t\t******CALL LOG******";
                            CALL.display();
                            cout<<"\n\n\t\t\t";
                            system("pause");
                        }
                    }while(choice!=3);break;
            case 3: //MESSAGE
                    do
                    {
                        system("CLS");
                        cout<<"\n\t\t\t------MESSAGES------";
                        cout<<"\n\n\t\t\t1.Send message\n\t\t\t2.Display Messages\n\t\t\t3.BACK";
                        cout<<"\n\n\t\t\t> ";
                        cin>>choice;
                        if(choice==1)
                        {
                            system("CLS");
                            cout<<"\n\t\t\t******SEND MESSAGE******";
                            MESSAGE.Create();
                            cout<<"\n\n\t\t\t";
                            system("pause");
                        }
                        else if(choice==2)
                        {
                            system("CLS");
                            cout<<"\n\t\t\t******ALL MESSAGES******";
                            MESSAGE.display();
                            cout<<"\n\n\t\t\t";
                            system("pause");
                        }
                    }while(choice!=3);break;
            case 4: //MEMO
                    do
                    {
                    system("CLS");
                    cout<<"\n\t\t\t------MEMO------";
                    cout<<"\n\n\t\t\t1.Create memo\n\t\t\t2.View Memo\n\t\t\t3.Delete memo\n\t\t\t4.BACK";
                    cout<<"\n\n\t\t\t> ";
                    cin>>choice;
                    switch(choice)
                    {
                        case 1: system("CLS");
                                cout<<"\n\t\t\t******CREATE MEMO******";
                                MEMO.create();break;
                        case 2: system("CLS");
                                cout<<"\n\t\t\t******MEMOS******";
                                MEMO.view();break;
                        case 3: system("CLS");
                                cout<<"\n\t\t\t******DELETE MEMO******";
                                MEMO.delete_memo();break;
                    }cout<<"\n\n\t\t\t";
                        system("pause");
                    }while(choice!=4);
                    break;
            case 5: //MINESWEEPER
                    GAMES.minesweeper(0);
                    break;
            case 6: system("CLS");
                    cout<<"\n\t\t\t------SETTINGS------";
                    cout<<"\n\n\t\t\t1.Change PIN\n\t\t\t2.BACK";
                    cout<<"\n\n\t\t\t> ";
                    cin>>choice;
                    if(choice==1)
                    {
                    system("CLS");
                    cout<<"\n\t\t\t******CHANE PIN******";
                    SETTINGS->changePIN();
                    cout<<"\n\n\t\t\t";
                    system("pause");
                    }
                    break;
            case 7: int ch=1;
                    while(ch!=0)
                    {
                        system("cls");
                        cout<<"\n\t------CALENDAR------\n\n";
                        printCalendarMonth(m,y);
                        Event.upcoming();
                        cout<<"\n\n(1) Previous Month\t\t(2) Next Month\n(3) Select Year\t\t\t"
                        <<"(4) Select Month\n(5) Add Event\t\t\t(6) Display Events\n"
                        <<"(7) Remove Event\t\t(8) Modify Event\n(9) Plan Using Calendar\t\t(0) Exit\n:";
                        cin>>ch;
                        if(ch>9 || ch<0)
                        {
                            cout<<"\nThis option is availiable only for secret agents. *insert some cool emoji here*\n";
                            system("pause");

                        }
                        else
                        switch(ch)
                        {
                        case 1: prev(m,y);
                            break;
                        case 2: next(m,y);
                            break;
                        case 3: cout<<"\nEnter Year Index:\t";
                            cin>>y;
                            break;
                        case 4: cout<<"\nEnter Month Index:\t";
                            cin>>m;
                            m-=1;
                            break;
                        case 5: Event.Add();
                            break;
                        case 6: Event.Disp();
                            cout<<endl;
                            system("pause");
                            break;
                        case 7: Event.Delete();
                            break;
                        case 8: Event.Modify();
                            break;
                        case 9: printCalendar(y);
                            break;
                        case 0: Event.writetofile();
                        }
                        }break;
                    }
        }while(data!=8);
    }
};

class homescreen
{
    menu MENU;
public:
    void Aggregate(settings &y)
    {
        MENU.aggregate(y);
    }
    void display()
    {
        int data;
        MENU.aggregate();       //to aggregate the contacts to call and message
        do
        {
            system("CLS");
            cout<<"\n\t\t\t-------HOMESCREEN-------";
            time_t tim;
            time(&tim);
            cout<<"\n\n\t\t\t"<<ctime(&tim);
            cout<<"\n\n\t\t\t1.MENU   2.LOCK";
            cout<<"\n\n\t\t\t> ";
            do{cin>>data;}while(data<1 || data>2);
            if(data==1)
                MENU.access();
            else if(data==2)
                return;
        }while(1);
    }
};

class phone
{
    bool lock;int attempts;
    homescreen HS;
    char *PIN;
public:
    phone()
    {
        lock=1;attempts=0;
    }
    void pin_associate(char *x)
    {
        PIN=x;
    }
    void aggregate(settings &x)
    {
        HS.Aggregate(x);
    }
    void unlock()
    {
        attempts++;
        char input[6];
        cout<<"\n\t\t\tEnter PIN:";
        cin>>input;
        if(strcmp(input,PIN)==0)
            lock=0;
    }
    int display()
    {
        int data;
        system("CLS");
        cout<<"\n\t\t\t-------LOCKSCREEN-------";
        time_t tim;
        time(&tim);
        cout<<"\n\n\t\t\t"<<ctime(&tim);
        cout<<"\n\t\t\t1.UNLOCK  2.TURN OFF ";
        cout<<"\n\n\t\t\t> ";
        cin>>data;
        if(data==2)return 2;
        attempts=0;
        while(lock==1)
        {
            if(attempts>=1)
            {
                cout<<"\n\t\t\tWrong PIN!";
                cout<<"\n\t\t\tTRY AGAIN :)\n";
            }
            unlock();
        }
        HS.display();
        lock=1;
        return 1;
    }
};

int main()
{
    char input;int data;
    phone p;
    settings SET;
    p.pin_associate(SET.get_pin());
    p.aggregate(SET);
    system("CLS");
    cout<<"\n\n\t\t\t ********MOBILE-PACKAGE******** \t\t\t";
    cout<<"\n\n\n\t\t\tTURN ON? (Y / N)";
    cout<<"\n\n\t\t\t> ";
    cin>>input;
    if(input=='y'||input=='Y')
        do{     data=p.display();}while(data!=2);
}
