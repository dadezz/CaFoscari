#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

int64_t sumOfDigits(int d, int N) {
    if (N==1) return d;
    int res = N;
    if (N>9) {
        int v[2] = {0,0};
        v[0] = N/10;
        v[1] = N%10;
        res = v[0]+v[1];
    }
    return res+2*sumOfDigits(d, N-1);
}

int main(){
    int N, d;
    std::cin>>d>>N;
    std::cout<<sumOfDigits(d, N);
}