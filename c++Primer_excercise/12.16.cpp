#include <iostream>
#include <memory>

int main() {
    int a = 123;
    std::unique_ptr<int> p(&a);


    // assign
    // std::unique_ptr<int> p2 = p;
    // error: use of deleted function 'std::unique_ptr<_Tp, _Dp>::unique_ptr(const std::unique_ptr<_Tp, _Dp>&)
    // [with _Tp = int; _Dp = std::default_delete<int>]'

    // copy
    // std::unique_ptr<int> p2(p);
    // error: use of deleted function 'std::unique_ptr<_Tp, _Dp>::unique_ptr(const std::unique_ptr<_Tp, _Dp>&)
    // [with _Tp = int; _Dp = std::default_delete<int>]'

    std::unique_ptr<int> p2 = std::move(p);
    std::cout << "p2: " << *p2 << std::endl;
    // std::cout << "p: " << *p << std::endl; 
    // Segmentation fault

    int* x = nullptr;
    std::cout << "nullptr " << x << std::endl; // good
    // std::cout << "visit nullptr " << *x << std::endl; // Segmentation fault

    return 0;
}