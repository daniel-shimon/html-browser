#include "GenericTag.h"

#pragma once
class RawText : public GenericTag
{
public:
	RawText();
	void specificProccess(ProccessContext& context);
	void specificDraw(DrawContext& context);
private:
	int font_size;
	sf::Text text;
	int GetTextStyle();
};