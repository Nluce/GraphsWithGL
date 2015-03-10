#pragma once
#include <string>
#include "GraphNode.h"
#include "Edge.h"
#include <vector>
#include <iostream>

using namespace std;

class GraphNode
{
	typedef std::vector<Edge> EdgeList;
public:
	int nodeNumber;
	
	EdgeList edges;
	bool visited;
	int stepCount;

	GraphNode(int num)
	{
		nodeNumber = num;
	}


	void AddEdge(const Edge & edge)
	{
		edges.push_back(edge);
	}

	void PrintNeighbors()
	{
		cout << "Neighbors of node " << nodeNumber << ":" << endl;
		for (Edge edge : edges){
			cout << " node " << edge.end->nodeNumber << endl;
		}
	}

	bool GoesTo(GraphNode * otherNode)
	{
		for (Edge edge : edges)
		{
			if (edge.end == otherNode)
			{
				return true;
			}
		}
		return false;
	}


	bool IsNeighbor(GraphNode * otherNode)
	{
		return otherNode->GoesTo(this) || this->GoesTo(otherNode);
	}

};
