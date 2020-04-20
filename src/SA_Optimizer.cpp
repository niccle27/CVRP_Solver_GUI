#include "SA_Optimizer.h"
#include <iostream>
SA_Optimizer::SA_Optimizer(bool t_isVerbose, double temp_init, double temp_final, double alpha, double beta, double n_iter_at_temp_init, int n_iter_without_impr, double low_cost_solution):
	IMetaheuristic(t_isVerbose),
	m_temp_init(temp_init),
	m_temp_final(temp_final),	
	m_alpha(alpha),
	m_beta(beta),
	m_n_iter_at_temp_init(n_iter_at_temp_init),
	m_n_iter_without_impr(n_iter_without_impr),
	m_low_cost_solution(low_cost_solution)
{
	m_temp = m_temp_init;
	m_n_iter_at_temp = m_n_iter_at_temp_init;
}

CVRP_Solution SA_Optimizer::optimize(const CVRP_instance& instance, const CVRP_Solution& solution)
{
	best_solution = solution;
	current_solution = solution;
	cvrp_instance = instance;
	m_temp = m_temp_init;
	m_n_iter_at_temp = m_n_iter_at_temp_init;
	count_iter_without_impr = 0;
	bool flag_solution_improved;
	while (!stop_condition())
	{
		for (int i = 0; i < m_n_iter_at_temp; i++)
		{
			if (stop_condition())break;
			flag_solution_improved = false;
			int move;
			bool flag_move_done = false;
			while (!flag_move_done)
			{
                if(current_solution.get_nb_of_vehicles() >= 2)
                {
                    move = rand() % 3;
                }else{
                    move=2;
                }

				if (current_solution.get_nb_of_vehicles() >= 2)
				{
					if (move == 0)
					{
						//if (m_isVerbose)
						//{
//                            std::cout << "exchange_customers_between_vehicles" << std::endl;
						//}
						flag_solution_improved = exchange_customers_between_vehicles();
						flag_move_done = true;
					}
					else if (move == 1)
					{
						//if (m_isVerbose)
						//{
//                            std::cout << "transfert_customer" << std::endl;
						//}
						flag_solution_improved = transfert_customer();
						flag_move_done = true;
					}
				}
				if (move == 2)
				{
					//if (m_isVerbose)
					//{
//                        std::cout << "exchange_customers_in_vehicle" << std::endl;
					//}
					flag_solution_improved = exchange_customers_in_vehicle();
					flag_move_done = true;
				}
			}
//            current_solution.display();

			if (flag_solution_improved && best_solution.get_cost() > current_solution.get_cost())
			{
				count_iter_without_impr = 0;
				best_solution = current_solution;
				if (m_isVerbose)
				{
					std::cout << "Solution improved" << std::endl;
					best_solution.display_cost();
				}
			}
			else {
				count_iter_without_impr++;
				if (count_iter_without_impr % 2000==0)
				{
					//std::cout << "count_iter_without_impr" << count_iter_without_impr <<std::endl;
				}
			}
		}
		m_temp *= m_alpha;
		m_n_iter_at_temp *= m_beta;
		if (m_isVerbose)
		{
			//std::cout << "temp: " << m_temp << std::endl;
			//std::cout << "step at temp: " << m_n_iter_at_temp << std::endl;
		}
	}

	return best_solution;
}

bool SA_Optimizer::isSolutionAccepted(int delta)
{
    return true; //TODO remove
	if (delta < 0)return true;
	else {
		double prob = exp(-delta / m_temp);
		double rand_num = rand_doubleRange(0, 1);
		return rand_num <= prob;
	}
}

double SA_Optimizer::rand_doubleRange(double a, double b)
{
	// from https://stackoverflow.com/questions/686353/random-float-number-generation
	return double((b - a) * ((double)rand() / RAND_MAX)) + a;
}

bool SA_Optimizer::stop_condition()
{
	//std::cout << (count_iter_without_impr >= m_n_iter_without_impr) << std::endl;
	if (m_n_iter_without_impr != 0 && count_iter_without_impr >= m_n_iter_without_impr)
	{
        if (m_isVerbose)
        {
            std::cout << "stop: "<<m_n_iter_without_impr<<" iterations without improvements" << std::endl;
        }

		return true;
	}
	if (m_low_cost_solution != 0 && m_low_cost_solution >= best_solution.get_cost()) {
        if (m_isVerbose)
        {
            std::cout << "stop lowcost criteria" << std::endl;
        }

		return true;
	}
	if (m_temp <= m_temp_final)
	{
		return true;
        if (m_isVerbose)
        {
            std::cout << "stop: temp "<<m_temp<<" <= "<<m_temp_final << std::endl;
        }
	}
	return false;
}


