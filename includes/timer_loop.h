//
// Created by Mason on 2022/5/6.
// This is an async function

#ifndef CATEGORY_SCRIPT_TIMER_LOOP_H
#define CATEGORY_SCRIPT_TIMER_LOOP_H
#include <functional>
#include <chrono>
#include <future>

class TimeLoop {
public:
    template<class callable, class... arguments>
    TimeLoop(int after, bool async, callable&& f, arguments&&... args)
    {
        std::function<typename std::result_of<callable(arguments...)>::type()> task(std::bind(std::forward<callable>(f), std::forward<arguments>(args)...));

        if (async)
        {
            std::thread([after, task]() {
                std::this_thread::sleep_for(std::chrono::milliseconds(after));
                task();
            }).detach();
        }
        else
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(after));
            task();
        }
    }
};

#endif //CATEGORY_SCRIPT_TIMER_LOOP_H
