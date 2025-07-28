#pragma once
#include "order.hpp"
#include <random>

//OrderGenerator type which introduces generateOrder() function
class OrderGenerator {
    private :
    std::mt19937 gen;
    std::uniform_real_distribution<double> randPrice;
    std::uniform_int_distribution<int> randQty;
    std::bernoulli_distribution randAct;
    int nextID;

    public:
    //constructor to further define generating parameters
    OrderGenerator() {
        gen = std::mt19937(std::random_device{}());
        randPrice = std::uniform_real_distribution<double>(10.0, 10010.0);
        randQty = std::uniform_int_distribution<int>(0, 10000);
        randAct = std::bernoulli_distribution(0.5);
        nextID = 1;
    }

    //generate a random Order
    Order generateOrder(){
        Order order;
        order.id = nextID++;
        order.price = randPrice(gen);
        order.quantity = randQty(gen);
        if (randAct(gen)){
            order.type = OrderType::BUY;
        }
        else {
            order.type = OrderType::SELL;
        }
        return order;
    }

};