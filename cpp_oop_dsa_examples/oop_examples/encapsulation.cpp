#include <iostream>
#include <string>

/**
 * OOP Tip #4: Encapsulation
 *
 * Key concepts:
 * - Data hiding with access specifiers (private, protected, public)
 * - Getter/setter methods for controlled access
 * - Validation in setters
 * - Const-correctness
 * - Friend functions/classes for exceptional cases
 *
 * Trick: Use const member functions for methods that don't modify the object.
 * This allows calling them on const objects and enables compiler optimizations.
 */

class BankAccount {
private:
    std::string accountNumber_;
    double balance_;
    std::string ownerName_;
    bool isActive_;

public:
    // Constructor with validation
    BankAccount(const std::string& accountNumber, const std::string& ownerName)
        : accountNumber_(accountNumber), balance_(0.0), ownerName_(ownerName), isActive_(true) {
        if (accountNumber.empty() || ownerName.empty()) {
            throw std::invalid_argument("Account number and owner name cannot be empty");
        }
    }

    // Getters (const member functions)
    std::string getAccountNumber() const { return accountNumber_; }
    double getBalance() const { return balance_; }
    std::string getOwnerName() const { return ownerName_; }
    bool isActive() const { return isActive_; }

    // Setters with validation
    void setOwnerName(const std::string& name) {
        if (!name.empty()) {
            ownerName_ = name;
        } else {
            std::cout << "Error: Owner name cannot be empty\n";
        }
    }

    // Business logic methods
    bool deposit(double amount) {
        if (amount > 0 && isActive_) {
            balance_ += amount;
            std::cout << "Deposited $" << amount << ". New balance: $" << balance_ << "\n";
            return true;
        }
        return false;
    }

    bool withdraw(double amount) {
        if (amount > 0 && amount <= balance_ && isActive_) {
            balance_ -= amount;
            std::cout << "Withdrew $" << amount << ". New balance: $" << balance_ << "\n";
            return true;
        }
        return false;
    }

    void closeAccount() {
        isActive_ = false;
        std::cout << "Account closed\n";
    }

    // Friend function for exceptional access (use sparingly!)
    friend void auditAccount(const BankAccount& account);
};

// Friend function implementation
void auditAccount(const BankAccount& account) {
    std::cout << "AUDIT: Account " << account.accountNumber_
              << " has balance $" << account.balance_ << "\n";
}

class SecureBankAccount : private BankAccount {
public:
    // Expose only necessary public interface
    using BankAccount::getBalance;
    using BankAccount::deposit;
    using BankAccount::withdraw;
    using BankAccount::getAccountNumber;

    SecureBankAccount(const std::string& accountNumber, const std::string& ownerName)
        : BankAccount(accountNumber, ownerName) {}

    // Add additional security
    bool secureWithdraw(double amount, const std::string& pin) {
        if (pin == "1234") { // Simple PIN check (in real code, use proper authentication)
            return withdraw(amount);
        } else {
            std::cout << "Invalid PIN\n";
            return false;
        }
    }
};

int main() {
    std::cout << "=== Encapsulation Demo ===\n\n";

    try {
        BankAccount account("123456789", "John Doe");

        std::cout << "Account: " << account.getAccountNumber() << "\n";
        std::cout << "Owner: " << account.getOwnerName() << "\n";
        std::cout << "Initial balance: $" << account.getBalance() << "\n\n";

        account.deposit(1000);
        account.withdraw(200);
        account.setOwnerName("Jane Doe");

        // Friend function access
        auditAccount(account);

        std::cout << "\n";

        // Private inheritance example
        SecureBankAccount secureAccount("987654321", "Bob Smith");
        secureAccount.deposit(500);
        secureAccount.secureWithdraw(100, "1234"); // Correct PIN
        secureAccount.secureWithdraw(50, "0000");  // Wrong PIN

    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }

    std::cout << "\n=== Tips ===\n";
    std::cout << "1. Keep data members private and provide controlled access via methods\n";
    std::cout << "2. Use const member functions for read-only operations\n";
    std::cout << "3. Validate input in setters to maintain object invariants\n";
    std::cout << "4. Use friend declarations sparingly - they break encapsulation\n";
    std::cout << "5. Private inheritance hides implementation details completely\n";
    std::cout << "6. Prefer composition over private inheritance when possible\n";

    return 0;
}