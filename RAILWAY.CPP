/*
	************  THIS IS A RAILWAY RESERVATION SYSTEM   ***********

FILE's USED :  TRAIN.TXT ( for storing the info about trains )
	       SIGNUP.TXT ( for storing the created accounts info )
	       SEATS.TXT ( for storing the info available seats in a train )
	       BOOKED.TXT ( for storing the info about booked ticket history )
	       PNR.TXT ( for storing the pnr numbers for unique train no creation )
	       ALLOT.TXT ( for storing the info about seat number allocated to the current user)
	       CODE.TXT( for storing the codes of station )

**** THIS IS A PROJECT ON RAILWAY RESERVATION SYSTEM ******

** BASIC FUNCTIONS PROVIDED BY SYSTEM :-
->sign up : for creating a new account.

->login for your account : for logging in and get the login user functionality
			 as book ticket,cancel ticket,check ticket history
			 and log-out option.

->check seats availabilty : This option is for checking the current seats
			    available in the particular train.

->check trains available : This option lets the user to check for the overall
			   info about the trains available in database currently.

->admin mode : This option lets you do the work of aadmin of manipulating the saved details.

*/

#include<iostream.h>
#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<constrea.h>

int pnr;       //global pnr varible for storing current pnr number

/* This structure saves all the info about the trains */
struct train
{
	char name[20];
	int id;
	char origin[20];
	char dest[20];
	float fare;
	char dep[20];
	int seats;
}s;

/* This structure saves the allotment status of seats of current trains
   to the current user */

struct allot
{
	int id;
	int p[100];
}h;

/* This structure keeps the station code */
struct code
{
	char sta[20];
	char code[20];
}e;

/*This structure saves all the info related to book status of current ticket
	*/

struct booked
{
	int id;
	char origin[20];
	char dest[20];
	int pnr;
	char dep[20];
	char name[20];
	int seat;
	char date[20];
}b;

/* This structure saves the info about the available seats */

struct seat
{
	int id;
	int seats;
	float fare;
}p;

/* This class stores the info about newly created account info */

class sign_up
{
public:	char name[20];
	char mob_no[20];
	char id[20];
	char pass[20];

	void get();
};

void sign_up :: get()
{
	cout.fill('*');cout.width(80);cout<<" \n";
	cout.fill(' ');
	cout<<"\t\t    WELCOME TO SIGN_UP SECTION    \t    "<<"\n";
	cout.fill('*');cout.width(80);cout<<" \n\n";cout.fill(' ');
	cout<<"\t********* ENTER THE INFO BELOW ***********\n";
	cout<<"\n\n\n\n\n";
	cout<<"\t\t   Enter the name : ";
	gets(name);
	cout<<"\n\t\t   Enter the mobile number : ";
	gets(mob_no);
	cout<<"\n\t\t   Enter the id : ";
	gets(id);
	cout<<"\n\t\t   Enter the password : ";
	int i = 0;
	char ch;
	while(1)
	{
		ch = getch();
		if(ch == '\r')
			break;
		if(ch == 8)
		{
			printf("\b \b");
			i--;
		}
		else
		{
		printf("*");
		pass[i] = ch;
		i++;
		}
	}
	pass[i] = '\0';
	cout<<"\n\n\t     YOUR ACCOUNT CREATED SUCCESSFULL\n";
	cout<<"\n\t    Press any key to return back ";
	getch();
}

/* This fuction fills up the sign_up by asking the required info from the
   user at the time of sign_up */

void fill_sign_up()
{
	fstream file;
	file.open("signup.txt",ios::out|ios::app|ios::binary);
	clrscr();

	sign_up s;
	s.get();
	file.write((char *)&s,sizeof(sign_up));
	file.close();
	clrscr();
}

/* This function displays all info related to the trains available in
 databse */

