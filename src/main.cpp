// clarkeAndWright.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "CVRP_instance.h"
#include "CW_Solver.h"
#include "CVRP_Solution.h"
#include "SA_Optimizer.h"
#include "json.hpp"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using json = nlohmann::json;


int main(int argc, char** argv)
{
	/* initialize random seed: */
	srand(time(NULL));

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
	//int max_capacity_per_vehicle = 35;

	//std::vector<int> demands{ 10,15,18,17,3,5,9,4,6};
	//int max_capacity_per_vehicle = 35;
    //std::vector<std::vector<int>> distanceMatrix{
    //std::vector<int>{0  ,12 ,11  ,7  ,10 ,10 ,9  ,8  ,6  ,12} ,
    //std::vector<int>{12 ,0  ,8   ,5  ,9  ,12 ,14 ,16 ,17 ,22} ,
    //std::vector<int>{11 ,8  ,0   ,9  ,15 ,17 ,8  ,18 ,14 ,22} ,
    //std::vector<int>{7  ,5  ,9   ,0  ,7  ,9  ,11 ,12 ,12 ,17} ,
    //std::vector<int>{10 ,9  ,15  ,7  ,0  ,3  ,17 ,7  ,15 ,18} ,
    //std::vector<int>{10 ,12 ,17  ,9  ,3  ,0  ,18 ,6  ,15 ,15} ,
    //std::vector<int>{9  ,14 ,8   ,11 ,17 ,18 ,0  ,16 ,8  ,16} ,
    //std::vector<int>{8  ,16 ,18  ,12 ,7  ,6  ,16 ,0  ,11 ,11} ,
    //std::vector<int>{6  ,17 ,14  ,12 ,15 ,15 ,8  ,11 ,0  ,10} ,
    //std::vector<int>{12 ,22 , 22 ,17 ,18 ,15 ,6  ,11 ,10 ,0} };

//    std::string testJson=R"foo({
//                         "matrix": [
//                           [0, 12, 11, 7, 10, 10, 9, 8, 6, 12],
//                           [12, 0, 8, 5, 9, 12, 14, 16, 17, 22],
//                           [11, 8, 0, 9, 15, 17, 8, 18, 14, 22],
//                           [7, 5, 9, 0, 7, 9, 11, 12, 12, 17],
//                           [10, 9, 15, 7, 0, 3, 17, 7, 15, 18],
//                           [10, 12, 17, 9, 3, 0, 18, 6, 15, 15],
//                           [9, 14, 8, 11, 17, 18, 0, 16, 8, 16],
//                           [8, 16, 18, 12, 7, 6, 16, 0, 11, 11],
//                           [6, 17, 14, 12, 15, 15, 8, 11, 0, 10],
//                           [12, 22, 22, 17, 18, 15, 6, 11, 10, 0]
//                         ],
//                         "demands": [10, 15, 18, 17, 3, 5, 9, 4, 6],
//                         "max_capacity_per_vehicle":40
//                       })foo";

//    std::cout<<testJson;


    std::string testJson=R"foo({
                         "matrix": [
                         [0, 53439.93, 66243.33, 101140.32, 80878.78, 76125.92, 228593.45, 153909.84],
                         [53187.9, 0, 120665.17, 155562.17, 121421.05, 102055.23, 257109.63, 187312.05],
                         [64478.95, 119745.16, 0, 62767.51, 87224.01, 109898.08, 256280.02, 181596.41],
                         [98553.64, 153819.84, 53036.12, 0, 76040.94, 170782.16, 323365.28, 248681.66],
                         [80240.86, 121575.29, 105684.68, 76687.63, 0, 155433.05, 307900.59, 233216.97],
                         [77686.79, 100828.34, 109152.48, 170823.34, 158495.16, 0, 173244.41, 98560.8],
                         [230463.7, 268381.31, 256361.88, 323600.28, 311272.09, 174217.02, 0, 82881.33],
                         [154238.48, 185441.55, 180136.66, 247375.05, 235046.86, 97991.79, 82208.95, 0]
                     ],
                         "demands": [13,13,13,13,13,13,13],
                         "max_capacity_per_vehicle":40
                       })foo";

	std::string jsonParsingTest = R"foo({
										"instance": {
											"matrix": [
												[0, 53439.93, 66243.33, 101140.32, 80878.78, 76125.92, 228593.45, 153909.84],
												[53187.9, 0, 120665.17, 155562.17, 121421.05, 102055.23, 257109.63, 187312.05],
												[64478.95, 119745.16, 0, 62767.51, 87224.01, 109898.08, 256280.02, 181596.41],
												[98553.64, 153819.84, 53036.12, 0, 76040.94, 170782.16, 323365.28, 248681.66],
												[80240.86, 121575.29, 105684.68, 76687.63, 0, 155433.05, 307900.59, 233216.97],
												[77686.79, 100828.34, 109152.48, 170823.34, 158495.16, 0, 173244.41, 98560.8],
												[230463.7, 268381.31, 256361.88, 323600.28, 311272.09, 174217.02, 0, 82881.33],
												[154238.48, 185441.55, 180136.66, 247375.05, 235046.86, 97991.79, 82208.95, 0]
											],
											"demands": [13, 13, 13, 13, 13, 13, 13],
											"max_capacity_per_vehicle": 40,
                                            "m_nb_vehicles": 3
										},
										"heuristic": "CW",
										"meta": "SA",
										"meta_parameter": {
											"t_isVerbose": false,
                                            "temp_init": 50000,
											"temp_final": 0.001,
											"alpha": 0.999,
                                            "beta": 1.01,
											"n_iter_at_temp_init": 5,
                                            "n_iter_without_impr": 10000000,
											"low_cost_solution": 0
										}
									})foo";

    bool isVerbose = false;
	//auto jsonParse=json::parse(argv[1]);
	auto jsonParse = json::parse(jsonParsingTest);
	CVRP_Solution start_solution;
	CVRP_Solution optimized_solution;

	// instance
	std::vector<std::vector<int>> distanceMatrix = jsonParse["instance"]["matrix"];	
	auto demands = jsonParse["instance"]["demands"];
	int max_capacity_per_vehicle = jsonParse["instance"]["max_capacity_per_vehicle"];
	int m_nb_vehicles = jsonParse["instance"]["m_nb_vehicles"];

