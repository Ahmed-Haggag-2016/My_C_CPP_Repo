#include "Circular_Buffer.hpp"
#include <iostream>

int main() {
    CircularBuffer<int, 4> buffer;

    std::cout << "Pushing values...\n";
    for (int i = 1; i <= 4; ++i) {
        bool ok = buffer.push(i);
        std::cout << "push(" << i << ") = " << (ok ? "ok" : "full") << "\n";
    }

    std::cout << "Buffer size: " << buffer.size() << " / " << buffer.capacity() << "\n";
    std::cout << "Popping values...\n";

    while (!buffer.empty()) {
        auto value = buffer.pop();
        if (value) {
            std::cout << "pop() = " << *value << "\n";
        }
    }

    std::cout << "Buffer empty: " << std::boolalpha << buffer.empty() << "\n";
    return 0;
}