void train_a()
{
	clrscr();
	char c = 179,d=196;
	cout.fill('-');cout.width(80);cout<<" \n";
	cout.fill(' ');
	cout<<"|\t\t  ************* TRAIN CHART *************\t\t    |"<<"\n";
	cout.fill('-');cout.width(80);cout<<" \n";
	cout.fill(' ');
	cout<<"\n";
	cout.fill(d);cout.width(80);cout<<" \n";
	cout.fill(' ');
	cout.setf(ios::left,ios::adjustfield);

	cout<<c;cout.width(20);cout<<" TRAIN NAME";cout.width(10);cout<<"TRAIN-ID";cout.width(15);
	cout<<"DEPATURE";cout.width(15);cout<<"DESTINATION";
	cout.width(6);cout<<"FARE";cout.width(12);cout<<"TOTAL-SEATS "<<c<<"\n";

	fstream file("train.txt",ios::in);

	while(file.read((char *)&s,sizeof(struct train)))
	{
	strupr(s.name);strupr(s.origin);strupr(s.dest);
	cout<<c<<" ";cout.width(18);cout<<s.name;cout.width(10);cout<<s.id;cout.width(15);
	cout<<s.origin;cout.width(15);cout<<s.dest;
	cout.width(6);cout<<s.fare;cout.width(12);cout<<s.seats<<" "<<c;
	}
	file.close();
	cout.unsetf(ios::left);
	cout.fill(d);cout.width(80);cout<<" \n";
	cout.fill(' ');
	cout<<"\npress any key to return back ";
	getch();
	cout.fill(' ');
	cout<<setclr(15);
	clrscr();
}

/* This function takes care of booking option.It asks the user for depature
   station and destination station and checks for available trains for this entry
   and if entries are present books ticket for it else displays no trains
   available
*/

