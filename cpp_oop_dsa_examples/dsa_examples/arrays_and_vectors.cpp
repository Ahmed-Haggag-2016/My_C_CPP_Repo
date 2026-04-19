#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

/**
 * @file arrays_and_vectors.cpp
 * @brief Comprehensive demonstration of arrays and vectors in C++
 * 
 * DSA Tip #1: Arrays and Vectors
 * 
 * Key concepts covered:
 * - Fixed-size arrays (std::array) vs dynamic vectors (std::vector)
 * - Memory layout: stack vs heap allocation
 * - Cache efficiency and performance implications
 * - Common operations: insertion, access, modification
 * - Standard library algorithms usage
 * - Bounds checking and safety
 * - Iterator invalidation pitfalls
 * - Memory management and capacity
 * 
 * Performance characteristics:
 * - std::array: O(1) access, fixed size, stack allocation, better cache locality
 * - std::vector: O(1) access, dynamic size, heap allocation, amortized O(1) push_back
 * 
 * Trick: Use std::array for fixed-size arrays (compile-time size, better performance)
 * and std::vector for dynamic arrays (runtime size flexibility, automatic memory management).
 */

/**
 * @brief Demonstrates std::array usage and characteristics
 * 
 * std::array is a fixed-size container that wraps a C-style array.
 * Advantages:
 * - Fixed size known at compile time
 * - Stack allocation (faster than heap)
 * - Better cache performance
 * - No dynamic memory allocation overhead
 * - Bounds checking with .at() method
 */
