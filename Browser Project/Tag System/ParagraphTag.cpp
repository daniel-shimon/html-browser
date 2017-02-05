#include "ParagraphTag.h"



ParagraphTag::ParagraphTag()
{
	this->type = P;
	this->block_level = true;
	this->setAttribute(MARGIN_TOP, to_string(this->getRowHeight()));
	this->setAttribute(MARGIN_BOTTOM, to_string(this->getRowHeight()));
}


ParagraphTag::~ParagraphTag()
{
}

void ParagraphTag::specificProccess(ProccessContext context)
{
}
