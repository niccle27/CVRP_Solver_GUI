#pragma once
class Vehicle;

class Node
{
private:
	int m_id;
	int m_demand;
	Vehicle* m_Vehicle = nullptr;
public:
	Node(int t_id, int t_capacity);
	void setVehicle(Vehicle* t_Vehicle);
	Vehicle* getVehicle() { return m_Vehicle; };
	int getId() { return m_id; };
	int getDemand() { return m_demand; };
	bool isAvailable();
	~Node();
};

