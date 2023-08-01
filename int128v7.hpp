#include<iostream>
#include<algorithm>
#include<stdint.h>
#include<inttypes.h>
#include<stdbool.h>

//using namespace std;
//By Steven Jinyan Cheng
//on 2023,July 31:
//uint with 128 bits
//using two unsigned long long
#define __SIZEOF_UINT128__ 16;
// Class to handle 128 bit unsigned integers
typedef struct uint128_t {
    unsigned long long lo;
    unsigned long long hi;

    // Default Constructor
    uint128_t(unsigned long long n = 0) : lo{n}, hi{0} {}
    // Constructor with pair
    uint128_t(const std::pair<unsigned long long, unsigned long long>& n) : lo{n.second}, hi{n.first} {}

    // Conversion to unsigned long long
    unsigned long long ull() const {
        return this->lo;
    }

    static unsigned long long to_ull(const uint128_t& n) {
        return n.ull();
    }
    
}uint128_t;

long double ld(uint128_t n){
    return ((n).hi) * 18446744073709551616.l + (n).lo;
}

//==,!= operator
//>>,<< operator
//bit operator
//compound:compound two unsigned long long objects

bool operator==(uint128_t a,uint128_t b){
    return (a.hi == b.hi)?a.lo == b.lo:0;
}
bool operator!=(uint128_t a,uint128_t b){
    return !(a == b);
}
bool operator<(uint128_t a,uint128_t b){
    return (a.hi <= b.hi)?a.lo < b.lo:0;
}
bool operator>(uint128_t a,uint128_t b){
    return !(a == b || a < b);
}
bool operator<=(uint128_t a,uint128_t b){
    return !(a > b);
}
bool operator>=(uint128_t a,uint128_t b){
    return !(a < b);
}
uint128_t operator>>(uint128_t n,int shift){
    uint128_t k = n;
    k.hi = k.hi >> shift;
    k.lo = k.lo >> shift;
    k.lo += (k.hi - (k.hi >> shift) * (1 << shift)) << (8 * sizeof(unsigned long long) - shift);
    return k;
}
uint128_t operator<<(uint128_t n,int shift){
    uint128_t k = n;
    if(shift < 64){
        k.hi = k.hi << shift;
        k.lo = k.lo << shift;
        k.hi += (k.lo >> (8 * sizeof(unsigned long long) - shift));
        return k;
    }
    if(shift == 64){
        k.hi = k.lo;
        k.lo = 0;
        return k;
    }
    return (k << shift - 64) << 64;
}
uint128_t compound(unsigned long long a,unsigned long long b){
    std::pair<unsigned long long, unsigned long long> k;
    k.first = a;
    k.second = b;
    return uint128_t(k);
}

//~,&,|,^
//bit operator

uint128_t operator~(uint128_t n){
    uint128_t k = n;
    k.hi = ~k.hi;
    k.lo = ~k.lo;
    return k;
}
uint128_t operator&(uint128_t a,uint128_t b){
    uint128_t k;
    k.lo = a.lo & b.lo;
    k.hi = a.hi & b.hi;
    return k;
}
uint128_t operator|(uint128_t a,uint128_t b){
    uint128_t k;
    k.lo = a.lo | b.lo;
    k.hi = a.hi | b.hi;
    return k;
}
uint128_t operator^(uint128_t a,uint128_t b){
    uint128_t k;
    k.lo = a.lo ^ b.lo;
    k.hi = a.hi ^ b.hi;
    return k;
}

//operator >>=,<<=,&=,|=,^=

uint128_t &operator>>=(uint128_t &a,int shift){
    return a = a >> shift;
}
uint128_t &operator<<=(uint128_t &a,int shift){
    return a = a << shift;
}
uint128_t &operator&=(uint128_t &a,uint128_t b){
    return a = a & b;
}
uint128_t &operator|=(uint128_t &a,uint128_t b){
    return a = a | b;
}
uint128_t &operator^=(uint128_t &a,uint128_t b){
    return a = a ^ b;
}

//+,- operator
unsigned long long add_mod_p64(unsigned long long p,unsigned long long q){
    const unsigned long long p32 = 1ull+__UINT32_MAX__;
    unsigned long long k;
    unsigned long long kl = p % p32 + q % p32;
    unsigned long long kh = ((p >> 32) + (q >> 32)) % p32;
    k = (kh << 32) + kl;
    return k;
}
uint128_t operator+(uint128_t a,uint128_t b){
    uint128_t k = uint128_t();
    if((a.hi != 0 and b.hi != 0) and __UINT64_MAX__ - a.lo + 1 > b.lo){
        //a + b > 2 ** 64
        //need carry
        k.lo = add_mod_p64(a.lo,b.lo);
        k.hi = add_mod_p64(add_mod_p64(a.hi,b.hi),1ll);
    }
    else{
        k.lo = add_mod_p64(a.lo,b.lo);
        k.hi = add_mod_p64(a.hi,b.hi);
    }
    return k;
}
uint128_t operator-(uint128_t a,uint128_t b){
    return a + ~b + 1;
}

