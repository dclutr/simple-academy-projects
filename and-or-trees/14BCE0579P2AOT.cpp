/*
14BCE0579
aksdadaks99@yahoo.co.in
9952577747
*/
#include<iostream>
#include<stdio.h>
using namespace std;
struct aot //And Or Tree
{
	char st; //Statement
	char ao1,ao2; //And 'a' Or 'o'
	aot *s1,*s2,*s3; //Sons of Node
}*root;
void crteps(aot *t) //Create Elaborate Problem Statement
{
	cout<<"For statement : "<<t->st<<"\n";
	t->s1=NULL; //Assumed no Statement 1
	t->s2=NULL; //Assumed no Statement 2
	t->s3=NULL; //Assumed no Statement 3
	int n=0; //Assumed Leaf Node
	cout<<"Enter number of statements 0,1,2,3\n";
	cin>>n;
	if((n<4)&&(n>-1)) //If valid case
	{
		if(n!=0) //If not leaf node
		{
			cout<<"Enter Conditon\n";
			if(n==1)
			{
				t->s1=new aot;
				cin>>t->s1->st; //Take in Statement 1
				crteps(t->s1); //Take in Children for Statement 1
			}
			else if(n==2)
			{
				t->s1=new aot;
				t->s2=new aot;
				cin>>t->s1->st; //Take in Statement 1
				cin>>t->ao1; //Take in Operand 1
				cin>>t->s2->st; //Take in Statement 2
				crteps(t->s1); //Take in Children for Statement 1
				crteps(t->s2); //Take in Children for Statement 2
			}
			else if(n==3)
			{
				t->s1=new aot;
				t->s2=new aot;
				t->s3=new aot;
				cin>>t->s1->st; //Take in Statement 1
				cin>>t->ao1; //Take in Operand 1
				cin>>t->s2->st; //Take in Statement 2
				cin>>t->ao2; //Take in Operand 2
				cin>>t->s3->st; //Take in Statement 3
				crteps(t->s1); //Take in Children for Statement 1
				crteps(t->s2); //Take in Children for Statement 2
				crteps(t->s3); //Take in Children for Statement 3
			}	
		}
	}
	else
	{
		cout<<"Invalid Input: Node will be treated as Independent Statement or Leaf Node\n";
	}
}
void prteps(aot *t) //Print Elaborate Problem Statement
{
	if(t->s3==NULL) //Max two students
	{
	    if(t->s2==NULL) //Max one student
		{
			if(t->s1==NULL) //Display Leaf Node
			{
				cout<<t->st;
			}
			else //Only one student
			{
				prteps(t->s1); //Access Statement 1
			}
		}
		else //Only two students
		{
			cout<<" ( ";
			prteps(t->s1); //Access Statement 1
			if(t->ao1=='a') //Print Operator 1
		    {
				cout<<" AND ";
		    }
		    else
		    {
			    cout<<" OR ";
		    }
			prteps(t->s2); //Access Statement 2
			cout<<" ) ";
		}	
	}
	else //Only three students
	{
		cout<<" ( ";
		prteps(t->s1); //Access Statement 1
		if(t->ao1=='a') //Print Operator 1
		{
			cout<<" AND ";
		}
		else
		{
			cout<<" OR ";
		}
		prteps(t->s2); //Access Statement 2
		if(t->ao2=='a') //Print Operator 2
		{
			cout<<" AND ";
		}
		else
		{
			cout<<" OR ";
		}
		prteps(t->s3); //Access Statement 3
		cout<<" ) ";
	}
}
int evaleps(aot *t) //Evaluate Problem Statement
{
	int x,y,z;
	if(t->s3==NULL) //Max two students
	{
	    if(t->s2==NULL) //Max one student
		{
			if(t->s1==NULL) //Leaf Node
			{
				cout<<"Enter true value (1 or 0) for "<<t->st<<"\n";
				cin>>x; //Take in truth value
			}
			else //Only one student
			{
				x=evaleps(t->s1); //Find truth value of Statement 1
			}
		}
		else //Only two students
		{
			x=evaleps(t->s1); //Find truth value of Statement 1
		    y=evaleps(t->s2); //Find truth value of Statement 2
			if(t->ao1=='a') //Case S1 AND S2
		    {
				if(x&&y)
				{
					x=1;
				}
				else
				{
					x=0;
				}
		    }
		    else //Case S1 OR S2
		    {
		    	if(x||y)
				{
					x=1;
				}
				else
				{
					x=0;
				}
		    }
		}	
	}
	else
	{
		x=evaleps(t->s1); //Find truth value of Statement 1
		y=evaleps(t->s2); //Find truth value of Statement 2
		z=evaleps(t->s3); //Find truth value of Statement 3
		if(t->ao1=='a')
		{
			if(t->ao2=='a') //Case S1 AND S2 AND S3
			{
				if(x&&y&&z)
				{
					x=1;
				}
				else
				{
					x=0;
				}
			}
			else //Case S1 AND S2 OR S3
			{
				if(x&&y||z)
				{
					x=1;
				}
				else
				{
					x=0;
				}
			}
			
		}
		else
		{
			if(t->ao2=='a') //Case S1 OR S2 AND S3
			{
				if(x||y&&z)
				{
					x=1;
				}
				else
				{
					x=0;
				}
			}
			else //Case S1 OR S2 OR S3
			{
				if(x||y||z) 
				{
					x=1;
				}
				else
				{
					x=0;
				}
			}
		}
		
	}
	return x; //Return truth value of evaluated portion
}
main()
{
	cout<<"NOTE: A condition for S is entered in order S1, O1, S2, O2, S3 where S is for statement and O is for operator\n      Mathematically S = S1 O1 S2 O2 S3, eg: A = B and C or D\n";
	cout<<"NOTE: Elaborated Problem Statement is Problem in terms of Independent Statements\n      Independent Statements are those whose true value does not depend on any other statement\n";
	cout<<"NOTE: And Operator = 'a', Or Operator='o' \n";
	int ch=5;
	while(ch!=0)
	{
		cout<<"Enter 1 to Solve your Logical And/Or Problem, 0 to Exit\n";
		cin>>ch;
		switch(ch)
		{
			case 0:break;
			case 1:
			{
				root=new aot;
		        cout<<"Enter problem to be solved\n";
		        cin>>root->st; //Take in Problem
				crteps(root); //Create Elaborate Problem Statement
				cout<<"Elaborated Problem Statement\n";
				cout<<root->st<<" = ";
				prteps(root); //Print Elaborate Problem Statement
				cout<<"\n";
				if(evaleps(root)) //Calculate truth value of problem
				{
					cout<<root->st<<" is true\n";
				}
				else
				{
					cout<<root->st<<" is false\n";
				}
				break;
			}
			default:
			{
				cout<<"Invalid Input\n";
				break;
			}
		}
	}
} 
