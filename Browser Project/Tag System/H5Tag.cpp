#include "H5Tag.h"



H5Tag::H5Tag()
{
	this->type = H5;
	this->block_level = true;
	this->setAttribute(FontSize, "13");
	this->setAttribute(Bold, "1");
	this->setAttribute(MARGIN_TOP, "22");
	this->setAttribute(MARGIN_BOTTOM, "22");
}


H5Tag::~H5Tag()
{
}