void book(char a[])
{
	clrscr();
	cout<<"\t**** NOTE: THE TICKET BOOKED IS NON-REFUNDABLE *****\n\n";
	int t_id[50],i=0;

	for(i=0;i<50;i++)
		t_id[i] = 0;
	i =0;
	char sou[20],de[20],date[20];
	int w = 0,id,seats,g = 1,l=1;

	ifstream f("code.txt",ios::binary);
	cout<<"CODE :- \n";
	char ch = 196;
	cout.fill(ch);cout.width(80);cout<<" \n\n";cout.fill('-');
	while(f.read((char*)&e,sizeof(struct code)))
	{
		strupr(e.sta);strupr(e.code);
		cout<<e.sta<<" - "<<e.code;
		if(g == (3*l))
		{
			cout<<"\n";
			l++;
		}
		else
			cout<<"               ";
		g++;
	}
	cout<<"\n";
	cout.fill(ch);cout.width(80);cout<<" \n";cout.fill(' ');
	f.close();
	f.open("code.txt",ios::binary);

	cout<<"\n\nPLEASE ENTER THE CODE AS ABOVE ONLY";
	cout<<"\n\nENTER THE DEPATURE STATION : ";
	gets(sou);
	cout<<"\nENTER THE DESTINATION STATION : ";
	gets(de);

	while(f.read((char *)&e,sizeof(struct code)))
	{
		if(!strcmpi(e.code,sou))
			strcpy(sou,e.sta);
		if(!strcmpi(e.code,de))
			strcpy(de,e.sta);
	}
	f.close();

	fstream in("train.txt",ios::in|ios::binary);
	cout<<"\n\n\t****** FOLLWING TRAINS ARE AVAILABLE FOR YOUR ENTRY : ********\n\n";
	cout.setf(ios::left,ios::adjustfield);
	cout.width(20);
	cout<<"TRAIN NAME";cout.width(10);cout<<"TRAIN-ID";cout.width(15);
	cout<<"DEPATURE";cout.width(15);cout<<"DESTINATION";
	cout.width(6);cout<<"FARE";cout.width(13);cout<<"DEPATURE-TIME\n\n";


	while(in.read((char *)&s,sizeof(struct train)))
	{

		if(!strcmpi(s.origin,sou) && !strcmpi(s.dest,de))
		{
		cout.width(20);
		strupr(s.name);strupr(s.origin);strupr(s.dest);
		cout<<s.name;cout.width(10);cout<<s.id;cout.width(15);
		cout<<s.origin;cout.width(15);cout<<s.dest;
		cout.width(6);cout<<s.fare;cout.width(14);cout<<s.dep;
		w =1;
		t_id[i] = s.id;
		i++;
		}
	}
	if(w==0)
	{
		cout<<"\n\nNO TRAINS AVAILABLE FOR THIS ENTRY\n\n";
		cout<<"Press any key to return back ";
		cout.unsetf(ios::left);
		getch();
		clrscr();
		return ;
	}

	in.close();
	in.open("seats.txt",ios::binary|ios::in);

	cout<<"\n\nENTER THE TRAIN ID TO BOOK TICKET : ";
	cin>>id;

	cout<<"\nENTER THE NUMBER OF TICKETS TO BOOK : ";
	cin>>seats;
	w = 0;
	unsigned int pay;
	int k=0;

	for(i=0;i<50;i++)
	{
		if(t_id[i] == id)
		{
			k =1;
			break;
		}
	}

	if(k==0)
	{
		cout<<"\nWRONG TRAIN ID ENTERED ";
		cout<<"\nPRESS ANY KEY TO RETURN BACK";
		cout.unsetf(ios::left);
		getch();
		clrscr();
		return ;
	}


	while(in.read((char*)&p,sizeof(struct seat)))
	{

		if(p.id == id && ((p.seats-seats)>=0))
		{
			cout<<"\nSEATS ARE AVAILABE IN TRAIN ";
			cout<<"\n\nENTER THE DATE OF TRAVEL : ";
			gets(date);
			cout<<"\n\nPRESS ANY KEY TO PROCEED FOR PAYMENT ";
			getch();
			clrscr();
			cout<<"AMOUNT TO BE PAID : "<<p.fare*seats<<"\n\n";
			cout<<"ENTER THE AMOUNT TO PAY : ";
			cin>>pay;
			if(pay>=(p.fare*seats))
			{
				cout<<"\nPAYMENT MADE SUCCESSFULLY";
				cout<<"\n\nCHECK THE BOOK TICKET INFO SECTION FOR TICKET INFORMATION";
				cout<<"\n\nPRESS ANY KEY TO RETURN BACK ";
				fstream t("train.txt",ios::binary|ios::in);
				fstream bo("booked.txt",ios::binary|ios::out|ios::app);
				while(t.read((char*)&s,sizeof(struct train)))
				{
					if(p.id == s.id)
					{
						b.id = p.id;
						strcpy(b.origin, s.origin);
						strcpy(b.dest,s.dest);
						fstream file("pnr.txt",ios::in);
						file>>pnr;
						pnr++;
						b.pnr = pnr;
						file.close();
						file.open("pnr.txt",ios::out|ios::trunc);
						file<<pnr;
						file.close();
						strcpy(b.dep,s.dep);
						b.seat = seats;
						strcpy(b.name,a);
						strcpy(b.date,date);
						bo.write((char*)&b,sizeof(struct booked));
					}
				}
				t.close();
				bo.close();
				getch();
			}
			else
			{
				cout<<"\n\nLESS AMOUNT ENTERED ";
				cout<<"\n\nRE-ENTER AMOUNT TO PAY : ";
				cin>>pay;
				if(pay<(p.fare*seats))
				{
					cout<<"\nYOU LOSE CHANCE TO PAY ";
					cout<<"PRESS ANY KEY TO RETURN BACK ";
					getch();
				}
				else
				{
				cout<<"\nPAYMENT MADE SUCCESSFULLY";
				cout<<"\n\nCHECK THE BOOK TICKET INFO SECTION FOR TICKET INFORMATION";
				cout<<"\n\nPRESS ANY KEY TO RETURN BACK ";
				fstream t("train.txt",ios::binary|ios::in);
				fstream bo("booked.txt",ios::binary|ios::out|ios::app);
				while(t.read((char*)&s,sizeof(struct train)))
				{
					if(p.id == s.id)
					{
						b.id = p.id;
						strcpy(b.origin, s.origin);
						strcpy(b.dest,s.dest);
						fstream file("pnr.txt",ios::in);
						file>>pnr;
						pnr++;
						b.pnr = pnr;
						file.close();
						file.open("pnr.txt",ios::out|ios::trunc);
						file<<pnr;
						file.close();
						strcpy(b.dep,s.dep);
						strcpy(b.name,a);
						bo.write((char*)&b,sizeof(struct booked));
					}
				}
				t.close();
				bo.close();
				getch();
				}
			}
			w = 1;
		}
	}
	in.close();
	fstream file("seats.txt",ios::in);
	fstream wc("seats1.txt",ios::out);

	if(w == 0)
	{
		cout<<"\nSORRY SEATS ARE NOT AVAILABLE IN TRAIN\n\n ";
		cout<<"\nPRESS ANY KEY TO RETURN BACK";
		cout.unsetf(ios::left);
		getch();
	}
	else
	{
		while(file.read((char*)&p,sizeof(struct seat)))
		{
			if(id != p.id)
			{
				wc.write((char*)&p,sizeof(struct seat));
			}
			else
			{
				p.seats = p.seats - seats;
				wc.write((char*)&p,sizeof(struct seat));
			}
		}
		file.close();
		wc.close();
		remove("seats.txt");
		rename("seats1.txt","seats.txt");

		file.open("allot.txt",ios::in|ios::binary);
		wc.open("allot1.txt",ios::binary|ios::out|ios::trunc);
		in.open("train.txt",ios::in|ios::binary);
		int z = 0;

		while(file.read((char*)&h,sizeof(struct allot)))
		{
			in.read((char *)&s,sizeof(struct train));
			if(id == h.id)
			{
			for(int i=0;i<s.seats;i++)
			{
				if(h.p[i] == 0)
				{
					h.p[i] = pnr;
					z++;
				}
				if(z == seats)
				{
					z=0;
					break;
				}
			}
			}
			wc.write((char*)&h,sizeof(struct allot));
		}
		file.close();
		in.close();
		wc.close();
		remove("allot.txt");
		rename("allot1.txt","allot.txt");
	}
	cout.unsetf(ios::left);
	clrscr();
}

