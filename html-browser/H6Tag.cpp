#include "H6Tag.h"



H6Tag::H6Tag()
{
	this->type = H6;
	this->block_level = true;
	this->setAttribute(FontSize, "11");
	this->setAttribute(Bold, "1");
	this->setAttribute(MARGIN_TOP, "25");
	this->setAttribute(MARGIN_BOTTOM, "25");
}


H6Tag::~H6Tag()
{
}
