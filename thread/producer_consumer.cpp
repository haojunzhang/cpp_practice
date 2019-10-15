#include <iostream>
#include <utility>
#include <thread>
#include <chrono>
#include <random>

#define DEFAULT_STOCK 3
#define STOCK_FULL_AMOUNT 10
#define STOCK_EMPTY_AMOUNT 0
#define PRODUCER_SPEED 300 // 300 ~ 1000, low = speed up
#define CONSUMER_SPEED 300 // 300 ~ 1000, low = speed up
#define AMOUNT_PER_PRODUCE_MIN 1
#define AMOUNT_PER_PRODUCE_MAX 3
#define AMOUNT_PER_CONSUME_MIN 1
#define AMOUNT_PER_CONSUME_MAX 3

void sleep(int milliseconds)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

int random_int(int from, int to)
{
    std::random_device rd;
    std::default_random_engine gen = std::default_random_engine(rd());
    std::uniform_int_distribution<int> dis(from, to);
    return dis(gen);
}

void increaseStock(int &i, int amount)
{
    i = i + amount;
}

void decreaseStock(int &i, int amount)
{
    i = i - amount;
}

void produceTask(int &stock)
{
    // fix loop cound
    for (int i = 0; i < 10; i++)
    {
        // produce amount
        int amount = random_int(AMOUNT_PER_PRODUCE_MIN, AMOUNT_PER_PRODUCE_MAX);

        // check stock full
        if (stock + amount > STOCK_FULL_AMOUNT)
        {
            // full, discard this task
            std::cout << "stock full" << std::endl;
        }
        else
        {
            // not full
            increaseStock(stock, amount);
            std::cout << "+" << amount
                      << " stock=" << stock << std::endl;
        }

        sleep(random_int(100, PRODUCER_SPEED));
    }
}

void consumeTask(int &stock)
{
    // fix loop cound
    for (int i = 0; i < 10; i++)
    {
        // consume amount
        int amount = random_int(AMOUNT_PER_CONSUME_MIN, AMOUNT_PER_CONSUME_MAX);

        // check stock availble
        if (stock - amount < STOCK_EMPTY_AMOUNT)
        {
            // not availble, discard this task
            std::cout << "stock not enough" << std::endl;
        }
        else
        {
            // availble
            decreaseStock(stock, amount);
            std::cout << "-" << amount
                      << " stock=" << stock << std::endl;
        }

        sleep(random_int(100, CONSUMER_SPEED));
    }
}

int main()
{
    int stock = DEFAULT_STOCK;
    std::thread mProducer(produceTask, std::ref(stock));
    std::thread mConsumer(consumeTask, std::ref(stock));

    mProducer.join();
    mConsumer.join();
    return 0;
} // clang++ -std=c++11 producer_consumer.cpp