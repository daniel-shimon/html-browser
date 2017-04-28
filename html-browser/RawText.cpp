#include "RawText.h"

RawText::RawText()
{
	this->type = TagType::RAWTEXT;
	this->standalone = true;
	this->wrapping = false;
}

void RawText::specificProccess(ProccessContext& context)
{
	this->font_size = safe_stoi(this->getAttribute(FontSize));
	this->text.setFont(context.font);
	this->text.setString(this->getAttribute(TEXT_CONTENT));
	this->text.setCharacterSize(this->font_size);
	this->text.setStyle(this->GetTextStyle());
	this->bounding_box.x = this->text.getLocalBounds().width + this->text.getLocalBounds().left + 2;
	this->bounding_box.y = this->font_size * 115 / 100;
}

void RawText::specificDraw(DrawContext& context)
{
	this->text.setColor(hexToColor(this->getAttribute(Color)));
	this->text.setPosition(this->location.x, this->location.y-1);
	this->text.setOrigin(0, this->font_size * 7 / 100);
	context.window.draw(this->text);
}

int RawText::GetTextStyle()
{
	int x = 0;
	if (this->getAttribute(Bold) == "1")
	{
		x |= sf::Text::Bold;
	}
	if (this->getAttribute(Italic) == "1")
	{
		x |= sf::Text::Italic;
	}
	if (this->getAttribute(Unlderlined) == "1")
	{
		x |= sf::Text::Underlined;
	}
	return x;
}
