#include "H4Tag.h"



H4Tag::H4Tag()
{
	this->type = H4;
	this->block_level = true;
	this->setAttribute(FontSize, "16");
	this->setAttribute(Bold, "1");
	this->setAttribute(MARGIN_TOP, "21");
	this->setAttribute(MARGIN_BOTTOM, "21");
}


H4Tag::~H4Tag()
{
}
