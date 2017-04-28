#include "BodyTag.h"



BodyTag::BodyTag()
{
	this->type = BODY;
}


BodyTag::~BodyTag()
{
}

void BodyTag::specificProccess(ProccessContext& context)
{

}

void BodyTag::specificDraw(DrawContext& context)
{
	sf::RectangleShape rectangle(sf::Vector2f(context.window.getSize().x, context.window.getSize().y));
	rectangle.setPosition(0, 0);
	rectangle.setFillColor(hexToColor(this->getAttribute(BackgroundColor)));
	context.window.draw(rectangle);
}
