// ==========================================
// KAPSAMLI OOP ÖRNEK PROGRAM
// Polymorphism, Templates, Smart Pointers
// ==========================================

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

// ==========================================
// BÖLÜM 1: ABSTRACT CLASS & POLYMORPHISM
// ==========================================

// Abstract Base Class - Pure Virtual Function içeriyor
class Employee {
protected:
    std::string m_name;
    int m_id;
    static int s_nextId;  // Static member - tüm nesneler için ortak

public:
    // Constructor
    Employee(const std::string& name) 
        : m_name(name), m_id(s_nextId++) {
        std::cout << "Employee constructor: " << m_name << " (ID: " << m_id << ")\n";
    }

    // Virtual Destructor - Polimorfik silme için gerekli!
    virtual ~Employee() {
        std::cout << "Employee destructor: " << m_name << "\n";
    }

    // Pure Virtual Function - Bu class'ı abstract yapar
    virtual double calculateSalary() const = 0;

    // Virtual Function - Override edilebilir
    virtual void print() const {
        std::cout << "Name: " << m_name << ", ID: " << m_id;
    }

    // Normal (non-virtual) function
    std::string getName() const { return m_name; }
    int getId() const { return m_id; }

    // Final virtual function - Override edilemez!
    virtual void companyPolicy() const final {
        std::cout << "Şirket politikası: Müşteri odaklı çalış!\n";
    }
};

// Static member initialization
int Employee::s_nextId = 1000;

// ==========================================
// DERIVED CLASSES - Inheritance & Polymorphism
// ==========================================

// Concrete Derived Class 1
class Developer : public Employee {
private:
    std::string m_programmingLanguage;
    int m_projectCount;

public:
    Developer(const std::string& name, const std::string& lang, int projects = 0)
        : Employee(name), m_programmingLanguage(lang), m_projectCount(projects) {
        std::cout << "Developer constructor: " << name << "\n";
    }

    ~Developer() override {  // override keyword - best practice
        std::cout << "Developer destructor: " << m_name << "\n";
    }

    // Pure virtual function'ı implement etmek ZORUNLU
    double calculateSalary() const override {
        return 5000.0 + (m_projectCount * 1000.0);  // Base + proje başı bonus
    }

    // Virtual function'ı override ediyoruz
    void print() const override {
        Employee::print();  // Base class versiyonunu çağır
        std::cout << ", Language: " << m_programmingLanguage
                  << ", Projects: " << m_projectCount
                  << ", Salary: $" << calculateSalary();
    }

    void code() const {  // Developer'a özel method
        std::cout << m_name << " is coding in " << m_programmingLanguage << "\n";
    }
};

// Concrete Derived Class 2
class Manager : public Employee {
private:
    int m_teamSize;
    double m_bonusPercentage;

public:
    Manager(const std::string& name, int teamSize, double bonus = 0.1)
        : Employee(name), m_teamSize(teamSize), m_bonusPercentage(bonus) {
        std::cout << "Manager constructor: " << name << "\n";
    }

    ~Manager() override {
        std::cout << "Manager destructor: " << m_name << "\n";
    }

    double calculateSalary() const override {
        double baseSalary = 7000.0;
        return baseSalary * (1 + m_bonusPercentage) + (m_teamSize * 500);
    }

    void print() const override {
        Employee::print();
        std::cout << ", Team Size: " << m_teamSize
                  << ", Bonus: " << (m_bonusPercentage * 100) << "%"
                  << ", Salary: $" << calculateSalary();
    }

    void conductMeeting() const {
        std::cout << m_name << " is conducting a meeting with " 
                  << m_teamSize << " team members\n";
    }
};

// ==========================================
// BÖLÜM 2: FUNCTION TEMPLATES
// ==========================================

// Basic Function Template
template <typename T>
T findMax(T a, T b) {
    return (a > b) ? a : b;
}

// Function Template with Multiple Parameters
template <typename T1, typename T2>
auto add(const T1& a, const T2& b) -> decltype(a + b) {
    return a + b;
}

// Function Template with Non-Type Parameter
template <typename T, int size>
void printArray(const T (&arr)[size]) {
    std::cout << "Array [";
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i];
        if (i < size - 1) std::cout << ", ";
    }
    std::cout << "]\n";
}

// Abbreviated Function Template (C++20 style)
auto multiply(auto a, auto b) {
    return a * b;
}

