#include <bits/stdc++.h>
using namespace std;
#define eb emplace_back
#define forr(i,a,b) for(int i=a;i<b;i++)
int n;
vector<int> v;
void build()
{for(int i=n-1;i>0;i--)	v[i]=min(v[i<<1],v[i<<1|1]);}

void update(int pos)
{for(int i=pos;i>1;i=i>>1)	v[i>>1]=min(v[i],v[i^1]);}

int query(int l,int r)
{
	int mini=INT_MAX;
	while(l<=r)
	{if(l%2==1)		mini=min(mini,v[l++]);
	 if(r%2==0)		mini=min(mini,v[r--]);
	 l=l>>1;r=r>>1;
	}
	return mini;
}
		
	
int main()
{
	cin>>n;
	forr(i,0,2*n)	v.eb(0);
	forr(i,n,v.size())	cin>>v[i];
	build();
	
	int u,val,pos;cin>>u;
	forr(i,0,u)	{cin>>val>>pos;pos+=n;
	v[pos]=val;update(pos);}
	
	
	int q,l,r;cin>>q;
	forr(i,0,q)		{cin>>l>>r;l+=n;r+=n;
	cout<<query(l,r)<<endl;}
	return 0;
}
