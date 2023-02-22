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
    int s2 = std::for_each(a, a + 5, Sum<int>());
    std::cout << s2 << std::endl;

    // Method 3
    int s3 = std::accumulate(a, a + 5, 1, mul<int>);
    std::cout << s3 << std::endl;

    // Method 4
    auto lambda = [&](int a, int b){ return a | b; };
    std::cout << std::accumulate(a, a + 5, 1, lambda) << std::endl;
}