void demonstrateArrays() {
    std::cout << "=== Fixed Arrays (std::array) ===\n";
    
    // Fixed-size array - allocated on stack, size determined at compile time
    // Template parameters: <element_type, size>
    std::array<int, 5> fixedArray = {1, 2, 3, 4, 5};
    
    std::cout << "Fixed array contents: ";
    // Range-based for loop - modern C++ way to iterate
    for (int num : fixedArray) {
        std::cout << num << " ";
    }
    std::cout << "\n";
    
    // Safe access with bounds checking using .at() method
    // Throws std::out_of_range exception if index is invalid
    try {
        std::cout << "Element at index 2: " << fixedArray.at(2) << "\n";
        // Uncommenting this would throw: fixedArray.at(10);
        // Because index 10 is beyond the array bounds (size = 5)
    } catch (const std::out_of_range& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
    
    // Direct access without bounds checking - faster but unsafe
    std::cout << "Direct access fixedArray[0]: " << fixedArray[0] << "\n";
    
    // Size information - all known at compile time
    std::cout << "Array size: " << fixedArray.size() << "\n";           // Current elements: 5
    std::cout << "Array max size: " << fixedArray.max_size() << "\n";   // Maximum possible: 5
    std::cout << "Array is empty: " << (fixedArray.empty() ? "yes" : "no") << "\n\n";
}

/**
 * @brief Demonstrates std::vector usage and dynamic behavior
 * 
 * std::vector is a dynamic array that can grow and shrink at runtime.
 * Advantages:
 * - Dynamic size that can change during execution
 * - Automatic memory management
 * - Efficient amortized operations
 * - Compatible with C++ algorithms
 * 
 * Key operations:
 * - push_back(): Add element to end (amortized O(1))
 * - size(): Current number of elements
 * - capacity(): Current allocated memory size
 * - reserve(): Pre-allocate memory to avoid reallocations
 */
void demonstrateVectors() {
    std::cout << "=== Dynamic Vectors (std::vector) ===\n";
    
    // Empty vector - starts with size 0, capacity may be 0 or small
    std::vector<int> dynamicVector;
    
    std::cout << "Initial state - Size: " << dynamicVector.size() 
              << ", Capacity: " << dynamicVector.capacity() << "\n";
    
    // Add elements using push_back()
    // This may trigger reallocations as capacity is exceeded
    std::cout << "Adding elements 10, 20, 30, 40, 50:\n";
    for (int i = 1; i <= 5; ++i) {
        dynamicVector.push_back(i * 10);
        std::cout << "  After push_back(" << (i * 10) << "): size=" << dynamicVector.size()
                  << ", capacity=" << dynamicVector.capacity() << "\n";
    }
    
    std::cout << "Dynamic vector contents: ";
    for (int num : dynamicVector) {
        std::cout << num << " ";
    }
    std::cout << "\n";
    
    // Vector operations demonstration
    std::cout << "Current size: " << dynamicVector.size() << "\n";
    std::cout << "Current capacity: " << dynamicVector.capacity() << "\n";
    
    // Reserve memory to avoid future reallocations
    // This is a performance optimization when you know you'll add more elements
    std::cout << "Reserving space for 20 elements...\n";
    dynamicVector.reserve(20);
    std::cout << "After reserve(20) - Capacity: " << dynamicVector.capacity() << "\n";
    
    // Add more elements - no reallocation needed until capacity is exceeded
    std::cout << "Adding elements 60, 70, 80, 90, 100:\n";
    for (int i = 6; i <= 10; ++i) {
        dynamicVector.push_back(i * 10);
        std::cout << "  After push_back(" << (i * 10) << "): size=" << dynamicVector.size()
                  << ", capacity=" << dynamicVector.capacity() << "\n";
    }
    
    std::cout << "Final state - Size: " << dynamicVector.size()
              << ", Capacity: " << dynamicVector.capacity() << "\n\n";
}

/**
 * @brief Demonstrates common algorithms from <algorithm> header
 * 
 * The C++ Standard Library provides many useful algorithms that work with
 * containers through iterators. These are efficient and well-tested.
 * 
 * Key algorithms demonstrated:
 * - std::sort: Sorts elements in range [first, last)
 * - std::binary_search: Searches in sorted range (O(log n))
 * - std::find: Linear search for element
 * - std::reverse: Reverses elements in range
 */
void demonstrateAlgorithms() {
    std::cout << "=== Common Algorithms ===\n";
    
    std::vector<int> numbers = {3, 1, 4, 1, 5, 9, 2, 6};
    std::cout << "Original vector: ";
    for (int n : numbers) std::cout << n << " ";
    std::cout << "\n";
    
    // std::sort - sorts elements in ascending order
    // Time complexity: O(n log n) on average
    // Requires random access iterators (works with vector, array, but not list)
    std::sort(numbers.begin(), numbers.end());
    std::cout << "After std::sort(): ";
    for (int n : numbers) std::cout << n << " ";
    std::cout << "\n";
    
    // std::binary_search - searches in sorted range
    // Returns true if element found, false otherwise
    // Requires sorted range, O(log n) time complexity
    bool found = std::binary_search(numbers.begin(), numbers.end(), 5);
    std::cout << "std::binary_search for 5: " << (found ? "found" : "not found") << "\n";
    
    // std::find - linear search
    // Returns iterator to first occurrence, or end() if not found
    // Time complexity: O(n)
    auto it = std::find(numbers.begin(), numbers.end(), 9);
    if (it != numbers.end()) {
        // Calculate index: iterator - begin() gives the index
        size_t index = it - numbers.begin();
        std::cout << "std::find: 9 found at index " << index << "\n";
    } else {
        std::cout << "std::find: 9 not found\n";
    }
    
    // std::reverse - reverses elements in range
    // Time complexity: O(n)
    std::reverse(numbers.begin(), numbers.end());
    std::cout << "After std::reverse(): ";
    for (int n : numbers) std::cout << n << " ";
    std::cout << "\n\n";
}

/**
 * @brief Demonstrates common pitfalls and how to avoid them
 * 
 * Iterator invalidation is a common source of bugs when working with vectors.
 * Understanding when iterators become invalid is crucial for writing correct code.
 * 
 * Key pitfalls:
 * 1. Iterator invalidation during modification
 * 2. Using invalidated iterators leads to undefined behavior
 * 3. Solutions: use indices, or collect changes and apply later
 */
void demonstratePitfalls() {
    std::cout << "=== Common Pitfalls and Solutions ===\n";
    
    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::cout << "Original vector: ";
    for (int n : vec) std::cout << n << " ";
    std::cout << "\n";
    
    // PITFALL: Iterator invalidation during traversal
    std::cout << "\nDANGER: Modifying vector while iterating with iterators\n";
    std::cout << "This can cause iterator invalidation and undefined behavior!\n";
    
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << "Processing: " << *it << " ";
        if (*it == 3) {
            // PROBLEM: push_back() may reallocate memory and invalidate ALL iterators!
            // The iterator 'it' may become invalid after this call
            vec.push_back(6);
            std::cout << "(push_back() called - iterators may be invalid!) ";
        }
    }
    std::cout << "\nResult may be unpredictable due to invalid iterators\n";
    
    // SAFE SOLUTION: Use indices instead of iterators when modifying during traversal
    std::cout << "\nSAFE APPROACH: Use indices to avoid iterator invalidation\n";
    std::vector<int> vec2 = {1, 2, 3, 4, 5};
    std::vector<int> toAdd;  // Collect changes separately
    
    std::cout << "Collecting elements to add...\n";
    for (size_t i = 0; i < vec2.size(); ++i) {
        if (vec2[i] == 3) {
            toAdd.push_back(6);  // Don't modify vec2 while iterating
            std::cout << "  Will add 6 after element " << vec2[i] << "\n";
        }
    }
    
    // Now apply the collected changes
    std::cout << "Applying collected changes...\n";
    for (int num : toAdd) {
        vec2.push_back(num);
    }
    
    std::cout << "Safe modification result: ";
    for (int n : vec2) std::cout << n << " ";
    std::cout << "\n\n";
    
    // Additional safety tips
    std::cout << "SAFETY REMINDERS:\n";
    std::cout << "- Always be aware of operations that can invalidate iterators\n";
    std::cout << "- push_back() may invalidate iterators if reallocation occurs\n";
    std::cout << "- erase() always invalidates iterators to erased elements\n";
    std::cout << "- insert() may invalidate iterators if reallocation occurs\n";
    std::cout << "- Use indices or collect changes when modifying during iteration\n\n";
}

