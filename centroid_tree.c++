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
int n;
vector<bool> visited;
vector<int> parent,ss,mark_centroid,centroid_tree,depth;
void init()
{
	visited=vector<bool>(n+1,false);
	depth=mark_centroid=ss=parent=vector<int> (n+1,0);	
}
void refresh()
{
	ss.clear();
	visited.clear();
	ss=vector<int> (n+1,0);
	visited=vector<bool> (n+1,0);
}

void dfs(int node,vector<vector<int>> &edge)
{
	if(mark_centroid[node])		visited[node]=true;
	
	if(visited[node])	return;
	
	visited[node]=true;
	
	ss[node]=1;
	
	for(int i:edge[node])
	{
		if(visited[i])	continue;
		dfs(i,edge);
		ss[node]+=ss[i];
	}
}
	
int get_centroid(int node,vector<vector<int>> &edge)
{
	bool flag=true;int tot=0;
	for(int i:edge[node])
	{
		tot+=ss[i];
	}
	
	int next_node=-1;
	for(int i:edge[node])
	{
		if(ss[i]>n/2)
		{
			flag=false;
			next_node=i;
			ss[node]=tot-ss[i]+1;
			break;
		}
	}
	
	if(flag)	return node;
	else 		get_centroid(next_node,edge);
}

	
	
		
		
		

void next_centroid(int node,int level,vector<vector<int>> &edge)
{
	refresh();
	dfs(node,edge);
	
	int new_node=get_centroid(node,edge);
	centroid_tree.eb(new_node);
	mark_centroid[new_node]=1;
	depth[new_node]=level;
	
	for(int i:edge[new_node])
	{
		if(mark_centroid[i])	continue;
		parent[i]=node;
		next_centroid(i,level+1,edge);
	}
}


int main()
{
    //~ ios_base::sync_with_stdio(false);
    //~ cin.tie(NULL);
    //~ std::cout.precision(30);
  
	cin>>n;
	init();
	vector<vector<int>> edge(n+1);
	forr(i,0,n-1)
	{
		int a,b;
		cin>>a>>b;
		edge[a].eb(b);
		edge[b].eb(a);
	}
	hello;
	init();
	next_centroid(1,0,edge);
		
	forr(i,0,centroid_tree.size())
	{
		cout<<centroid_tree[i]<<" ";
	}
	

	return 0;
}


