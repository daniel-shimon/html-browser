#include "ParagraphTag.h"



ParagraphTag::ParagraphTag()
{
	this->type = P;
	this->block_level = true;
}


ParagraphTag::~ParagraphTag()
{
}

void ParagraphTag::specificProccess(ProccessContext& context)
{
	this->setAttribute(MARGIN_TOP, to_string(this->getRowHeight()));
	this->setAttribute(MARGIN_BOTTOM, to_string(this->getRowHeight()));
	/*sf::Text text;
	int font_size = safe_stoi(this->getAttribute(FontSize));
	text.setString("I");
	text.setCharacterSize(font_size);
	text.setFont(context.font);
	int row_height = text.getLocalBounds().height + 2 + font_size * 7 / 100;
	this->location.y += row_height;
	context.accumulator.y += row_height;
	this->setAttribute(MARGIN_BOTTOM, to_string(row_height));*/
}
