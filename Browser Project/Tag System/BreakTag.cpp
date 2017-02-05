#include "BreakTag.h"

BreakTag::BreakTag()
{
	this->type = TagType::BR;
	this->standalone = true;
	this->block_level = true;
}

void BreakTag::specificProccess(ProccessContext context)
{
	if (context.max_height == 0)
	{
		sf::Text text;
		int font_size = safe_stoi(this->getAttribute(FontSize));
		text.setFont(context.font);
		text.setString("I");
		text.setCharacterSize(font_size);
		this->bounding_box.x = 0;
		this->bounding_box.y = text.getLocalBounds().height + 2 + font_size * 7 / 100;
	}
	else
	{
		this->bounding_box = Point();
	}
}

void BreakTag::specificDraw(DrawContext& context)
{
}

