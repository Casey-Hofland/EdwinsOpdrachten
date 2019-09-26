#pragma once

class Financieel {
public:
	Financieel(long payday);
	~Financieel();

	long getPayday_Bitcheees() const;

private:
	long payday;
};