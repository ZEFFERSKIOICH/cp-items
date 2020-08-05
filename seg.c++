#include <bits/stdc++.h>
using namespace std;
#define forr(i,a,b) for(int i=a;i<b;i++)
#define eb emplace_back
typedef long long int lli;
int n;vector<lli> v;

void build()
{
	for(int i=n-1;i>0;i--)	v[i]=v[i<<1]+v[i<<1|1];
}

void update(int pos)
{
	for(int i=pos;i>1;i=i>>1)	v[i>>1]=v[i]+v[i^1];
}

lli query(int l,int r)
{
	int s=0;
	while(l<=r)
	{if(l%2==1)	s+=v[l++];
	 if(r%2==0) s+=v[r--];
	 l=l>>1;r=r>>1;
	}
	return s;
}
		

int main()
{
	cin >>n;
	forr(i,0,2*n)	v.eb(0);
	for(int i=n;i<v.size();i++)	{cin>>v[i];}
	build();
	int u,pos,val;
	cin>>u; 
	forr(i,0,u)	
	{cin>>pos>>val;
	 pos+=n;v[pos]=val;
	 update(pos);}
	 
	 
	 forr(i,0,v.size())	cout<<v[i]<<" ";
	 int q,l,r;cin>>q;
	 forr(i,0,q)		{cin>>l>>r;l+=n;r+=n;cout<<query(l,r)<<endl;}
	 
	return 0;
}


	
