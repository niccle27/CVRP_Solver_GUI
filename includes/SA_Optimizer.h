#pragma once
#include <cmath>
#include "IMetaheuristic.h"

class SA_Optimizer:IMetaheuristic
{
	private:
		double m_temp_init;
		double m_temp;
		double m_temp_final;
		double m_alpha;
		double m_beta;
		double m_n_iter_at_temp;
		double m_n_iter_at_temp_init;
		int m_n_iter_without_impr;
		int count_iter_without_impr=0;
		double m_low_cost_solution;
	public:
		SA_Optimizer(bool t_isVerbose = false, double temp_init=5000, double temp_final=0.001, double alpha=0.999, double beta=1.001, double n_iter_at_temp_init=5, int n_iter_without_impr=10000000, double low_cost_solution=0);
		// Inherited via IMetaheuristic
		virtual CVRP_Solution optimize(const CVRP_instance& instance, const CVRP_Solution& solution) override;
	private:
		virtual bool isSolutionAccepted(int delta) override;
		double rand_doubleRange(double a, double b);
		bool stop_condition();
		

};

