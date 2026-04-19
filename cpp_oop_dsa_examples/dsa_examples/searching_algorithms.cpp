#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <chrono>

/**
 * DSA Tip #7: Searching Algorithms
 *
 * Key concepts:
 * - Linear search vs binary search
 * - Hash tables for O(1) average lookups
 * - Search in different data structures
 * - Time/space complexity trade-offs
 * - Collision handling in hash tables
 *
 * Trick: Use std::unordered_map/set for average O(1) operations
 * when you need fast lookups and don't care about order.
 */

class SearchingAlgorithms {
public:
    // Linear Search - O(n) time, O(1) space
    template <typename T>
    static int linearSearch(const std::vector<T>& arr, const T& target) {
        for (size_t i = 0; i < arr.size(); ++i) {
            if (arr[i] == target) {
                return static_cast<int>(i);
            }
        }
        return -1; // Not found
    }

    // Binary Search (iterative) - O(log n) time, O(1) space
    template <typename T>
    static int binarySearch(const std::vector<T>& arr, const T& target) {
        int left = 0;
        int right = arr.size() - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (arr[mid] == target) {
                return mid;
            } else if (arr[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return -1; // Not found
    }

    // Binary Search (recursive)
    template <typename T>
    static int binarySearchRecursive(const std::vector<T>& arr, const T& target,
                                   int left, int right) {
        if (left > right) return -1;

        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            return binarySearchRecursive(arr, target, mid + 1, right);
        } else {
            return binarySearchRecursive(arr, target, left, mid - 1);
        }
    }

    // Jump Search - O(√n) time, O(1) space
    template <typename T>
    static int jumpSearch(const std::vector<T>& arr, const T& target) {
        size_t n = arr.size();
        size_t step = std::sqrt(n);
        size_t prev = 0;

        // Jump ahead
        while (arr[std::min(step, n) - 1] < target) {
            prev = step;
            step += std::sqrt(n);
            if (prev >= n) return -1;
        }

        // Linear search in the block
        while (arr[prev] < target) {
            prev++;
            if (prev == std::min(step, n)) return -1;
        }

        if (arr[prev] == target) return prev;
        return -1;
    }

    // Interpolation Search - O(log log n) average for uniform distribution
    static int interpolationSearch(const std::vector<int>& arr, int target) {
        size_t low = 0;
        size_t high = arr.size() - 1;

        while (low <= high && target >= arr[low] && target <= arr[high]) {
            if (low == high) {
                if (arr[low] == target) return low;
                return -1;
            }

            // Interpolation formula
            size_t pos = low + (((double)(high - low) / (arr[high] - arr[low])) *
                               (target - arr[low]));

            if (arr[pos] == target) {
                return pos;
            } else if (arr[pos] < target) {
                low = pos + 1;
            } else {
                high = pos - 1;
            }
        }
        return -1;
    }
};

// Hash table demonstration
class HashTableDemo {
private:
    std::unordered_map<std::string, int> hashMap_;
    std::unordered_set<std::string> hashSet_;

public:
    void demonstrateHashMap() {
        std::cout << "=== Hash Map Operations ===\n";

        // Insert
        hashMap_["Alice"] = 25;
        hashMap_["Bob"] = 30;
        hashMap_["Charlie"] = 35;
        hashMap_.insert({"Diana", 28});

        // Access
        std::cout << "Alice's age: " << hashMap_["Alice"] << "\n";
        std::cout << "Bob's age: " << hashMap_.at("Bob") << "\n";

        // Check existence
        if (hashMap_.find("Eve") != hashMap_.end()) {
            std::cout << "Eve found\n";
        } else {
            std::cout << "Eve not found\n";
        }

        // Iterate
        std::cout << "All entries:\n";
        for (const auto& pair : hashMap_) {
            std::cout << pair.first << ": " << pair.second << "\n";
        }

        // Erase
        hashMap_.erase("Charlie");
        std::cout << "After erasing Charlie, size: " << hashMap_.size() << "\n";
    }

