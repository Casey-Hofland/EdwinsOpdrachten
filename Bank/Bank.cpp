// Bank.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include "Bankrekening.h"

int main()
{
	Bankrekening bankrekening = Bankrekening(500);

	bankrekening += Financieel(400);

	std::cout << bankrekening << std::endl;

	return 0;
}
