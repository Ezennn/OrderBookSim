# OrderBookSim

- **A high performance multithreaded order book simulator with optional logging features**
- Coded in C++
- Optimized with local buffers (for logging), thread-safe queues and minimal logging overheads
- Priority was given to code maintainability

<details>
<summary><strong>What is an order book that I am simulating?</strong></summary>

- An order book is a system that matches two groups, the buyer and the seller
- When the seller sells an item for a price lower than the amount of money the buyer is willing to pay a trade happens
- The order will decide when a trade happens, record each trade and keep track of buyers and sellers
- This order can process about 1,250,000 orders per second and could be even faster if you use a machine with more cores.

</details>

## Notable Features :
- Total runtime of O(n log n) where n is the total number of order
- Multi-threaded Producer Consumer Model
- Trade matching engine using bids and asks multimap structures
- Optional logging as a CSV output
- Simple timer for benchmarking

## Performance :
### Note that all this was implemented with a 4-core machine (hyperthreaded)
### This implies that the maximum threads used was 8 threads - 1 for producer, 7 for consumers
| Orders Processed | Logging | Time Taken | Trades Made | Throughput             |
|------------------|---------|------------|-------------|------------------------|
| 1,000,000        | Off     | 0.80 sec    | 780,000+    | 1,250,0000 orders/sec |
| 1,000,000        | On      | 1.75 sec    | 780,000+    | 570,000 orders/sec    |

## Comparison Graphs :
<img width="683" height="427" alt="Screenshot 2025-08-06 210624" src="https://github.com/user-attachments/assets/eca3d53e-954b-4cbd-b643-7b96aca42678" />

The graph indicates a counterintuitive drop in throughput as the number of threads increases. Instead of scaling linearly or plateauing, performance degrades — a clear sign of contention issues, likely due to:
- Lock contention on shared resources
- Inefficient synchronization (e.g., mutexes around critical paths)
- Potential false sharing or cache thrashing

This behavior is actively being investigated, with profiling tools focused on:
- Lock wait times
- Thread blocking statistics.

**Achieved PP99.9 latency of 4 microseconds, even under high load.**


## How to build and run :
- Pre-requisites : A C++17 compliant compiler (e.g., GCC, Clang)
- ` g++ main.cpp -std=c++17 -pthread -o orderbooksim `
- **WITH LOGGING :** ` ./orderbooksim --log `
- **WITHOUT LOGGING :**  ` ./orderbooksim `

## Trade logs :
- trade logs include quantity of trade, price of trade, Buyer ID and seller ID
- file generated will be called "trades.csv"

## Code reasonings 
<details>
<summary><strong>Click to expand code reasoning</strong></summary>
  
### std::multimap
purpose - maintain order of bids and asks. \n
**why multimap?**
- maintains order based on price of bids and asks
- supports duplicate price
- eliminate need for linear search, all process is done under O(log n)
- `insert()` is O(log n), `begin()` is O(1), `erase` is O(log n)

### std::ThreadSafe<Order>
purpose - store orders from producers until consumer can process them, acting essentially as a buffer.\n
**why std::queue?**
- keep processes in O(1)
- `push()` is O(1) and `pop()` is O(1)
- FIFO structure (First In First Out) ideal for producer consumer

### std::stringstream localBuffer
purpose - single thread buffer for log data to avoid locking every log write.\n
**why stringstream?**
- Logging to disk is slow.
- Buffering avoids the need to lock std::ofstream so frequently.
- Lock once per thread to flush buffer.

</details>

## Possible Improvements
- Make it a distributed system
- Web FrontEnd to visualise project better (A dashboard for example)
- Make it a live, networked service
- Log trades in database instead of CSV file

## Why This Project Was Done
This project:
- Allowed me to have better understanding of concurrency in C++
- Helped me learn about practical trade-offs between performance, and maintainability
  - Particularly tradeoff between having simple, maintainable code, but throughput wouldn't scale with number of threads  
- Real-world benchmarking and profiling practices
- Authored by Ezen
