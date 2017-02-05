#include "GenericTag.h"

GenericTag::GenericTag()
{
	this->type = TagType::GENERIC;
}

GenericTag::GenericTag(string type)
{
	this->type = TagType::GENERIC;
	this->type_string = type;
}

BaseTag * GenericTag::specificCopy()
{
	return new GenericTag(this->type_string);
}

void GenericTag::specificProccess(ProccessContext context)
{

}

void GenericTag::specificDraw(DrawContext& context)
{
	
}

