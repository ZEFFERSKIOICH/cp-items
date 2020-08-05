#include <bits/stdc++.h>
using namespace std;
vector<int> v;
vector<pair<int,int>> lazy;
#define eb emplace_back
#define mp make_pair
int n,l,r;
void build(int low,int high,int pos)
{
	if(low>high)	return ;
	if(low==high)		//leaf node reached
	{lazy[pos].first=v[low];return;}
	
	int mid=(low+high)/2;
	build(low,mid,2*pos+1);		//making the left heap call
	build(mid+1,high,2*pos+2);	//making the right heap call
	lazy[pos].first=lazy[2*pos+1].first+lazy[2*pos+2].first;
}



void lazy_update(int low,int high,int pos,int val)
{
	if(low>high) 	return;		//leaf node exceeded
	if(lazy[pos].second!=0)
	{
		lazy[pos].first+=(high-low+1)*lazy[pos].second;
		if(low<high)		//not yet reached the leaf node
		{
			lazy[2*pos+1].second+=lazy[pos].second;
			lazy[2*pos+2].second+=lazy[pos].second;
		}
		lazy[pos].second=0;
	}
	
	if(low>r || high<l || low>high)	return; 	//no overlap
	if(low>=l && high<=r)			//complete overlap
	{
		lazy[pos].first+=(high-low+1)*val;
		if(low<high)	
		{
			lazy[2*pos+1].second+=val;
			lazy[2*pos+2].second+=val;
		}
		return;
	}
	//cout<<"hye01"<<endl;
	int mid=(low+high)/2;
	lazy_update(low,mid,2*pos+1,val);
	lazy_update(mid+1,high,2*pos+2,val);
	lazy[pos].first=lazy[2*pos+1].first+lazy[2*pos+2].first;
}


int query(int low,int high,int pos)
{
	if(lazy[pos].second!=0)
	{
		lazy[pos].first+=(high-low+1)*lazy[pos].second;
		if(low<high)
		{
			lazy[2*pos+1].second+=lazy[pos].second;
			lazy[2*pos+2].second+=lazy[pos].second;
		}
		lazy[pos].second=0;
	}
	if(low>r || high<l || low>high)	return 0;	// no overlap
	 
	if(low>=l && high<=r)	return lazy[pos].first;			//complete overlap
	//case of partial overlap recur either sides
	int mid=(low+high)/2;
	long long s0=query(low,mid,2*pos+1);
	long long s1=query(mid+1,high,2*pos+2);
	return (s0+s1);
}
	
	
int main()
{
	cin>>n;
	
	for(int i=0;i<n;i++)	{int num;cin>>num;v.eb(num);}
	int z=(int)ceil(log2(n));
	z=(1<<z)*2-1;
	cout<<"z="<<z<<endl;
	for(int i=0;i<z;i++)	lazy.eb(mp(0,0));
	build(0,n-1,0);
	cout<<"heyy1"<<endl;
	
	cout<<"enter the range for  update and the val"<<endl;
	int val;cin>>l>>r>>val;
	lazy_update(0,n-1,0,val);
	cout<<"hey2"<<endl;
	
	cout<<"enter the query range\n";
	cin>>l>>r;
	cout<<query(0,n-1,0)<<endl;
	
	for(int i=0;i<z;i++)		cout<<lazy[i].first<<" ";
	cout<<endl;
	for(int i=0;i<z;i++)		cout<<lazy[i].second<<" ";
	return 0;
}

