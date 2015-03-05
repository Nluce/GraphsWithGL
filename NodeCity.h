#pragma once

#include <iostream>

using namespace std;

class NodeCity {
public:
	int widthInTiles = 10;
	int heightInTiles = 10;

	NodeCity(){
		cout << "NodeCity constructor" << endl;
	}
};