/* This function displays the book ticket history of current user by
   searching for the ticket's booked on current user name in the database
*/
void history(char c[])
{
	clrscr();
	int w=0;
	cout<<"\t\t******** BOOKED TICKET HISTORY **********\n\n";
	cout.setf(ios::left,ios::adjustfield);
	cout.width(5);cout<<"PNR";cout.width(15);cout<<"ORIGIN";cout.width(15);
	cout<<"DESTINATION";cout.width(12);cout<<"TRAIN-ID";cout.width(15);
	cout<<"DEPATURE-TIME";cout.width(13);cout<<"DATE";
	cout<<"\n\n";

	fstream file("booked.txt",ios::binary|ios::in);
	fstream in;
	fstream in1;

	while(file.read((char*)&b,sizeof(struct booked)))
	{

		if(!strcmpi(b.name,c))
		{
		cout.width(5);cout<<b.pnr;cout.width(15);cout<<b.origin;cout.width(15);
		cout<<b.dest;cout.width(12);cout<<b.id;cout.width(15);
		cout<<b.dep;cout.width(13);cout<<b.date;
		cout<<"\n";
		in.open("allot.txt",ios::binary|ios::in);
		in1.open("train.txt",ios::binary|ios::in);
		while(in.read((char*)&h,sizeof(struct allot)))
		{
			in1.read((char*)&s,sizeof(struct train));

			if(b.id == h.id)
			{
				cout<<"SEAT ALLOCATED : ";
				for(int i=0;i<s.seats;i++)
				{
					if(b.pnr == h.p[i])
					cout<<i+1<<" ";
				}
			}
		}
		cout<<"\n\n";
		in.close();
		in1.close();
		w =1;
		}
	}

	if(w == 0)
	cout<<"\n\n NO BOOK HISTORY YET \n\n";

	cout<<"\n\nPRESS ANY KEY TO RETURN BACK ";
		getch();
		file.close();
		cout.unsetf(ios::left);
		clrscr();
}
/* This function deals with cancellation of the ticket
   First it asks the user for pnr number and search for the pnr number
   in the database , if it is present then the ticket is cancelled succesfully
   and no refund is provided else it displays the required message
*/
void cancel(char d[])
{
	clrscr();
	int pn,w =0 ;
	fstream file("booked.txt",ios::in|ios::binary);
	fstream t("booked1.txt",ios::out|ios::binary);
	fstream in("seats.txt",ios::in|ios::binary);
	fstream out("seats1.txt",ios::out|ios::binary);

	cout<<"\t\t******** WELCOME TO CANCELLATION SECTION ***********\n\n";
	cout<<"ENTER THE PNR NUMBER TO CANCEL THAT TICKET : ";
	cin>>pn;

	while(file.read((char*)&b,sizeof(struct booked)))
	{
		if(b.pnr == pn && !strcmp(d,b.name))
		{
			cout<<"YOUR TICKET SUCCESFULLY CANCELED \n\n";
			w = 1;
			while(in.read((char*)&p,sizeof(struct seat)))
			{
				if(b.id == p.id)
				{
					p.seats = p.seats + b.seat;
					out.write((char*)&p,sizeof(struct seat));
				}
				else
				{
				 out.write((char*)&p,sizeof(struct seat));
				}
			}
			ifstream in("allot.txt",ios::binary);
			ofstream out("allot1.txt",ios::binary);
			ifstream in1("train.txt",ios::binary);

			while(in.read((char*)&h,sizeof(struct allot)))
			{
				in1.read((char *)&s,sizeof(struct train));
				for(int i=0;i<s.seats;i++)
				{
					if(h.p[i] == b.pnr)
						h.p[i] = 0;
				}
				out.write((char*)&h,sizeof(struct allot));
			}
			in.close();out.close();in1.close();
			remove("allot.txt");rename("allot1.txt","allot.txt");
		}
		else
		{
			t.write((char*)&b,sizeof(struct booked));
		}
	}
	file.close();
	t.close();
	in.close();
	out.close();

	if(w == 0)
	{
		cout<<"\nNO TICKETS AVAILABLE TO CANCEL\n\n";
	}
	else
	{
	remove("seats.txt");
	rename("seats1.txt","seats.txt");
	}

	remove("booked.txt");
	rename("booked1.txt","booked.txt");
	cout<<"PRESS ANY KEY TO RETURN BACK :";
	getch();
	cout.unsetf(ios::left);
	cout.fill(' ');
	clrscr();
}