    void demonstrateHashSet() {
        std::cout << "\n=== Hash Set Operations ===\n";

        // Insert
        hashSet_.insert("apple");
        hashSet_.insert("banana");
        hashSet_.insert("cherry");
        hashSet_.insert("apple"); // Duplicate - will be ignored

        // Check membership
        std::cout << "Contains 'banana': " << (hashSet_.count("banana") ? "yes" : "no") << "\n";
        std::cout << "Contains 'grape': " << (hashSet_.count("grape") ? "yes" : "no") << "\n";

        // Size
        std::cout << "Set size: " << hashSet_.size() << "\n";

        // Iterate
        std::cout << "Set contents: ";
        for (const std::string& fruit : hashSet_) {
            std::cout << fruit << " ";
        }
        std::cout << "\n";

        // Erase
        hashSet_.erase("banana");
        std::cout << "After erasing banana, size: " << hashSet_.size() << "\n";
    }
};

// Utility functions
std::vector<int> generateSortedArray(size_t size, int minVal = 0, int maxVal = 1000) {
    std::vector<int> arr(size);
    for (size_t i = 0; i < size; ++i) {
        arr[i] = minVal + i * (maxVal - minVal) / (size - 1);
    }
    return arr;
}

template <typename Func>
void benchmarkSearch(Func searchFunc, const std::vector<int>& arr, int target,
                    const std::string& name, int expectedIndex = -1) {
    auto start = std::chrono::high_resolution_clock::now();
    int result = searchFunc(arr, target);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    std::cout << name << ": ";
    if (result != -1) {
        std::cout << "Found at index " << result;
        if (expectedIndex != -1 && result == expectedIndex) {
            std::cout << " ✓";
        }
    } else {
        std::cout << "Not found";
    }
    std::cout << " (" << duration.count() << " ns)\n";
}

int main() {
    std::cout << "=== Searching Algorithms Demo ===\n\n";

    // Create test data
    std::vector<int> smallArr = {2, 5, 8, 12, 16, 23, 38, 45, 56, 72};
    std::vector<int> largeArr = generateSortedArray(100000);

    std::cout << "Small array: ";
    for (int num : smallArr) std::cout << num << " ";
    std::cout << "\n\n";

    // Test searches on small array
    int target = 23;
    std::cout << "Searching for " << target << " in small array:\n";

    benchmarkSearch(SearchingAlgorithms::linearSearch<int>, smallArr, target, "Linear Search", 5);
    benchmarkSearch(SearchingAlgorithms::binarySearch<int>, smallArr, target, "Binary Search", 5);
    benchmarkSearch([](const std::vector<int>& arr, int t) {
        return SearchingAlgorithms::binarySearchRecursive(arr, t, 0, arr.size() - 1);
    }, smallArr, target, "Recursive Binary Search", 5);
    benchmarkSearch(SearchingAlgorithms::jumpSearch<int>, smallArr, target, "Jump Search", 5);
    benchmarkSearch(SearchingAlgorithms::interpolationSearch, smallArr, target, "Interpolation Search", 5);

    std::cout << "\n";

    // Test searches on large array
    target = largeArr[50000]; // Middle element
    std::cout << "Searching for element at index 50000 in large array (" << largeArr.size() << " elements):\n";

    benchmarkSearch(SearchingAlgorithms::linearSearch<int>, largeArr, target, "Linear Search");
    benchmarkSearch(SearchingAlgorithms::binarySearch<int>, largeArr, target, "Binary Search");
    benchmarkSearch(SearchingAlgorithms::jumpSearch<int>, largeArr, target, "Jump Search");

    std::cout << "\n";

    // Hash table demonstration
    HashTableDemo hashDemo;
    hashDemo.demonstrateHashMap();
    hashDemo.demonstrateHashSet();

    std::cout << "\n=== Tips ===\n";
    std::cout << "1. Linear search: Simple, works on unsorted data, O(n) time\n";
    std::cout << "2. Binary search: Requires sorted data, O(log n) time, very fast\n";
    std::cout << "3. Jump search: O(√n) time, good for large sorted arrays\n";
    std::cout << "4. Interpolation search: Best for uniformly distributed data\n";
    std::cout << "5. Hash tables: Average O(1) operations, but use more memory\n";
    std::cout << "6. std::unordered_map/set: Great for fast lookups, no ordering\n";
    std::cout << "7. std::map/set: Ordered, O(log n) operations, use when order matters\n";
    std::cout << "8. Choose based on data size, distribution, and memory constraints\n";
    std::cout << "9. For custom types, provide hash functions and equality operators\n";

    return 0;
}