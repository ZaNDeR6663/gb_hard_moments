#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>

class Timer
{
private:
    using clock_t = std::chrono::high_resolution_clock;
    using second_t = std::chrono::duration<double, std::ratio<1> >;
    std::string m_name;
    std::chrono::time_point<clock_t> m_beg;
    [[nodiscard]] double elapsed() const
    {
        return std::chrono::duration_cast<second_t>(clock_t::now()
                                                    -m_beg).count();
    }
public:
    Timer() : m_beg(clock_t::now()) { }
    explicit Timer(std::string name) : m_name(std::move(name)), m_beg(clock_t::now()) { }
    void start(std::string name) {
        m_name = name;
        m_beg = clock_t::now();
    }
    void print() const {
        std::cout << m_name << ":\t" << elapsed() * 1000 << " ms" << '\n';
    }
};



//–еализуйте шаблонную функцию Swap, котора€ принимает два указател€
//и обменивает местами значени€, на которые указывают эти указатели
//(нужно обменивать именно сами указатели, переменные должны оставатьс€ в тех же адресах пам€ти).

template <typename T> void Swap(T& a, T& b)
{
    T mid = a;
    a = b;
    b = mid;
}

void l2_task1()
{
    std::cout << std::endl << "------------- task 1 ------------- " << std::endl;
    int* a = new int;
    *a = 10;

    int* b = new int;
    *b = 5;

    std::cout << "Before swap:" << std::endl;
    std::cout << "a = " << *a << ", b = " << *b << std::endl;
    std::cout << "ptr_a = " << a << ", ptr_b = " << b << std::endl;

    Swap(a, b);

    std::cout << "After swap:" << std::endl;
    std::cout << "a = " << *a << ", b = " << *b << std::endl;
    std::cout << "ptr_a = " << a << ", ptr_b = " << b << std::endl;

    delete a;
    delete b;
}


//–еализуйте шаблонную функцию SortPointers, котора€ принимает вектор указателей
//и сортирует указатели по значени€м, на которые они указывают.
template <typename T> void SortPointers(std::vector<T*>* vec)
{
    // компаратор от меньшего к большему
    std::sort(vec->begin(), vec->end(), [&](T* a, T* b){return *a < *b;});
}

void l2_task2()
{
    std::cout << std::endl << "------------- task 2 ------------- " << std::endl;
    int* a = new int{11};
    int* b = new int{1};
    int* c = new int{6};
    int* d = new int{9};
    int* e = new int{10};
    int* f = new int{2};

    auto *vec = new std::vector<int*>{a,b,c,d,e,f};
    std::cout << "Unsorted vector: ";
    for(auto it: *vec)
        std::cout << *it << " ";
    std::cout << std::endl;

    SortPointers(vec);

    std::cout << "Sorted vector: ";
    for(auto it: *vec)
        std::cout << *it << " ";
    std::cout << std::endl;

}


//    ѕодсчитайте количество гласных букв в книге У¬ойна и мирФ. ƒл€ подсчета используйте 4 способа:
//    - count_if и find
//    - count_if и цикл for
//    - цикл for и find
//    - 2 цикла for
//    «амерьте врем€ каждого способа подсчета и сделайте выводы.
//            —правка:
//    count_if - это алгоритмическа€ функци€ из STL, котора€ принимает 3 параметра: итератор на начало,
//    итератор на конец и унарный предикат (функцию, принимающую один параметр и возвращающую тип bool).
//    find - это метод класса string, который возвращает позицию символа (строки),
//    переданного в качестве параметра, в исходной строке. ≈сли символ не найден, то метод возвращает string::npos.

void count_if_find()
{
    Timer t;
    std::ifstream ifs("../voina-i-mir.txt");
    if (ifs.is_open())
    {
        std::string line;
        int count = 0;
        std::string vowels = "AEIOUYaeiouyја≈е®Є»иќо”уџыЁэёюя€";
        t.start("count_if and find");


        auto is_vowel = [vowels](char i){return std::find(vowels.begin(), vowels.end(), i) != std::end(vowels);};

        while(getline(ifs, line))
        {
            // сравниваем каждый символ в строке с правилом
            count += int(std::count_if(line.begin(), line.end(), is_vowel));
        }
        std::cout << "Number of vowels: " << count << std::endl;


    }
    else
        std::cout << "file not opened!" << std::endl;

    t.print();
    ifs.close();
}

void count_if_for()
{
    Timer t;
    std::ifstream ifs("../voina-i-mir.txt");
    if (ifs.is_open())
    {
        std::string line;
        int count = 0;
        std::string vowels = "AEIOUYaeiouyја≈е®Є»иќо”уџыЁэёюя€";
        t.start("count_if and for");


        auto is_vowel = [vowels](char i){
            for(auto vowel: vowels)
                if(vowel == i)
                    return true;
            return false;
        };

        while(getline(ifs, line))
        {
            // сравниваем каждый символ в строке с правилом
            count += int(std::count_if(line.begin(), line.end(), is_vowel));
        }
        std::cout << "Number of vowels: " << count << std::endl;


    }
    else
        std::cout << "file not opened!" << std::endl;

    t.print();
    ifs.close();
}

void for_find()
{
    Timer t;
    std::ifstream ifs("../voina-i-mir.txt");
    if (ifs.is_open())
    {
        std::string line;
        int count = 0;
        std::string vowels = "AEIOUYaeiouyја≈е®Є»иќо”уџыЁэёюя€";
        t.start("for and find");


        while(getline(ifs, line))
        // сравниваем каждый символ в строке с правилом
            for(auto & it: line)
                if(std::find(vowels.begin(), vowels.end(), it) != std::end(vowels))
                    count += 1;

        std::cout << "Number of vowels: " << count << std::endl;

    }
    else
        std::cout << "file not opened!" << std::endl;

    t.print();
    ifs.close();
}

void for_for()
{
    Timer t;
    std::ifstream ifs("../voina-i-mir.txt");
    if (ifs.is_open())
    {
        std::string line;
        int count = 0;
        std::string vowels = "AEIOUYaeiouyја≈е®Є»иќо”уџыЁэёюя€";
        t.start("for and for");


        while(getline(ifs, line))
            // сравниваем каждый символ в строке с правилом
            for(auto & ch: line)
                for(auto & v: vowels)
                    if(v == ch) {
                        count += 1;
                        continue;
                    }

        std::cout << "Number of vowels: " << count << std::endl;


    }
    else
        std::cout << "file not opened!" << std::endl;

    t.print();
    ifs.close();
}

void l2_task3()
{
    std::cout << std::endl << "------------- task 3 ------------- " << std::endl;
    count_if_find();
    std::cout  << std::endl;

    count_if_for();
    std::cout  << std::endl;

    for_find();
    std::cout  << std::endl;

    for_for();
}


