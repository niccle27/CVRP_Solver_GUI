#pragma once
class Vehicle;

class Node
{
private:
	int m_id;
	int m_demand;
	bool m_isAvailable=true;
public:
	Node(int t_id, int t_capacity);
	int getId() { return m_id; };
	int getDemand() { return m_demand; };
	bool isAvailable() { return m_isAvailable; };
	void setIsAvailable(bool t_isAvailable) { m_isAvailable = t_isAvailable; };
	~Node();
};

