#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <ctime>
#include <algorithm>


#include <vector>
#define MAX 1000
using namespace std;

int main()
{
	srand(time(NULL));
	//int mat1[MAX][MAX];
	vector<vector<int> > mat1(MAX,vector<int>(MAX,0));
	for(int i =0;i<MAX;i++)
	{
		for(int j=0;j<MAX;j++)
		{
			mat1[i][j] = rand()%100;
		}
	}

	vector<vector<int> > mat2(MAX,vector<int>(MAX,0));
	vector<vector<int> > mat3(MAX,vector<int>(MAX,0));
	for(int i=0;i<MAX;i++)
	{
		for(int j=0;j<MAX;j++)
		{
			mat2[i][j] = rand()%100;
			mat3[i][j] = 0;
		}
	}
	auto start = std::chrono::system_clock::now();
	for(int i=0;i<MAX;i++)
	{
		for(int j=0;j<MAX;j++)
		{
			for(int k = 0;k<MAX;k++)
			{
				mat3[i][j] += (mat1[i][k]) * (mat2[k][j]);
			}
		}
	}
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<float,std::milli> duration = end -start;
	cout<<duration.count()<<"ms"<<endl;
}
