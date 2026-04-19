#include <iostream>
#include <vector>
#include <memory>

/**
 * OOP Tip #3: Polymorphism
 *
 * Key concepts:
 * - Compile-time polymorphism: function/operator overloading
 * - Runtime polymorphism: virtual functions, abstract classes
 * - Dynamic binding through virtual tables
 * - Smart pointers for polymorphic objects
 *
 * Trick: Use std::unique_ptr for exclusive ownership and std::shared_ptr
 * for shared ownership of polymorphic objects.
 */

class Shape {
protected:
    std::string color_;

public:
    Shape(const std::string& color) : color_(color) {}
    virtual ~Shape() = default;

    virtual double area() const = 0; // Pure virtual function
    virtual void draw() const {
        std::cout << "Drawing a " << color_ << " shape\n";
    }

    std::string getColor() const { return color_; }
};

class Circle : public Shape {
private:
    double radius_;

public:
    Circle(const std::string& color, double radius)
        : Shape(color), radius_(radius) {}

    double area() const override {
        return 3.14159 * radius_ * radius_;
    }

    void draw() const override {
        std::cout << "Drawing a " << color_ << " circle with radius " << radius_ << "\n";
    }
};

class Rectangle : public Shape {
private:
    double width_, height_;

public:
    Rectangle(const std::string& color, double width, double height)
        : Shape(color), width_(width), height_(height) {}

    double area() const override {
        return width_ * height_;
    }

    void draw() const override {
        std::cout << "Drawing a " << color_ << " rectangle " << width_ << "x" << height_ << "\n";
    }
};

// Function overloading (compile-time polymorphism)
class Calculator {
public:
    int add(int a, int b) { return a + b; }
    double add(double a, double b) { return a + b; }
    std::string add(const std::string& a, const std::string& b) { return a + b; }
};

// Operator overloading
class Complex {
private:
    double real_, imag_;

public:
    Complex(double real = 0, double imag = 0) : real_(real), imag_(imag) {}

    Complex operator+(const Complex& other) const {
        return Complex(real_ + other.real_, imag_ + other.imag_);
    }

    void print() const {
        std::cout << real_ << " + " << imag_ << "i\n";
    }
};

int main() {
    std::cout << "=== Polymorphism Demo ===\n\n";

    // Runtime polymorphism with smart pointers
    std::vector<std::unique_ptr<Shape>> shapes;

    shapes.push_back(std::make_unique<Circle>("red", 5.0));
    shapes.push_back(std::make_unique<Rectangle>("blue", 4.0, 6.0));
    shapes.push_back(std::make_unique<Circle>("green", 3.0));

    for (const auto& shape : shapes) {
        shape->draw();
        std::cout << "Area: " << shape->area() << "\n\n";
    }

    // Function overloading
    Calculator calc;
    std::cout << "5 + 3 = " << calc.add(5, 3) << "\n";
    std::cout << "5.5 + 3.2 = " << calc.add(5.5, 3.2) << "\n";
    std::cout << "\"Hello\" + \" World\" = " << calc.add("Hello", " World") << "\n\n";

    // Operator overloading
    Complex c1(3, 4), c2(1, 2);
    Complex c3 = c1 + c2;
    std::cout << "Complex addition: ";
    c3.print();

    std::cout << "\n=== Tips ===\n";
    std::cout << "1. Use virtual destructors in base classes\n";
    std::cout << "2. Prefer smart pointers over raw pointers for polymorphism\n";
    std::cout << "3. Use 'override' and 'final' keywords for clarity\n";
    std::cout << "4. Pure virtual functions make classes abstract\n";
    std::cout << "5. Function overloading is resolved at compile-time\n";
    std::cout << "6. Virtual functions have a small performance cost due to v-table lookup\n";

    return 0;
}