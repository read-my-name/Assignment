#pragma once
class COrderKey
{
public:
	COrderKey(int id, double dPrice);
	~COrderKey();

public:
	int		m_id;
	double	m_dPrice;
};

