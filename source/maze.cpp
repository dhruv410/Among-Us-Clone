// #include "maze.h"
// #include <iostream>
// #include <fstream>
// using namespace std;
// typedef long long ll;
// bool vis[100][100];
// stack <ll> s;
// int fl = 0;
// void dfs(ll x, ll y, ll sz)
// {

// 	vis[x][y] = true;
// 	if(x==sz-1&&y==sz-1)
// 	{
// 		fl = 1;
// 		return ;
// 	}
// 	int f1,f2,f3,f4;
// 	f1 = f2 = f3 = f4 = 0;
// 	while(true)
// 	{
// 		int r = (rand())%4;
// 		if(x==0||vis[x-2][y]==true)
// 			f1 = 1;
// 		if(y==0||vis[x][y-2]==true)
// 			f2 = 1;
// 		if(x==sz-1||vis[x+2][y]==true)
// 			f3 = 1;
// 		if(y==sz-1||vis[x][y+2]==true)
// 			f4 = 1;
// 		if(fl)
// 			return ;
// 		if(x!=0&&r==0&&vis[x-2][y]==false)
// 		{
// 			vis[x-1][y] = true;
// 			dfs(x-2, y, sz);
// 			f1 = 1;
// 		}
// 		if(y!=0&&r==1&&vis[x][y-2]==false)
// 		{
// 			vis[x][y-1] = true;
// 			dfs(x, y-2, sz);
// 			f2 = 1;
// 		}
// 		if(x!=sz-1&&r==2&&vis[x+2][y]==false)
// 		{
// 			vis[x+1][y] = true;
// 			dfs(x+2, y, sz);
// 			f3 = 1;
// 		}
// 		if(y!=sz-1&&r==3&&vis[x][y+2]==false)
// 		{
// 			vis[x][y+1] = true;
// 			dfs(x, y+2, sz);
// 			f4 = 1;
// 		}
// 		if(f1+f2+f3+f4==4)
// 			break;
// 	}
// }
// void maze(int n )
// {
// 	srand(time(0));
// 	// ll n;
// 	// cin>>n;
// 	// n = 10;
// 	ll sz = 2*n-1;
// 	ll ar[sz+2][sz+2];
// 	for(int i=0;i<sz;i++)
// 	{
// 		for(int j=0;j<sz;j++)
// 		{
// 			ar[i][j] = 1;
// 			vis[i][j] = false;
// 		}
// 	}
// 	ar[0][0] = 0;
// 	ar[sz-1][sz-1] = 2;
// 	fl = 0;
// 	dfs(0, 0, sz);
// }