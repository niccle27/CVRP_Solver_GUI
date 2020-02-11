// clarkeAndWright.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//#include <iostream>
//#include <vector>
//#include <iomanip>
//#include "Node.h"
//#include "Vehicle.h"
//#include "Saving.h"
//#include <algorithm>
//#include <iterator>

#include "CVRP_instance.h"
#include "CW_Solver.h"
#include "CVRP_Solution.h"

//int get_distance_node2node(int id_node1, int id_node2, const std::vector<std::vector<int>>& distanceMatrix);
//void show_matrix(const std::vector<std::vector<int>>& distanceMatrix);
//void show_savings(const std::vector<Saving>& list_Saving);

int main()
{
	//std::vector<int> demands{ 3, 20, 1, 14, 8, 2, 6, 12, 9 };

	//std::vector<std::vector<int>> distanceMatrix{
	//std::vector<int>{0  ,16 ,12 ,4  ,17 ,1  ,10 ,8  ,18 ,6}  ,
	//std::vector<int>{16 ,0  ,13 ,15 ,20 ,3  ,18 ,7  ,17 ,14} ,
	//std::vector<int>{12 ,13 ,0  ,20 ,12 ,19 ,16 ,4  ,5  ,8}  ,
	//std::vector<int>{4  ,15 ,20 ,0  ,17 ,5  ,1  ,19 ,13 ,2}  ,
	//std::vector<int>{17 ,20 ,12 ,17 ,0  ,10 ,6  ,4  ,17 ,18} ,
	//std::vector<int>{1  ,3  ,19 ,5  ,10 ,0  ,4  ,15 ,18 ,10} ,
	//std::vector<int>{10 ,18 ,16 ,1  ,6  ,4  ,0  ,19 ,10 ,3}  ,
	//std::vector<int>{8  ,7  ,4  ,19 ,4  ,15 ,19 ,0  ,20 ,19} ,
	//std::vector<int>{18 ,17 ,5  ,13 ,17 ,18 ,10 ,20 ,0  ,5}  ,
	//std::vector<int>{6  ,14 ,8  ,2  ,18 ,10 ,3  ,19 ,5  ,0} };

	std::vector<int> demands{ 10,15,18,17,3,5,9,4,6};
	//Vehicle::capacityMax = 40;
	std::vector<std::vector<int>> distanceMatrix{
	std::vector<int>{0  ,12 ,11  ,7  ,10 ,10 ,9  ,8  ,6  ,12} ,
	std::vector<int>{12 ,0  ,8   ,5  ,9  ,12 ,14 ,16 ,17 ,22} ,
	std::vector<int>{11 ,8  ,0   ,9  ,15 ,17 ,8  ,18 ,14 ,22} ,
	std::vector<int>{7  ,5  ,9   ,0  ,7  ,9  ,11 ,12 ,12 ,17} ,
	std::vector<int>{10 ,9  ,15  ,7  ,0  ,3  ,17 ,7  ,15 ,18} ,
	std::vector<int>{10 ,12 ,17  ,9  ,3  ,0  ,18 ,6  ,15 ,15} ,
	std::vector<int>{9  ,14 ,8   ,11 ,17 ,18 ,0  ,16 ,8  ,16} ,
	std::vector<int>{8  ,16 ,18  ,12 ,7  ,6  ,16 ,0  ,11 ,11} ,
	std::vector<int>{6  ,17 ,14  ,12 ,15 ,15 ,8  ,11 ,0  ,10} ,
	std::vector<int>{12 ,22 , 22 ,17 ,18 ,15 ,6  ,11 ,10 ,0} };

	CVRP_instance instance(demands, distanceMatrix);
	CW_Solver cw_solver;
	CVRP_Solution* solution = cw_solver.solve(instance);
	solution->print();
	delete solution;
//	system("pause");
}
