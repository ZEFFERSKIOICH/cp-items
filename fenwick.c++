#include <bits/stdc++.h>
using namespace std;
#define forr(i,a,b) for(int i=a;i<b;i++)
#define eb emplace_back
int n;
vector<int> v;
vector<int> bit;
void build(int pos,int val)
{
	pos++;
	while(pos<=n)	{bit[pos]+=val;pos+=pos & (-pos);}
}

int bitsum(int pos)
{
	int s=0;
	while(pos>0)	{s+=bit[pos];pos-=pos & (-pos);}
	return s;
}


int main()
{
	
	cin>>n;
	forr(i,0,n)	{int num;cin>>num;v.eb(num);}
	forr(i,0,n+1)	bit.eb(0);
	forr(i,0,n)	build(i,v[i]);
	
	forr(i,1,n+1)	cout<<bit[i]<<" ";
	printf("\n");
	printf("enter elements for update\n");
	int u;cin>>u;
	forr(i,0,u)
	{printf("enter element and index of updation\n");
	 int pos,ele;
	 cin>>ele>>pos;
	 ele=ele-bit[pos];
	 pos--;
	 build(pos,ele);
    }
	
	cout<<"enter queries\n";
	int q;cin>>q;
	forr(i,0,q)		
	{
		cout<<"enter limits";
		int l,r;cin>>l>>r;
		cout<<bitsum(r)-bitsum(l-1)<<endl;
	}
	forr(i,1,n+1)	cout<<bit[i]<<" ";
	printf("\n");
	
	return 0;
}
