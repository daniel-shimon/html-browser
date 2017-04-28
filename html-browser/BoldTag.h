#pragma once
#include "BaseTag.h"
class BoldTag :
	public BaseTag
{
public:
	BoldTag();
	void specificProccess(ProccessContext& context);
	~BoldTag();
};

