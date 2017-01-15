//Game of life - CILK
//Author - arjunlal.b@gmail.com

#include<cstdlib>
#include<iostream>
#include<vector>
#include<stdlib.h>
#include<stdio.h>
#include <cilk/cilk.h>
#include "cilktime.h"

#define ROWS 10000
#define COLS 10000
#define MAXGEN 10000

using namespace std;

int liveNeighbors(vector<vector <int> > &cGen, long int i, long int j)
{
	int l=0;

	//left top corner condition
	if( i == 0 && j ==0 )
	{
		if( cGen[0][1] )
			l++;
		if( cGen[1][0] )
			l++;
		if( cGen[1][1] )
			l++;
		return l;
	}

	//right top corner condition
	if( i == 0 && j == COLS-1 )
	{
		if( cGen[0][COLS-2] )
			l++;
		if( cGen[1][COLS-2] )
			l++;
		if( cGen[1][COLS-1] )
			l++;
		return l;
	}

	//left bottom corner condition
	if( i == ROWS-1 && j == 0 )
	{
		if( cGen[ROWS-1][1] )
			l++;
		if( cGen[ROWS-2][0] )
			l++;
		if( cGen[ROWS-2][1] )
			l++;
		return l;
	}

	//right bottom corner condition
	if( i == ROWS-1 && j == COLS-1 )
	{
		if( cGen[ROWS-1][COLS-2] )
			l++;
		if( cGen[ROWS-2][COLS-2] )
			l++;
		if( cGen[ROWS-2][COLS-1] )
			l++;
		return l;
	}

	//top row except 0,0 and 0,COLS-1
	if( i == 0 )
	{
		if( cGen[0][j-1] )
			l++;
		if( cGen[0][j+1] )
			l++;
		if( cGen[1][j-1] )
			l++;
		if( cGen[1][j] )
			l++;
		if( cGen[1][j+1] )
			l++;
		return l;
	}

	//left column except 0,0 and ROWS-1,0
	if( j == 0 )
	{
		if( cGen[i-1][0] )
			l++;
		if( cGen[i-1][1] )
			l++;
		if( cGen[i][1] )
			l++;
		if( cGen[i+1][1] )
			l++;
		if( cGen[i+1][0] )
			l++;
		return l;
	}

	//bottom row except ROWS-1,0 and ROWS-1,COLS-1
	if( i == ROWS-1 )
	{
		if( cGen[i][j-1] )
			l++;
		if( cGen[i][j+1] )
			l++;
		if( cGen[i-1][j-1] )
			l++;
		if( cGen[i-1][j] )
			l++;
		if( cGen[i-1][j+1] )
			l++;
		return l;
	}

	//right colum except 0,COLS-1 and ROWS-1,COLS-1
	if( j == COLS-1 )
	{
		if( cGen[i-1][j-1] )
			l++;
		if( cGen[i][j-1] )
			l++;
		if( cGen[i+1][j-1] )
			l++;
		if( cGen[i-1][j] )
			l++;
		if( cGen[i+1][j] )
			l++;
		return l;
	}

	l=0;

	if( cGen[i-1][j-1] )
		l++;
	if( cGen[i-1][j] )
		l++;
	if( cGen[i-1][j+1] )
		l++;
	if( cGen[i][j-1] )
		l++;
	if( cGen[i][j+1] )
		l++;
	if( cGen[i+1][j-1] )
		l++;
	if( cGen[i+1][j] )
		l++;
	if( cGen[i+1][j+1] )
		l++;

	return l;
}

void transform(vector<vector <int> > &cGen, vector<vector <int> > &nGen )
{
	cilk_for(int i=0; i < ROWS; i++)
	{
		for(int j=0; j < COLS; j++)
		{
			int liveNcount = liveNeighbors( cGen, i, j );

			if( cGen[i][j] )
			{
				if( liveNcount < 2 )
				{
					nGen[i][j] = 0;
				}
				else if( liveNcount == 2 || liveNcount == 3 )
				{
					nGen[i][j] = 1;
				}
				else
				{
					nGen[i][j] = 0;
				}
			}
			else
			{
				if( liveNcount == 3 )
				{
					nGen[i][j] = 1;
				}
				else
				{
					nGen[i][j] = 0;
				}
			}
		}
	}
}

void print(vector<vector <int> > &matrix )
{
	for (int i=0; i < ROWS; i++)
	{
		for(int j=0;j < COLS; j++)
		{
			cout<<matrix[i][j]<<" ";
		}
		cout<<"\n";
	}
}

int main(int argc, char *argv[])
{

	int i, j, gen;

	vector<vector<int> > currentGen(ROWS, vector<int>(COLS));
	vector<vector<int> > nextGen(ROWS, vector<int>(COLS));

	for( i=0; i < ROWS; i++ )
	{
		for( j=0; j < COLS; j++ )
		{
			cin>>currentGen[i][j];
		}
	}

	cin>>gen;

	//static struct timeval t,start_time;
	//gettimeofday(&start_time,NULL);

	if( gen <= MAXGEN && gen >= 0 )
	{
		for( i=0; i < gen; i++)
		{
			transform( currentGen, nextGen );

			currentGen=nextGen;

			cilk_for( int i = 0; i < ROWS; i++ )
			{
				for( int j = 0; j < COLS; j++ )
				{
					nextGen[i][j] = 0;
				}
			}
		}
	}
	else
	{
		cout<<"No of generations given should be >= 0 and <= 10000"<<endl;
	}

	//gettimeofday(&t,NULL);

	//long long int totalTime=(t.tv_sec-start_time.tv_sec)*1000000 + (t.tv_usec-start_time.tv_usec);

	//cout<<"Game of Life for "<<gen<<" generations took "<<totalTime<<" microseconds\n";

	print( currentGen );

	return 0;
}
