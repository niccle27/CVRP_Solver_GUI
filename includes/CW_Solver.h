#pragma once
#include <vector>
#include "Saving.h"
#include "CVRP_instance.h"
#include "CVRP_Solution.h"
class CW_Solver
{
private:
	std::vector<Saving> m_list_saving;
public:
	void show_savings();
	CVRP_Solution* solve(const CVRP_instance &instance);
};

