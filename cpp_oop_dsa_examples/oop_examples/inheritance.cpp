#include <iostream>
#include <string>

/**
 * OOP Tip #2: Inheritance
 *
 * Key concepts:
 * - Base and derived classes
 * - Access specifiers in inheritance (public, protected, private)
 * - Virtual functions for polymorphism
 * - Constructor/destructor order in inheritance
 * - Multiple inheritance pitfalls
 *
 * Trick: Use virtual destructors in base classes to ensure proper cleanup
 * of derived objects through base pointers.
 */

class Animal {
protected:
    std::string name_;
    int age_;

public:
    Animal(const std::string& name, int age) : name_(name), age_(age) {
        std::cout << "Animal '" << name_ << "' created\n";
    }

    // Virtual destructor - crucial for inheritance!
    virtual ~Animal() {
        std::cout << "Animal '" << name_ << "' destroyed\n";
    }

    virtual void makeSound() const {
        std::cout << "Some generic animal sound\n";
    }

    void eat() const {
        std::cout << name_ << " is eating\n";
    }

    std::string getName() const { return name_; }
};

// Single inheritance
class Dog : public Animal {
private:
    std::string breed_;

public:
    Dog(const std::string& name, int age, const std::string& breed)
        : Animal(name, age), breed_(breed) {
        std::cout << "Dog '" << name_ << "' created\n";
    }

    ~Dog() override {
        std::cout << "Dog '" << name_ << "' destroyed\n";
    }

    void makeSound() const override {
        std::cout << "Woof! Woof!\n";
    }

    void fetch() const {
        std::cout << name_ << " is fetching the ball\n";
    }
};

// Multiple inheritance example
class Bird {
protected:
    double wingspan_;

public:
    Bird(double wingspan) : wingspan_(wingspan) {}

    void fly() const {
        std::cout << "Flying with " << wingspan_ << "m wingspan\n";
    }
};

class FlyingDog : public Dog, public Bird {
public:
    FlyingDog(const std::string& name, int age, const std::string& breed, double wingspan)
        : Dog(name, age, breed), Bird(wingspan) {
        std::cout << "FlyingDog created\n";
    }

    void makeSound() const override {
        std::cout << "Woof! (but from the sky)\n";
    }
};

int main() {
    std::cout << "=== Inheritance Demo ===\n\n";

    // Single inheritance
    Dog dog("Buddy", 3, "Golden Retriever");
    dog.makeSound();
    dog.eat();
    dog.fetch();

    std::cout << "\n";

    // Polymorphism through base pointer
    Animal* animalPtr = &dog;
    animalPtr->makeSound(); // Calls Dog's version

    std::cout << "\n";

    // Multiple inheritance
    FlyingDog flyingDog("Sky", 2, "Flying Breed", 2.5);
    flyingDog.makeSound();
    flyingDog.fly();

    std::cout << "\n=== Tips ===\n";
    std::cout << "1. Always make base class destructors virtual\n";
    std::cout << "2. Use 'override' keyword for clarity and safety\n";
    std::cout << "3. Be careful with multiple inheritance - can cause diamond problem\n";
    std::cout << "4. Prefer composition over inheritance when possible\n";
    std::cout << "5. Use protected for members that derived classes should access\n";

    return 0;
}