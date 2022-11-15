#include <iostream>
#include <map>
#include <iterator>
#include <vector>
#include <queue>
#include <array>
#include <algorithm>

// 1. Создать шаблонную функцию, которая принимает итераторы на начало и конец
// последовательности слов, и выводящую в консоль список уникальных слов
// (если слово повторяется больше 1 раза, то вывести его надо один раз).
// Продемонстрировать работу функции, передав итераторы различных типов.
template<typename Iter_>
void word_count(Iter_ begin, Iter_ end)
{
    std::map<std::string, int> map;
    for(auto it = begin; it != end; it++)
    {
        ++map[*it];
    }
    for(auto & it: map)
        std::cout << it.first << std::endl;

}

void l5_task1()
{
    std::cout << std::endl << "------------- task 1 ------------- " << std::endl;
    std::vector<std::string> c{"asdf",
                               "asdf1",
                               "asdf1",
                               "asdf1",
                               "asdf",
                               "asdf2",
                               "asdf3",
                               "asdf4",
                               "asdf5",
                               "asdf5"};

    std::array<std::string, 10> c1{"asdf",
                               "asdf1",
                               "asdf1",
                               "asdf1",
                               "asdf",
                               "asdf2",
                               "asdf3",
                               "asdf4",
                               "asdf5",
                               "asdf5"};

    word_count(c.begin(), c.end());
    std::cout << "-----------------------" << std::endl;
    word_count(c1.begin(), c1.end());
}


// 2. Используя ассоциативный контейнер, напишите программу, которая будет
// считывать данные введенные пользователем из стандартного потока ввода и
// разбивать их на предложения. Далее программа должна вывести пользователю
// все предложения, а также количество слов в них, отсортировав предложения по количеству слов.
void reader()
{
    int sent_idx = 0;
    std::map<int, std::vector<std::string>> map;

    std::string text;
    std::cout << "Enter your text and i will count your words. Enter 1111 to stop:" << std::endl;
    while(std::cin >> text)
    {
        if(text == "1111")
            break;

        auto dot = text.find('.');
        if(dot != std::string::npos)
            text.erase(dot);

        map[sent_idx].push_back(text);

        if(dot != std::string::npos)
            sent_idx++;
    }

    std::vector<std::vector<std::string>> v;
    for(auto & it: map)
        v.push_back(it.second);

    std::sort(v.begin(), v.end(), [](const auto &l, const auto &r){ return l.size() > r.size();});

    for(auto & it: v)
    {
        std::copy(it.begin(), it.end(), std::ostream_iterator<std::string>(std::cout, " "));
        std::cout << "| Words: " << it.size() << std::endl;
    }

}

void l5_task2()
{
    std::cout << std::endl << "------------- task 2 ------------- " << std::endl;
    reader();
}
