#include "Root.h"

Root::Root()
{
	this->type = TagType::ROOT;
	this->setAttribute(Bold, "0");
	this->setAttribute(Italic, "0");
	this->setAttribute(Unlderlined, "0");
	this->setAttribute(MARGIN_TOP, "8");
	this->setAttribute(MARGIN_LEFT, "8");
	this->setAttribute(MARGIN_BOTTOM, "8");
	this->setAttribute(MARGIN_RIGHT, "8");
	this->setAttribute(FontSize, "16");
	this->setAttribute(Color, "000000");
	this->setAttribute(BackgroundColor, "ffffff");
}

void Root::rootProccess(sf::Font & font)
{
	ProccessContext context(font);
	this->proccess(context);
}

void Root::rootDraw(sf::RenderWindow & window)
{
	DrawContext context = { window };
	this->draw(context);
}

void Root::specificProccess(ProccessContext& context)
{
}

void Root::specificDraw(DrawContext& context)
{
}

