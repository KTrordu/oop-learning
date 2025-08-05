#include <iostream>
#include <string>
#include <vector>
#include <memory>

// =============================================================================
// 1. TEMEL BASE CLASS - EMPLOYEE (Çalışan)
// =============================================================================
class Employee {
protected:  // Derived class'lar erişebilsin diye protected
    std::string m_name;
    int m_id;
    double m_baseSalary;
    
public:
    // Constructor
    Employee(const std::string& name, int id, double baseSalary)
        : m_name{name}, m_id{id}, m_baseSalary{baseSalary} {
        std::cout << "Employee constructor called for: " << m_name << std::endl;
    }
    
    // Virtual destructor (polymorphism için önemli)
    virtual ~Employee() {
        std::cout << "Employee destructor called for: " << m_name << std::endl;
    }
    
    // Getter methods
    std::string getName() const { return m_name; }
    int getId() const { return m_id; }
    double getBaseSalary() const { return m_baseSalary; }
    
    // Virtual method - derived class'larda override edilebilir
    virtual double calculateSalary() const {
        std::cout << "Employee::calculateSalary() called" << std::endl;
        return m_baseSalary;
    }
    
    // Virtual method - derived class'larda override edilebilir
    virtual void displayInfo() const {
        std::cout << "Employee Info:" << std::endl;
        std::cout << "  Name: " << m_name << std::endl;
        std::cout << "  ID: " << m_id << std::endl;
        std::cout << "  Base Salary: $" << m_baseSalary << std::endl;
    }
    
    // Non-virtual method - tüm çalışanlar için aynı
    void clockIn() const {
        std::cout << m_name << " clocked in at 9:00 AM" << std::endl;
    }
};

// =============================================================================
// 2. DERIVED CLASS - MANAGER (Yönetici)
// =============================================================================
class Manager : public Employee {  // PUBLIC INHERITANCE
private:
    double m_bonus;
    int m_teamSize;
    
public:
    // Constructor - base class constructor'ını çağırır
    Manager(const std::string& name, int id, double baseSalary, 
            double bonus, int teamSize)
        : Employee{name, id, baseSalary}, m_bonus{bonus}, m_teamSize{teamSize} {
        std::cout << "Manager constructor called for: " << name << std::endl;
    }
    
    // Destructor
    ~Manager() {
        std::cout << "Manager destructor called for: " << m_name << std::endl;
    }
    
    // OVERRIDE - Base class method'unu yeniden tanımlama
    double calculateSalary() const override {
        std::cout << "Manager::calculateSalary() called" << std::endl;
        return m_baseSalary + m_bonus + (m_teamSize * 100); // Takım başına bonus
    }
    
    // OVERRIDE - Base class method'unu yeniden tanımlama
    void displayInfo() const override {
        Employee::displayInfo(); // Base class method'unu çağır
        std::cout << "  Role: Manager" << std::endl;
        std::cout << "  Bonus: $" << m_bonus << std::endl;
        std::cout << "  Team Size: " << m_teamSize << std::endl;
    }
    
    // YENİ METHOD - Sadece Manager'da var
    void conductMeeting() const {
        std::cout << m_name << " is conducting a team meeting with " 
                  << m_teamSize << " members." << std::endl;
    }
    
    // Getter methods
    double getBonus() const { return m_bonus; }
    int getTeamSize() const { return m_teamSize; }
};

// =============================================================================
// 3. DERIVED CLASS - DEVELOPER (Geliştirici)
// =============================================================================
class Developer : public Employee {  // PUBLIC INHERITANCE
private:
    std::string m_programmingLanguage;
    int m_projectsCompleted;
    
public:
    // Constructor
    Developer(const std::string& name, int id, double baseSalary,
              const std::string& language, int projects)
        : Employee{name, id, baseSalary}, 
          m_programmingLanguage{language}, m_projectsCompleted{projects} {
        std::cout << "Developer constructor called for: " << name << std::endl;
    }
    
    // Destructor
    ~Developer() {
        std::cout << "Developer destructor called for: " << m_name << std::endl;
    }
    
    // OVERRIDE - Proje sayısına göre maaş hesaplama
    double calculateSalary() const override {
        std::cout << "Developer::calculateSalary() called" << std::endl;
        return m_baseSalary + (m_projectsCompleted * 500); // Proje başına bonus
    }
    
