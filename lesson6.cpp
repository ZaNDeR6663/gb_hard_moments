#include <iostream>
#include <thread>
#include <mutex>
#include <variant>
#include <iostream>
#include <chrono>
#include <ctime>
#include <cmath>
#include <condition_variable>
#include <queue>
#include <random>
#include <algorithm>
#include <execution>

using namespace std::chrono_literals;

class Timer
{
public:
    void start()
    {
        m_StartTime = std::chrono::system_clock::now();
        m_bRunning = true;
    }

    void stop()
    {
        m_EndTime = std::chrono::system_clock::now();
        m_bRunning = false;
    }

    double elapsedMilliseconds()
    {
        std::chrono::time_point<std::chrono::system_clock> endTime;

        if(m_bRunning)
        {
            endTime = std::chrono::system_clock::now();
        }
        else
        {
            endTime = m_EndTime;
        }

        return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - m_StartTime).count();
    }

    double elapsedSeconds()
    {
        return elapsedMilliseconds() / 1000.0;
    }

private:
    std::chrono::time_point<std::chrono::system_clock> m_StartTime;
    std::chrono::time_point<std::chrono::system_clock> m_EndTime;
    bool                                               m_bRunning = false;
};

std::mutex m;
//1. �������� ���������������� �������� ��� ������� cout. �������� �� pcout. ����������,
//����� ��������� ������� ����� ���������� � pcout � ���������� ���������� � �������. ����������������� ������ pcout.
class Pcout {
public:
    template<typename T>
    void operator<<(T var) {
        std::lock_guard<std::mutex> guard(m);
        std::cout << var << std::endl;
    }
};


void l6_task1()
{
    std::cout << std::endl << "------------- task 1 ------------- " << std::endl;
    Pcout pcout;

    std::thread t1(&Pcout::operator<< <std::basic_string<char>>, &pcout, "t1");
    std::thread t2(&Pcout::operator<< <std::basic_string<char>>, &pcout, "t2");
    std::thread t3(&Pcout::operator<< <std::basic_string<char>>, &pcout, "t3");

    t1.join();
    t2.join();
    t3.join();
}

//2. ����������� �������, ������������ i-�� ������� ����� (��������, ���������� �������
//����� ����� 15485863). ���������� ����������� �� ��������� ������. � ������� ����������
//�������� ���������� (� �������� ������).
bool checkSimplicity(int value)
{
    for(int i = 2; i <= sqrt(value); i++)
        if(value % i == 0) {
            return false;
        }
    return true;
}


std::condition_variable cv;
std::mutex cv_m;
bool done;


void display(int& result)
{
    std::unique_lock<std::mutex> lk(cv_m);
    std::cout << "Waiting... \n";
    cv.wait(lk, []{return done;});
    std::cout << "Result simple number: " << result << std::endl;

}

void processData(int endSimpleIdx, int& result)
{
    done = false;
    std::unique_lock<std::mutex> lk(cv_m);

    lk.unlock();
    cv.notify_one(); // waiting thread is notified with i == 1, cv.wait returns
    lk.lock();


    int currentSimpleIdx = 0;
    int number = 2;
    while(endSimpleIdx != currentSimpleIdx)
    {
        if(checkSimplicity(number))
        {
//            std::cout  << "Idx = " << currentSimpleIdx+1 << ", number = " << number << " " << std::endl;
            currentSimpleIdx++;
            if(currentSimpleIdx == endSimpleIdx)
            {
                result = number;
                lk.unlock();
                cv.notify_one(); // waiting thread is notified with i == 1, cv.wait returns
                done = true;
            }
        }

        number++;
    }

}


void l6_task2()
{
    std::cout << std::endl << "------------- task 2 ------------- " << std::endl;
    int simpleNumPosition = 10000;
    int result;
    std::thread displayTh(processData, simpleNumPosition, std::ref(result));
    std::thread processTh(display, std::ref(result));
    displayTh.join();
    processTh.join();
}

//3. ��������������� ��������� ��������. ���� ��� �������� (2 ������): ������ � ���.
//������ �������� ����� ���� (������� ����������� ��������� ����� � ������ � �������������� 1 ��� � �������).
//��� ���� � ������ ���� ���� ���� ��������. ��� �������� ���� (�������, ������� ������� ���������� �����
//� ������� �� ������� � �������������� 1 ��� � 0.5 ������), ������ ��� �������� ���� � ���������� ���������.
void ownerAdd(std::vector<int>& vec)
{
    std::mt19937 gen;
    std::uniform_int_distribution<int> dis(0, 25);
    auto rand_num([=]() mutable { return dis(gen); });

    while(!done)
    {
        std::this_thread::sleep_for(1000ms);
        vec.push_back(rand_num());

        std::cout << "Value added! Vector: ";
        std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
    }

}

void stealerRemove(std::vector<int>& vec)
{
    while(!done)
    {
        std::this_thread::sleep_for(500ms);
        auto max = std::max_element(vec.begin(), vec.end());
        vec.erase(max);
        std::cout << "Value stolen! Vector: ";
        std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;

        if(vec.empty())
            done = true;

    }
}

void l6_task3()
{
    std::cout << std::endl << "------------- task 3 ------------- " << std::endl;
    // ��������� ������ ��������� �������
    std::vector<int> vault(10);
    std::mt19937 gen;
    std::uniform_int_distribution<int> dis(0, 100);
    auto rand_num([=]() mutable { return dis(gen); });
    std::generate(std::execution::par, begin(vault), end(vault), rand_num);

    std::cout << "Initial Vector: ";
    std::copy(vault.begin(), vault.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    done = false;

    std::thread owner(ownerAdd, std::ref(vault));
    std::thread stealer(stealerRemove, std::ref(vault));

    owner.join();
    stealer.join();

    std::cout << "Stealer has stolen everything already, sorry :(" << std::endl;
}