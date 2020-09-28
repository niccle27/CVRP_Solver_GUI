#pragma once
class Saving
{
private:
	int id_cust_1;
	int id_cust_2;
	int m_saving;
public:
	Saving(int id_cust_1, int id_cust_2, int m_saving);
	~Saving();
	friend bool operator> (const Saving& c1, const Saving& c2);
	void display() const;
	int get_id_cust_1() { return id_cust_1; };
	int get_id_cust_2() { return id_cust_2; };
	bool isPositive() { return m_saving > 0; };
};

