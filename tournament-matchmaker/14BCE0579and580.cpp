#include<iostream>
#include<stdio.h>
#include<string.h>
using namespace std;
#define size 100
class cq //Circular Queue => cq
{
	int f,r; // Front Index = f % size and Rear Index = r % size
	char name[size][30]; //Max names = size
public:
	void ini();
	int isfull();
	int isempty();
	void enqueue(char*);
	char* remove();
	void display();
	void tournament();
	int* chkdup();
	void deldup();
}t;
void cq::ini() //Intially, Front and Rear Index = -1 as cq is empty
{
	f=-1;
	r=-1;
}
int cq::isfull() //If cq is full returns 1, else returns 0
{
	if(((r+1)%size)==(f%size)) //Checks if in a circle of indices 0 to n-1 whether Front Index is next to Rear Index
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
int cq::isempty() //If cq is empty returns 1 else returns 0
{
	if(r==-1) //Checks if Rear Index = -1
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
void cq::enqueue(char *str) //Enqueues string at Rear Index
{
	//*str is address of string to be enqueued
	int i;
	if(isfull()) //Checking if full before string is enqueued
	{
	    cout<<"Full\n";		
	}
	else
	{
		if(isempty()) //If cq is empty, we need a cq of 1 element
		{
			f=0; //Front Index = 0
			r=0; //Rear Index = 0
		}
		else //If cq is partially filled
		{
			r++; //Rear Index is equal to the index next to it
		}
		for(i=0;*(str+i)!='\0';i++) //Enqueues string at Rear index
		{
			name[r%size][i]=*(str+i); //Copying string, character by character
		}
		name[r%size][i]='\0'; //Terminating character added
	}
}
char* cq::remove() //Removes string at Front Index
{
	char p[30];
	if(isempty())
	{
		cout<<"Empty\n";
		p[0]='\0'; //Just to return
	}
	else if((f%size)==(r%size)) //If only one string left
	{
		strcpy(p,name[f%size]); //Make copy of string to be removed
		//After removal cq should be empty, so Front and Rear Index = -1
		f=-1;
		r=-1;
	}
	else //More than one string in cq
	{
		strcpy(p,name[f%size]); //Make copy of string to be removed
		f++; //Front Index is the index next to it
	}
	return p; //Return address of the copy of the string to be removed
}
void cq::display() //Displays list of names as tournament status
{
	int i;
	cout<<"Tournament status\n";
	if((r%size)>=(f%size)) //If Front Index <= Rear Index
	{
		for(i=(f%size);i<=(r%size);i++) //Display names from Front Index to Rear Index
		{
			cout<<name[i]<<" ";
		}
		cout<<"\n";
	}
	else //If Front Index > Rear Index
	{
		for(i=(f%size);i<size;i++) //Display names from Front Index to size-1
		{
			cout<<name[i]<<" ";
		}
		for(i=0;i<=(r%size);i++) //Dislay names from 0 to Rear Index
		{
			cout<<name[i]<<" ";
		}
		cout<<"\n";
	}
}
void cq::tournament() //Gives byes and shows status after each round
{
	cout<<"Tournament Initiated\n";
	char cmp1[30],cmp2[30],*cmp;
	int pwt,cntr,rprv,s,nb,ch;
	display(); //Displays all participants
	rprv=(r%size); //rprv = Rear Index
	if((f%size)<=(r%size)) //If Front Index < = Rear Index
	{
		//Size of cq = Rear Index - Front Index + 1
		s=(r%size)-(f%size)+1;
	}
	else //If Rear Index < Front index
	{
		//Size of cq = ((size -1) - Front Index + 1) + (Rear Index - 0 + 1)
		s=(size-(f%size))+((r%size)+1);
	}
	pwt=1; //pwt is short for power of two and say pwt = 2^n => 2^n = 1
	while(pwt<s) //Untill 2^n > Size of cq
	{
		pwt=pwt*2; //n++ or 2^n = 2 x 2^n
	}
	nb=pwt-s; //No of Byes(nb) = 2^n - Size of cq
	cntr=0; //COUNTER = 0
	//LIST OF BYES
	if(nb>0) //If there are byes to give
	{
		cout<<"Bye given to:\n";
	}
	while(cntr!=nb) //Till COUNTER = no of byes
	{
		cout<<name[f]<<"\n"; //Display string at Front Index
		enqueue(remove()); //Remove it and then enqueue it again
 		cntr++; //COUNTER = COUNTER + 1
	}
	while((f%size)!=((rprv+1)%size)) //Till Front Index is not equal to rprv
	{
		cmp=remove(); //Removes from cq and Stores string in cmp
		for(cntr=0;*(cmp+cntr)!='\0';cntr++)
		{
			cmp1[cntr]=*(cmp+cntr); //Copies string to cmp1, character by character
		}
		cmp1[cntr]='\0';
		cmp=remove(); //Removes from cq and Stores string in cmp
		for(cntr=0;*(cmp+cntr)!='\0';cntr++)
		{
			cmp2[cntr]=*(cmp+cntr); //Copies string to cmp2, character by character
		}
		cmp2[cntr]='\0';
		do //do till ch not equal to 1 and 2
		{
			cout<<"Enter 1 or 2 to select winner \n1."<<cmp1<<"\n2."<<cmp2<<"\n";
		    cin>>ch;
		    if(ch==1) //ch = 1 => Participant 1 wins => Enqueue its name
		    {
		    	enqueue(cmp1);
			}
			else if(ch==2) //ch = 2 => Participant 2 wins => Enqueue its name 
			{
				enqueue(cmp2);
			}
			else
			{
				cout<<"Wrong Input\n";
			}
		}while((ch!=1)&&(ch!=2));
		if((f%size)==(r%size)) //After removal if only one string is left
		{
			s=2; //Then size was two before removal
			break; //break while loop
		}
	}
	while(s!=2) //Repeat untill s becomes 2
	{
		display(); //Display all participants
		rprv=(r%size); //rprv = Rear Index
		while((f%size)!=((rprv+1)%size)) //Till Front Index is not equal to rprv
		{
			cmp=remove(); //Removes from cq and Stores string in cmp
		    for(cntr=0;*(cmp+cntr)!='\0';cntr++)
		    {
			    cmp1[cntr]=*(cmp+cntr); //Copies string to cmp1, character by character
		    }
			cmp1[cntr]='\0';
		    cmp=remove(); //Removes from cq and Stores string in cmp
		    for(cntr=0;*(cmp+cntr)!='\0';cntr++)
		    {
			    cmp2[cntr]=*(cmp+cntr); //Copies string to cmp2, character by character
		    }
		    cmp2[cntr]='\0';
			do //do till ch not equal to 1 and 2
			{
				cout<<"Enter 1 or 2 to select winner \n1."<<cmp1<<"\n2."<<cmp2<<"\n";
			    cin>>ch;
			    if(ch==1) //ch = 1 => Participant 1 wins => Enqueue its name
			    {
			    	enqueue(cmp1);
				}
				else if(ch==2) //ch = 2 => Participant 2 wins => Enqueue its name 
				{
					enqueue(cmp2);
				}
				else
				{
					cout<<"Wrong Input\n";
				}
			}while((ch!=1)&&(ch!=2));
			if((f%size)==(r%size)) //After removal if only one string is left
			{
				s=2; //Then size was two before removal
				break; //break while loop
			}
		}
	}
	cout<<"Winner is "<<name[f%size]<<"\n"; //Winner is string at Front Index(Only String Left)
}
int* cq::chkdup() //Return information on duplicates found as integer array pointer dupfnd
{
	int i,j,dupfnd[2];
	dupfnd[0]=0; //Initially assumed no dulicate found (0)
	dupfnd[1]=0; //Initially assumed duplicate position as 0(0)
	//Here we work with two strings at unequal indices i and j
	if((r%size)>=(f%size)) //Traversal of cq similar to that in display function
	{
		for(i=(f%size);i<=(r%size);i++)
		{
			for(j=i+1;j<=(r%size);j++)
			{
				if(strcmp(name[i],name[j])==0) //If duplicate is found
				{
					dupfnd[0]=1; //Duplicate Found is true(1)
					dupfnd[1]=j; //Index of Duplicate = j
					break; //break for loop
				}
			}
			if(dupfnd[0]==1) //If duplicate was aldready found
			{
				break; //break for loop
			}
		}
	}
	else
	{
		for(i=(f%size);i<size;i++)
		{
			for(j=i+1;j<size;j++)
			{
				if(strcmp(name[i],name[j])==0) //If duplicate is found
				{
					dupfnd[0]=1; //Duplicate Found is true(1)
					dupfnd[1]=j; //Index of Duplicate = j
					break; //break for loop
				}
			}
			if(dupfnd[0]==1) //If duplicate was aldready found
			{
				break; //break for loop
			}
			for(j=0;j<=(r%size);j++)
			{
				if(strcmp(name[i],name[j])==0) //If duplicate is found
				{
					dupfnd[0]=1; //Duplicate Found is true(1)
					dupfnd[1]=j; //Index of Duplicate = j
					break; //break for loop
				}
			}
			if(dupfnd[0]==1) //If duplicate was aldready found			
			{
				break; //break for loop
			}
		}
		for(i=0;i<=(r%size);i++)
		{
			for(j=i+1;j<=(r%size);j++)
			{
				if(strcmp(name[i],name[j])==0) //If duplicate is found
				{
					dupfnd[0]=1; //Duplicate Found is true(1)
					dupfnd[1]=j; //Index of Duplicate = j
					break; //break for loop
				}
			}
			if(dupfnd[0]==1) //If duplicate was aldready found
			{
				break; //break for loop
			}
		}
	}
	return dupfnd; //Return information on duplicate found
}
void cq::deldup() //Deletes duplicates
{
	int i,*dpf;
	dpf=chkdup(); //Store info on duplicates in dpf
	if(*(dpf+0)) //If duplicate was found
	{
		cout<<"Duplicates found\n";
		do //do till there are no more duplicates found
		{
			while((f%size)!=*(dpf+1)) //Repeatedly remove a string and enqueue it till Front Index = Index at which Duplicate Found
			{
				enqueue(remove());
			}
			remove(); //Remove Duplicate
			dpf=chkdup(); //Store info on duplicates in dpf
		}while(*(dpf+0));
	}
	else //If absolutely no duplicate was found ever
	{
		cout<<"No duplicates found\n";
	}
}
main()
{
	char s[30];
	int ch=8,i,n;
	while(ch!=0) //Repeat MENU till ch = 0
	{
		cout<<"Enter 1 to have a tournament, 0 to exit\n";
		cin>>ch;
		switch(ch)
		{
			case 0:break;
			case 1:
			{
				t.ini(); //Initialize circular queue t as empty
				cout<<"Enter number of participants and names\n";
				cin>>n;
				i=0;
				while(i<n) //Take in and enqueue names n times
				{
					cin>>s;
					t.enqueue(s);
					i++;
				}
				t.deldup(); //Delete duplicates
				t.tournament(); //Start Tournament
				break;
			}
			default:cout<<"Wrong Input\n";
		}
	}
}
