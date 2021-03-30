#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <time.h>
#include <vector>
	
#include <ctime>
	
	
#define MAX 1000
	using namespace std;
	
	int main()
	{
		srand(time(NULL));
		vector<vector<int> > mat1(MAX,vector<int>(MAX,0));
		vector<vector<int> > mat2(MAX,vector<int>(MAX,0));
		vector<vector<int> > mat3(MAX,vector<int>(MAX,0));
		for(int i=0;i<MAX;i++)
		{
			for(int j=0;j<MAX;j++)
			{
				mat1[i][j] = rand()%100;
			}
		}
		
		for(int i=0;i<MAX;i++)
		{
			for(int j=0;j<MAX;j++)
			{
				mat2[i][j] = rand()%100;
				mat3[i][j] =0;
			}
		}
		int bloque = MAX/4;
		auto start = std::chrono::system_clock::now();
		for(int ib=0;ib<MAX;ib+=bloque)
		{
			for(int jb =0;jb<MAX;jb+=bloque)
			{
				for(int kb=0;kb<MAX;kb+=bloque)
				{
					for(int i = ib;i<ib+bloque;i++)
					{
						for(int j=jb;j<ib+bloque;j++)
						{
							for(int k=kb;k<kb+bloque;k++)
							{
								mat3[i][j] += mat1[i][k]*mat2[k][j];
							}
						}
						
					}
				}
			}
		}
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<float,std::milli> duration = end -start;
		cout<<duration.count()<<" ms"<<endl;
	}
	
	
	
	
	
	
	
	
	
