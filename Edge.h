#pragma once

class GraphNode;

struct Edge
{
	GraphNode*		start;
	GraphNode*		end;
	float			cost;
};

