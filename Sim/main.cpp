#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <thread>
#include "order.hpp"
#include "orderBook.hpp"
#include "orderGenerator.hpp"
#include "threadManager.hpp"

//Template definition with Order as the typename
ThreadSafe<Order> orderQueue;

//producer : produce a random order and push it into orderqueue
void produceOrder(int count) {
    OrderGenerator generator;
    for (int i=0; i < count; i++){
        Order order = generator.generateOrder();
        orderQueue.push(order);
    }

}

//consumer : consumes (pop) order from queue and and process said order 
void consumeOrder(OrderBook& book, int totalOrders, size_t& tradecount){
    for (int i=0; i < totalOrders; i++){
        Order order;
        orderQueue.pop(order);
        book.addOrder(order);
        book.matchOrder(tradecount);
    }
}

int main() {
    OrderBook book;

    const int TOTAL_ORDERS = 1000000;

    //static trade statistics
    size_t tradecount = 0;

    auto start = std::chrono::high_resolution_clock::now();

    //number of consumer thread (max hardware threads - no.of producer threads)
    int num_consumers = std::thread::hardware_concurrency() - 1;

    //consumer runs (process orders with orderbook) with equal work on each cores
    //vector used to join threads for speed, list is too slow
    std::vector<std::thread> consumers;
    for (int i =0; i < num_consumers;i++){
        consumers.emplace_back(consumeOrder, std::ref(book), TOTAL_ORDERS/num_consumers, std::ref(tradecount));
    }


    //producer runs (generate random orders)
    std::thread producer(produceOrder, TOTAL_ORDERS);
    producer.join();
    
    for (auto& t : consumers){
        t.join();
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> total_time = end - start;

    std::cout << std::endl << "Processed " << TOTAL_ORDERS << " orders in " << total_time.count() << " seconds" << std::endl;
    std::cout << tradecount << " trades made in total." << std::endl;
    std::cout<< "Using " << num_consumers << " consumers threads."<< std::endl; 
    return 0;

}