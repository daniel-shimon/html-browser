#include "ItalicTag.h"



ItalicTag::ItalicTag()
{
	this->type = TagType::I;
}

void ItalicTag::specificProccess(ProccessContext & context)
{
	this->setAttribute(Italic, "1");
}

ItalicTag::~ItalicTag()
{
}