/* This function let's the user to login in it's account
   it searches for the login id and password and if it is available
   in databse then provides the further fucntionality to user else
   displays the required error message
*/
void fill_login()
{
	char log[20];
	char pas[20];
	int ch,w = 1;
	clrscr();
	cout.fill('*');cout.width(80);cout<<" \n";
	cout.fill(' ');
	cout<<"\t\t     WELCOME TO LOGIN SECTION\t\t    "<<"\n";
	cout.fill('*');cout.width(80);cout<<" \n\n\n\n\n\n\n\n\n";
	cout<<"\t\t   Enter the LOGIN-ID : ";
	gets(log);
	cout<<"\n\n\t\t   Enter the PASSWORD : ";
	int i = 0;
	char ch1;
	while(1)
	{
		ch1 = getch();
		if(ch1 == '\r')
			break;
		if(ch1 == 8)
		{
			printf("\b \b");
			i--;
		}
		else
		{
		printf("*");
		pas[i] = ch1;
		i++;
		}
	}
	pas[i] = '\0';
	cout.fill(' ');

	fstream file("signup.txt",ios::in |ios::binary);
	sign_up s;
	clrscr();
	char c = 22;

	while(file.read((char *)&s,sizeof(sign_up)))
	{
	       if(!strcmpi(s.id,log) && !strcmpi(s.pass,pas))
		{
		       while(ch != 4)
			{
			cout.fill(c);cout.width(80);cout<<" \n";cout.fill(' ');
		       cout<<"\t\t   ******* WELCOME BACK "<<log<<" *********\n";
			cout.fill(c);cout.width(80);cout<<" \n\n";cout.fill(' ');
			cout.width(15);cout<<" ";
			cout.fill(c);cout.width(45);cout<<" \n";cout.fill(' ');
			cout.width(15);cout<<" ";
			cout<<"\t**** WHAT DO YOU WANT TO DO ? ******\t\n";
			cout.width(15);cout<<" ";
			cout.fill(c);cout.width(45);cout<<" \n\n";cout.fill(' ');
			cout<<"\n\n";
			cout<<"\t\t1.BOOK TICKET\n\t\t2.CANCEL TICKET\n\t\t3.BOOK TICKET HISTORY\n\t\t4.LOG OUT\n\n";
			cout<<"\n\t\tEnter your choice : ";
			cin>>ch;
			w = 0;
				switch(ch)
				{
				case 1 : book(s.id);
					break;
				case 2 : cancel(s.id);
					break;
				case 3 : history(s.id);
					break;
				case 4 : break;
				}
			}
		}

	}
	if(w == 1)
		{
			cout<<"\n\n\n\n\n\t\t  Sorry Your account is not present";
			cout<<"\n\n\n\n\t\t   Press any key to return back ";
			getch();
		}
		clrscr();
		cout.unsetf(ios::left);
		file.close();
}
/* This function displays the amount of seats available in current train */
void seat()
{
	clrscr();
	ifstream in("seats.txt",ios::binary);
	ifstream in1("train.txt",ios::binary);
	char c = 179,d=196;
	cout.fill('-');cout.width(80);cout<<" \n";
	cout.fill(' ');
	cout<<"\t   ********* WELCOME TO SEAT AVAILABILITY SECTION *********\n";
	cout.fill('-');cout.width(80);cout<<" \n";
	cout.fill(' ');
	cout<<"\n";
	cout.fill(d);cout.width(69);cout<<" \n";
	cout.fill(' ');
	cout.setf(ios::left,ios::adjustfield);
	cout<<c;cout.width(20);cout<<" TRAIN-ID";cout.width(20);cout<<"SEATS-AVAILABLE";
	cout.width(15);cout<<"TOTAL-SEATS";
	cout.width(10);cout<<"FARE      "<<c<<"\n\n";

	while(in.read((char*)&p,sizeof(struct seat)))
	{
		in1.read((char *)&s,sizeof(struct train));
		//cout.setf(ios::left,ios::adjustfield);
		cout<<c<<" ";
		cout.width(20);cout<<p.id;cout.width(20);cout<<p.seats;
		cout.width(15);cout<<s.seats;
		cout.width(9);cout<<p.fare<<c<<"\n";
	}
	in.close();in1.close();
	cout.unsetf(ios::left);
	   cout.fill(d);cout.width(69);cout<<" \n";
	cout.fill(' ');
	cout<<"\n\nPRESS ANY KEY TO RETURN BACK ";
	getch();
	clrscr();
}

