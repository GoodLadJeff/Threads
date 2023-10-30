#pragma once

#include <iostream>
#include <mutex>

class countdown
{

private:

    int odd_even;
    int* count;
    std::mutex& my_mutex;

    void startcount() const
    {
        while (*count < 1000)
        {
            std::lock_guard<std::mutex> lock(my_mutex);
            if (*count % 2 == odd_even)
            {
                std::cout << odd_even << " counts : " << *count << std::endl;
                *count += 1;
            }
        }
    }

public:

    countdown(int* count_p, const int odd_even_p, std::mutex& mutex) :
        odd_even(odd_even_p),
        count(count_p),
        my_mutex(mutex)
    {}

    void operator()() const
    {
        startcount();
    }
};
