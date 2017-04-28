#include "BreakTag.h"

BreakTag::BreakTag()
{
	this->type = TagType::BR;
	this->standalone = true;
	this->wrapping = false;
}

void BreakTag::specificProccess(ProccessContext& context)
{
	context.accumulator.y += context.max_height;
	context.accumulator.x = 0;
	context.max_height = 0;
	sf::Text text;
	int font_size = safe_stoi(this->getAttribute(FontSize));
	text.setFont(context.font);
	text.setString("I");
	text.setCharacterSize(font_size);
	this->bounding_box.x = 0;
	this->bounding_box.y = text.getLocalBounds().height + 2 + font_size * 7 / 100;
}

void BreakTag::specificDraw(DrawContext& context)
{
}

