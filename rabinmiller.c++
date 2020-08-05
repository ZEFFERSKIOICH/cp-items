#include <bits/stdc++.h>
using namespace std;
#define forr(i,a,b) for(int i=a;i<b;i++)
typedef long long int lli;
int n;
lli bine(lli a,int p)
{
	lli  res=1;
	while(p>0)
	{
		if(p&1)	res=(res*a)%n;
		a=(a*a)%n;	p=p>>1;
	}
	return res;
}

bool rm(int a,int d)
{
	
		lli po=bine(a,d);
		if(po==1 || po==n-1)	return true;
		
		while(d!=n-1)
		{
			po=(po*po)%n;
			if(po==1)	return false;
			if(po==n-1)	return true;
			d=d<<1;
		}
		return false;
}

int main()
{
	cin>>n;int num=1;
	if(n<=1 || n==4)	{cout<<"flase\n";return 0;}
	if(n<=3)			{cout<<"true\n" ;return 0;}
	if(num%2==0)		{cout<<"false\n";return 0;}
	while((n-1)%num==0)
	{
		num=num*2;
	}
	num=num/2;int d=(n-1)/num;bool b=true;
	
	for(int i=0;i<3;i++)
	{
		int a=2+(rand()%(n-4));//random number between 2 and n-2
		b&=rm(a,d);// d will generally be an odd number
	}
		
	if(b==true)		cout<<"true\n";
	else 			cout<<"false\n"; 
	return 0;
}
