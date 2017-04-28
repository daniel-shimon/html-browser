#pragma once
#include "BaseTag.h"
class ItalicTag :
	public BaseTag
{
public:
	ItalicTag();
	void specificProccess(ProccessContext& context);
	~ItalicTag();
};

