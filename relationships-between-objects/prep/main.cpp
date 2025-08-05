#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <cmath>

// ===== COMPOSITION ÖRNEĞI =====
// Point sınıfı - Triangle'ın parçası olacak
class Point {
private:
    int m_x, m_y;
    
public:
    // Parametreli constructor - default yok!
    Point(int x, int y) : m_x{x}, m_y{y} {
        std::cout << "Point(" << m_x << "," << m_y << ") oluşturuldu\n";
    }
    
    // Copy constructor
    Point(const Point& other) : m_x{other.m_x}, m_y{other.m_y} {
        std::cout << "Point(" << m_x << "," << m_y << ") kopyalandı\n";
    }
    
    // Destructor
    ~Point() {
        std::cout << "Point(" << m_x << "," << m_y << ") yok edildi\n";
    }
    
    // Getter metodları
    int getX() const { return m_x; }
    int getY() const { return m_y; }
    
    // İki nokta arası mesafe hesaplama (operator overloading)
    double operator-(const Point& other) const {
        int dx = m_x - other.m_x;
        int dy = m_y - other.m_y;
        return sqrt(dx*dx + dy*dy);
    }
    
    void print() const {
        std::cout << "(" << m_x << "," << m_y << ")";
    }
};

// Triangle sınıfı - COMPOSITION ilişkisi
class Triangle {
private:
    // Composition: Triangle silinince Point'ler de silinir
    Point m_corner1, m_corner2, m_corner3;
    
public:
    // Constructor 1: Koordinatları alır
    Triangle(int x1, int y1, int x2, int y2, int x3, int y3)
        : m_corner1{x1, y1}, m_corner2{x2, y2}, m_corner3{x3, y3} {
        std::cout << "Triangle oluşturuldu (koordinatlarla)\n";
    }
    
    // Constructor 2: Mevcut Point'lerin kopyalarını alır
    Triangle(const Point& p1, const Point& p2, const Point& p3)
        : m_corner1{p1}, m_corner2{p2}, m_corner3{p3} {
        std::cout << "Triangle oluşturuldu (Point referanslarıyla)\n";
    }
    
    ~Triangle() {
        std::cout << "Triangle yok edildi\n";
    }
    
    // Çevreyi hesapla - member nesnelerin metodlarını kullan
    double getPerimeter() const {
        return (m_corner2 - m_corner1) + 
               (m_corner3 - m_corner2) + 
               (m_corner1 - m_corner3);
    }
    
    void print() const {
        std::cout << "Triangle köşeleri: ";
        m_corner1.print(); std::cout << " ";
        m_corner2.print(); std::cout << " ";
        m_corner3.print(); std::cout << "\n";
    }
};

// ===== AGGREGATION ÖRNEĞI =====
// ClassRoom sınıfı - Course'un bir parçası değil, sadece kullanılır
class ClassRoom {
private:
    std::string m_building;
    std::string m_id;
    unsigned int m_capacity;
    
public:
    ClassRoom(const std::string& building, const std::string& id, unsigned int capacity)
        : m_building{building}, m_id{id}, m_capacity{capacity} {
        std::cout << "ClassRoom " << m_id << " oluşturuldu\n";
    }
    
    ~ClassRoom() {
        std::cout << "ClassRoom " << m_id << " yok edildi\n";
    }
    
    unsigned int getCapacity() const { return m_capacity; }
    std::string getId() const { return m_id; }
    std::string getBuilding() const { return m_building; }
};

// Course sınıfı - AGGREGATION ilişkisi
class Course {
private:
    std::string m_crn;
    unsigned int m_numOfStudents;
    const ClassRoom* m_classRoom; // Aggregation: pointer/referans
    
public:
    // Constructor - dışarıdan ClassRoom referansı alır
    Course(const std::string& crn, unsigned int numStudents, const ClassRoom* room)
        : m_crn{crn}, m_numOfStudents{numStudents}, m_classRoom{room} {
        std::cout << "Course " << m_crn << " oluşturuldu\n";
    }
    
    ~Course() {
        // ClassRoom'u silmez! Aggregation
        std::cout << "Course " << m_crn << " yok edildi\n";
    }
    
    bool isAvailable() const {
        return m_classRoom->getCapacity() > m_numOfStudents;
    }
    
    const ClassRoom* getClassRoom() const { return m_classRoom; }
    
    void print() const {
        std::cout << "Course: " << m_crn 
                  << ", Öğrenci: " << m_numOfStudents
                  << ", Sınıf: " << m_classRoom->getId() << "\n";
    }
};

// ===== ASSOCIATION ÖRNEĞI =====
// Student sınıfı
class Student {
private:
    std::string m_name;
    std::string m_id;
    std::vector<Course*> m_courses; // Association: many-to-many
    
public:
    Student(const std::string& name, const std::string& id)
        : m_name{name}, m_id{id} {
        std::cout << "Student " << m_name << " oluşturuldu\n";
    }
    
    ~Student() {
        // Course'ları silmez! Association
        std::cout << "Student " << m_name << " yok edildi\n";
    }
    
