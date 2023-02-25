#include "myfunctions.hpp"

int root(int x, int y){
	//return largest z such that z^y <= z
	int z = 0;

	while(power(z+1, y)<=x) z++;

	return z;
}
