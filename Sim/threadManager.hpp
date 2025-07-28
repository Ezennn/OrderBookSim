#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>

template<typename T>
class ThreadSafe {
    private :
    std::queue<T> q;
    std::mutex mut;
    std::condition_variable convar;

    public :
    void push(const T& item) {
        std::lock_guard<std::mutex> lock(mut);
        q.push(item);
        convar.notify_one();
    }

    bool pop(T& item) {
        std::unique_lock<std::mutex> ulock(mut);
        //put consumer to sleep when queue is empty
        convar.wait(ulock, [this]() {return !q.empty(); });
        item = q.front();
        q.pop();
        return true;
    }

    bool empty(){
        std::lock_guard<std::mutex> lock(mut);
        return q.empty();
    }

};