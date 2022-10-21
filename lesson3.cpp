#include <iostream>
#include <list>
#include <complex>
#include <iomanip>
#include <numeric>
#include <vector>
#include <initializer_list>
#include <stdexcept>

using namespace std::complex_literals;
//1. Ќаписать функцию, добавл€ющую в конец списка вещественных чисел элемент,
//значение которого равно среднему арифметическому всех его элементов.

void addAvgSum(std::list<std::complex<double>>& list)
{
    std::complex<double> avgSum;
    for(auto & it: list)
        avgSum += it;
    avgSum = avgSum / std::complex<double>(static_cast<double>(list.size()) + 0i);
    list.push_back(avgSum);
}

void l3_task1()
{

    std::list<std::complex<double>> list_complex = {(1.+1i), (5.+3i), (2.+0i), (4.+1i)};
    std::cout << std::fixed << std::setprecision(1);

    for(auto & it : list_complex)
        std::cout << it << " ";
    std::cout << std::endl;

    addAvgSum(list_complex);

    for(auto & it : list_complex)
        std::cout << it << " ";
    std::cout << std::endl;
}

//2. —оздать класс, представл€ющий матрицу. –еализовать в нем метод,
//вычисл€ющий определитель матрицы. ƒл€ реализации используйте контейнеры из STL.
template <typename T> class Matrix
{
private:
    int x_size, y_size;
    std::vector<std::vector<T>*>* data_container;

public:
    // дефолтный конструктор
    Matrix()
    {
        // создаем верхний уровень вектора, типом которого €вл€ютс€ вектора нижнего уровн€ (строк)
        data_container = new std::vector<std::vector<T>*>;
        x_size = 0,
        y_size = 0;
    };

    Matrix(int x_size, int y_size, T fill_value=(0.+0i))
    : x_size(x_size), y_size(y_size)
    {
        data_container = new std::vector<std::vector<T>*>(y_size);
        for(auto & it : *data_container)
        {
            it = new std::vector<T>(x_size, fill_value);
        }
    };

    Matrix(std::initializer_list<std::initializer_list<T>> l)
    {
        y_size = l.size();
        x_size = l.begin()->size();
        // сразу резервируем пространство под все векторы
        data_container = new std::vector<std::vector<T>*>;
        data_container->reserve(l.size());

        auto x_len = l.begin()->size();
        for(auto it : l)
        {
            if(it.size() != x_len)
                throw std::length_error("Length error, row length unequal to first row.");
            data_container->insert(data_container->end(), new std::vector<T>(it));
        }
    }

    ~Matrix(){
        for(auto & it : *data_container)
            delete it;
        delete data_container;
        std::cout << "Matrix deleted" << std::endl;
    }
    friend std::ostream& operator<<(std::ostream& os, Matrix& m)
    {
        for(auto it = m.data_container->begin(); it != m.data_container->end(); it++)
        {
            for(auto val_it : **it)
                os << val_it;
            std::cout << std::endl;
        }
        return os;
    }
    void determinant() {
        if (x_size != y_size)
        {
            std::cout << "Matrix have to be same height and width." << std::endl;
            return;
        }
        if(x_size > 3)
        {
            std::cout << "Matrix size is too big. Try 3x3 matrix maximum." << std::endl;
            return;
        }
        std::complex<double> plus_line = (T)1 + 0i;
        std::complex<double> minus_line = (T)1. + 0i;
        std::complex<double> result_plus = (T)0. + 0i;
        std::complex<double> result_minus = (T)0. + 0i;
        for(auto x_it = 0; x_it < data_container->size(); x_it++)
        {
            for (auto i = 0; i < x_size; i++) {
                // значение выходит за пределы, если выходит, то нужно обратитьс€ в начало вектора
                plus_line *= data_container->at(i)->at((i + x_it) % x_size);
                minus_line *= data_container->at(i)->at((x_size - 1 + i - x_it) % x_size);
            }
            result_plus += plus_line;
            result_minus += minus_line;
            plus_line = (T)1 + 0i;
            minus_line = (T)1 + 0i;
        }
        std::cout << "Determinant = " << result_plus - result_minus << std::endl;

    };
};

void l3_task2()
{
    std::cout << std::endl << "------------- task 2 ------------- " << std::endl;
    Matrix<std::complex<double>> m2{
            {5.+1i, 1.+2i, 2.+3i},
            {5.+1i, 1.+2i, 2.+3i},
            {5.+1i, 1.+2i, 2.+3i}

    };
    std::cout << m2;
    m2.determinant();

}


//3. –еализовать собственный класс итератора, с помощью которого можно будет
//проитерироватьс€ по диапазону целых чисел в цикле for-range-based.
template<long FROM, long TO>
class Range {
public:
    class iterator: public std::iterator<
            std::input_iterator_tag,   // iterator_category
            long,                      // value_type
            long,                      // difference_type
            const long*,               // pointer
            long                       // reference
    >{
        long num = FROM;
    public:
        explicit iterator(long _num = 0) : num(_num) {}

        iterator& operator++() {num = TO >= FROM ? num + 1: num - 1; return *this;}
        iterator operator++(int) {iterator retval = *this; ++(*this); return retval;}
        bool operator==(iterator other) const {return num == other.num;}
#pragma clang diagnostic push
#pragma ide diagnostic ignored "Simplify"
        bool operator!=(iterator other) const {return !(*this == other);}
#pragma clang diagnostic pop
        reference operator*() const {return num;}
    };
    iterator begin() {return iterator(FROM);}
    iterator end() {return iterator(TO >= FROM ? TO+1 : TO-1);}
};

void l3_task3()
{
    std::cout << std::endl << "------------- task 3 ------------- " << std::endl;

    Range<1,8> range;

    std::cout << "Range based for loop with iterator implementation:" << std::endl;
    for(auto it: range)
        std::cout << it << " ";

    std::cout << std::endl;

}