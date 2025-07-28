# OrderBookSim

- A high performance multithreaded order book simulator with optional logging features
- Coded in C++
- Optimized with local buffers (for logging), thread-safe queues and minimal logging overheads
- Priority was given to code maintainability

## Notable Features :
- Total runtime of O(n log n) where n is the total number of order
- Multi-threaded Producer Consumer Model
- Trade matching engine using bids and asks multimap structures
- Optional logging as a CSV output
- Simple timer for benchmarking
- Lock-safe queues for effective concurrency

## Performance :
### Note that all this was implemented with a 4-core machine (hyperthreaded)
### This implies that the maximum threads used was 8 threads - 1 for producer, 7 for consumers
- 1M (1,000,000) orders processed in 1.5 seconds WITHOUT logging
- Throughput: ~660,000 orders/second
- 1M orders processed in 2.5 seconds WITH logging
- Throughput: ~400,000 orders/second

## How to build and run :
- Pre-requisites : A C++17 compliant compiler (e.g., GCC, Clang)
- " g++ main.cpp -std=c++17 -pthread -o OrderBookSim "
- **WITH LOGGING :** " " ./OrderBookSim --log=true "
- **WITHOUT LOGGING :**  " ./OrderBookSim "

## Trade logs :
- trade logs include quantity of trade, price of trade, Buter ID and seller ID
- file generated will be called "trades.csv"

## Code reasonings 
### std::multimap
purpose - maintain order of bids and asks\n
**why multimap?**
- maintains order based on price of bids and asks
- supports duplicate price
- eliminate need for linear search, all process is done under O(log n)
- **insert()** is O(log n), **begin()** is O(1), **erase** is O(log n)

### std::ThreadSafe<Order>
purpose - store orders from producers until consumer can process them, acting essntially as a buffer.\n
**why std::queue?**
- keep processes in O(1)
- push is O(1) and pop is O(1)
- FIFO structure (First In First Out) ideal for producer consumer

### std::stringstream localBuffer
purpose - single thread buffer for log data to avoid locking every log write.\n
**why stringstream?**
- Logging to disk is slow.
- Buffering avoids the need to lock std::ofstream so frequently.
- Lock once per thread to flush buffer.

## Possible Improvements
- Make it a distributed system
- Web FrontEnd to visualise project better (A dashboard for example)
- Make it a live, networked service
- Log trades in database instead of CSV file
