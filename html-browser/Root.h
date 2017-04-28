#pragma once
#include "BaseTag.h"
class Root :
	public BaseTag
{
public:
	Root();
	void rootProccess(sf::Font& font);
	void rootDraw(sf::RenderWindow& window);
	void specificProccess(ProccessContext& context);
	void specificDraw(DrawContext& context);
};

