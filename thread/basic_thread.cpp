#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

void sleep(int milliseconds)
{
    this_thread::sleep_for(chrono::milliseconds(milliseconds));
}

void task1()
{
    for (int i = 0; i < 10; i++)
    {
        cout << "task1:" << i << endl;
        sleep(300);
    }
}

void task2()
{
    for (int i = 0; i < 10; i++)
    {
        cout << "task2:" << i << endl;
        sleep(700);
    }
}

int main()
{
    thread mThread1(task1);
    thread mThread2(task2);

    cout << "main thread" << endl;

    mThread1.join();
    mThread2.join();
    return 0;
}