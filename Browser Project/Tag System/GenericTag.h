#pragma once
#include "BaseTag.h"
class GenericTag :
	public BaseTag
{
public:
	GenericTag();
	GenericTag(string type);
	BaseTag* specificCopy();
	void specificProccess(ProccessContext context);
	void specificDraw(DrawContext& context);
	inline bool isType(string type) const { return type == this->type_string; };
private:
	string type_string;
};

