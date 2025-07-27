#pragma once
#include <map>
#include <iostream>
#include <mutex>
#include "order.hpp"

//OrderBook Type which introduces addOrder and matchOrder functions
class OrderBook {
    //inaccessible outside this file
    private :
    std::multimap<double, Order, std::greater<double>> bids;

    std::multimap<double, Order> asks;

    std::mutex mut;

    //accessible outside this file
    public :

    //addOrder adds an Order, and format to fit into OrderBook type
    void addOrder (const Order& order){
        std::lock_guard<std::mutex> lock(mut); 

        if (order.type == OrderType::BUY){
            bids.insert({order.price, order});
        }
        if (order.type == OrderType::SELL){
            asks.insert({order.price, order});
        }

    }

    //main function to compare Orders
    void matchOrder (){
        std::lock_guard<std::mutex> lock(mut);

        while (!bids.empty() && !asks.empty()){
            auto highestBid = bids.begin();
            auto lowestAsks = asks.begin();

            if (highestBid->first >= lowestAsks->first){
                int qty = std::min(highestBid->second.quantity, lowestAsks->second.quantity);
                double tradePrice = lowestAsks->first;

                std::cout << "TRADE : " << qty << " @ $ " << tradePrice << std::endl;

                highestBid->second.quantity -= qty;
                lowestAsks->second.quantity -= qty;

                if (highestBid->second.quantity == 0){bids.erase(highestBid);}
                if (lowestAsks->second.quantity == 0){asks.erase(lowestAsks);}

            }
            else { 
                break;
            }
        }
    }


};