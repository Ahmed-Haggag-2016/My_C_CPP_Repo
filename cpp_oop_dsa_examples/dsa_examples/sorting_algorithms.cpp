#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

/**
 * DSA Tip #6: Sorting Algorithms
 *
 * Key concepts:
 * - Comparison-based vs non-comparison sorts
 * - Time/space complexity analysis
 * - Stable vs unstable sorts
 * - In-place vs out-of-place algorithms
 * - Adaptive algorithms
 *
 * Trick: Choose the right algorithm based on data characteristics:
 * - Small arrays: Insertion sort
 * - Nearly sorted: Insertion sort (adaptive)
 * - Large random: Quick sort or Merge sort
 * - Limited range: Counting sort
 */

class SortingAlgorithms {
public:
    // Bubble Sort - O(n²) time, O(1) space, stable
    static void bubbleSort(std::vector<int>& arr) {
        size_t n = arr.size();
        for (size_t i = 0; i < n - 1; ++i) {
            bool swapped = false;
            for (size_t j = 0; j < n - i - 1; ++j) {
                if (arr[j] > arr[j + 1]) {
                    std::swap(arr[j], arr[j + 1]);
                    swapped = true;
                }
            }
            if (!swapped) break; // Optimization: stop if already sorted
        }
    }

    // Insertion Sort - O(n²) worst, O(n) best, O(1) space, stable
    static void insertionSort(std::vector<int>& arr) {
        size_t n = arr.size();
        for (size_t i = 1; i < n; ++i) {
            int key = arr[i];
            int j = i - 1;

            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                --j;
            }
            arr[j + 1] = key;
        }
    }

    // Quick Sort - O(n log n) average, O(n²) worst, O(log n) space
    static void quickSort(std::vector<int>& arr, int low, int high) {
        if (low < high) {
            int pivotIndex = partition(arr, low, high);
            quickSort(arr, low, pivotIndex - 1);
            quickSort(arr, pivotIndex + 1, high);
        }
    }

private:
    static int partition(std::vector<int>& arr, int low, int high) {
        int pivot = arr[high];
        int i = low - 1;

        for (int j = low; j < high; ++j) {
            if (arr[j] <= pivot) {
                ++i;
                std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[high]);
        return i + 1;
    }

public:
    // Merge Sort - O(n log n) time, O(n) space, stable
    static void mergeSort(std::vector<int>& arr) {
        if (arr.size() <= 1) return;
        mergeSortHelper(arr, 0, arr.size() - 1);
    }

private:
    static void mergeSortHelper(std::vector<int>& arr, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSortHelper(arr, left, mid);
            mergeSortHelper(arr, mid + 1, right);
            merge(arr, left, mid, right);
        }
    }

    static void merge(std::vector<int>& arr, int left, int mid, int right) {
        std::vector<int> temp(right - left + 1);
        int i = left, j = mid + 1, k = 0;

        while (i <= mid && j <= right) {
            if (arr[i] <= arr[j]) {
                temp[k++] = arr[i++];
            } else {
                temp[k++] = arr[j++];
            }
        }

        while (i <= mid) temp[k++] = arr[i++];
        while (j <= right) temp[k++] = arr[j++];

        for (int p = 0; p < k; ++p) {
            arr[left + p] = temp[p];
        }
    }

public:
    // Heap Sort - O(n log n) time, O(1) space, unstable
    static void heapSort(std::vector<int>& arr) {
        int n = arr.size();

        // Build max heap
        for (int i = n / 2 - 1; i >= 0; --i) {
            heapify(arr, n, i);
        }

        // Extract elements one by one
        for (int i = n - 1; i > 0; --i) {
            std::swap(arr[0], arr[i]);
            heapify(arr, i, 0);
        }
    }

private:
    static void heapify(std::vector<int>& arr, int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && arr[left] > arr[largest]) largest = left;
        if (right < n && arr[right] > arr[largest]) largest = right;

        if (largest != i) {
            std::swap(arr[i], arr[largest]);
            heapify(arr, n, largest);
        }
    }

