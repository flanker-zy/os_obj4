#pragma once
#include<iostream>
#include<fstream>
using namespace std;

struct work {
	char name = 'A';
	int size = 0;
};

struct queue {
	int size = 0;
	char name[10] = {'A'};
	int n = 0;
};