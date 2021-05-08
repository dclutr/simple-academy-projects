#include<iostream.h>
#include<stdio.h>
#include<string.h>
#include<fstream.h>
int flag=1;
class patient
{
                int age,id;
                char name[100],mobile[10],fname[100],mname[100],address[100],insurancecompname[100];
           		void get();//input user data
				void disp();//display data
				void wtf();//write to file
				void rff();//read from file
				void search();//search a record
				void del();//delete a file
				void mod();//modify details of record
				void insert();//insert a record   
                public:
                int bill;
				void hey();//access funtion
}s,s1;
class staff//DOCTOR or PARAMEDICAL STAFF or OTHER
{
	char prof,fname[100],lname[100],email[100],phno[15],Dqual[40],Dqualins[60],Dqualoc[20],Dspec[20],Dpc[80],Odes[30],Ocom[40],Ocombr[20],Pdep[50];
	int id1,age,nov,com,Dinout,Dtnr,Drmn,l,fees;
	/*    SUMMARY OF VARIABLES
	id=idno flag and l{last} used for validations
	fname:-First Name ; lname:-Last Name ;email:-email;age:-age;phno:-phno
	prof=D for Doctor , P for Paramedical ,O for Other used for displaying purposes
	'D' indicates Doctor Only Details;
	    
	    Dqual:-Qualification ; Dqualins:-Institution from ; Dqualoc:-Place/Branch from
		Dspec:-Speciality ; Dpc:-Parallel Clinic ; Dinout '1'=In hospital '0'=Not in
		Dtnr:-Tenure(yrs) ; Drmn:-Room No: 

	'P' indicates Paramedical Staff Only Details;

		Pdep:-Operation Department ;

	'O' indicates Other Staff(Electrician,SecurityGuard)

        Odes:-Designation ;
		Ocom:-Company Contracted ;
		Ocombr:-Which Branch in case of multiple branches ;

	if any detail is not applicable the answer will be 'n'
	|---------END OF SUMMARY-------------Phew!-----:)---------------------------------------|
	*/
	void get();//get details
	void disp();//show details
	void wtf();//write detail to file
	void rff();//read detail from file
	void search();//search particular entry from file
	void del();//delete staff member
	void mod();//modify staff member
	void insert();//insert staff member
	public:
	int ids();//staffs id function
	void hello();//access funtion
}stf;//object name is stf
int staff::ids()
{
	int i,bill1=0,a;
  	cout<<"The Doctors List is-"<<endl;
	ifstream ifile;
	fstream f;
	ifile.open("staffmembers");
	ifile.seekg(0,ios::beg);
	ifile.read((char*)&stf,sizeof(stf));
	while(ifile)
	{
		if(prof=='D')
		{        
				cout<<"NAME: "<<fname<<" "<<lname<<"\n";
                cout<<"ID: "<<id1<<"\n";
				cout<<"FEES: "<<fees<<endl;
				cout<<"SPECIALITY:   "<<Dspec<<endl;
			    cout<<"______________________________"<<endl;
		}
		ifile.read((char*)&stf,sizeof(stf));		
	}
	cout<<"Enter the Id of the reqd doctor"<<endl;
	cin>>i;
	ifile.close();
	f.open("staffmembers",ios::in|ios::out);
	f.seekg(0,ios::beg);
    f.read((char*)&stf,sizeof(stf));
	a=f.tellg();
	while(!f.eof())
	{
		if((prof=='D')&&(id1==i))
		{
				bill1+=fees;
				nov++;
				f.seekp(a-sizeof(stf),ios::beg);
				f.write((char*)&stf,sizeof(stf));
		}
		f.read((char*)&stf,sizeof(stf));
		a=f.tellg();
	}
	f.close();
	return bill1;
		
}
void staff::get()
{
	ifstream ifile;
	ifile.open("staffmembers");
	ifile.seekg(0-sizeof(stf),ios::end);
	ifile.read((char*)&stf,sizeof(stf));
	if(flag)
		id1=stf.id1+1;
	else
		id1=stf.id1+2;
	char choice;//D-Doctor,P-Paramedical Staff,O-Other Staff;
	//COMMON DETAILS
	cout<<"Enter your first name , last name , email ,age ,phone no \n";
	cin>>fname>>lname>>email>>age>>phno;
	cout<<"Enter 'D' for Doctor , 'P' for Paramedical Staff , 'O' for Other Staff\n";
	cin>>choice;
	com=0;
	nov=0;
	switch(choice)
	{
	case 'D'://Doctor only details
		{
			cout<<"Qualification , Institution(Qualification) and Branch of Institution\n";
			cin>>Dqual>>Dqualins>>Dqualoc;
			cout<<"Enter your Speciality(one word) , Parallel clinic(if any otherwise enter 'notapplicable') and if you are in hospital(1=yes,0=no)\n";
			cin>>Dspec>>Dpc>>Dinout;
			cout<<"Enter your tenure and room number\n";
			cin>>Dtnr>>Drmn;
			cout<<"Enter the fees of the doctor"<<endl;
	        cin>>fees;
			cout<<"Enter commision per person\n";
			cin>>com;
			prof='D';
		}break;
	case 'P'://Paramedical staff only details
		{
			cout<<"Enter Operation Department(one word)\n";
			cin>>Pdep;
			prof='P';
		}break;
	case 'O'://Other staff only details
		{
			cout<<"Enter you Designation , Company Contracted( for multiword companies use slashes like for a company ABC Electronics enter ABC/Electronics):\n";
			cin>>Odes>>Ocom;
			cout<<"In case the company has multiple branches enter the branch else enter 'notapplicable':\n";
			cin>>Ocombr;
			prof='O';
		}break;
	default:prof='I';//I refers to Invalid;
	}
	l=id1;
}
void staff::wtf()
{
	ofstream ofile;
	ofile.open("staffmembers",ios::app);
	if(ofile)
	{
		get();
		ofile.write((char*)&stf,sizeof(stf));
	    ofile.close();
	}
}
void staff::rff()
{
	ifstream ifile;
	ifile.open("staffmembers");
	ifile.seekg(0,ios::beg);
	ifile.read((char*)&stf,sizeof(stf));
	while(ifile)
	{
		disp();
		ifile.read((char*)&stf,sizeof(stf));
	}
	ifile.close();
}
void staff::disp()
{
	//COMMON DETAILS
	cout<<"NAME: "<<fname<<" "<<lname<<"\n";
	cout<<"AGE: "<<age<<"\n";
	cout<<"EMAIL: "<<email<<"\n";
	cout<<"PHONE NUMBER: "<<phno<<"\n";
	cout<<"ID: "<<id1<<"\n";
	if(prof=='D')//Doctor only details
	{
		cout<<"Commission per Person: "<<com<<endl;
		cout<<"No of Visits: "<<nov<<"\n";
		cout<<"Total Earnings: "<<((nov*com)+(nov*fees))<<"\n";
		cout<<Dqual<<" from "<<Dqualins<<"'s "<<Dqualoc<<" branch \n";
		cout<<"SPECIALITY: "<<Dspec<<"\n";
		if(Dpc!="notapplicable")
		{
			cout<<"PARALLEL CLINIC: "<<Dpc<<"\n";
		}
		if(Dinout)
			cout<<"In Hospital\n";
		else
			cout<<"Not in Hospital\n";
		cout<<"TENURE: "<<Dtnr<<" years\n";
		cout<<"ROOM NUMBER: "<<Drmn<<"\n";
		cout<<"FEES: "<<fees<<endl;
	}
	if(prof=='P')//Paramedical staff only details
	{
		cout<<"OPERATION DEPARTMENT: "<<Pdep<<"\n";
	}
	if(prof=='O')//Other staff only details
	{
		cout<<"DESIGNATION: "<<Odes<<"\n";
		cout<<"COMPANY CONTRACTED "<<Ocom<<"\n";
		if(Ocombr!="notapplicable")
			cout<<"BRANCH OF COMPANY: "<<Ocombr<<"\n";
	}
	if(prof=='I')//Display invalid if invalid
	{
		cout<<"Sorry Unrecognized Profession\n";
	}
	cout<<"________________________________________________________"<<endl;
}
void staff::search()
{
	ifstream ifile;
	ifile.open("staffmembers");
	char c,fn[100],ln[100],em[100],ph[15];
	cout<<"Enter 'n' to search by name, 'e' to search by email and 'p' to search by phone no.";
	cin>>c;
	if(c=='n')
	{
		cout<<"Enter the first name and last name\n";
		cin>>fn>>ln;
		ifile.read((char*)&stf,sizeof(stf));
		while(ifile)
		{
			if(((strcmpi(fn,fname))==0)&&((strcmpi(ln,lname))==0))
				disp();
			ifile.read((char*)&stf,sizeof(stf));
		}
		ifile.close();
	}
	if(c=='e')
	{
		cout<<"Enter the email\n";
		cin>>em;
		ifile.read((char*)&stf,sizeof(stf));
		while(ifile)
		{
			if((strcmpi(em,email))==0)
				disp();
			ifile.read((char*)&stf,sizeof(stf));
		}
		ifile.close();
	}
	if(c=='p')
	{
		cout<<"Enter the phone no\n";
		cin>>ph;
		ifile.read((char*)&stf,sizeof(stf));
		while(ifile)
		{
			if((strcmpi(ph,phno))==0)
				disp();
			ifile.read((char*)&stf,sizeof(stf));
		}
		ifile.close();
	}
}
void staff::del()
{
	ifstream ifile;
	ifile.open("staffmembers");
	ifile.seekg(0,ios::beg);
	char c,fn[100],ln[100],em[100],ph[15];
	cout<<"Enter 'n' to delete by name, 'e' to delete by email and 'p' to delete by phone no.";
	cin>>c;
	ofstream ofile("stafftemp",ios::app);
	if(c=='n')
	{
		cout<<"Enter the first name and last name\n";
		cin>>fn>>ln;
		ifile.read((char*)&stf,sizeof(stf));
		while(ifile)
		{
			if(((strcmpi(fn,fname))!=0)||((strcmpi(ln,lname))!=0))
			{
				if(l==id1)
					flag=0;
				ofile.write((char*)&stf,sizeof(stf));
			}
			ifile.read((char*)&stf,sizeof(stf));
		}
		ifile.close();
	}
	if(c=='e')
	{
		cout<<"Enter the email\n";
		cin>>em;
		ifile.read((char*)&stf,sizeof(stf));
		while(ifile)
		{
			if((strcmpi(em,email))!=0)
			{
				if(l==id1)
					flag=0;
				ofile.write((char*)&stf,sizeof(stf));
			}
			ifile.read((char*)&stf,sizeof(stf));
		}
		ifile.close();
	}
	if(c=='p')
	{
		cout<<"Enter the phone no\n";
		cin>>ph;
		ifile.read((char*)&stf,sizeof(stf));
		while(ifile)
		{
			if((strcmpi(ph,phno))!=0)
			{
				if(l==id1)
					flag=0;
				ofile.write((char*)&stf,sizeof(stf));
			}
			ifile.read((char*)&stf,sizeof(stf));
		}
		ifile.close();
	}
	ifile.close();
	ofile.close();
	remove("staffmembers");
	rename("stafftemp","staffmembers");
}
void staff::mod()
{
	fstream f("staffmembers",ios::in|ios::out);
	f.seekg(0,ios::beg);
	f.read((char*)&stf,sizeof(stf));
	int a=f.tellg();
	char fn[100],ln[100],em[100],ph[15],c,ci;
	cout<<"Enter n to modify by searching name\n";
	cout<<"Enter e to modify by searching email\n";
	cout<<"Enter p to modify by searching phone no\n";
	cin>>c;
	if(c=='n')
	{
		cout<<"Enter the entry's first and last name you want to modify\n";
		cin>>fn>>ln;
		cout<<"To modify all enter a , name enter n , email enter e , phone no enter p\n";
		cin>>ci;
		while(!f.eof())
		{
			if(((strcmpi(fn,fname))==0)&&((strcmpi(ln,lname))==0))
			{
				if(ci=='a')
					get();
				else if(ci=='n')
				{
					cout<<"Enter first and last name\n";
					cin>>fname>>lname;
				}
				else if(ci=='e')
				{
					cout<<"Enter email\n";
					cin>>email;
				}
				else if(ci=='p')
				{
					cout<<"Enter phone no.\n";
					cin>>phno;
				}
				else
				{
					cout<<"Invalid input\n";break;
				}
				f.seekp(a-sizeof(stf),ios::beg);
				f.write((char*)&stf,sizeof(stf));
			}
			f.read((char*)&stf,sizeof(stf));
			a=f.tellg();
		}
	}
	if(c=='e')
	{
		cout<<"Enter the entry's email you want to modify\n";
		cin>>em;
		cout<<"To modify all enter a , name enter n , email enter e , phone no enter p\n";
		cin>>ci;
		while(!f.eof())
		{
			if((strcmpi(em,email))==0)
			{
				if(ci=='a')
					get();
				else if(ci=='n')
				{
					cout<<"Enter first and last name\n";
					cin>>fname>>lname;
				}
				else if(ci=='e')
				{
					cout<<"Enter email\n";
					cin>>email;
				}
				else if(ci=='p')
				{
					cout<<"Enter phone no.\n";
					cin>>phno;
				}
				else
				{
					cout<<"Invalid input\n";break;
				}
				f.seekp(a-sizeof(stf),ios::beg);
				f.write((char*)&stf,sizeof(stf));
			}
			f.read((char*)&stf,sizeof(stf));
			a=f.tellg();
		}
	}
	if(c=='p')
	{
		cout<<"Enter the entry's phone number you want to modify\n";
		cin>>ph;
		cout<<"To modify all enter a , name enter n , email enter e , phone no enter p\n";
		cin>>ci;
		while(!f.eof())
		{
			if((strcmpi(ph,phno))==0)
			{
				if(ci=='a')
					get();
				else if(ci=='n')
				{
					cout<<"Enter first and last name\n";
					cin>>fname>>lname;
				}
				else if(ci=='e')
				{
					cout<<"Enter email\n";
					cin>>email;
				}
				else if(ci=='p')
				{
					cout<<"Enter phone no.\n";
					cin>>phno;
				}
				else
				{
					cout<<"Invalid input\n";break;
				}
				f.seekp(a-sizeof(stf),ios::beg);
				f.write((char*)&stf,sizeof(stf));
			}
			f.read((char*)&stf,sizeof(stf));
			a=f.tellg();
		}
	}
	f.close();
}
void patient::get()
{
	ifstream ifile;
	ifile.open("patient");
	ifile.seekg(0-sizeof(s),ios::end);
	ifile.read((char*)&s,sizeof(s));
	id=s.id+1;	
	ifile.close();
	cout<<"Enter the name"<<endl;
	cin>>name;
	cout<<"Enter fathers name"<<endl;
	cin>>fname;
	cout<<"Enter mothers name"<<endl;
	cin>>mname;
	cout<<"Enter the address"<<endl;
	cin>>address;
	cout<<"Enter the insurance company name"<<endl;
	cin>>insurancecompname;
	cout<<"Enter age"<<endl;
	cin>>age;
	cout<<"Enter the mobile number"<<endl;
	cin>>mobile;
	bill=stf.ids();
	cout<<"Your final bill is"<<endl;
	cout<<bill<<endl;
}
void patient::disp()
{
	cout<<"the name                   :";
	cout<<name<<endl;
	cout<<"the fathers name           :";
	cout<<fname<<endl;
	cout<<"the mothers name           :";
	cout<<mname<<endl;
	cout<<"the address                :";
	cout<<address<<endl;
	cout<<"the insurance company name :";
	cout<<insurancecompname<<endl;
	cout<<"the age                    :";
	cout<<age<<endl;
	cout<<"the mobile number          :";
	cout<<mobile<<endl;
	cout<<"The bill is                :";
	cout<<bill<<endl;
	cout<<"The ID number is           :";
	cout<<id<<endl;
	cout<<"The final bill is          :";
	cout<<bill<<endl;
	cout<<"______________________________________________"<<endl;
}
void patient::wtf()
{
	ofstream ofile;
	ofile.open("patient",ios::app);
	get();
	ofile.write((char*)&s,sizeof(s));
	ofile.close();
}
void patient::rff()
{
	ifstream ifile;
	ifile.open("patient");
	ifile.seekg(0,ios::beg);
	ifile.read((char*)&s,sizeof(s));
	while(ifile)
	{
		disp();
		ifile.read((char*)&s,sizeof(s));
	}
	ifile.close();
}
void patient::search()
{
	int i;
	char name1[100],mob[100];
	ifstream ifile;
	ifile.open("patient");
    ifile.seekg(0,ios::beg);
    ifile.read((char*)&s,sizeof(s));
	ifile.read("patient",ios::beg);
	cout<<"(1) Name (2) Mobile Number"<<endl;
	cin>>i;
	if(i==1)
	{
			cout<<"Enter the NAME you wamt to search"<<endl;
			cin>>name1;
	        while(ifile)
			{
		          if(strcmp(name1,name)==0)
		          disp();
		          ifile.read((char*)&s,sizeof(s));
			}
	}
	else if(i==2)
	{
		cout<<"Enter the mobile number"<<endl;
		cin>>mob;
		    while(ifile)
			{
				  if(strcmp(mob,mobile)==0)
		          disp();
		          ifile.read((char*)&s,sizeof(s));
			}
	}
}
void patient::del()
{

	ifstream ifile("patient");//default in mode
	ifile.seekg(0,ios::beg);
	ofstream ofile;
	ofile.open("New",ios::app);
	int j;
	char mo[10],n[200];
	cout<<"(1) Name (2) Mobile Number"<<endl;
	cin>>j;
	if(j==1)
	{	cout<<"Enter the name you want to delete"<<endl;
	    cin>>n;
		ifile.read((char*)&s,sizeof(s));
	    while(ifile)
		{
		     if(strcmpi(n,name)!=0)
		     ofile.write((char*)&s,sizeof(s));
		     ifile.read((char*)&s,sizeof(s));
		}
	}
	else if(j==2)
	{
		cout<<"Enter the Number you want to delete"<<endl;
		cin>>mo;
		ifile.read((char*)&s,sizeof(s));
	    while(ifile)
		{
		     if(strcmpi(mo,mobile)!=0)
		     ofile.write((char*)&s,sizeof(s));
		     ifile.read((char*)&s,sizeof(s));
		}
	}

	ifile.close();
	ofile.close();
	remove("patient");
	rename("New","patient");
}
void patient::mod()
{
	int opt,option,a;
	char n[100],m[10];
	fstream f("patient",ios::in|ios::out);
	f.seekg(0,ios::beg);
	cout<<"Do you want to read on the basis of (1)Name (2)Mobile Number"<<endl;
	cin>>opt;
	if(opt==1)
	{
		cout<<"Enter the name"<<endl;
		cin>>n;
		f.read((char*)&s,sizeof(s));
        a=f.tellg();
		while(!f.eof())
		{
			if(strcmpi(n,name)==0)
			{
			cout<<"Do you want to change (1)Name (2)Mobile Number (3)Both"<<endl;
			cin>>option;
			if(option==1)
			{
					cout<<"Enter the NEW NAME"<<endl;
                    cin>>name;
					f.seekp(a-sizeof(s),ios::beg);
					f.write((char*)&s,sizeof(s));
				
			}
			else if(option==2)
				{
					cout<<"Enter the NEW NUMBER"<<endl;
					cin>>mobile;
					f.seekp(a-sizeof(s),ios::beg);
					f.write((char*)&s,sizeof(s));
				}
			else
				{
					cout<<"Enter the NEW NAME"<<endl;
					cin>>name;
					cout<<"Enter the NEW NUMBER"<<endl;
					cin>>mobile;
					f.seekp(a-sizeof(s),ios::beg);
					f.write((char*)&s,sizeof(s));
				}
				
			}
			f.read((char*)&s,sizeof(s));
				a=f.tellg();
		}
			f.close();
	}
	if(opt==2)
	{
		cout<<"Enter the mobile number"<<endl;
		cin>>m;
		f.read((char*)&s,sizeof(s));
		while(!f.eof())
		{
			if(strcmpi(m,mobile)==0)
			{
				cout<<"Do you want to change (1)Name (2)Mobile Number (3)Both"<<endl;
				cin>>option;
				if(option==1)
				{
					cout<<"Enter the NEW NAME"<<endl;
                    cin>>name;
					f.seekp(a-sizeof(s),ios::beg);
					f.write((char*)&s,sizeof(s));
				}
				else if(option==2)
				{
					cout<<"Enter the NEW NUMBER"<<endl;
					cin>>mobile;
					f.seekp(a-sizeof(s),ios::beg);
					f.write((char*)&s,sizeof(s));
				}
				else
				{
					cout<<"Enter the NEW NAME"<<endl;
					cin>>name;
					cout<<"Enter the NEW NUMBER"<<endl;
					cin>>mobile;
					f.seekp(a-sizeof(s),ios::beg);
					f.write((char*)&s,sizeof(s));
				}
				f.read((char*)&s,sizeof(s));
				a=f.tellg();
			}
			f.read((char*)&s,sizeof(s));
				a=f.tellg();
		}
		f.close();
	}
}
void staff::hello()
{
	int ch;				
		cout<<"Enter 1 to make a new entry\n";
		cout<<"Enter 2 to display all entries\n";
		cout<<"Enter 3 to search a particular\n";
		cout<<"Enter 4 to delete a particular\n";
		cout<<"Enter 5 to modify a particular\n";
		cin>>ch;
	    switch(ch)
		{
		case 1:stf.wtf();break;//Entry creator;
	    case 2:stf.rff();break;//Entry displayer;
		case 3:stf.search();break;//Entry search;
		case 4:stf.del();break;//Entry deletor;
		case 5:stf.mod();break;//Entry modifier;
	    default:break;
		}
}
void patient::hey()
{
	int ch1;
	cout<<"Press (1)Write (2)Read (3)Search (4)Delete (5)Modify"<<endl;
		    cin>>ch1;
		    switch(ch1)
			{
                    case 1:s.wtf();break;
                    case 2:s.rff();break;
                    case 3:s.search();break;
                    case 4:s.del();break;
		            case 5:s.mod();break;
                    default:break;
			}
			
}
void main()
{
    int o;
	char c;
	do
	{
		cout<<"Enter (1) to check details of patient and (2) to check details of hospital staff"<<endl;
		cin>>o;
		switch(o)
		{
		case 1:
			{
				s.hey();break;//access function
			}
		case 2:
			{
			    stf.hello();break;//access function
			}
	}
	cout<<"Do you want to cont. y or n"<<endl;
	cin>>c;
	}while(c=='y');
}
