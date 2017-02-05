#pragma once
#include "TagSystem.h"
class Renderer
{
public:
	Renderer(Root* root, string title);
	void proccessTree();
	void drawTree();
	void maintainWindow();
	sf::RenderWindow window;
	sf::Font font;
private:
	Root* root;
};