void add_train()
{
	clrscr();
	fstream file("train.txt",ios::binary|ios::app|ios::out);
	fstream file1("code.txt",ios::binary|ios::app|ios::out);

	cout.fill('*');cout.width(80);cout<<" \n";cout.fill(' ');
	cout<<"\t\t  -------- WELCOME TO ADD TRAIN SECTION "<<" --------\n";
	cout.fill('*');cout.width(80);cout<<" \n\n";cout.fill(' ');
	cout.width(15);cout<<" ";
	cout.fill('*');cout.width(45);cout<<" \n";cout.fill(' ');
	cout.width(15);cout<<" ";
	cout<<"\t------ ENTER THE TRAIN INFO BELOW ---------\t\n";
	cout.width(15);cout<<" ";
	cout.fill('*');cout.width(45);cout<<" \n\n";cout.fill(' ');
	cout<<"\n\n";
	cout<<"\t\tENTER THE TRAIN NAME : ";
	gets(s.name);
	cout<<"\t\tENTER THE TRAIN ID : ";
	cin>>s.id;
	cout<<"\t\tENTER THE TRAIN DEPATURE STATION : ";
	gets(s.origin);strcpy(e.sta,s.origin);
	cout<<"\t\tENTER THE STATION CODE : ";
	gets(e.code);
	file1.write((char*)&e,sizeof(struct code));
	cout<<"\t\tENTER THE DESTINATION STATION : ";
	gets(s.dest);strcpy(e.sta,s.dest);
	cout<<"\t\tENTER THE STATION CODE : ";
	gets(e.code);
	file1.write((char*)&e,sizeof(struct code));
	cout<<"\t\tENTER THE FARE : ";
	cin>>s.fare;
	cout<<"\t\tENTER THE TIME OF DEPATURE : ";
	gets(s.dep);
	cout<<"\t\tENTER THE NUMBER OF SEATS : ";
	cin>>s.seats;
	file.write((char *)&s,sizeof(struct train));
	cout<<"\n\n\t\tTRAIN INFO ADDED SUCCESSFULLY\n\n";
	cout<<"press any key to return back";
	getch();
	h.id = s.id;
	for(int i=0;i<s.seats;i++)
		h.p[i] = 0;
	file.close();
	file1.close();
	file.open("allot.txt",ios::binary|ios::app|ios::out);
	file.write((char*)&h,sizeof(struct allot));
	file.close();
	file.open("seats.txt",ios::binary|ios::app|ios::out);
	p.id = s.id;
	p.seats = s.seats;
	p.fare = s.fare;
	file.write((char*)&p,sizeof(struct seat));
	file.close();
	clrscr();
}

