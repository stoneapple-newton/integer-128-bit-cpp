#include "int128v7.hpp"
#include <iostream>
int main()
{
	//test case 1:
	std::cout << sqrt(uint128_t(2)) << std::endl;
	//test case 2: n^2 + (0,1,-1)
	std::cout << sqrt(uint128_t(8)) << std::endl << sqrt(uint128_t(9)) << std::endl << sqrt(uint128_t(10)) << std::endl;
	//test case 3:normal cases
	std::cout << sqrt(uint128_t(20000)) << std::endl;
	//test case 4:2 ^ 64
	std::cout << sqrt(uint128_t(1) << 64) << std::endl;
	return 0;
}