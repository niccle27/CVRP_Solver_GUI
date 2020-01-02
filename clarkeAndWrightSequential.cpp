//
//#include <iostream>
//#include <vector>
//#include <list>
//#include <map>
//#include <iomanip>
//#include <algorithm>
//#include <iterator>
//#include <string>
////#include <stdio.h>
//
//
//class Saving
//{
//private:
//	int id_cust_1;
//	int id_cust_2;
//	int m_saving;
//public:
//	Saving(int id_cust_1, int id_cust_2, int m_saving);
//	~Saving();
//	friend bool operator> (const Saving& c1, const Saving& c2);
//	void display() const;
//	int get_id_cust_1() { return id_cust_1; };
//	int get_id_cust_2() { return id_cust_2; };
//	bool isPositive() { return m_saving > 0; };
//};
//
//bool operator>(const Saving& c1, const Saving& c2)
//{
//	return c1.m_saving > c2.m_saving;
//}
//
//void Saving::display() const
//{
//	std::cout << "[" << id_cust_1 << "," << id_cust_2 << "]:" << m_saving << std::endl;
//}
//Saving::Saving(int id_cust_1, int id_cust_2, int m_saving) :id_cust_1(id_cust_1), id_cust_2(id_cust_2), m_saving(m_saving)
//{
//}
//
//
//Saving::~Saving()
//{
//}
//
//class Vehicle;
//
//class Node
//{
//private:
//	int m_id;
//	int m_demand;
//	Vehicle* m_Vehicle = nullptr;
//public:
//	Node(int t_id, int t_capacity);
//	void setVehicle(Vehicle* t_Vehicle);
//	Vehicle* getVehicle() { return m_Vehicle; };
//	int getId() { return m_id; };
//	int getDemand() { return m_demand; };
//	bool isAvailable();
//	~Node();
//};
//
//bool Node::isAvailable()
//{
//	return m_Vehicle == nullptr;
//}
//void Node::setVehicle(Vehicle* t_Vehicle) {
//	m_Vehicle = t_Vehicle;
//}
//
//Node::Node(int t_id, int t_demand) :m_id(t_id), m_demand(t_demand)
//{
//
//}
//
//
//
//Node::~Node()
//{
//}
//
//int get_distance_node2node(int id_node1, int id_node2, const std::vector<std::vector<int>>& distanceMatrix)
//{
//	return distanceMatrix[id_node1][id_node2];
//}
//
//void show_matrix(const std::vector<std::vector<int>>& distanceMatrix)
//{
//	for (auto it_row = distanceMatrix.begin(); it_row != distanceMatrix.end(); ++it_row) {
//		for (auto it_column = (*it_row).begin(); it_column != (*it_row).end(); ++it_column)
//		{
//			std::cout << std::setw(5) << (*it_column);
//		}
//		std::cout << std::endl;
//	}
//}
//
//void show_savings(const std::vector<Saving>& list_Saving)
//{
//	for (auto it = list_Saving.begin(); it != list_Saving.end(); ++it)
//	{
//		it->display();
//	}
//}
//
//class Vehicle
//{
//private:
//	static const int capacityMax = 35;
//public:
//	Vehicle(Node* t_customer1);
//	Vehicle(Node* t_customer1, Node* t_customer2);
//	~Vehicle();
//	bool addNode(Node* t_node, Node* neighbour);
//	void print_list()const;
//private:
//	int capacity;
//	std::list<Node*> list_customers;
//private:
//	bool is_enough_capacity_left(int cap1, int cap2 = 0);
//
//};
//bool Vehicle::is_enough_capacity_left(int cap1, int cap2)
//{
//	int capToTest = cap1 + cap2;
//	return capacity + capToTest <= capacityMax;
//}
//
//void Vehicle::print_list()const
//{
//	for (auto it = list_customers.begin(); it != list_customers.end(); ++it)
//	{
//		std::cout << (*it)->getId();
//		auto next = std::next(it, 1);
//		if (next != list_customers.end())
//		{
//			std::cout << ",";
//		}
//	}
//	std::cout << std::endl;
//}
//bool Vehicle::addNode(Node* t_node, Node* neighbour = nullptr)
//{
//	if (!is_enough_capacity_left(t_node->getDemand()))
//	{
//		return false;
//	}
//	else
//	{
//		capacity += t_node->getDemand();
//	}
//	if (neighbour != nullptr)
//	{
//		Node* front_node = list_customers.front();
//		Node* back_node = list_customers.back();
//		if (neighbour == front_node)
//		{
//			list_customers.push_front(t_node);
//			t_node->setVehicle(this);
//			return true;
//		}
//		if (neighbour == back_node)
//		{
//			list_customers.push_back(t_node);
//			t_node->setVehicle(this);
//			return true;
//		}
//	}
//	else
//	{
//		list_customers.push_back(t_node);
//		t_node->setVehicle(this);
//		return true;
//	}
//	return false;
//}
//
//Vehicle::Vehicle(Node* t_customer1)
//{
//	capacity = 0;
//	addNode(t_customer1);
//}
//
//Vehicle::Vehicle(Node* t_customer1, Node* t_customer2)
//{
//	capacity = 0;
//	addNode(t_customer1);
//	addNode(t_customer2);
//	//list_customers.push_back(t_customer1);
//	//t_customer1->setVehicle(this);
//	//list_customers.push_back(t_customer2);
//	//t_customer2->setVehicle(this);
//}
//
//Vehicle::~Vehicle()
//{
//}
//
//int main()
//{
//	std::vector<int> demands{ 3, 20, 1, 14, 8, 2, 6, 12, 9 };
//
//	std::vector<std::vector<int>> distanceMatrix{
//	std::vector<int>{0  ,16 ,12 ,4  ,17 ,1  ,10 ,8  ,18 ,6}  ,
//	std::vector<int>{16 ,0  ,13 ,15 ,20 ,3  ,18 ,7  ,17 ,14} ,
//	std::vector<int>{12 ,13 ,0  ,20 ,12 ,19 ,16 ,4  ,5  ,8}  ,
//	std::vector<int>{4  ,15 ,20 ,0  ,17 ,5  ,1  ,19 ,13 ,2}  ,
//	std::vector<int>{17 ,20 ,12 ,17 ,0  ,10 ,6  ,4  ,17 ,18} ,
//	std::vector<int>{1  ,3  ,19 ,5  ,10 ,0  ,4  ,15 ,18 ,10} ,
//	std::vector<int>{10 ,18 ,16 ,1  ,6  ,4  ,0  ,19 ,10 ,3}  ,
//	std::vector<int>{8  ,7  ,4  ,19 ,4  ,15 ,19 ,0  ,20 ,19} ,
//	std::vector<int>{18 ,17 ,5  ,13 ,17 ,18 ,10 ,20 ,0  ,5}  ,
//	std::vector<int>{6  ,14 ,8  ,2  ,18 ,10 ,3  ,19 ,5  ,0} };
//
//	int dim = distanceMatrix.size();
//
//	std::vector<Saving> list_saving;
//	std::vector<Node*> list_Nodes;
//	std::vector<Vehicle*> list_vehicles;
//
//	Node* depot = new Node(0, 0);
//	list_Nodes.push_back(depot);
//
//	for (int i = 0; i < demands.size(); ++i)
//	{
//		Node* el = new Node(i + 1, demands.at(i));
//		list_Nodes.push_back(el);
//	}//TODO Delete
//
//	for (int i = 1; i < dim - 1; i++) {
//		for (int j = i + 1; j < dim; j++)
//		{
//			int dist_cust_1_to_depot = get_distance_node2node(0, i, distanceMatrix);
//			int dist_cust_2_to_depot = get_distance_node2node(0, j, distanceMatrix);
//			int dist_cust_1_to_cust_2 = get_distance_node2node(i, j, distanceMatrix);
//			int saving_val = dist_cust_1_to_depot + dist_cust_2_to_depot - dist_cust_1_to_cust_2;
//			Saving el(i, j, saving_val);
//			list_saving.push_back(el);
//		}
//	}
//	std::sort(list_saving.begin(), list_saving.end(), std::greater<Saving>());
//	show_savings(list_saving);
//
//	int numberOfCustomer = list_Nodes.size() - 1;
//	for (auto it = list_saving.begin(); it != list_saving.end(); ++it)
//	{
//		if (!it->isPositive()) break;
//		if (numberOfCustomer == 0) break;
//		int id_cust_1 = it->get_id_cust_1();
//		int id_cust_2 = it->get_id_cust_2();
//
//		if (list_Nodes[id_cust_1]->isAvailable() && list_Nodes[id_cust_2]->isAvailable())
//		{
//			Vehicle* el = new Vehicle(list_Nodes[id_cust_1], list_Nodes[id_cust_2]);
//			list_vehicles.push_back(el);
//			numberOfCustomer -= 2;
//		}
//		else if (list_Nodes[id_cust_1]->isAvailable())
//		{
//			bool isSuccessed = list_Nodes[id_cust_2]->getVehicle()->addNode(list_Nodes[id_cust_1], list_Nodes[id_cust_2]);
//			if (isSuccessed)
//			{
//				numberOfCustomer -= 1;
//			}
//		}
//		else if (list_Nodes[id_cust_2]->isAvailable())
//		{
//			bool isSuccessed = list_Nodes[id_cust_1]->getVehicle()->addNode(list_Nodes[id_cust_2], list_Nodes[id_cust_1]);
//			if (isSuccessed)
//			{
//				numberOfCustomer -= 1;
//			}
//		}
//	}
//
//	//commentaire
//	int i = 1;
//	while (numberOfCustomer > 0)
//	{
//		if (list_Nodes[i]->isAvailable()) {
//			Vehicle* el = new Vehicle(list_Nodes[i]);
//			list_vehicles.push_back(el);
//			numberOfCustomer -= 1;
//		}
//		++i;
//	}
//
//	for (auto it = list_vehicles.begin(); it != list_vehicles.end(); ++it)
//	{
//		(*it)->print_list();
//	}
//
//	system("pause");
//	for (auto it = list_Nodes.begin(); it != list_Nodes.end(); ++it)
//	{
//		delete* it;
//	}
//	for (auto it = list_vehicles.begin(); it != list_vehicles.end(); ++it)
//	{
//		delete* it;
//	}
//
//}
//
////[
////	[0, 134033.33, 2384902, 10214803],
////	[134325.92, 0, 2336135.5, 10166036],
////	[2381911, 2333727.25, 0, 7629222],
////	[10220471, 10172287, 7634122, 0]
////]
//
