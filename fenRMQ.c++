//bit1 is forwatd bit
//bit2 is backward bit
//** traversals in both trees  end at the same node and 
//** can be mathematically proven
#include <bits/stdc++.h>
using namespace std;
#define eb emplace_back
#define forr(i,a,b) for(int i=a;i<b;i++)
int n;
vector<int> v;
vector<int> bit1;
vector<int> bit2;
void build(int pos,int val)
{
	pos++;
	while(pos>0)
	{
		bit1[pos]=min(bit1[pos],val);
		pos-=pos & -pos;
	}
}

void buildo(int pos,int val)
{
	int k=ceil(log2(n));
	k=pow(2,k);
	while(pos<k)
	{
		bit2[pos]=min(bit2[pos],val);
		if(pos==0)	break;
		pos+=pos & -pos;
	}
}


bool parent1(int p,int l)
{
	p-=p&-p;
	if(p>=l)	return true;
	return false;
}


bool parent2(int p,int r)
{
	p+=p&-p;
	if(p<=r)	return true;
	return false;
}

int min_query(int l,int r)
{
	int val=INT_MAX;
	int pos=r;
	//traverse in bit 1 lookup in bit2
	while(parent1(pos,l))	{val=min(val,bit2[pos]);pos-=pos&-pos;}
	//cout<<pos<<endl;
	pos=l;
	//traverse in bit2 looup in bit1
	while(parent2(pos,r))	{val=min(val,bit1[pos]);pos+=pos&-pos;}
	//cout<<pos<<endl;
	return min(val,v[pos-1]);
}

	
int main()
{
	cin>>n;
	forr(i,0,n)
	{
		int num;cin>>num;v.eb(num);
	}
	forr(i,0,n+1)	bit1.eb(INT_MAX);
	forr(i,0,n+1)	bit2.eb(INT_MAX);
	
	forr(i,0,n)	build(i,v[i]);
	cout<<"bit1\n";
	forr(i,1,n+1)	cout<<bit1[i]<<" ";
	cout<<"\n";
	
	for(int i=n;i>0;i--)	buildo(i,v[i-1]);
	cout<<"bit2\n";
	forr(i,1,n+1)		cout<<bit2[i]<<" ";
	cout<<"\n";	
	
	cout<<"enter the number of queries\n";
	int q;cin>>q;
	int l,r;
	forr(i,0,q)	
	{
		cin>>l>>r;
		cout<<min_query(l,r)<<endl;
	}
	
		
	return 0;
}
