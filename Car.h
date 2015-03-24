#pragma once
#include "GraphNode.h"
#include "Graph.h"
#include "NodeCity.h"
#include <glm\glm.hpp>

using namespace glm;

class Car
{
public:
	const Graph& graph;
	const vector <ivec2> checkpoints;
	int currentCheckpoint = 0;
	glm::vec2 position;
	glm::vec2 direction;
	Car(ivec2 spawnPoint, const Graph& graph, const vector <ivec2> checkpoints) :
		graph(graph),
		checkpoints(checkpoints)
	{
		GraphNode* start = graph.FindClosestNode(spawnPoint);
		ivec2 goal = checkpoints[0];
		GraphNode* end = graph.FindClosestNode(goal);
		//path = graph.FindPath(start, end);
	}
	void SpawnCars()
	{
		
	}

	~Car();
	vector <GraphNode> path;

};

