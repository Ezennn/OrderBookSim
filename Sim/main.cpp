#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include "order.hpp"
#include "orderBook.hpp"
#include "orderGenerator.hpp"

int main() {
    OrderBook book;
    OrderGenerator generator;

    const int TOTAL_ORDERS = 10000;

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < TOTAL_ORDERS; i++){
        Order order = generator.generateOrder();
        book.addOrder(order);
        book.matchOrder();
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> total_time = end - start;

    std::cout << std::endl << "Processed " << TOTAL_ORDERS << " orders in " << total_time.count() << " seconds" << std::endl;
    
    return 0;

}