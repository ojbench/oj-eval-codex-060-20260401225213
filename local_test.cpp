#include "src.hpp"
int main(){ auto e = expect(5).ge(3).lt(10).Not().toBe(7); return e?0:1; }
