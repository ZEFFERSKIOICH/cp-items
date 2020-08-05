//finding RMQ lazily
#include <bits/stdc++.h>
using namespace std;
#define forr(i,a,b) for(int i=a;i<b;i++)
#define eb emplace_back
#define mp make_pair
vector<int> v;
vector<pair<int,int>> lazy;
int n;
int l,r;

void build(int low,int high,int pos)
{
	if(low==high)	{lazy[pos].first=v[low];return;}	//leaf node
	int mid=(low+high)/2;
	build(low,mid,2*pos+1);	//left heap call;
	build(mid+1,high,2*pos+2);//right heap call
	lazy[pos].first=min(lazy[2*pos+1].first,lazy[pos*2+2].first);//f(x)
}

//start=starting & end=ending index of query
void update_lazy(int low,int high,int pos,int delta)
{

	if(low>high)	return; //leaf node exceeded
	if(lazy[pos].second!=0)
	{
		lazy[pos].first+=lazy[pos].second;
		if(low!=high)		//not a leaf node
		{
			lazy[2*pos+1].second+=lazy[pos].second;
			lazy[2*pos+2].second+=lazy[pos].second;
		}
		lazy[pos].second=0;
	}
	
	if(l>high || r<low)	return; //no overlap
	if(l<=low && r>=high)			//complete overlap
	{
		lazy[pos].first+=delta;
		if(low!=high)					//not a leaf node
		{
			lazy[2*pos+1].second+=delta;
			lazy[2*pos+2].second+=delta;
		}
		return;
	}
	
	//otherwise go for partial overlap(recur both left and right sides)
	int mid=(low+high)/2;
	update_lazy(low,mid,2*pos+1,delta);	//left heap call
	update_lazy(mid+1,high,2*pos+2,delta);	//right heap call
	lazy[pos].first=min(lazy[2*pos+1].first,lazy[pos*2+2].first);
}
	
int query_min(int low,int high,int pos)
{
	if(lazy[pos].second!=0)
	{
		lazy[pos].first+=lazy[pos].second;
		if(low!=high)		//not a leaf node
		{
			lazy[2*pos+1].second+=lazy[pos].second;
			lazy[2*pos+2].second+=lazy[pos].second;
		}
		lazy[pos].second=0;
	}
	
	if(low>high || low>r || high<l)	return INT_MAX;	//no overlap
	
	if(low>=l && high<=r)		return lazy[pos].first;//complete overlap
	
	int mid=(low+high)/2;
	return min(query_min(low,mid,2*pos+1),	//left heap
			   query_min(mid+1,high,2*pos+2));//right heap
}


int main()
{
	cin>>n;
	forr(i,0,n)	{int num;cin>>num;v.eb(num);}
	
	int m=(int)ceil(log2(n));
	int k=(int)pow(2,m)*2-1;
	forr(i,0,k+1)	lazy.eb(mp(0,0));	//inialisation
	build(0,n-1,0);
	cout<<endl;
	
	int u;printf("enter no. of updates\n");cin>>u;
	forr(i,0,u)	
	{
		int val;cin>>l>>r>>val;
		update_lazy(0,n-1,0,val);
	}
	
	int q;printf("enter the number of queries\n");cin>>q;
	forr(i,0,q)
	{
		cin>>l>>r;
		cout<<query_min(0,n-1,0)<<endl;
	}
	
	return 0;
}