//    distanceMatrix={
//        std::vector<int>{0  ,12 ,11  ,7  ,10 ,10 ,9  ,8  ,6  ,12} ,
//        std::vector<int>{12 ,0  ,8   ,5  ,9  ,12 ,14 ,16 ,17 ,22} ,
//        std::vector<int>{11 ,8  ,0   ,9  ,15 ,17 ,8  ,18 ,14 ,22} ,
//        std::vector<int>{7  ,5  ,9   ,0  ,7  ,9  ,11 ,12 ,12 ,17} ,
//        std::vector<int>{10 ,9  ,15  ,7  ,0  ,3  ,17 ,7  ,15 ,18} ,
//        std::vector<int>{10 ,12 ,17  ,9  ,3  ,0  ,18 ,6  ,15 ,15} ,
//        std::vector<int>{9  ,14 ,8   ,11 ,17 ,18 ,0  ,16 ,8  ,16} ,
//        std::vector<int>{8  ,16 ,18  ,12 ,7  ,6  ,16 ,0  ,11 ,11} ,
//        std::vector<int>{6  ,17 ,14  ,12 ,15 ,15 ,8  ,11 ,0  ,10} ,
//        std::vector<int>{12 ,22 , 22 ,17 ,18 ,15 ,6  ,11 ,10 ,0} };
//    demands={ 10,15,18,17,3,5,9,4,6};
//    max_capacity_per_vehicle = 35;
//    m_nb_vehicles = 2;

	CVRP_instance instance(demands, distanceMatrix, max_capacity_per_vehicle, m_nb_vehicles);
    if(isVerbose)
    {
       std::cout<<"instance done"<<std::endl;
    }

	// heuristic
	std::string heuristic_name = jsonParse["heuristic"];
	if (heuristic_name == "CW")
	{
		CW_Solver cw_solver(isVerbose);
		start_solution = cw_solver.solve(instance);
	}
	else {
		CW_Solver cw_solver(isVerbose);
		start_solution = cw_solver.solve(instance);
	}
    if(isVerbose)
    {
         std::cout<<"heuristic done"<<std::endl;
         start_solution.display_json();
    }



	//meta
	bool using_meta = !(jsonParse["meta"] == nullptr);
	if (using_meta)
	{
        if(isVerbose)
        {
            std::cout<<"enter meta"<<std::endl;
        }
		std::string meta_name = jsonParse["meta"];
		if (meta_name == "SA")
		{

			double temp_init = jsonParse["meta_parameter"]["temp_init"];
			double temp_final = jsonParse["meta_parameter"]["temp_final"];
			double alpha = jsonParse["meta_parameter"]["alpha"];
			double beta = jsonParse["meta_parameter"]["beta"];
			double n_iter_at_temp_init = jsonParse["meta_parameter"]["n_iter_at_temp_init"];
			int n_iter_without_impr = jsonParse["meta_parameter"]["n_iter_without_impr"];
			double low_cost_solution = jsonParse["meta_parameter"]["low_cost_solution"];

			SA_Optimizer sa_optimizer(isVerbose,
				temp_init,
				temp_final,
				alpha,
				beta,
				n_iter_at_temp_init,
				n_iter_without_impr,
				low_cost_solution);
			optimized_solution = sa_optimizer.optimize(instance, start_solution);
		}
		else {
			double temp_init = jsonParse["meta_parameter"]["temp_init"];
			double temp_final = jsonParse["meta_parameter"]["temp_final"];
			double alpha = jsonParse["meta_parameter"]["alpha"];
			double beta = jsonParse["meta_parameter"]["beta"];
			double n_iter_at_temp_init = jsonParse["meta_parameter"]["n_iter_at_temp_init"];
			int n_iter_without_impr = jsonParse["meta_parameter"]["n_iter_without_impr"];
			double low_cost_solution = jsonParse["meta_parameter"]["low_cost_solution"];

			SA_Optimizer sa_optimizer(isVerbose,
				temp_init,
				temp_final,
				alpha,
				beta,
				n_iter_at_temp_init,
				n_iter_without_impr,
				low_cost_solution);
			optimized_solution = sa_optimizer.optimize(instance, start_solution);
        }
        if(isVerbose)
        {
            std::cout<<"end meta"<<std::endl;
        }
		optimized_solution.display_json();
    }
	else {
		start_solution.display_json();
	}
    if(isVerbose)
    {
        std::cout<<"meta done"<<std::endl;
    }
//	system("pause");
}
