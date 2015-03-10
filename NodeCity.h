#pragma once


#include <iostream>
//#include <stdio.h>
#include <GL/glew.h>
#include <gl/wglew.h>
#include <GLFW\glfw3.h>
#include <fstream>
//#include <time.h>
#include "Texture.h"
#include "Text.h"
#include "Sprite.h"
#include "Shape.h"
//#include "Game.h"

#include "Graph.h"

#include <iostream>

using namespace std;

class NodeCity {
public:
	static const int TILE_SIZE = 32;
	static const int widthInTiles = 640 / TILE_SIZE;
	static const int heightInTiles = 480 / TILE_SIZE;

	int tiles[widthInTiles][heightInTiles];

	Texture cursorTexture = Texture("cursor.png");
	Shape cursorShape = Shape(&cursorTexture, BOTTOM_LEFT);
	Sprite cursorSprite = Sprite(&cursorShape);
	GLuint shaderIDMVP;
	GLFWwindow* window;

	Texture fourWayTexture = Texture("4way.png");
	Texture threeWayTexture = Texture("3way.png");
	Texture cornerTexture = Texture("Corner.png");
	Texture straightTexture = Texture("StraightRoad.png");

	Texture buildingTexture = Texture("Building.png");
	Texture buildingTexture2 = Texture("Building2.png");
	Texture buildingTexture3 = Texture("Building3.png");
	Texture buildingTexture4 = Texture("Building4.png");
	Texture buildingTexturePD = Texture("BuildingPD.png");

	Texture grassTexture = Texture("GrassTile.png");
	Texture dirtTexture = Texture("DirtTile.png");
	Texture mountainTexture = Texture("Mountain.png");
	Texture waterTexture = Texture("WaterTile.png");


	Shape fourWayShape = Shape(&fourWayTexture);
	Shape threeWayShape = Shape(&threeWayTexture);
	Shape cornerShape = Shape(&cornerTexture);
	Shape straightShape = Shape(&straightTexture);

	Shape buildingShape = Shape(&buildingTexture);
	Shape buildingShape2 = Shape(&buildingTexture2);
	Shape buildingShape3 = Shape(&buildingTexture3);
	Shape buildingShape4 = Shape(&buildingTexture4);
	Shape buildingShapePD = Shape(&buildingTexturePD);

	Shape grassShape = Shape(&grassTexture);
	Shape dirtShape = Shape(&dirtTexture);
	Shape mountainShape = Shape(&mountainTexture);
	Shape waterShape = Shape(&waterTexture);



	Sprite fourWaySprite = Sprite(&fourWayShape);
	Sprite northSouthSprite = Sprite(&straightShape, 90);
	Sprite eastWestSprite = Sprite(&straightShape);

	Sprite southEastSprite = Sprite(&cornerShape);
	Sprite northEastSprite = Sprite(&cornerShape, 90);
	Sprite northWestSprite = Sprite(&cornerShape, 180);
	Sprite southWestSprite = Sprite(&cornerShape, 270);

	Sprite north3WaySprite = Sprite(&threeWayShape, 180);
	Sprite east3WaySprite = Sprite(&threeWayShape, 90);
	Sprite south3WaySprite = Sprite(&threeWayShape, 0);
	Sprite west3WaySprite = Sprite(&threeWayShape, 270);

	Sprite buildingSprite = Sprite(&buildingShape);
	Sprite buildingSprite2 = Sprite(&buildingShape2);
	Sprite buildingSprite3 = Sprite(&buildingShape3);
	Sprite buildingSprite4 = Sprite(&buildingShape4);
	Sprite buildingSpritePD = Sprite(&buildingShapePD);

	Sprite grassSprite = Sprite(&grassShape);
	Sprite dirtSprite = Sprite(&dirtShape);
	Sprite mounatinSprite = Sprite(&mountainShape);
	Sprite waterSprite = Sprite(&waterShape);

	
	ivec2 cursorPos;
	static NodeCity * theCity;

