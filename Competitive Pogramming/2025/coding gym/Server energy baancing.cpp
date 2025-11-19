/*
A massive data center has servers numbered from to , each consuming power proportional to its number. 
To optimize cooling and energy distribution, you need to develop an algorithm to find the server where the total energy consumption from 
servers to equals the energy consumption from to
In other words, you must find the number such that the sum from to (inclusive) equals the sum from to (inclusive).

If no such server exists, return -1

. It is guaranteed that there will be at most one of such server for the given input.

Input Format

  n , the number of servers

Constraints

Output Format

The server

.

Sample Input 0

8

Sample Output 0

6

Explanation 0

6 is the answer since:

    1 + 2 + 3 + 4 + 5 + 6 = 21
    6 + 7 + 8 = 21

Sample Input 1

11

Sample Output 1

-1

Explanation 1

We can't find a number that balances the energy.
*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;


long long verify_triangular(long long n){
    long long argument = n * (n+1) / 2;
    long long r = std::llround(std::sqrt((long double)argument));

    if (r * r == argument){
        
        return r;
    }
        
    else return -1;

    
}

int main() {
    long long n;
    std::cin >> n;
    
    cout << verify_triangular(n);
    
    return 0;
}
