#include "BoldTag.h"



BoldTag::BoldTag()
{
	this->type = TagType::B;
	this->setAttribute(Bold, "1");
}

void BoldTag::specificProccess(ProccessContext context)
{
}

BoldTag::~BoldTag()
{
}
