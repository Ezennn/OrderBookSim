#pragma once

//OrderType type that could only be BUY or SELL
enum class OrderType { BUY , SELL };

//Order type which contains an id, OrderType (BUY or SELL), a price and a quantity
struct Order {
    int id;
    OrderType type;
    double price;
    int quantity;
};