// ==========================================
// BÖLÜM 3: CLASS TEMPLATES
// ==========================================

// Generic Container Class Template
template <typename T>
class Stack {
private:
    static const int MAX_SIZE = 10;
    T m_data[MAX_SIZE];
    int m_top;

public:
    Stack() : m_top(0) {
        std::cout << "Stack created\n";
    }

    void push(const T& item) {
        if (m_top >= MAX_SIZE) {
            throw std::overflow_error("Stack is full!");
        }
        m_data[m_top++] = item;
    }

    T pop() {
        if (m_top <= 0) {
            throw std::underflow_error("Stack is empty!");
        }
        return m_data[--m_top];
    }

    bool isEmpty() const { return m_top == 0; }
    int size() const { return m_top; }
};

// Class Template Specialization for pointers
template <typename T>
class Stack<T*> {
private:
    static const int MAX_SIZE = 10;
    T* m_data[MAX_SIZE];
    int m_top;

public:
    Stack() : m_top(0) {
        std::cout << "Pointer Stack created\n";
    }

    void push(T* item) {
        if (m_top >= MAX_SIZE) {
            throw std::overflow_error("Pointer Stack is full!");
        }
        m_data[m_top++] = item;
    }

    T* pop() {
        if (m_top <= 0) {
            throw std::underflow_error("Pointer Stack is empty!");
        }
        return m_data[--m_top];
    }

    bool isEmpty() const { return m_top == 0; }
};

// ==========================================
// BÖLÜM 4: COMPANY CLASS - Smart Pointers Kullanımı
// ==========================================

class Company {
private:
    std::string m_name;
    std::vector<std::shared_ptr<Employee>> m_employees;  // Shared ownership
    std::weak_ptr<Manager> m_ceo;  // Weak reference to avoid circular dependency

public:
    Company(const std::string& name) : m_name(name) {
        std::cout << "Company " << m_name << " created\n";
    }

    ~Company() {
        std::cout << "Company " << m_name << " destroyed\n";
    }

    // Unique_ptr parametresi - ownership transfer
    void hireEmployee(std::unique_ptr<Employee> emp) {
        std::shared_ptr<Employee> sharedEmp = std::move(emp);
        m_employees.push_back(sharedEmp);
        
        // CEO olup olmadığını kontrol et (RTTI - dynamic_cast)
        if (auto* mgr = dynamic_cast<Manager*>(sharedEmp.get())) {
            if (mgr->getName().find("CEO") != std::string::npos) {
                m_ceo = std::dynamic_pointer_cast<Manager>(sharedEmp);
            }
        }
    }

    // Shared_ptr döndür - ownership paylaşımı
    std::shared_ptr<Employee> getEmployee(int id) {
        auto it = std::find_if(m_employees.begin(), m_employees.end(),
            [id](const std::shared_ptr<Employee>& emp) {
                return emp->getId() == id;
            });
        
        return (it != m_employees.end()) ? *it : nullptr;
    }

    // Polymorphic behavior demonstration
    void printAllEmployees() const {
        std::cout << "\n=== " << m_name << " Employee List ===\n";
        for (const auto& emp : m_employees) {
            emp->print();  // Virtual function call - polymorphism
            std::cout << "\n";
        }
    }

    double getTotalSalaries() const {
        double total = 0.0;
        for (const auto& emp : m_employees) {
            total += emp->calculateSalary();  // Pure virtual function call
        }
        return total;
    }

    void demonstratePolymorphism() {
        std::cout << "\n=== Demonstrating Polymorphism ===\n";
        
        for (const auto& emp : m_employees) {
            // Base class pointer, derived class behavior
            emp->companyPolicy();  // Final function - aynı davranış
            
            // Dynamic casting for specific behavior
            if (auto* dev = dynamic_cast<Developer*>(emp.get())) {
                dev->code();  // Developer-specific method
            } else if (auto* mgr = dynamic_cast<Manager*>(emp.get())) {
                mgr->conductMeeting();  // Manager-specific method
            }
            std::cout << "---\n";
        }
    }

    // Template member function
    template <typename T>
    void processData(T data) {
        std::cout << "Processing data: " << data << "\n";
    }
};

// ==========================================
// MAIN FUNCTION - Tüm Özellikleri Test Et
// ==========================================

