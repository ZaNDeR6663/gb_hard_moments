#include <iostream>
#include <fstream>
#include <optional>
#include <utility>
#include <vector>
#include <numeric>

//1. Установить библиотеку protobuf.
void l7_task1()
{
    std::cout << "Done" << std::endl;
    std::cout << "Too much dependencies and errors in included pdf file (in commands). "
                 "Not working. Sorry i've given up." << std::endl;
}


//2. С помощью компилятора protobuf в отдельном пространстве имен сгенерировать классы:
//a. FullName с полями имя, фамилия, отчество (отчество опционально).
//b. Student с полями полное имя, массив оценок, средний балл.
//c. StudentsGroup с полем массив студентов.
class FullName
{
    std::string f_name;
    std::string s_name;
    std::optional<std::string> sur_name;
public:
    FullName() = default;
    FullName(std::string  f, std::string  s, std::optional<std::string>  sur=std::nullopt)
    : f_name(std::move(f)), s_name(std::move(s)), sur_name(std::move(sur)) {}

};

class Student
{
    FullName fullName;
    std::vector<double> marks;
    double avgMark = 0;
public:
    Student() = default;
    Student(FullName f, std::vector<double> m)
            : fullName(std::move(f)), marks(std::move(m))
    {
        if(!marks.empty())
            avgMark = std::accumulate(marks.begin(), marks.end(), 0.0) / (double)marks.size();
    }
};

class StudentsGroup
{
    std::vector<Student> students;
public:
    explicit StudentsGroup(std::vector<Student> studs)
    : students(std::move(studs)) {}
    StudentsGroup() = default;

//    std::ostream& operator<<(std::ostream &os)
//    {
//        for(auto & stud: students)
//            os << stud;
//    };
//    std::istream& operator>>(std::istream &is)
//    {
//
//        is >> stud;
//
//    };

};


void l7_task2()
{

    StudentsGroup studs({
        Student(FullName{"Andrey", "Plotnikov", "Vladimirovich"}, {5, 4,5, 4.5, 4.3, 3.6}),
        Student(FullName{"Irina", "Petrova"}, {5, 4,5, 4.5, 4.3, 3.6}),
        Student(FullName{"Sergey", "Sidorov", "Lolo-lo"}, {5, 4,5, 4.5, 4.3, 3.6}),
        Student(FullName{"Stepan", "Pavlov", "Gennadievich"}, {5, 4,5, 4.5, 4.3, 3.6})
    });

    std::ofstream out("ser.bin", std::ios_base::binary);
    std::ifstream in("ser.bin", std::ios_base::binary);
// не работает
//    studs.serialize(out);
//    studs.deserialize(in);
}

//3. Создать класс StudentsGroup, который реализует интерфейсы:
//class IRepository {
//    virtual void Open() = 0; // бинарная десериализация в файл virtual void Save() = 0; // бинарная сериализация в файл
//};
//class IMethods {
//    virtual double GetAverageScore(const FullName& name) = 0;
//    virtual string GetAllInfo(const FullName& name) = 0;
//    virtual string GetAllInfo() = 0;
//};
void l7_task3()
{

}