void clear()
{
	clrscr();
	cout.fill('*');cout.width(80);cout<<" \n";cout.fill(' ');
	cout<<"\t\t  -------- WELCOME TO CLEAR_DATABSE SECTION "<<" --------\n";
	cout.fill('*');cout.width(80);cout<<" \n\n";cout.fill(' ');
	cout<<"\n\n\n\n\n";
	cout.width(15);cout<<" ";
	cout<<"DO YOU TO RESET THE COMPLETE DATABASE (y/n) : ";
	char ch;
	cin>>ch;

	if(ch == 'y' || ch=='Y')
	{
		ofstream f1("signup.txt",ios::trunc);f1.close();f1.open("booked.txt",ios::trunc);
		f1.close();f1.open("pnr.txt",ios::trunc);f1.close();
		fstream f2("train.txt",ios::in|ios::binary);
		f1.open("allot.txt",ios::trunc);
		ofstream f3("seats.txt",ios::trunc);

		while(f2.read((char*)&s,sizeof(struct train)))
		{
			h.id = s.id;
			p.id = s.id;
			p.seats = s.seats;
			p.fare = s.fare;
			for(int i=0;i<s.seats;i++)
				h.p[i] = 0;
			f1.write((char*)&h,sizeof(struct allot));
			f3.write((char*)&p,sizeof(struct seat));
		}

		f1.close();
		f2.close();
		f3.close();int j=1;
		f1.open("pnr.txt");f1<<j;f1.close();
		cout<<"\n\tDATABSE CLEARED SUCCESSFULY\n\n";
	}

	cout<<"\tpress any key to return back ";
	getch();
	clrscr();
}

void admin()
{
	clrscr();
	char c = 22;
	int choice;
	char a_pass[20] = "ASMIT004";
	char take[20];
	cout<<"\n\n\n\n\n\n\n\n\n\n\n";cout.width(20);cout<<" ";cout.fill(' ');
	cout<<"ENTER THE ADMIN PASSWORD : ";
	int i = 0;
	char ch1;
	while(1)
	{
		ch1 = getch();
		if(ch1 == '\r')
			break;
		if(ch1 == 8)
		{
			printf("\b \b");
			i--;
		}
		else
		{
		printf("*");
		take[i] = ch1;
		i++;
		}
	}
	take[i] = '\0';

	if(!strcmpi(a_pass,take))
	{
	while(choice != 3)
	{
	clrscr();
	cout.fill(c);cout.width(80);cout<<" \n";cout.fill(' ');
	cout<<"\t\t ******* WELCOME TO ADMIN SECTION "<<" *********\n";
	cout.fill(c);cout.width(80);cout<<" \n\n";cout.fill(' ');
	cout.width(15);cout<<" ";
	cout.fill(c);cout.width(45);cout<<" \n";cout.fill(' ');
	cout.width(15);cout<<" ";
	cout<<"\t**** WHAT DO YOU WANT TO DO ? ******\t\n";
	cout.width(15);cout<<" ";
	cout.fill(c);cout.width(45);cout<<" \n\n";cout.fill(' ');
	cout<<"\n\n";
	cout<<"\t\t1.ADD_TRAIN\n\t\t2.CLEAR_A_DATABSE_COMPLETELY\n\t\t3.LOG OUT\n\n";
	cout<<"\n\t\tEnter your choice : ";
	cin>>choice;

		switch(choice)
		{
			case 1 : add_train();
				break;
			case 2 : clear();
				break;
			case 3 : break;
			default : cout<<"\n\nWRONG CHOICE ENTERED ";
				 getch();
		}
	}
	}
	else
	{
		cout<<"\n\nWRONG PASSWORD ENTERED ";
		cout<<"\n\nPRESS ANY KEY TO RETURN BACK ";
		getch();
	}
	clrscr();
}