    // OVERRIDE
    void displayInfo() const override {
        Employee::displayInfo(); // Base class method'unu çağır
        std::cout << "  Role: Developer" << std::endl;
        std::cout << "  Programming Language: " << m_programmingLanguage << std::endl;
        std::cout << "  Projects Completed: " << m_projectsCompleted << std::endl;
    }
    
    // YENİ METHOD - Sadece Developer'da var
    void writeCode() const {
        std::cout << m_name << " is writing code in " 
                  << m_programmingLanguage << std::endl;
    }
    
    // Getter methods
    std::string getProgrammingLanguage() const { return m_programmingLanguage; }
    int getProjectsCompleted() const { return m_projectsCompleted; }
};

// =============================================================================
// 4. MULTIPLE INHERITANCE ÖRNEĞI - RESEARCH ASSISTANT
// =============================================================================
class Student {
protected:
    std::string m_university;
    std::string m_degree;
    
public:
    Student(const std::string& university, const std::string& degree)
        : m_university{university}, m_degree{degree} {
        std::cout << "Student constructor called" << std::endl;
    }
    
    virtual ~Student() {
        std::cout << "Student destructor called" << std::endl;
    }
    
    void study() const {
        std::cout << "Studying for " << m_degree << " at " << m_university << std::endl;
    }
    
    std::string getUniversity() const { return m_university; }
    std::string getDegree() const { return m_degree; }
};

class ResearchAssistant : public Employee, public Student {  // MULTIPLE INHERITANCE
private:
    std::string m_researchArea;
    
public:
    ResearchAssistant(const std::string& name, int id, double baseSalary,
                     const std::string& university, const std::string& degree,
                     const std::string& researchArea)
        : Employee{name, id, baseSalary}, Student{university, degree},
          m_researchArea{researchArea} {
        std::cout << "ResearchAssistant constructor called for: " << name << std::endl;
    }
    
    ~ResearchAssistant() {
        std::cout << "ResearchAssistant destructor called for: " << m_name << std::endl;
    }
    
    // OVERRIDE Employee method
    double calculateSalary() const override {
        std::cout << "ResearchAssistant::calculateSalary() called" << std::endl;
        return m_baseSalary * 0.8; // Araştırma görevlileri daha az maaş alır
    }
    
    // OVERRIDE Employee method
    void displayInfo() const override {
        Employee::displayInfo();
        std::cout << "  Role: Research Assistant" << std::endl;
        std::cout << "  University: " << m_university << std::endl;
        std::cout << "  Degree: " << m_degree << std::endl;
        std::cout << "  Research Area: " << m_researchArea << std::endl;
    }
    
    void conductResearch() const {
        std::cout << m_name << " is conducting research in " 
                  << m_researchArea << std::endl;
    }
};

// =============================================================================
// 5. PRIVATE INHERITANCE ÖRNEĞI
// =============================================================================
class SecureEmployee : private Employee {  // PRIVATE INHERITANCE
private:
    std::string m_securityLevel;
    
public:
    SecureEmployee(const std::string& name, int id, double baseSalary,
                   const std::string& securityLevel)
        : Employee{name, id, baseSalary}, m_securityLevel{securityLevel} {
        std::cout << "SecureEmployee constructor called" << std::endl;
    }
    
    // Public interface - sadece belirli metodları açığa çıkar
    void showPublicInfo() const {
        std::cout << "Name: " << getName() << std::endl;  // protected getter kullanılabilir
        std::cout << "Security Level: " << m_securityLevel << std::endl;
        // displayInfo(); // Bu private inheritance olduğu için dışarıdan erişilemez
    }
    
    // Base class'ın bazı metodlarını tekrar public yapma
    using Employee::clockIn;  // clockIn metodunu public yap
    
    double getCalculatedSalary() const {
        return calculateSalary(); // Private olarak inherited method'u kullan
    }
};

// =============================================================================
// 6. POLYMORPHISM VE POINTER KULLANIMI
// =============================================================================
void demonstratePolymorphism() {
    std::cout << "\n=== POLYMORPHISM DEMONSTRATION ===" << std::endl;
    
    // Base class pointer'ları ile derived class objelerini tutma
    std::vector<std::unique_ptr<Employee>> employees;
    
    employees.push_back(std::make_unique<Employee>("John Doe", 1001, 50000));
    employees.push_back(std::make_unique<Manager>("Jane Smith", 1002, 70000, 15000, 5));
    employees.push_back(std::make_unique<Developer>("Bob Johnson", 1003, 60000, "C++", 8));
    employees.push_back(std::make_unique<ResearchAssistant>("Alice Brown", 1004, 40000, 
                                                           "MIT", "PhD", "AI Research"));
    
    // Polymorphic behavior - her obje kendi calculateSalary() metodunu çağırır
    for (const auto& emp : employees) {
        std::cout << "\n--- Employee Details ---" << std::endl;
        emp->displayInfo();
        std::cout << "Total Salary: $" << emp->calculateSalary() << std::endl;
        emp->clockIn(); // Tüm çalışanlar için aynı davranış
        std::cout << std::endl;
    }
}

