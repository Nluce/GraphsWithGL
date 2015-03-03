#include "Graph.h"
#include <iostream>
#include <stdio.h>

using namespace std;


void CheckLinks(Graph graph)
{



	cout << "There are " << graph.nodes.size() << " nodes in the graph." << endl;

	cout << "Which node is the start" << endl;
	int startNodeNumber;
	cin >> startNodeNumber;

	cout << "Which node is the end" << endl;
	int endNodeNumber;
	cin >> endNodeNumber;

	GraphNode * start = graph.nodes[startNodeNumber];
	GraphNode * end = graph.nodes[endNodeNumber];

	if (graph.SearchDFS(start, end)){
		int links = graph.HowManyLinksBetween(start, end);
		cout << "There are " << links << " link(s) between those nodes" << endl;
	}
	else {
		cout << "those nodes are not connected " << endl;
	}

}

void UserGuidedWalk(Graph graph)
{

	int graphSize = graph.nodes.size();

	int i = rand() % graphSize;
	GraphNode * node = graph.nodes[i];
	bool stop = false;
	do {
		cout << endl << "you are at this node... " << endl;

		node->PrintNeighbors();

		cout << "Which node do you want to go to? (enter -1 to stop) " << endl;
		int newNodeNumber;
		cin >> newNodeNumber;

		if (newNodeNumber == -1){
			stop = true;
		}
		else
			if (newNodeNumber < 0 || newNodeNumber >= graphSize)
			{
				cout << "bad node number" << endl;
			}
			else {
				GraphNode * node2 = graph.nodes[newNodeNumber];
				if (node->IsNeighbor(node2)){
					node = node2;
				}
				else {
					cout << "nodes are not neighbors" << endl;
				}
			}

	} while (!stop);

}

int main(int argc, char ** argv)
{
	int graphSize;

	// create a graph
	cout << "Please enter the number of nodes in the graph" << endl;
	cin >> graphSize;

	Graph graph1 = Graph(graphSize);


	//UserGuidedWalk(graph1);
	CheckLinks(graph1);
	

	// code goes here
	system("pause");
	return 0;
}