#include "H1Tag.h"



H1Tag::H1Tag()
{
	this->type = H1;
	this->block_level = true;
	this->setAttribute(FontSize, "32");
	this->setAttribute(Bold, "1");
	this->setAttribute(MARGIN_TOP, "22");
	this->setAttribute(MARGIN_BOTTOM, "22");
}


H1Tag::~H1Tag()
{
}
