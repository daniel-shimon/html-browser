#include "BoldTag.h"



BoldTag::BoldTag()
{
	this->type = TagType::B;
}

void BoldTag::specificProccess(ProccessContext & context)
{
	this->setAttribute(Bold, "1");
}

BoldTag::~BoldTag()
{
}
