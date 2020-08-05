//finding rmq in o(1) time preprocessing o(log n)
#include <bits/stdc++.h>
using namespace std;
int n;
vector<int>v;
int a[100][100];
#define forr(i,a,b) for(int i=a;i<b;i++)
#define eb emplace_back

void build()
{
	for(int j=1;(int)pow(2,j)<n;j++)
	{
		for(int i=0;(int)pow(2,j-1)+i<n;i++)
		{
			if(v[a[i][j-1]]<v[a[i+(int)pow(2,j-1)][j-1]])
			{
				a[i][j]=a[i][j-1];
			}
			else
			{
				a[i][j]=a[i+(int)pow(2,j-1)][j-1];
			}
		}
	}
}

int querymin(int low,int high)
{
	int l=high-low+1;
	int k=log2(l);
	return(min(v[a[low][k]],v[a[low+l-(int)pow(2,k)][k]]));
}
int main()
{
	cin >>n;
	forr(i,0,n)
	{
		int num;
		cin >>num;
		v.eb(num);
	}
	
	forr(i,0,100)
	{
		forr(j,0,100)
		{
			a[i][j]=0;
		}
	}
	
	forr(i,0,n)
	{
		a[i][0]=i;
	}
	
	build();
	
	cout<<"enter range\n";
	int low,high;
	cin >>low>>high;
	cout<<querymin(low,high)<<endl;
	return 0;
}
	
	
	
	
