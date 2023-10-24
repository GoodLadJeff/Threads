#pragma once
/*
Write a program that computes the sum of the element of a table of n elements
1. Write a sequential version;
2. Write a version using thread local variable : the table is divided into m sub - tables, and each thread
compute the sum into its own local variable and return it;
3. Write a version using a global sum variable and mutexes.
*/

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

namespace Thread
{
    vector<int> getTable() { return { 65,83,31,20,63,2,11,45,54,80 }; };

    void Sequencial()
    {
        int total = 0;
        int size = getTable().size();

        for (int i = 0; i < size; i++) 
        {
            total += getTable()[i];
        }

        std::cout << "Sequencial : the sum of the table is " << total << std::endl;
    }

    void ThreadLocalSum(int threadID, int startIndex, int endIndex, int& threadSum) 
    {
        threadSum = 0;
        for (int i = startIndex; i < endIndex; i++) 
        {
            threadSum += getTable()[i];
        }
    }

    void ThreadLocal()
    {
        const int size = 10;
        const int sections = 2;

        int chunkSize = size / sections;
        std::vector<std::thread> thread_vector(sections);
        std::vector<int> threadSums(sections);

        for (int i = 0; i < sections; i++) {
            int startIndex = i * chunkSize;
            int endIndex = (i == sections - 1) ? size : (i + 1) * chunkSize;
            thread_vector[i] = std::thread(ThreadLocalSum, i, startIndex, endIndex, std::ref(threadSums[i]));
        }

        for (int i = 0; i < sections; i++) {
            thread_vector[i].join();
        }

        int finalSum = 0;
        for (int i = 0; i < sections; i++) {
            finalSum += threadSums[i];
        }

        std::cout << "ThreadLocal : the sum of the table is " << finalSum << std::endl;
    }

    std::mutex my_mutex;
    int globalSum = 0;

    void ThreadGlobalSum(int startIndex, int endIndex) 
    {
        int localSum = 0;
        for (int i = startIndex; i < endIndex; i++) 
        {
            localSum += getTable()[i];
        }

        std::lock_guard<std::mutex> lock(my_mutex);
        globalSum += localSum;
    }

    void ThreadGlobal()
    {
        const int size = 10;
        const int sections = 2;

        int chunkSize = size / sections;
        std::vector<std::thread> thread_vector(sections);

        for (int i = 0; i < sections; i++) 
        {
            int startIndex = i * chunkSize;
            int endIndex = (i == sections - 1) ? size : (i + 1) * chunkSize;
            thread_vector[i] = std::thread(ThreadGlobalSum, startIndex, endIndex);
        }

        for (int i = 0; i < sections; i++) {
            thread_vector[i].join();
        }

        std::cout << "ThreadLocal : the sum of the table is " << globalSum << std::endl;
    }
}