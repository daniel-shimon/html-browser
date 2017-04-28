#include "Renderer.h"



Renderer::Renderer(Root* root, string title):
	window(sf::VideoMode(600, 800), title)
{
	this->font.loadFromFile("arial.ttf");
	this->root = root;
}

void Renderer::proccessTree()
{
	root->rootProccess(this->font);
}

void Renderer::drawTree()
{
	this->window.clear(sf::Color::White);
	root->rootDraw(this->window);
}

void Renderer::maintainWindow()
{
	while (this->window.isOpen())
	{
		sf::Event event;
		while (this->window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				this->window.close();
				break;
			case sf::Event::Resized:
				window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
				this->drawTree();
				break;
			}
		}
		this->drawTree();
		this->window.display();
	}
}
