
//seg tree construction is 1 based indexing 
//querying and updations are all 0 based indexing

#include <bits/stdc++.h>
using namespace std;
#define eb emplace_back
#define mp make_pair
#define hello cout<<"hello"<<"\n"
#define forr(i,a,b) for(int i=a;i<b;i++)
#define it(s)	for(auto itr:s)
#define dvg(s) 	for(auto itr:s)	cout<<itr<<" ";cout<<endl;
#define dbg(s)	cout<<#s<<"= "<<s<<endl;
typedef long long int lli;
typedef unsigned long long int ulli;
const int INF=INT_MAX;
const ulli MOD=1e6+3;
int n,m;
void build(vector<vector<int>>&seg)
{
	//~ O(n*m)
	forr(i,n,2*n)
	{
		for(int j=m-1;j>0;j--)
		{
			seg[i][j]=seg[i][j<<1]+seg[i][j<<1|1];
		}
	}
	
	//O(n*2*m)
	for(int i=n-1;i>0;i--)
	{
		for(int j=0;j<2*m;j++)
		{
			seg[i][j]=seg[i<<1][j]+seg[i<<1|1][j];
		}
	}
}


void update(vector<vector<int>> &seg,int posx,int posy,int val)
{
	//~ o(logn) rwo updates
	for(int j=posy;j>0;j=j>>1)
	{
		seg[posx][j>>1]=seg[posx][j]+seg[posx][j^1];
	}
	
	//o(logn)	col upadtes
	for(int i=posx;i>0;i=i>>1)
	{
		seg[i>>1][posy]=seg[i][posy]+seg[i^1][posy];
	}
	
	for(int i=posx;i>0;i=i>>1)
	{
		for(int j=posy;j>0;j=j>>1)
		{
			seg[i>>1][j>>1]=seg[i][j]+seg[i^1][j^1];
		}
	}
	
}


int query(vector<vector<int>> &seg,int rl,int cl,int rr,int cr)
{
	rl+=n;cl+=m;
	rr+=n;cr+=m;
	int sum=0;
	while(rl<=rr)
	{
		if(rl&1)
		{
			int a=cl;
			int b=cr;
			int s=0;
			while(a<=b)
			{
				if(a&1)	s+=seg[rl][a++];
				if(b%2==0)	s+=seg[rl][b--];
				a=a>>1;b=b>>1;
			}
			sum+=s;	
		}
		if(rr%2==0)
		{
			int a=cl;
			int b=cr;
			int s=0;
			while(a<=b)
			{
				if(a&1)	s+=seg[rr][a++];
				if(b%2==0)	s+=seg[rr][b--];
				a=a>>1;b=b>>1;
			}
			sum+=s;	
		}
		rl++;rr--;
		rl=rl>>1;rr=rr>>1;
	}
	return sum;
}

int main()
{
    //~ ios_base::sync_with_stdio(false);
    //~ cin.tie(NULL);
    std::cout.precision(30);
	
	cin>>n>>m;
	vector<vector<int>> seg(2*n,vector<int>(2*m,0));
	
	forr(i,n,2*n)
	{
		forr(j,m,2*m)
		{
			cin>>seg[i][j];
		}
	}
	
	
	build(seg);
	
	forr(i,1,2*n)
	{
		forr(j,1,2*m)
		{
			cout<<seg[i][j]<<" ";
		}
		cout<<"\n";
	}
	
	int u;
	cout<<"enter the number of updates\n";
	cin>>u;
	while(u--)
	{
		int posx,posy,val;
		cin>>posx>>posy>>val;
		
		posx+=n;
		posy+=m;
		seg[posx][posy]=val;
		update(seg,posx,posy,val);
	}
	
	int q;
	cout<<"enter query\n";
	cin>>q;
	while(q--)
	{
		int cl,cr,rl,rr;
		cin>>rl>>cr>>rr>>cr;
		
		cout<<query(seg,rl,cl,rr,cr)<<"\n";
	}
	
	return 0;
	
}
