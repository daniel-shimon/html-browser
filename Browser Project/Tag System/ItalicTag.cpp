#include "ItalicTag.h"



ItalicTag::ItalicTag()
{
	this->type = TagType::I;
	this->setAttribute(Italic, "1");
}

void ItalicTag::specificProccess(ProccessContext context)
{
}

ItalicTag::~ItalicTag()
{
}
