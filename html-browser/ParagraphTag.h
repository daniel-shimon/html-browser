#pragma once
#include "BaseTag.h"
class ParagraphTag :
	public BaseTag
{
public:
	ParagraphTag();
	~ParagraphTag();
	void specificProccess(ProccessContext& context);
};

