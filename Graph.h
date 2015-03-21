#pragma once
#include "GraphNode.h"
#include <stack>
#include <math.h>
#include <set>
#include <glm/glm.hpp>

class Graph
{
	typedef std::vector<GraphNode*> NodeList;
public:
	Graph();
	Graph(int a_uiNodeCount)
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
		if (node != nullptr){
			nodes.push_back(node);
		}
	}

	void RemoveNode(GraphNode* nodeToRemove)
	{
		if (nodeToRemove == nullptr)
		{
			return;
		}
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

	GraphNode* FindClosestNode(glm::ivec2 position) const
	{
		float closestDistance = 1000000;
		GraphNode * closestNode = nullptr;
		for (auto node : nodes)
		{
			float distance = node->distanceTo(position);
			if (distance < closestDistance)
			{
				closestDistance = distance;
				closestNode = node;
			}
		}
		return closestNode;
	}



	bool conpareGScores(GraphNode * left, GraphNode * right)
	{
		return left->gScore < right->gScore;
	}

	vector<GraphNode *> FindPath(GraphNode * start, GraphNode * end)
	{
		vector<GraphNode *> path;
		set<GraphNode *> queue;

		for (auto node : nodes){
			node->n = nullptr;
			node->gScore = INFINITY;
		}

		queue.insert(start);
		start->n = start;
		start->gScore = 0;


		while (!queue.empty())
		{
			auto current = queue.erase(queue.rbegin());
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
		if (start == nullptr || end == nullptr)
		{
			return false;
		}
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
		if (start == nullptr || end == nullptr)
		{
			return -1;
		}
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
		if (nodeA == nullptr || nodeB == nullptr) {
			return;
		}
		// this initializes the Edge struct with the start, end and cost.
		Edge edge = {
			nodeB,
			cost
		};
		nodeA->AddEdge(edge);
	}

};

