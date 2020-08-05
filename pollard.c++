#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
lli n;

lli bine(lli a,lli b)
{
	//cout<<a<<" "<<b<<endl;
	a=a%n;lli exp=2;lli res=1;
	while(exp)
	{
		if(exp&1)	res=res*a%n;
		a=a*a%n;
		exp>>=1;
	}
	//cout<<"hi"<<endl;
	return (res+b)%n;
}


lli rho()
{
	//cout<<"hi"<<endl;
	lli x;lli y;lli c;
	x=rand()%(n-3)+2;
	y=x;
	c=rand()%(n-2)+2;lli g=1;
	cout<<x<<" "<<c<<endl;
	while(g==1)
	{	x=bine(x,c);
		y=bine(y,c);
		y=bine(y,c);
		cout<<x<<" "<<y<<endl;
		g=__gcd(abs(x-y),n);
		if(g==n)	rho();
	}
	return g;
}


int main()
{
	cin>>n;
	lli  x,y;
	cout<<rho()<<endl;
	return 0;
}
	
