#include <iostream>
#include <string>
#include <vector>

using std::vector; using std::string; using std::cout; using std::cin; using std::endl;

/**
 * binary search:
 * returns the position of x onto the vector if x is found, -1 otherwise
*/
int binary_search_aux(const vector<int> & a, int x, int lo, int hi){
    if (lo > hi) return -1;

    int mid = (hi+lo)/2;
    if (x == a.at(mid)) return mid;
    else {
        if (a.at(mid) < x) return binary_search_aux(a, x, mid, hi);
        else return binary_search_aux(a, x, lo, mid);
    }
}
int binary_search(const vector<int> & a, int x){
    return binary_search_aux(a, x, 0, a.size()-1);
}

/**
 * bubble sort ricorsivo
*/
void swap(int* a, int n){
    //moves a[0] in the correct position inside a
    if (n<=1) return;
    //a has at least 2 elements
    if (a[1] < a[0]) {
        int aux = a[0];
        a[0] = a[1];
        a[1] = aux;
        swap(a+1, n-1);
    }

}
void sort(int* a, int n){
    if (n<=1) return;
    sort (a+1, n-1);
    swap(a, n);
}

/**
 * integer to base 2
*/
string bin(uint64_t n){
    if (n==0) return "0";
    if (n==1) return "1";

    return bin(n/2) + (n%2 ? string{"1"} : string{"0"});
}

int main(){
    int a[] = {8, -1, 0, 17, 19, 2};
    int dim = sizeof(a)/sizeof(int);

    sort(a, dim);
    cout<<"lmao"<<endl;

    for(auto each:a) {
        cout<<" "<<each<<" ";
    }
    cout<<endl;
    long int n = 23574733562;
    string s;
    s = bin(n);
    cout << s << endl;
}

/**
 * next time we'll see some example where recursive functs calls others recursive functs and viceversa.
*/