// =============================================================================
// 7. MAIN FUNCTION - TÜM ÖRNEKLERİ TEST ETME
// =============================================================================
int main() {
    std::cout << "=== INHERITANCE EXAMPLES ===" << std::endl;
    
    // 1. Basic inheritance test
    std::cout << "\n1. Basic Employee Creation:" << std::endl;
    Employee emp("Alice", 100, 45000);
    emp.displayInfo();
    std::cout << "Salary: $" << emp.calculateSalary() << std::endl;
    
    std::cout << "\n2. Manager Creation (shows constructor chain):" << std::endl;
    Manager mgr("Bob", 200, 60000, 10000, 3);
    mgr.displayInfo();
    std::cout << "Salary: $" << mgr.calculateSalary() << std::endl;
    mgr.conductMeeting(); // Manager'a özel method
    
    std::cout << "\n3. Developer Creation:" << std::endl;
    Developer dev("Carol", 300, 55000, "Python", 12);
    dev.displayInfo();
    dev.writeCode(); // Developer'a özel method
    
    std::cout << "\n4. Multiple Inheritance - Research Assistant:" << std::endl;
    ResearchAssistant ra("David", 400, 35000, "Stanford", "PhD", "Machine Learning");
    ra.displayInfo();
    ra.study();        // Student'tan gelen method
    ra.conductResearch(); // Kendi methodu
    
    std::cout << "\n5. Private Inheritance Example:" << std::endl;
    SecureEmployee secEmp("Eve", 500, 80000, "Top Secret");
    secEmp.showPublicInfo();
    secEmp.clockIn(); // using declaration ile public yapılmış
    // secEmp.displayInfo(); // ERROR! Private inheritance nedeniyle erişilemez
    
    std::cout << "\n6. Pointer and Reference Behavior:" << std::endl;
    Manager* mgrPtr = &mgr;
    Employee* empPtr = mgrPtr; // Manager* -> Employee* (implicit conversion)
    
    empPtr->displayInfo(); // Manager'ın override ettiği method çağırılır (virtual)
    empPtr->clockIn();     // Employee'daki method çağırılır
    // empPtr->conductMeeting(); // ERROR! Employee'da bu method yok
    
    std::cout << "\n7. Polymorphism with containers:" << std::endl;
    demonstratePolymorphism();
    
    std::cout << "\n=== PROGRAM ENDING (destructors will be called) ===" << std::endl;
    
    return 0;
}

/* 
=============================================================================
ÖNEMLI KAVRAMLAR VE AÇIKLAMALAR:

1. PUBLIC INHERITANCE (is-a relationship):
   - Manager is-a Employee
   - Tüm public ve protected memberlar erişilebilir
   
2. PRIVATE INHERITANCE (implemented-in-terms-of):
   - SecureEmployee implemented-in-terms-of Employee
   - Base class public members private olur
   
3. MULTIPLE INHERITANCE:
   - ResearchAssistant hem Employee hem Student
   - Diamond problem'a dikkat (virtual inheritance ile çözülür)
   
4. VIRTUAL FUNCTIONS:
   - Runtime'da doğru method çağırılması (polymorphism)
   - Base class destructor'ı virtual olmalı
   
5. CONSTRUCTOR/DESTRUCTOR CHAIN:
   - Construction: Base -> Derived
   - Destruction: Derived -> Base
   
6. METHOD OVERRIDING vs HIDING:
   - Override: virtual function'ları yeniden tanımlama
   - Hiding: aynı isimli method tanımlama (virtual olmasa da)
   
7. PROTECTED MEMBERS:
   - Derived class'lar erişebilir, dış dünya erişemez
   - Encapsulation'ı koruyarak inheritance'ı destekler
   
8. USING DECLARATION:
   - Private inheritance'da belirli memberleri tekrar public yapma
   
Bu örnek inheritance'ın tüm temel kavramlarını kapsar!
=============================================================================
*/