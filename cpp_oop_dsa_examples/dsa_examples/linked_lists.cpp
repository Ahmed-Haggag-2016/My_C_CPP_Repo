#include <iostream>
#include <memory>

/**
 * DSA Tip #2: Linked Lists
 *
 * Key concepts:
 * - Singly vs doubly linked lists
 * - Node structure and pointer management
 * - Insertion/deletion operations
 * - Memory management with smart pointers
 * - Cycle detection
 *
 * Trick: Use std::unique_ptr for automatic memory management and
 * to prevent memory leaks in linked list implementations.
 */

// Singly linked list node
template <typename T>
struct Node {
    T data;
    std::unique_ptr<Node<T>> next;

    Node(T value) : data(value), next(nullptr) {}
};

// Doubly linked list node
template <typename T>
struct DoublyNode {
    T data;
    std::shared_ptr<DoublyNode<T>> prev;
    std::shared_ptr<DoublyNode<T>> next;

    DoublyNode(T value) : data(value), prev(nullptr), next(nullptr) {}
};

// Singly Linked List
template <typename T>
class SinglyLinkedList {
private:
    std::unique_ptr<Node<T>> head_;
    size_t size_;

public:
    SinglyLinkedList() : head_(nullptr), size_(0) {}

    // Add to front (O(1))
    void pushFront(T value) {
        auto newNode = std::make_unique<Node<T>>(value);
        newNode->next = std::move(head_);
        head_ = std::move(newNode);
        ++size_;
    }

    // Add to back (O(n))
    void pushBack(T value) {
        if (!head_) {
            head_ = std::make_unique<Node<T>>(value);
        } else {
            Node<T>* current = head_.get();
            while (current->next) {
                current = current->next.get();
            }
            current->next = std::make_unique<Node<T>>(value);
        }
        ++size_;
    }

    // Remove from front (O(1))
    bool popFront() {
        if (!head_) return false;
        head_ = std::move(head_->next);
        --size_;
        return true;
    }

    // Find element (O(n))
    bool contains(T value) const {
        Node<T>* current = head_.get();
        while (current) {
            if (current->data == value) return true;
            current = current->next.get();
        }
        return false;
    }

    // Print list
    void print() const {
        Node<T>* current = head_.get();
        while (current) {
            std::cout << current->data << " -> ";
            current = current->next.get();
        }
        std::cout << "null\n";
    }

    size_t size() const { return size_; }
    bool empty() const { return size_ == 0; }
};

// Doubly Linked List
template <typename T>
class DoublyLinkedList {
private:
    std::shared_ptr<DoublyNode<T>> head_;
    std::shared_ptr<DoublyNode<T>> tail_;
    size_t size_;

public:
    DoublyLinkedList() : head_(nullptr), tail_(nullptr), size_(0) {}

    // Add to back (O(1))
    void pushBack(T value) {
        auto newNode = std::make_shared<DoublyNode<T>>(value);
        if (!head_) {
            head_ = tail_ = newNode;
        } else {
            tail_->next = newNode;
            newNode->prev = tail_;
            tail_ = newNode;
        }
        ++size_;
    }

    // Remove from back (O(1))
    bool popBack() {
        if (!tail_) return false;
        if (head_ == tail_) {
            head_ = tail_ = nullptr;
        } else {
            tail_ = tail_->prev.lock(); // weak_ptr to shared_ptr
            if (tail_) tail_->next = nullptr;
        }
        --size_;
        return true;
    }

    void print() const {
        auto current = head_;
        while (current) {
            std::cout << current->data << " <-> ";
            current = current->next;
        }
        std::cout << "null\n";
    }

    size_t size() const { return size_; }
};

// Cycle detection using Floyd's algorithm
template <typename T>
bool hasCycle(const Node<T>* head) {
    if (!head || !head->next) return false;

    const Node<T>* slow = head;
    const Node<T>* fast = head;

    while (fast && fast->next) {
        slow = slow->next.get();
        fast = fast->next->next.get();

        if (slow == fast) return true;
    }

    return false;
}

int main() {
    std::cout << "=== Linked Lists Demo ===\n\n";

    // Singly linked list
    std::cout << "Singly Linked List:\n";
    SinglyLinkedList<int> sll;
    sll.pushFront(3);
    sll.pushFront(2);
    sll.pushFront(1);
    sll.print();

    sll.pushBack(4);
    sll.pushBack(5);
    sll.print();

    std::cout << "Contains 3: " << (sll.contains(3) ? "yes" : "no") << "\n";
    std::cout << "Contains 6: " << (sll.contains(6) ? "yes" : "no") << "\n";

    sll.popFront();
    sll.print();

    std::cout << "\n";

    // Doubly linked list
    std::cout << "Doubly Linked List:\n";
    DoublyLinkedList<std::string> dll;
    dll.pushBack("Alice");
    dll.pushBack("Bob");
    dll.pushBack("Charlie");
    dll.print();

    dll.popBack();
    dll.print();

    std::cout << "\n";

    // Cycle detection demo
    std::cout << "Cycle Detection:\n";
    auto node1 = std::make_unique<Node<int>>(1);
    auto node2 = std::make_unique<Node<int>>(2);
    auto node3 = std::make_unique<Node<int>>(3);

    node1->next = std::move(node2);
    node1->next->next = std::move(node3);

    std::cout << "No cycle: " << (hasCycle(node1.get()) ? "yes" : "no") << "\n";

    // Create a cycle for demonstration
    auto cycleNode1 = std::make_unique<Node<int>>(1);
    auto cycleNode2 = std::make_unique<Node<int>>(2);
    auto cycleNode3 = std::make_unique<Node<int>>(3);

    cycleNode1->next = std::move(cycleNode2);
    cycleNode1->next->next = std::move(cycleNode3);
    // Create cycle: 3 -> 1
    cycleNode1->next->next->next = cycleNode1.get(); // Raw pointer for cycle

    std::cout << "Has cycle: " << (hasCycle(cycleNode1.get()) ? "yes" : "no") << "\n";

    std::cout << "\n=== Tips ===\n";
    std::cout << "1. Use std::unique_ptr for singly linked lists to prevent leaks\n";
    std::cout << "2. Use std::shared_ptr for doubly linked lists (shared ownership)\n";
    std::cout << "3. Singly linked: O(1) front ops, O(n) back ops\n";
    std::cout << "4. Doubly linked: O(1) front/back ops, more memory overhead\n";
    std::cout << "5. Use Floyd's cycle detection algorithm for cycle detection\n";
    std::cout << "6. Prefer std::list or std::forward_list from STL when possible\n";

    return 0;
}