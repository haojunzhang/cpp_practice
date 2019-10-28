#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <ctime>
using namespace std;

class Wallet
{
private:
    int money = 0;
    mutex mutex;

public:
    void add_amount(int amount)
    {
        mutex.lock();
        money += amount;
        mutex.unlock();
    }

    int get_money()
    {
        return money;
    }
};

void add_amount_task(Wallet *wallet, int amount)
{
    wallet->add_amount(amount);
}

int main()
{
    Wallet wallet;
    vector<thread> vec;

    for (size_t i = 0; i < 10000; i++)
    {
        vec.push_back(thread(&add_amount_task, &wallet, 100));
    }
    for (size_t i = 0; i < 10000; i++)
    {
        vec.push_back(thread(&add_amount_task, &wallet, -100));
    }

    for (size_t i = 0; i < vec.size(); i++)
    {
        vec.at(i).join();
    }
    cout << wallet.get_money() << endl;

    return 0;
} // clang++ -std=c++11 thread_race.cpp