    // Derse kayıt ol
    void enrollCourse(Course* course) {
        m_courses.push_back(course);
        std::cout << m_name << " " << course->getClassRoom()->getId() 
                  << " dersine kayıt oldu\n";
    }
    
    std::string getName() const { return m_name; }
    std::string getId() const { return m_id; }
    
    void printCourses() const {
        std::cout << m_name << "'in dersleri:\n";
        for(const auto* course : m_courses) {
            std::cout << "  - " << course->getClassRoom()->getId() << "\n";
        }
    }
};

// ===== VISIBILITY ÖRNEĞI =====
// GraphicTools sınıfı - Parameter visibility için
class GraphicTools {
public:
    GraphicTools() {
        std::cout << "GraphicTools oluşturuldu\n";
    }
    
    ~GraphicTools() {
        std::cout << "GraphicTools yok edildi\n";
    }
    
    // Parameter visibility - Point referansı alır
    double distanceFromOrigin(const Point& point) const {
        double x = point.getX();
        double y = point.getY();
        return sqrt(x*x + y*y);
    }
};

// AdvancedPoint sınıfı - Attribute visibility için
class AdvancedPoint {
private:
    int m_x, m_y;
    GraphicTools* m_toolPtr; // Attribute visibility
    
public:
    AdvancedPoint(int x, int y, GraphicTools* tools)
        : m_x{x}, m_y{y}, m_toolPtr{tools} {
        std::cout << "AdvancedPoint(" << m_x << "," << m_y << ") oluşturuldu\n";
    }
    
    ~AdvancedPoint() {
        std::cout << "AdvancedPoint(" << m_x << "," << m_y << ") yok edildi\n";
    }
    
    int getX() const { return m_x; }
    int getY() const { return m_y; }
    
    // 'this' pointer'ı gönder - Parameter visibility
    double distanceFromOrigin() const {
        Point tempPoint(m_x, m_y); // Local visibility
        return m_toolPtr->distanceFromOrigin(tempPoint);
    }
};

// ===== MAIN FUNCTION =====
int main() {
    std::cout << "\n=== COMPOSITION ÖRNEĞİ ===\n";
    {
        // Triangle oluşturulduğunda Point'ler de otomatik oluşturulur
        Triangle triangle1(0, 0, 10, 0, 5, 10);
        triangle1.print();
        std::cout << "Çevre: " << triangle1.getPerimeter() << "\n\n";
        
        // Mevcut Point'lerle Triangle oluştur
        Point p1(1, 1), p2(4, 1), p3(2, 4);
        Triangle triangle2(p1, p2, p3); // Copy constructor çağrılır
        triangle2.print();
    } // Scope bitince önce Triangle sonra Point'ler silinir
    
    std::cout << "\n=== AGGREGATION ÖRNEĞİ ===\n";
    {
        // ClassRoom bağımsız oluşturulur
        ClassRoom room1("EEB", "1101", 150);
        ClassRoom room2("EEB", "1102", 100);
        
        // Course'lar ClassRoom referansı alır
        Course course1("BLG223E", 120, &room1);
        Course course2("BLG233E", 80, &room2);
        
        course1.print();
        std::cout << "Uygunluk: " << (course1.isAvailable() ? "Var" : "Yok") << "\n";
        course2.print();
        std::cout << "Uygunluk: " << (course2.isAvailable() ? "Var" : "Yok") << "\n";
    } // Course'lar silinir ama ClassRoom'lar da silinir (aynı scope'ta)
    
    std::cout << "\n=== ASSOCIATION ÖRNEĞİ ===\n";
    {
        ClassRoom room3("ITU", "2201", 200);
        Course course3("BLG252E", 150, &room3);
        
        Student student1("Ahmet Yılmaz", "12345");
        Student student2("Fatma Kaya", "67890");
        
        // Öğrenciler derse kayıt olur - bidirectional association
        student1.enrollCourse(&course3);
        student2.enrollCourse(&course3);
        
        student1.printCourses();
        student2.printCourses();
    }
    
    std::cout << "\n=== VISIBILITY ÖRNEĞİ ===\n";
    {
        GraphicTools tools;
        AdvancedPoint point1(3, 4, &tools); // Attribute visibility
        
        std::cout << "Orijine uzaklık: " << point1.distanceFromOrigin() << "\n";
        // Bu çağrıda: parameter visibility ve local visibility kullanılır
    }
    
    std::cout << "\n=== PROGRAM BİTTİ ===\n";
    return 0;
}

/* 
ÇIKTI AÇIKLAMASI:
1. COMPOSITION: Point'ler Triangle'dan önce oluşturulur, Triangle'dan sonra silinir
2. AGGREGATION: ClassRoom ve Course bağımsız yaşam döngüleri
3. ASSOCIATION: Student ve Course birbirlerini kullanır ama sahiplik yok
4. VISIBILITY: Farklı görünürlük türleri gösterilir

ÖNEMLİ NOKTALAR:
- Constructor/Destructor sıralaması
- Member initializer list kullanımı
- Pointer/referans kullanımı
- Yaşam döngüsü yönetimi
*/