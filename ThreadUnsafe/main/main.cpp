// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <boost/algorithm/string.hpp>
#include <numeric>

// gebruik functies uit <algorithm> en <functional> om (steeds vanuit een ORIGINELE copie van deze vector)
// 1) de vector in 2 nieuwe vectoren te splitsen: 1 met alles wat alfabetisch voor 'purple' komt, 1 met alles er na
// 2) alle elementen UPPERCASE te maken.
// 3) alle dubbele te verwijderen
std::vector<std::string> SortCaseSplit(std::vector<std::string>& vec, std::string splitString) {
	// Sort alphabetically and remove dubbels
	std::sort(vec.begin(), vec.end());
	vec.erase(std::unique(vec.begin(), vec.end()), vec.end());

	// Set strings to uppercase
	for( auto& it : vec )
		boost::to_upper(it);

	// Get the index of the splitString
	int purpleIndex = std::distance(vec.begin(), std::find(vec.begin(), vec.end(), boost::to_upper_copy(splitString)));

	if( purpleIndex >= vec.size() )
	{
		return std::vector<std::string>();
	}

	// Split into 2 vectors
	std::vector<std::string> vecLower(vec.begin(), vec.begin() + purpleIndex);
	std::vector<std::string> vecUpper(vec.begin() + purpleIndex + 1, vec.end());

	vec = vecLower;
	return vecUpper;
}

// gebruik functies uit <algorithm> en <functional> om (steeds vanuit een ORIGINELE copie van deze vector)
// 1) alle negatieve elementen te verwijderen
// 2) voor alle elementen te bepalen of ze even of oneven zijn
// 3) de som, het gemiddelde, en het product van alle getallen te berekenen
void Method(std::vector<double>* vec) {
	vec->erase(std::remove_if(vec->begin(), vec->end(), [](double d)
		{
			return d < 0.0;
		}), vec->end());

	for( auto it : *vec )
	{
		double intPart;
		std::cout << (( std::modf(it, &intPart) == 0.0 && (int)it % 2 == 0 ) ? "Even   " : "Uneven ") << it << '\n';
	}
	std::cout << std::endl;

	double sum{std::accumulate(vec->begin(), vec->end(), 0.0)};
	double average{sum / vec->size()};
	double product{std::accumulate(vec->begin(), vec->end(), 1.0, std::multiplies<>())};

	std::cout << std::fixed;
	std::cout << "Sum: " << sum << '\n';
	std::cout << "Average: " << average << '\n';
	std::cout << "Product: " << product << '\n';
	std::cout << std::endl;
	std::cout.unsetf(std::ios_base::floatfield); 
}

int main() {
	std::vector<std::string> colours{"red", "green", "white", "blue", "orange", "green", "orange", "black", "purple"};
	std::vector<std::string> upper = SortCaseSplit(colours, "purple");

	std::cout << "Lower:" << '\n';
	for( auto it : colours )
		std::cout << it << '\n';
	std::cout << std::endl;

	std::cout << "Upper:" << '\n';
	for( auto it : upper )
		std::cout << it << '\n';
	std::cout << std::endl;

	// -------------------------------------------------------------------------------------------------------

	std::vector<double> numbers{10, 324422, 6, -23, 234.5, 654.1, 3.1242, -9.23, 635};
	Method(&numbers);

	return 0;
}
