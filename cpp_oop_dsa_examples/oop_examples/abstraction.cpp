#include <iostream>
#include <vector>
#include <memory>

/**
 * OOP Tip #5: Abstraction
 *
 * Key concepts:
 * - Abstract classes with pure virtual functions
 * - Interfaces (classes with only pure virtual functions)
 * - Implementation hiding
 * - Factory pattern for object creation
 * - Dependency inversion principle
 *
 * Trick: Use abstract base classes to define interfaces that concrete
 * classes must implement, enabling loose coupling and testability.
 */

// Abstract base class (interface)
class DatabaseConnection {
public:
    virtual ~DatabaseConnection() = default;

    virtual bool connect() = 0;
    virtual bool disconnect() = 0;
    virtual bool executeQuery(const std::string& query) = 0;
    virtual std::vector<std::string> getResults() const = 0;
};

// Concrete implementation 1
class MySQLConnection : public DatabaseConnection {
private:
    bool connected_ = false;
    std::vector<std::string> results_;

public:
    bool connect() override {
        // Simulate connection logic
        connected_ = true;
        std::cout << "Connected to MySQL database\n";
        return true;
    }

    bool disconnect() override {
        connected_ = false;
        std::cout << "Disconnected from MySQL database\n";
        return true;
    }

    bool executeQuery(const std::string& query) override {
        if (!connected_) return false;

        // Simulate query execution
        std::cout << "MySQL executing: " << query << "\n";
        results_ = {"Row 1", "Row 2", "Row 3"};
        return true;
    }

    std::vector<std::string> getResults() const override {
        return results_;
    }
};

// Concrete implementation 2
class PostgreSQLConnection : public DatabaseConnection {
private:
    bool connected_ = false;
    std::vector<std::string> results_;

public:
    bool connect() override {
        connected_ = true;
        std::cout << "Connected to PostgreSQL database\n";
        return true;
    }

    bool disconnect() override {
        connected_ = false;
        std::cout << "Disconnected from PostgreSQL database\n";
        return true;
    }

    bool executeQuery(const std::string& query) override {
        if (!connected_) return false;

        std::cout << "PostgreSQL executing: " << query << "\n";
        results_ = {"Data A", "Data B", "Data C"};
        return true;
    }

    std::vector<std::string> getResults() const override {
        return results_;
    }
};

// Abstract factory
class DatabaseFactory {
public:
    enum class DatabaseType { MySQL, PostgreSQL };

    static std::unique_ptr<DatabaseConnection> createConnection(DatabaseType type) {
        switch (type) {
            case DatabaseType::MySQL:
                return std::make_unique<MySQLConnection>();
            case DatabaseType::PostgreSQL:
                return std::make_unique<PostgreSQLConnection>();
            default:
                return nullptr;
        }
    }
};

// High-level module that depends on abstraction
class DataProcessor {
private:
    std::unique_ptr<DatabaseConnection> db_;

public:
    DataProcessor(std::unique_ptr<DatabaseConnection> db) : db_(std::move(db)) {}

    void processData() {
        if (db_->connect()) {
            db_->executeQuery("SELECT * FROM users");
            auto results = db_->getResults();

            std::cout << "Processing " << results.size() << " records:\n";
            for (const auto& row : results) {
                std::cout << "  " << row << "\n";
            }

            db_->disconnect();
        }
    }
};

int main() {
    std::cout << "=== Abstraction Demo ===\n\n";

    // Using MySQL
    std::cout << "Using MySQL:\n";
    auto mysqlDb = DatabaseFactory::createConnection(DatabaseFactory::DatabaseType::MySQL);
    DataProcessor processor1(std::move(mysqlDb));
    processor1.processData();

    std::cout << "\nUsing PostgreSQL:\n";
    auto postgresDb = DatabaseFactory::createConnection(DatabaseFactory::DatabaseType::PostgreSQL);
    DataProcessor processor2(std::move(postgresDb));
    processor2.processData();

    std::cout << "\n=== Tips ===\n";
    std::cout << "1. Use pure virtual functions to create abstract interfaces\n";
    std::cout << "2. Abstract classes cannot be instantiated directly\n";
    std::cout << "3. Factory patterns help create objects without specifying concrete types\n";
    std::cout << "4. Dependency inversion: depend on abstractions, not concretions\n";
    std::cout << "5. Abstract base classes enable polymorphism and loose coupling\n";
    std::cout << "6. Use smart pointers to manage polymorphic objects safely\n";

    return 0;
}