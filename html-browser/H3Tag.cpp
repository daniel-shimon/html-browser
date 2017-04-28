#include "H3Tag.h"



H3Tag::H3Tag()
{
	this->type = H3;
	this->block_level = true;
	this->setAttribute(FontSize, "19");
	this->setAttribute(Bold, "1");
	this->setAttribute(MARGIN_TOP, "19");
	this->setAttribute(MARGIN_BOTTOM, "19");
}


H3Tag::~H3Tag()
{
}
