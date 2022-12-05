#ifndef GB_HARD_MOMENTS_LESSON1_H
#define GB_HARD_MOMENTS_LESSON1_H
#include <iostream>
#include <optional>
#include <utility>
#include <tuple>
#include <vector>
#include <utility>
#include <fstream>
#include <algorithm>
#include "gtest/gtest.h"


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

#endif //GB_HARD_MOMENTS_LESSON1_H
