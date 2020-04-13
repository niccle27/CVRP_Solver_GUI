#pragma once
#include <vector>
#include "Saving.h"
#include "CVRP_instance.h"
#include "CVRP_Solution.h"
#include "IHeuristic.h"
class CW_Solver:IHeuristic
{
private:
	std::vector<Saving> m_list_saving;
	std::vector<Vehicle> m_list_vehicles;
	bool isVerbose;
public:
	CW_Solver(bool t_isVerbose = false);
	~CW_Solver();
	CVRP_Solution solve(const CVRP_instance &instance);
private:
	void show_savings();
	void display_vehicles();
};