	const char * FILE_NAME = "NodeCity.txt";

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		theCity->keyEvent(key, scancode, action, mods);
	}

	NodeCity(GLFWwindow* window) :
		window(window)
	{
		cursorTexture.filterNearest();
		glfwSetKeyCallback(window, &key_callback);
		theCity = this;
		cursorPos = ivec2(widthInTiles / 2, heightInTiles / 2);

		load(FILE_NAME);
	}

	Sprite * getSpriteForTile(int tileNumber)
	{
		switch (tileNumber)
		{
		case 1:
			return &eastWestSprite;
		case 2:
			return &northSouthSprite;
		case 3:
			return &northSouthSprite;
		case 4:
			return &northSouthSprite;
		case 5:
			return &eastWestSprite;
		case 6:
			return &northEastSprite;
		case 7:
			return &southEastSprite;
		case 8:
			return &east3WaySprite;
		case 9:
			return &eastWestSprite;
		case 10:
			return &northWestSprite;
		case 11:
			return &southWestSprite;
		case 12:
			return &west3WaySprite;
		case 13:
			return &eastWestSprite;
		case 14:
			return &north3WaySprite;
		case 15:
			return &south3WaySprite;
		case 16:
			return &fourWaySprite;
		case 17:
			return &buildingSprite;
		case 18:
			return &buildingSprite2;
		case 19:
			return &buildingSprite3;
		case 20:
			return &buildingSprite4;
		case 21:
			return &buildingSpritePD;
		case 22:
			return &grassSprite;
		case 23:
			return &dirtSprite;
		case 24:
			return &mounatinSprite;
		case 25:
			return &waterSprite;
		default:
			return nullptr;
			break;
		}
	}

	void save(const char * fileName)
	{
		ofstream out = ofstream(fileName);

		for (int y = 0; y < heightInTiles; y++) {
			for (int x = 0; x < widthInTiles; x++) {
				int tileNumber = tiles[x][y];
				out << tileNumber << " ";
			}
			out << endl;
		}

		out.close();
	}

	void load(const char * fileName)
	{
		ifstream in = ifstream(fileName);

		for (int y = 0; y < heightInTiles; y++) {
			for (int x = 0; x < widthInTiles; x++) {
				int tileNumber;
				in >> tileNumber;
				tiles[x][y] = tileNumber;
			}
		}

		in.close();
	}

	void draw()
	{
		static const ivec2 TILE_CENTER(TILE_SIZE / 2);

		for (int y = 0; y < heightInTiles; y++) {
			for (int x = 0; x < widthInTiles; x++) {
				int tileNumber = tiles[x][y];
				{
					Sprite * tileSprite = getSpriteForTile(tileNumber);
					if (tileSprite){
						tileSprite->position = ivec2(x, y) * TILE_SIZE + TILE_CENTER;
						tileSprite->draw();
					}
				}
			}
		}

		cursorSprite.position = cursorPos * TILE_SIZE;
		cursorSprite.draw();
	}

	bool isOnMap(int x, int y){
		return x >= 0 && x < widthInTiles && y >= 0 && y < heightInTiles;
	}

	int getTileNumber(int x, int y)
	{
		if (isOnMap(x, y)){
			return tiles[x][y];
		}
		return 0;
	}

	bool isRoad(int x, int y)
	{
		int t = getTileNumber(x, y);
		return t >= 1 && t <= 16;
	}

	void fixRoad(int x, int y){
		if (isRoad(x, y)) {
			int tileNumber = 1;
			if (isRoad(x, y + 1))
				tileNumber += 1;
			if (isRoad(x, y - 1))
				tileNumber += 2;
			if (isRoad(x + 1, y))
				tileNumber += 4;
			if (isRoad(x - 1, y))
				tileNumber += 8;
			tiles[x][y] = tileNumber;
		}
	}

	void fixRoads()
	{
		int x = cursorPos.x;
		int y = cursorPos.y;
		fixRoad(x, y);
		fixRoad(x, y + 1);
		fixRoad(x, y - 1);
		fixRoad(x + 1, y);
		fixRoad(x - 1, y);
	}

	void setTile(int tileNumber)
	{
		tiles[cursorPos.x][cursorPos.y] = tileNumber;
		fixRoads();
	}

	void keyEvent(int key, int scancode, int action, int mods)
	{
		if (action == GLFW_PRESS){
			if (key == GLFW_KEY_UP){
				cursorPos.y++;
			}
			if (key == GLFW_KEY_DOWN){
				cursorPos.y--;
			}
			if (key == GLFW_KEY_LEFT){
				cursorPos.x--;
			}
			if (key == GLFW_KEY_RIGHT){
				cursorPos.x++;
			}
			if (key == GLFW_KEY_BACKSPACE || key == GLFW_KEY_DELETE){
				setTile(0);
			}
			if (key == GLFW_KEY_1)
			{
				setTile(17);
			}
			if (key == GLFW_KEY_2)
			{
				setTile(18);
			}
			if (key == GLFW_KEY_3)
			{
				setTile(19);
			}
			if (key == GLFW_KEY_4)
			{
				setTile(20);
			}
			if (key == GLFW_KEY_P)
			{
				setTile(21);
			}
			if (key == GLFW_KEY_G)
			{
				setTile(22);
			}
			if (key == GLFW_KEY_D)
			{
				setTile(23);
			}
			if (key == GLFW_KEY_M)
			{
				setTile(24);
			}
			if (key == GLFW_KEY_W)
			{
				setTile(25);
			}
			if (key == GLFW_KEY_R){
				setTile(1);
			}
			if (key == GLFW_KEY_L){
				load(FILE_NAME);
			}
			if (key == GLFW_KEY_S){
				save(FILE_NAME);
			}
		}

		if (cursorPos.x < 0) {
			cursorPos.x = 0;
		}
		else if (cursorPos.x >= widthInTiles) {
			cursorPos.x = widthInTiles - 1;
		}
		if (cursorPos.y < 0) {
			cursorPos.y = 0;
		}
		else if (cursorPos.y >= heightInTiles) {
			cursorPos.y = heightInTiles - 1;
		}
	}

};