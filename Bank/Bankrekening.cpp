#include "Bankrekening.h"

Bankrekening::Bankrekening(long moneeeys) : moneeeys(moneeeys) {}

Bankrekening::~Bankrekening() {}

Bankrekening Bankrekening::operator+(const Financieel& f) {
	return Bankrekening(moneeeys + f.getPayday_Bitcheees() );
}

Bankrekening& Bankrekening::operator+=(const Financieel& f) {
	moneeeys += f.getPayday_Bitcheees();
	return *this;
}

Bankrekening Bankrekening::operator-(const Financieel& f) {
	return Bankrekening(moneeeys - f.getPayday_Bitcheees());
}

Bankrekening& Bankrekening::operator-=(const Financieel& f) {
	moneeeys -= f.getPayday_Bitcheees();
	return *this;
}

std::ostream& operator<<(std::ostream& os, const Bankrekening& b) {
	os << b.moneeeys << std::endl;
	return os;
}
