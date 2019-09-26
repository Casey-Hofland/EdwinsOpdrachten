#pragma once

#include <ostream>
#include "Financieel.h"

class Bankrekening {
public:
	Bankrekening(long moneeeys);
	virtual ~Bankrekening();

	Bankrekening operator+(const Financieel& f);
	Bankrekening& operator+=(const Financieel& f);
	Bankrekening operator-(const Financieel& f);
	Bankrekening& operator-=(const Financieel& f);

	friend std::ostream& operator<<(std::ostream& os, const Bankrekening& b);

private:
	long moneeeys;
};