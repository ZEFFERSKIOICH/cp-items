#// coded by zeffy
#pragma GCC optimize("O3","unroll-loops","omit-frame-pointer","inline") //Optimization flags
#pragma GCC option("arch=native","tune=native","no-zeroupper") //Enable AVX
#pragma GCC target("avx","popcnt")  //Enable AVX
#include <x86intrin.h> //SSE Extensions
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
const lli INF=(lli)1e17+5;
const ulli MOD=1e8+7;
int n,q,gpos=0;
vector<int> ss,pos,head,depth,heavy,par;
vector<lli> v,seg;
vector<vector<int>> edge;
void init()
{
	ss=par=head=pos=depth=vector<int> (n+1,0);
	v=vector<lli> (n+1,0);
	seg=vector<lli> (4*n,0);
	heavy=vector<int> (n+1,-1);
	edge=vector<vector<int>> (n+1);
}

void dfs(int node=1,int lvl=0,int p=0)
{
	ss[node]=1;
	depth[node]=lvl+1;
	int maxi=0;
	for(int i:edge[node])
	{
		if(i==p) continue;
		dfs(i,lvl+1,node);
		par[i]=node;
		ss[node]+=ss[i];
		if(maxi<ss[i])
		{
			maxi=ss[i];
			heavy[node]=i;
		}
	}
}


void decompose(int node=1,int h=1)
{
	head[node]=h;	
	pos[node]=gpos++;
	if(heavy[node]!=-1)
	{
		decompose(heavy[node],h);
	}

	for(int i:edge[node])
	{
		if(i==par[node] || i==heavy[node]) continue;
		decompose(i,i);
	}
}

void build()
{
	forr(i,0,n)
	{
		seg[pos[i+1]+n]=v[i];
	}

	for(int i=n-1;i>0;i--)
	{
		seg[i]=seg[i<<1]+seg[i<<1|1];
	}
}


void update(int qpos,lli val)
{
	int npos=pos[qpos]+n;
	seg[npos]=val;
	for(int i=npos;i>1;i=i>>1)
	{
		seg[i>>1]=seg[i]+seg[i^1];
	}
}


lli segquery(int l,int r)
{
	l+=n;r+=n;
	lli sum=0;
	while(l<=r)
	{
		if(l&1) 	sum+=seg[l++];
		if(!(r&1))  sum+=seg[r--];
		l=l>>1;r=r>>1;
	}
	return sum;
}


lli query(int l,int r)
{
	lli sum=0;
	while(head[l]!=head[r])
	{
		if(depth[head[l]]>depth[head[r]])
		{
			sum+=segquery(pos[head[l]],pos[l]);
			l=par[head[l]];
		}
		else
		{
			sum+=segquery(pos[head[r]],pos[r]);
			r=par[head[r]];
		}
	}

	if(head[l]==head[r])
	{
		if(pos[l]>pos[r])
		{
			sum+=segquery(pos[r],pos[l]);
		}
		else
		{
			sum+=segquery(pos[l],pos[r]);
		}
	}

	return sum;
}






int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    std::cout<< std::fixed;
    std::cout.precision(6);
    
	cin>>n>>q;
	init();
	forr(i,0,n) cin>>v[i];
	forr(i,1,n)
	{
		int a,b;
		cin>>a>>b;
		edge[a].eb(b);
		edge[b].eb(a);
	}

	dfs();
	decompose();
	build();

	while(q--)
	{
		int ch;
		cin>>ch;
		if(ch==1)
		{
			int qpos;lli val;
			cin>>qpos>>val;
			update(qpos,val);
		}
		else
		{
			int l,r;cin>>l>>r;
			cout<<query(l,r)<<"\n";
		}
	}
    return 0;
}

