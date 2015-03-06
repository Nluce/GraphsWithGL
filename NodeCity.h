#pragma once


#include <iostream>
//#include <stdio.h>
#include <GL/glew.h>
#include <gl/wglew.h>
#include <GLFW\glfw3.h>
//#include <fstream>
//#include <time.h>
#include "Texture.h"
#include "Text.h"
#include "Sprite.h"
#include "Shape.h"
//#include "Game.h"

#include <iostream>

using namespace std;


class NodeCity {
public:
	static const int TILE_SIZE = 32;
	static const int widthInTiles = 640 / TILE_SIZE;
	static const int heightInTiles = 480 / TILE_SIZE;

	int tiles[widthInTiles][heightInTiles];

	Texture cursorTexture;
	Shape cursorShape;
	Sprite cursorSprite;
	GLuint shaderIDMVP;
	GLFWwindow* window;

	ivec2 cursorPos;

	static NodeCity * theCity;

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		theCity->keyEvent(key, scancode, action, mods);
	}


	NodeCity(GLuint shaderIDMVP, GLFWwindow* window) :
		cursorTexture("cursor.png"),
		cursorShape(&cursorTexture, BOTTOM_RIGHT),
		shaderIDMVP(shaderIDMVP),
		cursorSprite(),
		window(window)
	{
		cout << "NodeCity constructor" << endl;
		cursorTexture.filterNearest();
		cursorSprite.setShape(&cursorShape);
		glfwSetKeyCallback(window, &key_callback);
		theCity = this;
		cursorPos = ivec2(widthInTiles / 2, heightInTiles / 2);
	}

	void draw(const mat4 & world)
	{
		cursorSprite.position = cursorPos * TILE_SIZE;
		cursorSprite.draw(world, shaderIDMVP);
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