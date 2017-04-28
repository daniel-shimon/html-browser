#include "H2Tag.h"



H2Tag::H2Tag()
{
	this->type = H2;
	this->block_level = true;
	this->setAttribute(FontSize, "24");
	this->setAttribute(Bold, "1");
	this->setAttribute(MARGIN_TOP, "20");
	this->setAttribute(MARGIN_BOTTOM, "20");
}


H2Tag::~H2Tag()
{
}
