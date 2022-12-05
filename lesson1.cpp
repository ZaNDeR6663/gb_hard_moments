#include "lesson1.h"

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






/// -----------------------------------------------------------------------------------------------------


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




/// ---------------------------------------------------------------------------------------------

//Создайте класс PhoneBook, который будет в контейнере хранить пары:Человек – Номер телефона.
//Конструктор этого класса должен принимать параметр типа ifstream
//– поток данных, полученных из файла. В теле конструктора происходит считывание данных из файла и заполнение контейнера.
//Класс PhoneBook должен содержать перегруженный оператор вывода, для вывода всех данных из контейнера в консоль.



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