int main()
{
	int ch = 1;
	clrscr();
	constream cout;

	while(ch != 5)
	{
	cout<<setclr(15);
	cout<<"/**** PROJECT DEVELOPED AND DESIGNED BY ASMIT BAJAJ(0187CS181037) ****/\n";
	cout<<"** GUIDED BY RAHUL JAIN SIR ****\n";
	cout<<setclr(5);
	cout.fill(22);cout.width(80);cout<<" ";
	cout<<"          ***** SAGAR INSTITUTE OF SCIENCE AND TECHNOLOGY *****\n";
	cout.fill(22);cout.width(80);cout<<" ";
	cout<<setclr(10);
	cout.fill(22);
	cout.width(80);cout<<" ";cout<<"|       *********** WELCOME TO RAILWAY RESERVATION SYSTEM ************       |\n";
	cout.fill(22);cout.width(80);cout<<" ";cout<<setclr(9);
	cout.width(40);cout.fill(22);cout<<" ";cout<<"\n";
	cout.fill(' ');
	cout<<"|   *** WHAT DO YOU WANT TO DO? ***   |\n";

	cout.fill(22);cout.width(40);cout<<" ";cout<<"\n\n";
	cout<<setclr(15);
	cout.fill('-');cout.width(20);cout<<" ";
	cout.fill(' ');cout.width(20);cout<<" ";cout.fill('-');cout.width(20);cout<<" \n";
	cout.width(20);cout<<"|  1. SIGN_UP       |";
	cout.fill(' ');cout.width(20);cout<<" ";cout.width(20);cout<<"|   2. LOGIN       |";cout<<"\n";
	cout.fill('-');cout.width(20);cout<<" ";
	cout.fill(' ');cout.width(20);cout<<" ";cout.fill('-');cout.width(20);cout<<" ";cout<<"\n\n";
	cout.fill('-');cout.width(33);cout<<" ";
	cout.fill(' ');cout.width(10);cout<<" ";cout.fill('-');cout.width(35);cout<<" \n";
	cout.width(20);cout<<"| 3. CHECK SEAT AVAILABILITY   |";
	cout.fill(' ');cout.width(11);cout<<" ";cout.width(32);cout<<"|  4. CHECK TRAINS AVAILABLE   |";cout<<"\n";
	cout.fill('-');cout.width(33);cout<<" ";cout.fill(' ');cout.width(11);cout<<" ";
	cout.fill('-');cout.width(34);cout<<" \n\n";
	cout.fill('-');cout.width(20);cout<<" ";cout<<"\n";
	cout.fill(' ');
	cout.width(20);cout<<"|    5. EXIT      |\n";
	cout.fill('-');cout.width(20);cout<<" ";cout<<" \n";
	cout.fill(' ');cout.width(45);cout<<setclr(12);
	cout<<"ENTER YOUR CHOICE : ";
	cin>>ch;
	cout<<setclr(15);
		/*This is the basic menu of program */

		switch(ch)
		{
		       case 1 : fill_sign_up();
				break;
		       case 2 : fill_login();
				break;
		       case 3 : seat();
				break;

			case 4 : train_a();
				 break;

			case 5 :break;
			case 1999 :  admin();
				break;
			default : cout<<"\nWrong choice entered";
				  getch();
				  clrscr();
		}
	}
	 return 0;
}



