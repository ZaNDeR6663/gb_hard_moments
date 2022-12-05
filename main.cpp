#include "lesson1.h"
#include <gtest/gtest.h>

// lesson 1
void l1_task1()
{
    Person person1("Plotnikov", "Andrey");
    Person person2("Plotnikov", "Andrey", "Vladimirovich");
    std::cout << person1 << std::endl;
    std::cout << person2 << std::endl;

    std::cout << std::boolalpha << "p1 less then p2:  " << (person1 < person2) << std::endl;
    std::cout << std::boolalpha << "p1 eq to p2: " << (person1 == person2) << std::endl;

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


// lesson 2
void l2_task1();
void l2_task2();
void l2_task3();


// lesson 3
void l3_task1();
void l3_task2();
void l3_task3();

// lesson 4
//void l4_task1();
//void l4_task2();

// lesson 5
//void l5_task1();
//void l5_task2();

// lesson 6
//void l6_task1();
//void l6_task2();
//void l6_task3();

// lesson 7
void l7_task1();
void l7_task2();
void l7_task3();


TEST(TestSuiteClassPerson, test_first_name) {
    Person p("Plotnikov", "Andrey", "Vladimirovich");
    ASSERT_EQ(p.getFirstName(), "Andrey");
}

TEST(TestSuiteClassPerson, test_second_name) {
    Person p("Plotnikov", "Andrey", "Vladimirovich");
    ASSERT_EQ(p.getSecondName(), "Plotnikov");
}

TEST(TestSuiteClassPerson, test_sur_name) {
    Person p("Plotnikov", "Andrey", "Vladimirovich");
    ASSERT_EQ(p.getSurname(), "Vladimirovich");
}





int main() {
// lesson 1
    l1_task1();
    l1_task2();
    l1_task3();



// lesson 2
//    l2_task1();
//    l2_task2();
//    l2_task3();

// lesson 3
//    l3_task1();
//    l3_task2();
//    l3_task3();

// lesson 4
//    l4_task1();
//    l4_task2();

// lesson 5
//    l5_task1();
//    l5_task2();

// lesson 6
//    l6_task1();
//    l6_task2();
//    l6_task3();

// lesson 7
//    l7_task1();
//    l7_task2();
//    l7_task3();
    RUN_ALL_TESTS();
    return 0;

}


