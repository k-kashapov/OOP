#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

template <typename T>
struct Sum {
    T res;
    Sum() : res(0) {}
    void operator() (const T& elem) { res += elem; };
    operator T() { return res; };
};

template <typename T>
T mul(T a, T b) {
    return a * b;
}

template <typename T>
auto lambda = [](T a, T b){ return a + b; };

int main(void) { 
    int a[5] = { 1, 2, 3, 4, 5 }; // find sum
    
    // Method 1
    int n = 0;

    //   VVVV - we do not change a
    for (const auto& elem : a) {
        n += elem;
    }
    std::cout << n << std::endl;

    // Method 2
    std::cout << std::for_each(a, a + 5, Sum<int>()) << std::endl;

    // Method 3
    std::cout << std::accumulate(a, a + 5, 1, mul<int>) << std::endl;

    // Method 4
    std::cout << std::accumulate(a, a + 5, 1, lambda<int>) << std::endl;
}
