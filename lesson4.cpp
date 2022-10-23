#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <random>
#include <iomanip>
#include <iterator>

//1. Имеется отсортированный массив целых чисел. Необходимо разработать функцию insert_sorted,
//которая принимает вектор и новое число и вставляет новое число в определенную позицию в векторе,
//чтобы упорядоченность контейнера сохранялась. Реализуйте шаблонную функцию insert_sorted,
//которая сможет аналогично работать с любым контейнером, содержащим любой тип значения.
template<class Container> void insert_sorted_template(Container &c, int value)
{
    auto pos = std::find_if(c.begin(), c.end(), [&value](int x){return x >= value;});
    std::cout << "Inserting value: " << value << " on positions: " << *pos << std::endl;
    c.insert(pos, value);
}

void l4_task1()
{
    std::cout << std::endl << "------------- task 1 ------------- " << std::endl;
    std::vector<int> v1{1,3,2,6,4,8,9,11,0,-3};
    std::list<double> v2{1,2,3,4,6,7,8,9};

    std::sort(v1.begin(), v1.end(), [](int& x, int& y){return x < y;});

    std::cout << "Vector:" << std::endl;
    for(auto it: v1)
        std::cout << it << " ";
    std::cout << std::endl;

    auto value = 5;
    insert_sorted_template(v1, value);

    std::cout << "Vector after insertion:" << std::endl;
    for(auto it: v1)
        std::cout << it << " ";
    std::cout << std::endl;

    std::cout << "List:" << std::endl;
    for(auto it: v2)
        std::cout << it << " ";
    std::cout << std::endl;

    value = 7;
    insert_sorted_template(v2, value);

    std::cout << "List after insertion:" << std::endl;
    for(auto it: v2)
        std::cout << it << " ";
    std::cout << std::endl;
}




//2. Сгенерируйте вектор a, состоящий из 100 вещественный чисел, представляющий собой значения
//аналогового сигнала. На основе этого массива чисел создайте другой вектор целых чисел b,
//представляющий цифровой сигнал, в котором будут откинуты дробные части чисел.
//Выведите получившиеся массивы чисел.
void l4_task2()
{
    std::cout << std::endl << "------------- task 2 ------------- " << std::endl;
//    copy(vs.begin(), vs.end(), ostream_iterator<string>(cout, "\n"));

    const size_t data_points{ 100 };
    const size_t sample_points{ 100 };

    std::random_device rd;
    std::mt19937 gen{ rd() };


    std::normal_distribution<> d{ 0, 10 };
    std::vector<double> analog_signal;
    std::vector<int> digital_signal;

    // резервируем место под данные
    analog_signal.reserve(data_points);
    digital_signal.reserve(data_points);

    // генерируем вещественные числа в диапазоне 1-19
    generate_n(back_inserter(analog_signal), data_points, [&] { return d(gen); });


    std::vector<int> v_norm;
    v_norm.reserve(analog_signal.size());

    auto normalize = [](double a){ return (int)round(a); };
    std::transform(analog_signal.begin(), analog_signal.end(), back_inserter(digital_signal), normalize);

    std::cout << "Analog signal data vector (first 20):" << std::endl;
    std::copy(analog_signal.begin(), analog_signal.begin()+20, std::ostream_iterator<double>(std::cout << std::setprecision(3) , " "));
    std::cout << std::endl;

    std::cout << "Digital signal data vector (first 20):" << std::endl;
    std::copy(digital_signal.begin(), digital_signal.begin()+20, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    //Посчитайте ошибку, которой обладает цифровой
//сигнал по сравнению с аналоговым по формуле: sum(ai - bi)^2: (0 -> N-1)
//где:
//N - количество элементов в векторе,
//        a - элемент вектора с дробными числами, b - элемент вектора с целыми числами
//        Постарайтесь воспользоваться алгоритмическими функциями, не используя циклы.

//    std::accumulate(analog_signal.begin(), analog_signal.end(), )

    std::vector<double> result;
    std::transform(analog_signal.begin(), analog_signal.end(), digital_signal.begin(),
                   std::back_inserter(result),
                   [](double a, int b){return std::pow(a - b, 2);});

    double error_value = std::accumulate(result.begin(), result.end(), 0.);

    std::cout << "Error value = " << error_value << std::endl;

}