public:
    // Counting Sort - O(n + k) time, O(n + k) space, stable
    static void countingSort(std::vector<int>& arr) {
        if (arr.empty()) return;

        // Find range
        int minVal = *std::min_element(arr.begin(), arr.end());
        int maxVal = *std::max_element(arr.begin(), arr.end());
        int range = maxVal - minVal + 1;

        std::vector<int> count(range, 0);
        std::vector<int> output(arr.size());

        // Count occurrences
        for (int num : arr) {
            count[num - minVal]++;
        }

        // Cumulative count
        for (int i = 1; i < range; ++i) {
            count[i] += count[i - 1];
        }

        // Build output array
        for (int i = arr.size() - 1; i >= 0; --i) {
            output[count[arr[i] - minVal] - 1] = arr[i];
            count[arr[i] - minVal]--;
        }

        arr = output;
    }
};

// Utility functions
void printArray(const std::vector<int>& arr, const std::string& label) {
    std::cout << label << ": ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << "\n";
}

std::vector<int> generateRandomArray(size_t size, int minVal = 0, int maxVal = 100) {
    std::vector<int> arr(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(minVal, maxVal);

    for (size_t i = 0; i < size; ++i) {
        arr[i] = dis(gen);
    }
    return arr;
}

void benchmarkSort(void (*sortFunc)(std::vector<int>&),
                   std::vector<int> arr,
                   const std::string& name) {
    auto start = std::chrono::high_resolution_clock::now();
    sortFunc(arr);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << name << " took " << duration.count() << " microseconds\n";
}

int main() {
    std::cout << "=== Sorting Algorithms Demo ===\n\n";

    // Small array for demonstration
    std::vector<int> arr = {64, 34, 25, 12, 22, 11, 90};
    printArray(arr, "Original array");

    // Demonstrate different sorts
    auto bubbleArr = arr;
    SortingAlgorithms::bubbleSort(bubbleArr);
    printArray(bubbleArr, "Bubble sort");

    auto insertionArr = arr;
    SortingAlgorithms::insertionSort(insertionArr);
    printArray(insertionArr, "Insertion sort");

    auto quickArr = arr;
    SortingAlgorithms::quickSort(quickArr, 0, quickArr.size() - 1);
    printArray(quickArr, "Quick sort");

    auto mergeArr = arr;
    SortingAlgorithms::mergeSort(mergeArr);
    printArray(mergeArr, "Merge sort");

    auto heapArr = arr;
    SortingAlgorithms::heapSort(heapArr);
    printArray(heapArr, "Heap sort");

    // Counting sort with small range
    std::vector<int> countArr = {4, 2, 2, 8, 3, 3, 1};
    printArray(countArr, "Before counting sort");
    SortingAlgorithms::countingSort(countArr);
    printArray(countArr, "After counting sort");

    std::cout << "\n=== Performance Comparison ===\n";
    std::vector<int> largeArr = generateRandomArray(10000);

    benchmarkSort(SortingAlgorithms::bubbleSort, largeArr, "Bubble Sort");
    benchmarkSort(SortingAlgorithms::insertionSort, largeArr, "Insertion Sort");
    benchmarkSort([](std::vector<int>& a) { SortingAlgorithms::quickSort(a, 0, a.size() - 1); }, largeArr, "Quick Sort");
    benchmarkSort(SortingAlgorithms::mergeSort, largeArr, "Merge Sort");
    benchmarkSort(SortingAlgorithms::heapSort, largeArr, "Heap Sort");

    std::cout << "\n=== Tips ===\n";
    std::cout << "1. Bubble/Insertion: Good for small or nearly sorted arrays\n";
    std::cout << "2. Quick Sort: Fast average case, but O(n²) worst case\n";
    std::cout << "3. Merge Sort: Stable, consistent O(n log n), uses extra space\n";
    std::cout << "4. Heap Sort: In-place, O(n log n), but not stable\n";
    std::cout << "5. Counting Sort: Linear time for small integer ranges\n";
    std::cout << "6. Use std::sort (introsort hybrid) for general-purpose sorting\n";
    std::cout << "7. Consider std::stable_sort when relative order matters\n";
    std::cout << "8. For custom objects, provide comparison operators or functors\n";

    return 0;
}