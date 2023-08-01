# integer-128-bit-cpp
## Quick Start
You can use my code is other C++ header code.like this:
```cpp
#include "int128v6.hpp"//or other version 
```
## Versions
- the v1 and v2 code is to construct a `uint128_t` with two `unsigned long long int` and got basic operators.
- v2 have `read` and `write` to read and write the number in a `uint128_t`,`pow` and `factorial` functions with some bugs on the high `unsigned long long`.
- v3 will fix these bugs.
- v4 will got a struct but not a type `uint128_t` by ChatGPT.
- v5 will delete the `read` and `write` functions and replace them by overloaded `>>` and `<<`.
- v6 will have a `sqrt` and `cubert` function.
## My tests
To let my code correct,I use tests to test my code on Xcode.I test my `sqrt` and `cubert` function like this:
```cpp
#include"int128v6.hpp"
#include<iostream>
int main(){
	std::cout << sqrt(uint128_t(1000000ull));//expect answer:1000
	return 0;
}
```
You can see my test code in the file "example".
Important:Do Not use my not final version!
