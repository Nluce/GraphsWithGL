#pragma once
#include "GraphNode.h"
#include <stack>
class Graph
{
	typedef std::vector<GraphNode*> NodeList;
public:
	Graph();
	Graph(unsigned int a_uiNodeCount)
	{
		for (int i = 0; i < a_uiNodeCount; i++){
			GraphNode* node = new GraphNode(i);
			AddNode(node);
		}

		for (int i = 0; i < a_uiNodeCount; i++){
			GraphNode* node1 = nodes[i];
			for (int k = 0; k < 2; k++){
				int j = rand() % a_uiNodeCount;
				GraphNode* node2 = nodes[j];

				if (node1 != node2) {
					if (!node1->IsNeighbor(node2)){
						ConnectNodes(node1, node2, 1.0f);
					}
				}

			}
		}
	}
	~Graph();
public:
	NodeList nodes;

public:
	void AddNode(GraphNode* node)
	{
		nodes.push_back(node);
	}

	void RemoveNode(GraphNode* nodeToRemove)
	{
		for (int i = 0; i < nodes.size(); i++)
		{
			GraphNode * node = nodes[i];

			for (int j = 0; j < node->edges.size(); j++)
			{
				Edge edge = node->edges[j];
				if (edge.end == node)
				{
					// this removes element j from the vector...
					node->edges.erase(node->edges.begin() + j);

					// backup one step, because we deleted one.
					j--;  
				}
			}
			if (node == nodeToRemove)
			{
				nodes.erase(nodes.begin() + i);
				i--;
			}

		}
	}

	void ResetVisited()
	{
		for (auto node : nodes){
			node->visited = false;
		}
	}

	bool SearchDFS(GraphNode* start, GraphNode* end)
	{
		ResetVisited();

		std::stack<GraphNode*> nodeStack;
		nodeStack.push(start);
		while (!nodeStack.empty())
		{
			//the rest of the algorithm goes in here
			GraphNode* current = nodeStack.top();
			nodeStack.pop();
			if (current->visited == true)
			{
				continue;
			}

			current->visited = true;

			if (current == end)
			{
				return true;
			}
			for (int i = 0; i < current->edges.size(); ++i)
			{
				nodeStack.push(current->edges[i].end);
			}
		}

		//return false if we didn't find a_pEnd
		return false;
	}

	int HowManyLinksBetween(GraphNode* start, GraphNode* end)
	{
		start->stepCount = 0;

		ResetVisited();

		std::stack<GraphNode*> nodeStack;
		nodeStack.push(start);
		while (!nodeStack.empty())
		{
			//the rest of the algorithm goes in here
			GraphNode* current = nodeStack.top();
			nodeStack.pop();
			if (current->visited == true)
			{
				continue;
			}

			current->visited = true;

			if (current == end)
			{
				return end->stepCount;
			}
			for (int i = 0; i < current->edges.size(); ++i)
			{
				GraphNode* nextNode = current->edges[i].end;
				if (!nextNode->visited)
				{
					nextNode->stepCount = current->stepCount + 1;
					nodeStack.push(nextNode);
				}
			}
		}

		//return -1 if we cant find a path
		return -1;
	}

	void ConnectNodes(GraphNode* nodeA, GraphNode* nodeB, float cost)
	{
		// this initializes the Edge struct with the start, end and cost.
		Edge edge = {
			nodeA,
			nodeB,
			cost
		};

		// the edge must be added to both nodes
		nodeA->AddEdge(edge);

		// for now only store the edge on the start node.
		//nodeB->AddEdge(edge);
	}

};

