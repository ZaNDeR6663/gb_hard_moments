#include <iostream>
#include <optional>
#include <utility>
#include <tuple>
#include <vector>
#include <utility>
#include <fstream>
#include <algorithm>

class Person{
public:
    Person(std::string a, std::string b, std::optional<std::string> c=std::nullopt)
            : first_name(std::move(b)), second_name(std::move(a)), sur_name(std::move(c)) {};

    std::string getFirstName(){return first_name;};
    std::string getSecondName(){return second_name;};
    std::string getSurname(){return sur_name.has_value() ? sur_name.value() : "";};
private:
    std::string first_name;
    std::string second_name;
    std::optional<std::string> sur_name;

    friend std::ostream& operator<<(std::ostream& os, Person& person);
    friend bool operator<(Person& p1, Person& p2);
    friend bool operator==(Person& p1, Person& p2);

};

std::ostream& operator<<(std::ostream &os, Person& person) {
    os << person.second_name << "\t";
    os << person.first_name;
    if(person.sur_name.has_value()) {
        os << "\t" << person.sur_name.value();
    }
    return os;
}

bool operator==(Person &p1, Person &p2) {
    return std::tie(p1.second_name, p1.first_name, p1.sur_name) ==
           std::tie(p2.second_name, p2.first_name, p2.sur_name);
}

bool operator<(Person &p1, Person &p2) {
    return std::tie(p1.second_name, p1.first_name, p1.sur_name) <
           std::tie(p2.second_name, p2.first_name, p2.sur_name);
}

void l1_task1()
{
    Person person1("Plotnikov", "Andrey");
    Person person2("Plotnikov", "Andrey", "Vladimirovich");
    std::cout << person1 << std::endl;
    std::cout << person2 << std::endl;

    std::cout << std::boolalpha << "p1 less then p2:  " << (person1 < person2) << std::endl;
    std::cout << std::boolalpha << "p1 eq to p2: " << (person1 == person2) << std::endl;

}

/// -----------------------------------------------------------------------------------------------------

class PhoneNumber
{
public:
    PhoneNumber(int a, int b, std::string c, std::optional<int> d=std::nullopt)
            : countryCode(a), cityCode(b), number(std::move(c)), additionalNum(d) {};
    PhoneNumber() = default;
private:
    int countryCode;
    int cityCode;
    std::string number;
    std::optional<int> additionalNum;

    friend std::ostream&operator<<(std::ostream&os, PhoneNumber& ph);
    friend bool operator<(PhoneNumber& ph1, PhoneNumber &ph2);
    friend bool operator==(PhoneNumber& ph1, PhoneNumber &ph2);
};

std::ostream &operator<<(std::ostream &os, PhoneNumber &ph) {
    std::cout << "+" << ph.countryCode;
    std::cout << "(" << ph.cityCode << ")";
    std::cout << ph.number;
    if(ph.additionalNum.has_value())
        std::cout << " " << ph.additionalNum.value();

    return os;
}

bool operator<(PhoneNumber &ph1, PhoneNumber &ph2) {
    return std::tie(ph1.cityCode, ph1.countryCode, ph1.number, ph1.additionalNum) <
           std::tie(ph2.cityCode, ph2.countryCode, ph2.number, ph2.additionalNum);
}

bool operator==(PhoneNumber &ph1, PhoneNumber &ph2) {
    return std::tie(ph1.cityCode, ph1.countryCode, ph1.number, ph1.additionalNum) ==
           std::tie(ph2.cityCode, ph2.countryCode, ph2.number, ph2.additionalNum);
}

void l1_task2()
{
    PhoneNumber ph1(12, 13, "123456", 3);
    PhoneNumber ph2(12, 13, "123456", 3);

    std::cout << ph1 << std::endl;
    std::cout << ph2 << std::endl;

    std::cout << "ph1 eq ph2: " << std::boolalpha << (ph1==ph2) << std::endl;
    std::cout << "ph1 less then ph2: " << std::boolalpha << (ph1<ph2) << std::endl;
}


/// ---------------------------------------------------------------------------------------------

//Создайте класс PhoneBook, который будет в контейнере хранить пары:Человек – Номер телефона.
//Конструктор этого класса должен принимать параметр типа ifstream
//– поток данных, полученных из файла. В теле конструктора происходит считывание данных из файла и заполнение контейнера.
//Класс PhoneBook должен содержать перегруженный оператор вывода, для вывода всех данных из контейнера в консоль.

class PhoneBook
{
public:
    explicit PhoneBook(std::ifstream& ifs);
    void SortByName();
    void SortByPhone();
    std::tuple<std::string, PhoneNumber> GetPhoneNumber(const std::string& secondName);
    void ChangePhoneNumber(Person p, const PhoneNumber& ph);

private:
    std::vector<std::pair<Person, PhoneNumber>> book;

    friend std::ostream& operator<<(std::ostream& os, PhoneBook& ph);
};

