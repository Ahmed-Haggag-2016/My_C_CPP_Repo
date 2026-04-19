#include <iostream>
#include <string>

/**
 * OOP Tip #1: Classes and Objects
 *
 * Key concepts:
 * - Class definition with member variables and functions
 * - Constructor initialization lists for efficiency
 * - Default vs parameterized constructors
 * - Destructor for cleanup
 * - Member function definitions (inline vs out-of-line)
 *
 * Trick: Use initialization lists in constructors to avoid default initialization
 * then assignment, which is more efficient.
 */

class Person {
private:
    std::string name_;
    int age_;
    double height_; // in centimeters

public:
    // Default constructor
    Person() : name_("Unknown"), age_(0), height_(0.0) {
        std::cout << "Default Person created\n";
    }

    // Parameterized constructor with initialization list
    Person(const std::string& name, int age, double height)
        : name_(name), age_(age), height_(height) {
        std::cout << "Person '" << name_ << "' created\n";
    }

    // Copy constructor
    Person(const Person& other)
        : name_(other.name_), age_(other.age_), height_(other.height_) {
        std::cout << "Person copied\n";
    }

    // Destructor
    ~Person() {
        std::cout << "Person '" << name_ << "' destroyed\n";
    }

    // Member functions
    void introduce() const {
        std::cout << "Hi, I'm " << name_ << ", " << age_ << " years old, "
                  << height_ << "cm tall.\n";
    }

    void setAge(int age) {
        if (age >= 0 && age <= 150) {
            age_ = age;
        } else {
            std::cout << "Invalid age!\n";
        }
    }

    int getAge() const { return age_; }
};

int main() {
    std::cout << "=== Classes and Objects Demo ===\n\n";

    // Stack allocation
    Person person1("Alice", 25, 165.5);
    person1.introduce();

    // Heap allocation (don't forget to delete!)
    Person* person2 = new Person("Bob", 30, 180.0);
    person2->introduce();

    // Copy construction
    Person person3 = person1;
    person3.introduce();

    // Cleanup
    delete person2;

    std::cout << "\n=== Tips ===\n";
    std::cout << "1. Always initialize member variables in constructor initialization lists\n";
    std::cout << "2. Use const member functions for read-only operations\n";
    std::cout << "3. Prefer stack allocation over heap when possible\n";
    std::cout << "4. Implement copy constructors if your class manages resources\n";

    return 0;
}