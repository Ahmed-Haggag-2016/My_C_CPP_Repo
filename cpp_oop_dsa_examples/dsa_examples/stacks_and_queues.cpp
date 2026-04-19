#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <string>

/**
 * DSA Tip #3: Stacks and Queues
 *
 * Key concepts:
 * - LIFO (Last In, First Out) for stacks
 * - FIFO (First In, First Out) for queues
 * - Array-based vs linked implementations
 * - Common applications and algorithms
 * - Priority queues with custom comparators
 *
 * Trick: Use std::stack and std::queue adapters with different underlying
 * containers for different performance characteristics.
 */

// Stack implementation using vector
template <typename T>
class VectorStack {
private:
    std::vector<T> data_;

public:
    void push(const T& value) {
        data_.push_back(value);
    }

    void pop() {
        if (!empty()) {
            data_.pop_back();
        }
    }

    T& top() {
        return data_.back();
    }

    const T& top() const {
        return data_.back();
    }

    bool empty() const {
        return data_.empty();
    }

    size_t size() const {
        return data_.size();
    }
};

// Queue implementation using vector (inefficient for large queues)
template <typename T>
class VectorQueue {
private:
    std::vector<T> data_;
    size_t front_;

public:
    VectorQueue() : front_(0) {}

    void push(const T& value) {
        data_.push_back(value);
    }

    void pop() {
        if (!empty()) {
            ++front_;
        }
    }

    T& front() {
        return data_[front_];
    }

    const T& front() const {
        return data_[front_];
    }

    bool empty() const {
        return front_ >= data_.size();
    }

    size_t size() const {
        return data_.size() - front_;
    }
};

// Stack applications
bool isBalancedParentheses(const std::string& expression) {
    std::stack<char> s;

    for (char c : expression) {
        if (c == '(' || c == '[' || c == '{') {
            s.push(c);
        } else if (c == ')' || c == ']' || c == '}') {
            if (s.empty()) return false;

            char top = s.top();
            s.pop();

            if ((c == ')' && top != '(') ||
                (c == ']' && top != '[') ||
                (c == '}' && top != '{')) {
                return false;
            }
        }
    }

    return s.empty();
}

std::string reverseString(const std::string& str) {
    std::stack<char> s;
    for (char c : str) {
        s.push(c);
    }

    std::string result;
    while (!s.empty()) {
        result += s.top();
        s.pop();
    }

    return result;
}

// Queue applications
void simulateQueue() {
    std::queue<std::string> q;

    // People joining queue
    q.push("Alice");
    q.push("Bob");
    q.push("Charlie");
    q.push("Diana");

    std::cout << "Queue size: " << q.size() << "\n";
    std::cout << "Front of queue: " << q.front() << "\n";
    std::cout << "Back of queue: " << q.back() << "\n\n";

    // Process queue
    while (!q.empty()) {
        std::cout << "Serving: " << q.front() << "\n";
        q.pop();
    }
}

// Priority Queue with custom comparator
struct Task {
    std::string description;
    int priority;

    Task(const std::string& desc, int prio) : description(desc), priority(prio) {}
};

struct TaskComparator {
    bool operator()(const Task& a, const Task& b) const {
        return a.priority < b.priority; // Higher priority first
    }
};

void demonstratePriorityQueue() {
    std::priority_queue<Task, std::vector<Task>, TaskComparator> pq;

    pq.push(Task("Low priority task", 1));
    pq.push(Task("High priority task", 5));
    pq.push(Task("Medium priority task", 3));

    std::cout << "Processing tasks by priority:\n";
    while (!pq.empty()) {
        const Task& task = pq.top();
        std::cout << "Priority " << task.priority << ": " << task.description << "\n";
        pq.pop();
    }
}

int main() {
    std::cout << "=== Stacks and Queues Demo ===\n\n";

    // Stack applications
    std::cout << "Stack Applications:\n";
    std::cout << "Balanced parentheses:\n";
    std::cout << "\"(a + b)\" : " << (isBalancedParentheses("(a + b)") ? "balanced" : "unbalanced") << "\n";
    std::cout << "\"(a + b\" : " << (isBalancedParentheses("(a + b") ? "balanced" : "unbalanced") << "\n";
    std::cout << "\"a + b)\" : " << (isBalancedParentheses("a + b)") ? "balanced" : "unbalanced") << "\n";

    std::cout << "\nString reversal:\n";
    std::cout << "\"Hello World\" -> \"" << reverseString("Hello World") << "\"\n\n";

    // Queue simulation
    std::cout << "Queue Simulation:\n";
    simulateQueue();
    std::cout << "\n";

    // Priority queue
    std::cout << "Priority Queue:\n";
    demonstratePriorityQueue();

    std::cout << "\n=== Tips ===\n";
    std::cout << "1. Use std::stack for LIFO operations (function calls, undo)\n";
    std::cout << "2. Use std::queue for FIFO operations (task scheduling, BFS)\n";
    std::cout << "3. std::priority_queue uses heap internally for O(log n) operations\n";
    std::cout << "4. Custom comparators control priority queue ordering\n";
    std::cout << "5. Stack-based: balanced parentheses, expression evaluation\n";
    std::cout << "6. Queue-based: breadth-first search, task scheduling\n";
    std::cout << "7. Vector-based queues waste space; use std::deque for efficiency\n";

    return 0;
}