PhoneBook::PhoneBook(std::ifstream& ifs)
{

    if (ifs.is_open())
    {
        std::string line;
        while(getline(ifs, line)) {
            if (line.find("//") == 0)
                continue;

            std::string delimiter = " - ";
            std::string person = line.substr(0, line.find(delimiter)); // person f_name, s_name, surname
            std::string number = line.substr(line.find(delimiter) + delimiter.length(), line.length());

            // разбираем имя, отчество, фамилию и добавляем
            delimiter = " ";
            std::string s_name = person.substr(0, person.find(delimiter));
            person.erase(0, person.find(delimiter) + delimiter.length());


            std::string f_name;
            std::optional<std::string> sur_name;
            auto del_pos = person.find(delimiter);

            // если больше нет разделителей, значит это последнее слово, значит это фамилия
            if(del_pos != std::string::npos) {
                f_name = person.substr(0, person.find(delimiter));
                person.erase(0, person.find(delimiter) + delimiter.length());
                sur_name = person;

            } else {
                f_name = person;
            }


            Person p(s_name, f_name, sur_name);

            // разбираем номер

            // убираем плюс в начале номера
            number.erase(0,1);

            delimiter = "(";
            std::string countryCode = number.substr(0, number.find(delimiter));
            number.erase(0, number.find(delimiter) + delimiter.length());

            delimiter = ")";
            std::string cityCode = number.substr(0, number.find(delimiter));
            number.erase(0, number.find(delimiter) + delimiter.length());

            delimiter = " ";
            std::string ph = number.substr(0, number.find(delimiter));
            number.erase(0, number.find(delimiter) + delimiter.length());

            std::optional<int> addNum = std::nullopt;
            if(!number.empty())
                addNum = std::stoi(number);

            // заполняем книгу
            PhoneNumber phNumber(std::stoi(countryCode), std::stoi(cityCode), ph, addNum);

            book.emplace_back(p, phNumber);

        }
    }
    else
        std::cout << "failed to open file." << std::endl;

    ifs.close();

}

std::ostream& operator<<(std::ostream &os, PhoneBook &ph) {
    if(ph.book.empty())
    {
        std::cout << "Book is empty" << std::endl;
        return os;
    }
    for(auto p: ph.book)
        std::cout << p.first << ": " << p.second << std::endl;
    return os;
}
//Метод SortByName, который должен сортировать элементы контейнера по фамилии людей в алфавитном порядке.
//Если фамилии будут одинаковыми, то сортировка должна выполняться по именам, если имена будут одинаковы,
//то сортировка производится по отчествам. Используйте алгоритмическую функцию sort.
void PhoneBook::SortByName() {
    std::sort(book.begin(), book.end(), [](std::pair<Person, PhoneNumber> a,
                                           std::pair<Person, PhoneNumber> b) -> bool
    {return a.first < b.first;}); // сравниваем ФИО
}

void PhoneBook::SortByPhone() {
    std::sort(book.begin(), book.end(), [](std::pair<Person, PhoneNumber> a,
                                           std::pair<Person, PhoneNumber> b) -> bool
    {return a.second < b.second;}); // сравниваем ФИО
}


//Реализуйте метод GetPhoneNumber, который принимает фамилию человека, а возвращает кортеж из строки и PhoneNumber.
//Строка должна быть пустой, если найден ровно один человек с заданной фамилией в списке.
//Если не найден ни один человек с заданной фамилией, то в строке должна быть запись «not found»,
//если было найдено больше одного человека, то в строке должно быть «found more than 1».
std::tuple<std::string, PhoneNumber> PhoneBook::GetPhoneNumber(const std::string& secondName) {
    int cnt = 0;
    std::string str;
    PhoneNumber phNum;

    for(auto &a: book)
    {
        if(a.first.getSecondName() == secondName)
        {
            phNum = a.second;
            cnt++;
        }
    }
    if(cnt == 0)
        str = "not found";
    else if(cnt > 1) {
        str = "found more than 1";
    }

    return {str, phNum};
}

void PhoneBook::ChangePhoneNumber(Person p, const PhoneNumber& ph) {
    for(auto& a: book)
    {
        if(a.first == p)
        {
            a.second = ph;
            return;
        }
    }
}


void l1_task3()
{

    std::ifstream file("../PhoneBook.txt"); // путь к файлу PhoneBook.txt
    PhoneBook book(file);

    std::cout << book;
    std::cout << "------SortByPhone-------" << std::endl;
    book.SortByPhone();
    std::cout << book;
    std::cout << "------SortByName--------" << std::endl;
    book.SortByName();
    std::cout << book;
    std::cout << "-----GetPhoneNumber-----" << std::endl;

// лямбда функция, которая принимает фамилию и выводит номер телефона
//    человека, либо строку с ошибкой
    auto print_phone_number = [&book](const std::string& surname){
        std::cout << surname << "\t";
        auto answer = book.GetPhoneNumber(surname);
        if (std::get<0>(answer).empty())
            std::cout << std::get<1>(answer);
        else
            std::cout << std::get<0>(answer);
        std::cout << std::endl;
    };

// вызовы лямбды
    print_phone_number("Ivanov");
    print_phone_number("Petrov");
    std::cout << "----ChangePhoneNumber----" << std::endl;

    book.ChangePhoneNumber(Person{ "Kotov", "Vasilii", "Eliseevich" },
                           PhoneNumber{7, 123, "15344458", std::nullopt});

    book.ChangePhoneNumber(Person{ "Mironova", "Margarita", "Vladimirovna" },
                           PhoneNumber{ 16, 465, "9155448", 13 });


    std::cout << book;

}