//seg trees use 0 based indxing when querying
#include <bits/stdc++.h>
using namespace std;
#define eb emplace_back
#define forr(i,a,b) for(int i=a;i<b;i++)
int n;
vector <int> v;

void update(int pos,int val)
{
	pos+=n;
	v[pos]=val;
	for(int i=pos;i>1;i=i>>1)	v[i>>1]=min(v[i],v[i^1]);
}

int query_min(int l,int r)
{
	l+=n;r+=n;
	int mini=INT_MAX;
	while(l<=r)
	{
		if(l%2==1)	mini=min(mini,v[l++]);
		if(r%2==0)	mini=min(mini,v[r--]);
		l=l>>1;r=r>>1;
	}
	return mini;
}

		
int main()
{
	cin>>n;
	forr(i,0,2*n)	v.eb(0);
	forr(i,n,2*n)	cin>>v[i];
	for(int i=n-1;i>0;i--)	v[i]=min(v[i<<1],v[i<<1|1]);
	forr(i,1,v.size())	cout<<v[i]<<" ";
	cout<<endl;
	
	cout<<"enter the number of updates\n";
	int u;cin>>u;
	forr(i,0,u)
	{
		cout<<"enter pos and val\n";
		int pos,val;cin>>pos>>val;
		update(pos,val);
	}
	
	forr(i,1,v.size())	cout<<v[i]<<" ";
	cout<<endl;
	
	cout<<"enter  number of query\n";
	int q;cin>>q;
	forr(i,0,q)	
	{
		int l,r;cin>>l>>r;
		cout<<query_min(l,r)<<endl;
	}
}
		
