/*
 * verifier.cpp
 *
 *  Created on: Feb 15, 2014
 *      Author: arjunlal
 */

#include<iostream>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

int main(int argc, char *argv[])
{
	ifstream f1;
	ifstream f2;
	f1.open(argv[1]);
	f2.open(argv[2]);

	string X,Y;
	char ch1,ch2;

	while(!f1.eof())
	{
		f1>>ch1;
		f2>>ch2;

		if(ch1!=ch2)
		{
			cout<<"not matching "<<ch1<<" "<<ch2<<"\n";
			exit(0);
		}
	}
	cout<<"Matched\n";
}



