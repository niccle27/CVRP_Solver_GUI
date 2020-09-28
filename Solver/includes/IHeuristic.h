#pragma once
#include "CVRP_instance.h"
#include "CVRP_Solution.h"

class IHeuristic
{
	protected:
		virtual CVRP_Solution solve(const CVRP_instance& instance) = 0;
};

