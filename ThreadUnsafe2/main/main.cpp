// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <thread>
#include <boost/algorithm/string.hpp>
#include <set>
#include "concurrent_vector.h"
#include <mutex>
#include <numeric>

std::mutex oMutex;
int i = 1;

template <class T>
void Print(std::vector<T> vec) {
	for( auto it : vec )
		std::cout << it << '\n';
	std::cout << std::endl;
}

template <class T>
void ThreadFunc(std::function<void(std::vector<T>*)> func, std::vector<T> vec, std::mutex* mutex) {
	mutex->lock();

	func(&vec);

	std::cout << i << ":" << '\n';
	for( auto it : vec )
		std::cout << it << '\n';
	std::cout << std::endl;

	i++;
	mutex->unlock();
}

void Split(std::vector<std::string>* vec) {
	std::sort(vec->begin(), vec->end());
	int purpleIndex = std::distance(vec->begin(), std::find(vec->begin(), vec->end(), "purple"));

	if( purpleIndex >= vec->size() )
	{
		std::cout << "No instance of purple found!" << std::endl;
		return;
	}

	// Split into 2 vectors
	std::vector<std::string> vecLower(vec->begin(), vec->begin() + purpleIndex);
	std::vector<std::string> vecUpper(vec->begin() + purpleIndex + 1, vec->end());

	vec->assign(vecLower.begin(), vecLower.end());
	vec->push_back("");
	vec->insert(vec->end(), vecUpper.begin(), vecUpper.end());
}

void Case(std::vector<std::string>* vec) {
	for( auto& it : *vec )
		boost::to_upper(it);
}

void Unique(std::vector<std::string>* vec) {
	std::set<std::string> s(vec->begin(), vec->end());
	vec->assign(s.begin(), s.end());
}

void RemoveNegatives(std::vector<double>* vec) {
	vec->erase(std::remove_if(vec->begin(), vec->end(), [](double d)
		{
			return d < 0.0;
		}), vec->end());
}

void Even(std::vector<double>* vec) {
	for( auto it : *vec )
	{
		double intPart;
		std::cout << ( ( std::modf(it, &intPart) == 0.0 && (int)it % 2 == 0 ) ? "Even   " : "Uneven " ) << it << '\n';
	}

	vec->clear();
}

void Calculate(std::vector<double>* vec) {
	double sum{std::accumulate(vec->begin(), vec->end(), 0.0)};
	double average{sum / vec->size()};
	double product{std::accumulate(vec->begin(), vec->end(), 1.0, std::multiplies<>())};

	vec->clear();
	vec->push_back(sum);
	vec->push_back(average);
	vec->push_back(product);

	std::cout << std::fixed;
}

int main() {
	std::vector<std::string> colours{"red", "green", "white", "blue", "orange", "green", "orange", "black", "purple"};
	// gebruik functies uit <algorithm> en <functional> om (steeds vanuit een ORIGINELE copie van deze vector)
	// 1) de vector in 2 nieuwe vectoren te splitsen: 1 met alles wat alfabetisch voor 'purple' komt, 1 met alles er na
	// 2) alle elementen UPPERCASE te maken.
	// 3) alle dubbele te verwijderen

	std::mutex m;

	std::thread splitColours(&ThreadFunc<std::string>, Split, colours, &m);
	std::thread caseColours(&ThreadFunc<std::string>, Case, colours, &m);
	std::thread uniqueColours(&ThreadFunc<std::string>, Unique, colours, &m);

	splitColours.join();
	caseColours.join();
	uniqueColours.join();

	// --------------------------------------------------------------------------------------------------------------

	std::vector<double> numbers{10, 324422, 6, -23, 234.5, 654.1, 3.1242, -9.23, 635};
	// gebruik functies uit <algorithm> en <functional> om (steeds vanuit een ORIGINELE copie van deze vector)
	// 1) alle negatieve elementen te verwijderen
	// 2) voor alle elementen te bepalen of ze even of oneven zijn
	// 3) de som, het gemiddelde, en het product van alle getallen te berekenen

	std::thread removedNumbers(&ThreadFunc<double>, RemoveNegatives, numbers, &m);
	std::thread evenOddNumbers(&ThreadFunc<double>, Even, numbers, &m);
	std::thread calcNumbers(&ThreadFunc<double>, Calculate, numbers, &m);

	removedNumbers.join();
	evenOddNumbers.join();
	calcNumbers.join();

	return 0;
}