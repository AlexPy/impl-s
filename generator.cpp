#include <stdio.h>	
#include <stdlib.h>	
#include <vector>	
#include <map>
#include <set>
#include <algorithm> 	
#include <string>
#include <queue>
#include <iostream>
#include "generator.h"
#include<ctime>

#define threshold 2000000		//threshold of 2 seconds for reseting the seed for rand()
using namespace std;

//generates a random connected graph of 'n' nodes that does not contain
//.. loops, double edges and all edges have distinct weights

vector<Edge*> generateGraph(int n) {
	set<int> weights;
	vector<Edge*> graph;
	map<int, vector<Edge*> > g;
	for (int i = 0; i<n; i++) {
		g[i] = *(new vector<Edge*>());
	}
	if (n == 1) return graph;

	long long rtime;
	while (true) {
		//change seed if no valid edge was produced in more than 2 seconds (threshold)
		if ((timer() - rtime) > threshold) {
			rtime = timer();
		}
		int src = rand() % n;
		int dest = rand() % n;
		int weight = rand() % ((long)n*(long)n);

		Edge *edge = new Edge();
		edge->src = src;
		edge->dest = dest;
		edge->weight = -1;
		if (src == dest || contains(g, *edge) || contains(&weights, weight)) {
			continue;
		}
		edge->weight = weight;
		graph.insert(graph.end(), edge);
		g[src].insert(g[src].end(), edge);
		g[dest].insert(g[dest].end(), edge);
		weights.insert(weight);
		if (isConnected(g, n) && (graph.size() >= (n * 6)))
			break;

		rtime = timer();

	}

	return graph;
}
//checks if the graph (i.e. 'm') contains the edge 'val'
bool contains(map<int, vector<Edge*> > m, Edge val) {
	vector<Edge*>::iterator it;
	for (it = m[val.src].begin(); it != m[val.src].end(); it++) {
		if (edgeEquals(*it, &val))
			return true;
	}
	return false;
}
//checks if the set of weights (i.e. 'myset') contains the value 'val'
bool contains(set<int>* myset, int val) {
	return myset->find(val) != myset->end();
}
//checks if two edges are equal.
//Two edges are equal, if their endpoints are equal (unordered pairs of endpoints).
bool edgeEquals(Edge* e1, Edge* e2) {
	return (e1->src == e2->src && e1->dest == e2->dest) || (e1->src == e2->dest && e1->dest == e2->src);
}
//checks if the graph given as input is connected
bool isConnected(map<int, vector<Edge*> > g, int n) {
	bool *visited = new bool[n];
	for (int i = 0; i<n; i++) {
		visited[i] = false;
	}

	queue<int> q;
	q.push(0);
	visited[0] = true;
	int count = 1;
	while (!q.empty()) {
		int node = q.front();
		q.pop();
		vector<Edge*>::iterator it;
		for (it = g[node].begin(); it != g[node].end(); it++) {
			//neighbour index
			int index = (*it)->getOtherEndpoint(node);
			if (index == -1)
				printf("error!!");
			if (visited[index]) continue;
			q.push(index);
			visited[index] = true;
			count++;
		}
	}
	return count == n;
}
void print(vector<Edge*> g) {
	cout << "graph begin" << endl;
	vector<Edge*>::iterator it;
	for (it = g.begin(); it != g.end(); it++) {
		cout << (**it).src << " " << (**it).dest << " " << (**it).weight << endl;
	}
	cout << "graph end" << endl;
}
void print(set<int> s) {
	cout << "weights begin" << endl;
	set<int>::iterator it;
	for (it = s.begin(); it != s.end(); it++) {
		cout << (*it) << " ";
	}
	cout << endl;
	cout << "weights end" << endl;
}
void print(vector<int> s) {
	vector<int>::iterator it;
	for (it = s.begin(); it != s.end(); it++) {
		cout << (*it) << " ";
	}
	cout << endl;
}
