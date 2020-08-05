#include <bits/stdc++.h>
using namespace std;
int n;
#define forr(i,a,b) for(int i=a;i<b;i++)
#define eb emplace_back
typedef long long int lli;
int a[100][100];
vector <int> v;
void build()
{
	for(int j=1;(1<<j)<=n;j++)
	{
		for(int i=0;i+(1<<j)<=n;i++)
			{
				a[i][j]=a[i][j-1]+a[i+(1<<(j-1))][j-1];
			}
	}
}

int sumquery(int low,int high)
{
		
	lli result=0;
	int l=log2(high-low+1);
	for(int j=l;j>=0;j--)
	{
		//printf("hi\n");
		if(low+(1<<j)-1<=high)
		{
			result+=a[low][j];
		}
		low+=(1<<j);
	}
	return result;
}

int main()
{
	cin >>n;
	forr(i,0,n)
	{
		int num;
		cin>>num;
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
			a[i][0]=v[i];
		}
		
		build();
		
		int q;
		cout<<"enter number of query\n";
		cin>>q;
		printf("enter limits of range\n");
		int left, right;
		cin >>left>>right;
		cout<<sumquery(left,right)<<endl;

	return 0;
}