//* operator

uint128_t operator*(uint128_t a,uint128_t b)
{
    if(b == 0) return 0;
    if(b == 1) return a;
    if(a == 1) return b;
    uint128_t t = a * (b >> 1);
    t <<= 1;
    if((b & 1) == 1) t = t + a;
    return t;
}

// %,/ operator
// By ChatGPT


uint128_t &operator+=(uint128_t &a,uint128_t b){
    return a = a + b;
}
uint128_t &operator-=(uint128_t &a,uint128_t b){
    return a = a - b;
}
uint128_t &operator*=(uint128_t &a,uint128_t b){
    return a = a * b;
}

uint128_t operator%(uint128_t n,unsigned long long c){
    unsigned long long a = n.lo,b = n.hi;
    unsigned long long base = 2,exp = 64,mod = c;
    unsigned long long int result = 1;
    base %= mod;
    
    while (exp > 0) {
        if (exp & 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp >>= 1;
    }
    
    unsigned long long int powResult = result,bTimesPow = (b % c * powResult % c) % c;
    unsigned long long int fin = (a % c + bTimesPow) % c;
    return fin;
}

uint128_t operator/(uint128_t p,unsigned long long c){
    if (p.hi > __UINT32_MAX__ + 1) {
            return 0;
    }
    unsigned long long a = p.lo,b = p.hi, quotient = (a / c);

    // Break down b into two 32-bit parts
    unsigned long long b_high = 0;
    unsigned long long b_low = b & 0xFFFFFFFF;
    // Calculate (b_high * 2^32 + b_low) * 2^32 / c
    quotient += ((b_high << 32) / c) << 32;
    quotient += ((b_high << 32) % c + (b_low << 32)) / c;
    return uint128_t(quotient);
}

uint128_t& operator/=(uint128_t& a, unsigned long long b){
    return a = a / b;
}

uint128_t &operator%=(uint128_t &a,unsigned long long b){
    return a = a % b;
}

std::string to_str(uint128_t x){
	if (x == 0)
		return "0";

	
	std::string res = "";

	while (x > 0){
		res += ((x % 10).lo + '0');
		x /= 10;
	}
	std::reverse(res.begin(), res.end());
	return res;
}
std::istream &operator>>(std::istream &cin,uint128_t &x) {
    char c;

    for (c = getchar(); c < '0' || c > '9'; c = getchar());

    for (x = 0; c <= '9' && c >= '0'; c = getchar())
        x = x * 10 + (c & 15);
    
    return cin;
}
std::ostream &operator<<(std::ostream &cout, uint128_t x) {
    return (cout << to_str(x));
}
//math
uint128_t pow(uint128_t a,int b){
	if(a == 0)return 0;
	if(b >= 80 and a != 2)return 0;
	if(b >= 38 and a > 10)return 0;
	if(b > 20 and a > 100)return 0;
    if(b == 0) return 1;
    if(a == 2) return uint128_t(1) << b;
    uint128_t t = pow(a,b >> 1);
	if(t > __UINT64_MAX__)return 0;
    t = t * t;
    if(b & 1) t = t * a;
    return t;
}
uint128_t factorial(int n){
    if(n <= 1)return 1;
	if(n > 20)return 0;
    return factorial(n - 1) * n;
}
//sqrt using bit shifts
unsigned long long sqrt(uint128_t n){
    unsigned long long s = 1;
    while(!(uint128_t(s) * s <= n and uint128_t(s) * s + (s << 1) + 1 > n)){
        s = (s >> 1) + (uint128_t::to_ull(n / s) >> 1);
        if(s == (s >> 1) + (uint128_t::to_ull(n / s) >> 1)){
            if(uint128_t(s) * s < n){
                s += 1ull;
            }
            if(uint128_t(s) * s > n){
                s -= 1ull;
            }
        }
    }
    return s;
}
unsigned long long cubert(uint128_t n){
    unsigned long long s = 1;
    
    while(!(uint128_t(s) * s * s <= n and uint128_t(s + 1) * (s + 1) * (s + 1) > n)){
        s = ((s << 1) + uint128_t::to_ull(n / s / s)) / 3;
        if(s == ((s << 1) + uint128_t::to_ull(n / s / s)) / 3){
            if(uint128_t(s) * s * s < n){
                s += 1ull;
            }
            if(uint128_t(s) * s * s > n){
                s -= 1ull;
            }
        }
    }
    return s;
}
#define UINT128_MAX ~uint128_t(0)
#define __UINT128_MAX__ UINT128_MAX