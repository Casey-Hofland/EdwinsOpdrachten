#include "Financieel.h"

Financieel::Financieel(long payday) : payday(payday) {}

Financieel::~Financieel() {}

long Financieel::getPayday_Bitcheees() const {
	return payday;
}
