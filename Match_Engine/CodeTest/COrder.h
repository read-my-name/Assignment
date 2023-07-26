#pragma once
#include "include.h"

class COrder
{
public:
	COrder() : m_id(0), m_dPrice(0.0), m_eDir(CDirection::eDefault), m_iAmount(0) {}
	COrder(int id, CDirection::eDirection eDirection, double dPrice, int iAmount);
	~COrder();

	int getID();
	double getPrice();
	bool setPrice(double dPrice);
	int getAmount();
	bool setAmount(int iAmount);
	std::string getDirection();
	CDirection::eDirection getDir();
	std::string to_string();

private:
	CDirection::eDirection	m_eDir;
	int						m_id;
	double					m_dPrice;
	int						m_iAmount;

};

