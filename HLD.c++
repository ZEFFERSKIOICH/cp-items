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
const ulli MOD=1e9+7;		
//heavy light decomposition
int n;
// depth size	head pos 
vector<int> depth,subtree_size,head,pos,heavy,parent,seg;
vector<bool> visited;
int cu_pos=0;

void dfs(int node,int level,vector<vector<int>> &edge)		//subtree_size  depth heavy
{
	subtree_size[node]=1;
	depth[node]=level;
	int maxi=INT_MIN;
	forr(i,0,edge[node].size())
	{
		if(edge[node][i]==parent[node])	continue;
		parent[edge[node][i]]=node;
		dfs(edge[node][i],level+1,edge);
		subtree_size[node]+=subtree_size[edge[node][i]];
		int val=subtree_size[edge[node][i]];
		if(maxi<val)
		{
			heavy[node]=edge[node][i];
            maxi=val;
		}
	}
}


void decompose(int node,int h,vector<vector<int>> &edge)
{
	head[node]=h;
	pos[node]=cu_pos++;
	
	if(heavy[node]!=-1)
	{
		decompose(heavy[node],h,edge);
	}
	
	forr(i,0,edge[node].size())
	{
		if(edge[node][i]!=parent[node] && edge[node][i]!=heavy[node])
		{
			decompose(edge[node][i],edge[node][i],edge);
		}
	}
	
}

int sumseg(int l,int r)
{
	l+=n;
	r+=n;
	int sum=0;
	while(l<=r)
	{
		if(l&1)		sum+=seg[l++];
		if(r%2==0)	sum+=seg[r--];
		l=l>>1;r=r>>1;
	}
	return sum;
}
	

int query(int l,int r)
{
	int ans=0;

	while(head[l]!=head[r])
	{
		if(depth[head[l]]>depth[head[r]])
		{
			ans+=sumseg(pos[head[l]],pos[l]);
			l=parent[head[l]];
		}
		else
		{
			ans+=sumseg(pos[head[r]],pos[r]);
			r=parent[head[r]];
		}
	}
	
	if(head[l]==head[r])
	{
		if(depth[l]>depth[r])
		{
			ans+=sumseg(pos[r],pos[l]);
		}
		else
		{
			ans+=sumseg(pos[l],pos[r]);
		}
	}
	return ans;
}
	
		

	
	
	
	
	
	

int main()
{
    //~ ios_base::sync_with_stdio(false);
    //~ cin.tie(NULL);
    //~ std::cout.precision(30);
  
	cout<<"enter number of nodes in the graph\n";
	cin>>n;

	depth=vector<int> (n+1,0);
	subtree_size=vector<int> (n+1,0);
	heavy=vector<int> (n+1,-1);
	head=vector<int> (n+1,-1);
	pos=vector<int> (n+1,-1);
	parent=vector<int> (n+1,-1);
	visited=vector<bool> (n+1,0);
	vector<vector<int>> edge(n+1);
	seg=vector<int> (2*n,0);
	forr(i,0,n-1)
	{
		int a,b;
		cin>>a>>b;
		edge[a].eb(b);
		edge[b].eb(a);
	}
	parent[1]=0;
	//~ cout<<"hey1\n";
	depth[1]=0;		//depth of root =0;
	dfs(1,0,edge);
	
	
	
	head[1]=1;		//head of root is root itself
	decompose(1,1,edge);
	for(int i=1;i<=n;i++)
	{
		seg[pos[i]+n]=i;
	}
	
	for(int i=n-1;i>0;i--)
	{
		seg[i]=seg[i<<1]+seg[i<<1|1];
	}
	cout<<"enter modification quereis\n";
	int modi;
	cin>>modi;
	while(modi--)
	{
		int node,val;
		cout<<"enter node and val\n";
		cin>>node>>val;
		int posq=pos[node]+n;
		seg[posq]=val;
		for(int i=posq;i>1;i=i>>1)
		{
			seg[i>>1]=seg[i]+seg[i^1];
		}
	}
		
		
	
	cout<<"enter number of queries\n";
	int q;cin>>q;
	while(q--)
	{
		int l,r;
		cin>>l>>r;
		cout<<query(l,r)<<"\n";
	}

	return 0;
}