int main() {
    try {
        std::cout << "====================================\n";
        std::cout << "KAPSAMLI OOP ÖRNEK PROGRAM\n";
        std::cout << "====================================\n\n";

        // BÖLÜM 1: Abstract Class Test - OLAMAZ!
        std::cout << "=== Abstract Class Test ===\n";
        // Employee emp("Test");  // HATA! Abstract class'tan nesne oluşturulamaz
        std::cout << "Abstract class'tan nesne oluşturulamaz!\n\n";

        // BÖLÜM 2: Smart Pointers & Polymorphism
        std::cout << "=== Smart Pointers & Polymorphism ===\n";
        
        // Company oluştur
        auto techCorp = std::make_unique<Company>("TechCorp");
        
        // Unique_ptr ile Employee oluştur ve transfer et
        techCorp->hireEmployee(std::make_unique<Developer>("Alice", "C++", 5));
        techCorp->hireEmployee(std::make_unique<Developer>("Bob", "Python", 3));
        techCorp->hireEmployee(std::make_unique<Manager>("CEO Charlie", 10, 0.25));
        techCorp->hireEmployee(std::make_unique<Manager>("Diana", 5, 0.15));

        // Polymorphic behavior
        techCorp->printAllEmployees();
        
        std::cout << "\nTotal Salaries: $" << std::fixed << std::setprecision(2) 
                  << techCorp->getTotalSalaries() << "\n\n";

        techCorp->demonstratePolymorphism();

        // BÖLÜM 3: Function Templates
        std::cout << "\n=== Function Templates ===\n";
        
        // Basic template
        std::cout << "Max of 10 and 20: " << findMax(10, 20) << "\n";
        std::cout << "Max of 3.14 and 2.71: " << findMax(3.14, 2.71) << "\n";
        
        // Multiple type template
        std::cout << "Add int and double: " << add(5, 3.14) << "\n";
        
        // Non-type parameter template
        int arr[] = {1, 2, 3, 4, 5};
        printArray(arr);
        
        // Abbreviated template (C++20)
        std::cout << "Multiply: " << multiply(4, 5.5) << "\n\n";

        // BÖLÜM 4: Class Templates
        std::cout << "=== Class Templates ===\n";
        
        // Stack for integers
        Stack<int> intStack;
        intStack.push(10);
        intStack.push(20);
        intStack.push(30);
        std::cout << "Popped from int stack: " << intStack.pop() << "\n";

        // Stack for strings
        Stack<std::string> stringStack;
        stringStack.push("Hello");
        stringStack.push("World");
        std::cout << "Popped from string stack: " << stringStack.pop() << "\n";

        // Template member function
        techCorp->processData(42);
        techCorp->processData("Template test");

        // BÖLÜM 5: Shared Pointer Demonstration
        std::cout << "\n=== Shared Pointer Reference Counting ===\n";
        {
            auto emp1 = techCorp->getEmployee(1000);
            std::cout << "Reference count: " << emp1.use_count() << "\n";
            {
                auto emp2 = emp1;  // Share ownership
                std::cout << "After sharing: " << emp1.use_count() << "\n";
            }
            std::cout << "After inner scope: " << emp1.use_count() << "\n";
        }

        std::cout << "\n=== Program Ending ===\n";
        // Destructors will be called automatically
        
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}

// ==========================================
// ÖZET: Bu program şunları gösteriyor:
// 
// 1. POLYMORPHISM:
//    - Virtual functions (print)
//    - Pure virtual functions (calculateSalary)
//    - Virtual destructors
//    - Override keyword kullanımı
//    - Final functions (companyPolicy)
//    - Dynamic binding (runtime polymorphism)
//
// 2. ABSTRACT CLASSES:
//    - Employee abstract base class
//    - Concrete derived classes (Developer, Manager)
//    - Abstract class'tan nesne oluşturulamaz
//
// 3. TEMPLATES:
//    - Function templates (single & multiple parameters)
//    - Class templates (Stack)
//    - Template specialization
//    - Non-type template parameters
//    - Auto return type deduction
//    - Abbreviated function templates
//
// 4. SMART POINTERS:
//    - unique_ptr (ownership transfer)
//    - shared_ptr (shared ownership)
//    - weak_ptr (no ownership)
//    - make_unique, make_shared usage
//    - Reference counting demonstration
//
// 5. MODERN C++ FEATURES:
//    - Range-based for loops
//    - Lambda expressions
//    - Auto keyword
//    - Move semantics
//    - RTTI (dynamic_cast)
// ==========================================