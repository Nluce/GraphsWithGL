#pragma once
#include "GraphNode.h"
#include <stack>
#include <math.h>
#include <set>
#include <glm/glm.hpp>

// This class repersents the entrie graph, It holds a list of all the nodes
// This class has methods for adding and removing nodes.
// It has A* path search
// It has methods for searching for nodes.
// It has depth first search


class Graph
{
	typedef std::vector<GraphNode*> NodeList;
public:
	Graph();
	//This constructor was for testing. It creates a set ammount of randomly connected nodes.
	Graph(int a_uiNodeCount)
	{
		//add blank nodes to the graph
		for (int i = 0; i < a_uiNodeCount; i++)
		{
			GraphNode* node = new GraphNode(i);
			AddNode(node);
		}
		//This connects random nodes
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
	//This is the list that holds the nodes.
	NodeList nodes;

public:
	//This adds a node to the end of the list.
	void AddNode(GraphNode* node)
	{
		if (node != nullptr){
			nodes.push_back(node);
		}
	}

	//This Removes a node. also removes any connected edges.
	void RemoveNode(GraphNode* nodeToRemove)
	{
		if (nodeToRemove == nullptr)
		{
			return;
		}
		//search all the nodes looking for connected edges.
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
			//remove the actuall node from the node list.
			if (node == nodeToRemove)
			{
				nodes.erase(nodes.begin() + i);
				i--;
			}

		}
	}

	//Find the node closest to a position
	GraphNode* FindClosestNode(glm::ivec2 position) const
	{
		float closestDistance = FLT_MAX;
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

	GraphNode* GetNodeAtPosition(glm::ivec2 position) const
	{
		//Returns node at a position
		for (auto node : nodes){
			if (node->position == position) {
				return node;
			}
		}

		return nullptr;
	}
	//Flip order of nodes
	vector<GraphNode *> ReverseOrder(vector<GraphNode *> in)
		
	{
		auto size = in.size();
		vector<GraphNode *> out;

		for (int i = 0; i < size; i++){
			out.push_back(in[size - i - 1]);
		}

		return out;
	}

	//This is used by the searching algorythm
	GraphNode * GetNodeWithLowestFScore()
	{
		GraphNode * out = nullptr;
		for (auto node : nodes){
			if (node->inOpenSet){
				if (out == nullptr || node->fScore < out->fScore){
					out = node;
				}
			}
		}
		return out;
	}

	//This is the A* searching algorythm
	//It tries to find the shortest path between the start and the goal.
	//It determens what node to search first by calculating the nodes distance to the goal.
	//start: This is the node to start from.
	//Goal: This is the node to attempt to find a path to.
	//Returns: the path from start to goal as a vector of nodes.d
	vector<GraphNode *> AStar(GraphNode * start, GraphNode * goal)
	{
		vector<GraphNode *> out;

		set<GraphNode *> queue;
		//reset all the scores on all the nodes
		for (auto node : nodes)
		{
			node->cameFrom = nullptr;
			node->gScore = INFINITY;
			node->fScore = INFINITY;
			node->inClosedSet = false;
			node->inOpenSet = false;
		}
		//this sets up the scores on the start nodes.
		queue.insert(start);
		start->cameFrom = start;
		start->gScore = 0;
		start->fScore = start->gScore + start->distanceTo(goal->position);
		start->inOpenSet = true;

		//loop until we find a path or fail.
		while (GetNodeWithLowestFScore())
		{
			GraphNode * current = GetNodeWithLowestFScore();
			current->inOpenSet = false;
			//check to see if we made it to the goal.
			if (current == goal)
			{
				//working backwards towards the start, adding each node to the output
				do{
					out.push_back(current);
					current = current->cameFrom;
				}
				while (current != start);
				out.push_back(current);

				// the path is in the wrong order so we have to reverse it
				return ReverseOrder(out);
			}
			//we did not make it to the goal, so we keep searching for a path.
			current->inClosedSet = true;
			//search each edge
			for (auto edge : current->edges)
			{
				auto neighbor = edge.end;
				//Don't search nodes we already searched.
				if (!neighbor->inClosedSet)
				{
					float newScore = current->gScore + edge.cost;

					//If current path is better than previous path, then remove old path.
					if (newScore < neighbor->gScore){
						if (neighbor->inOpenSet){
							auto f = queue.find(neighbor);
							queue.erase(f);
						}

						neighbor->cameFrom = current;
						neighbor->gScore = newScore;
						neighbor->fScore = neighbor->gScore + neighbor->distanceTo(goal->position);
						queue.insert(neighbor);
						neighbor->inOpenSet = true;
					}
				}
			}
		}

		return out;
	}
	// This resets the visited flag on all the nodes.
	// This is used for the searchDFS routine
	void ResetVisited()
	{
		for (auto node : nodes){
			node->visited = false;
		}
	}
	//does a simple depth first search to find a path.
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
	//Returns number of links between two nodes.
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
	//add edges between two nodes.
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

