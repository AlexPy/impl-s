#pragma once
#ifndef GRAPH_GEN_HPP
#define GRAPH_GEN_HPP

#include <stdio.h>
#include<iostream>
#include<omp.h>
#include<vector>
#include<algorithm>
#include<set>
#include<omp.h>

using namespace std;

// Структура, представляющая ребро графа
struct Edge
{
	int src;	//one endpoint
	int dest;	//other endpoint
	int weight;	//weight
	bool inserted = false;
	int getOtherEndpoint(int endpoint) {
		return src == endpoint ? dest : (dest == endpoint ? src : -1);	
	}
};

#endif