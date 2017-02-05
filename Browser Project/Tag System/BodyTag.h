#pragma once
#include "BaseTag.h"
class BodyTag :
	public BaseTag
{
public:
	BodyTag();
	~BodyTag();
	void specificProccess(ProccessContext context);
	void specificDraw(DrawContext& context);
};

