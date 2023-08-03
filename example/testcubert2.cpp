#include "int128v7.hpp"
#include <iostream>
int main()
{
	//test case 1:
	std::cout << cubert(uint128_t(2)) << std::endl;
	//test case 2: n^3 + (0,1,-1)
	std::cout << cubert(uint128_t(7)) << std::endl << cubert(uint128_t(8)) << std::endl << cubert(uint128_t(9)) << std::endl;
	//test case 3:normal cases
	std::cout << cubert(uint128_t(20000)) << std::endl;
	//test case 4:2 ^ 63
	std::cout << cubert(uint128_t(1) << 63) << std::endl;
	return 0;
}