/**
 * @brief Main function demonstrating all array and vector concepts
 * 
 * This program showcases the fundamental differences between:
 * - std::array: Fixed size, stack allocation, better performance for small fixed arrays
 * - std::vector: Dynamic size, heap allocation, flexibility for changing sizes
 * 
 * Both are essential tools in C++ programming with different use cases.
 */
int main() {
    std::cout << "=== Arrays and Vectors Comprehensive Demo ===\n\n";
    
    // Demonstrate fixed arrays
    demonstrateArrays();
    
    // Demonstrate dynamic vectors
    demonstrateVectors();
    
    // Demonstrate standard algorithms
    demonstrateAlgorithms();
    
    // Demonstrate common pitfalls and solutions
    demonstratePitfalls();
    
    // Summary of key takeaways
    std::cout << "=== Key Takeaways ===\n";
    std::cout << "1. Use std::array for fixed-size arrays (better performance, stack allocation)\n";
    std::cout << "2. Use std::vector for dynamic arrays (flexible size, automatic memory management)\n";
    std::cout << "3. Call reserve() to pre-allocate memory and avoid reallocations\n";
    std::cout << "4. Be aware of iterator invalidation when modifying containers during iteration\n";
    std::cout << "5. Use standard algorithms from <algorithm> for common operations\n";
    std::cout << "6. Prefer range-based for loops for readability and safety\n";
    std::cout << "7. Use .at() for bounds-checked access, [] for performance when bounds are guaranteed\n";
    std::cout << "8. Understand capacity vs size: capacity >= size always\n";
    std::cout << "9. std::array has zero runtime overhead compared to C-style arrays\n";
    std::cout << "10. std::vector provides amortized O(1) push_back with occasional O(n) reallocations\n";
    
    return 0;
}
