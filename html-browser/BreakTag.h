#pragma once
#include "BaseTag.h"
class BreakTag :
	public BaseTag
{
public:
	BreakTag();
	void specificProccess(ProccessContext& context);
	void specificDraw(DrawContext& context);
};

