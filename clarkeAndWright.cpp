// clarkeAndWright.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <iomanip>
#include "Node.h"
#include "Vehicle.h"
#include "Saving.h"
#include <algorithm>
//#include <iterator>

int get_distance_node2node(int id_node1, int id_node2, const std::vector<std::vector<int>>& distanceMatrix)
{
	return distanceMatrix[id_node1][id_node2];
}

void show_matrix(const std::vector<std::vector<int>>& distanceMatrix)
{
	for (auto it_row = distanceMatrix.begin(); it_row != distanceMatrix.end(); ++it_row) {
		for (auto it_column = (*it_row).begin(); it_column != (*it_row).end(); ++it_column)
		{
			std::cout << std::setw(5) << (*it_column);
		}
		std::cout << std::endl;
	}
}

void show_savings(const std::vector<Saving>& list_Saving)
{
	for (auto it = list_Saving.begin(); it != list_Saving.end(); ++it)
	{
		it->display();
	}
}

int main()
{
	std::vector<int> demands{ 3, 20, 1, 14, 8, 2, 6, 12, 9 };

	std::vector<std::vector<int>> distanceMatrix{
	std::vector<int>{0  ,16 ,12 ,4  ,17 ,1  ,10 ,8  ,18 ,6}  ,
	std::vector<int>{16 ,0  ,13 ,15 ,20 ,3  ,18 ,7  ,17 ,14} ,
	std::vector<int>{12 ,13 ,0  ,20 ,12 ,19 ,16 ,4  ,5  ,8}  ,
	std::vector<int>{4  ,15 ,20 ,0  ,17 ,5  ,1  ,19 ,13 ,2}  ,
	std::vector<int>{17 ,20 ,12 ,17 ,0  ,10 ,6  ,4  ,17 ,18} ,
	std::vector<int>{1  ,3  ,19 ,5  ,10 ,0  ,4  ,15 ,18 ,10} ,
	std::vector<int>{10 ,18 ,16 ,1  ,6  ,4  ,0  ,19 ,10 ,3}  ,
	std::vector<int>{8  ,7  ,4  ,19 ,4  ,15 ,19 ,0  ,20 ,19} ,
	std::vector<int>{18 ,17 ,5  ,13 ,17 ,18 ,10 ,20 ,0  ,5}  ,
	std::vector<int>{6  ,14 ,8  ,2  ,18 ,10 ,3  ,19 ,5  ,0} };

	int dim = distanceMatrix.size();

	std::vector<Saving> list_saving;
	std::vector<Node*> list_Nodes;
	std::vector<Vehicle*> list_vehicles;

	Node* depot = new Node(0, 0);
	list_Nodes.push_back(depot);

	for (int i = 0; i < demands.size(); ++i)
	{
		Node* el = new Node(i + 1, demands.at(i));
		list_Nodes.push_back(el);
	}//TODO Delete

	for (int i = 1; i < dim - 1; i++) {
		for (int j = i + 1; j < dim; j++)
		{
			int dist_cust_1_to_depot = get_distance_node2node(0, i, distanceMatrix);
			int dist_cust_2_to_depot = get_distance_node2node(0, j, distanceMatrix);
			int dist_cust_1_to_cust_2 = get_distance_node2node(i, j, distanceMatrix);
			int saving_val = dist_cust_1_to_depot + dist_cust_2_to_depot - dist_cust_1_to_cust_2;
			Saving el(i, j, saving_val);
			list_saving.push_back(el);
		}
	}
	std::sort(list_saving.begin(), list_saving.end(), std::greater<Saving>());
	show_savings(list_saving);

	int numberOfCustomer = list_Nodes.size() - 1;
	for (auto it = list_saving.begin(); it != list_saving.end(); ++it)
	{
		if (!it->isPositive()) break;
		if (numberOfCustomer == 0) break;
		int id_cust_1 = it->get_id_cust_1();
		int id_cust_2 = it->get_id_cust_2();

		if (list_Nodes[id_cust_1]->isAvailable() && list_Nodes[id_cust_2]->isAvailable())
		{
			Vehicle* el = new Vehicle(list_Nodes[id_cust_1], list_Nodes[id_cust_2]);
			list_vehicles.push_back(el);
			numberOfCustomer -= 2;
		}
		else if (list_Nodes[id_cust_1]->isAvailable())
		{
			bool isSuccessed = list_Nodes[id_cust_2]->getVehicle()->addNode(list_Nodes[id_cust_1], list_Nodes[id_cust_2]);
			if (isSuccessed)
			{
				numberOfCustomer -= 1;
			}
		}
		else if (list_Nodes[id_cust_2]->isAvailable())
		{
			bool isSuccessed = list_Nodes[id_cust_1]->getVehicle()->addNode(list_Nodes[id_cust_2], list_Nodes[id_cust_1]);
			if (isSuccessed)
			{
				numberOfCustomer -= 1;
			}
		}
	}

	//commentaire
	int i = 1;
	while (numberOfCustomer > 0)
	{
		if (list_Nodes[i]->isAvailable()) {
			Vehicle* el = new Vehicle(list_Nodes[i]);
			list_vehicles.push_back(el);
			numberOfCustomer -= 1;
		}
		++i;
	}

	for (auto it = list_vehicles.begin(); it != list_vehicles.end(); ++it)
	{
		(*it)->print_list();
	}

	system("pause");
	for (auto it = list_Nodes.begin(); it != list_Nodes.end(); ++it)
	{
		delete* it;
	}
	for (auto it = list_vehicles.begin(); it != list_vehicles.end(); ++it)
	{
		delete* it;
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
