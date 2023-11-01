#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

//variables
vector<int> ingredient_vector = {1,2,3,4,5,6,7,8,9,10};
vector<int> order = vector<int>();
vector<int> ingredients_to_prepare = vector<int>();
vector<int> ingredients_cooked = vector<int>();
string final_meal = string();

std::condition_variable cv;
std::mutex mtx;

//simple function to return a random int between 1 and 10
int GetARandomIngredient()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(1, ingredient_vector.size()-1);
    int random_number = distribution(gen);

    return random_number;
}

void Customer()// the customer picks 3 random ingredients (which are simply ints) and pushes them into the order vector and notifies the cv
{
    {
        lock_guard<mutex> lock(mtx);

        cout << "customer is picking the meal" << endl;
        this_thread::sleep_for(chrono::seconds(1));

        for (int i = 0; i < 3; i++)
        {
            int random_ingredient = ingredient_vector[GetARandomIngredient()];
            order.push_back(random_ingredient);
            cout << "customer picked ingredient " << random_ingredient << std::endl;
        }
    }
    cv.notify_one();

    // when the final meal is done the customer will eat the meal and leave
    unique_lock<mutex> lock(mtx);
    cv.wait(lock, [] { return !final_meal.empty(); });

    cout << "customer is eating the meal" << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "customer enjoyed his meal, paid and left" << endl;
}

void Waiter()// the waiter waits for the order to not be empty anymore, and fills the ingredients to prepare vector, the clears the order
{
    unique_lock<mutex> lock(mtx);
    cv.wait(lock, [] { return !order.empty(); });

    for (int i = 0; i < order.size(); i++)
    {
        ingredients_to_prepare.push_back(order[i]);
        cout << "waiter order contains " << order[i] << endl;
    }

    cout << "waiter is bringing the order" << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "waiter brought the order" << endl;

    order.clear();

    cv.notify_one();
}

void Cook()// the cook fills the ingredients cooked vector, after waiting for each ingredient to be cooked, then clears the ing to prepapre and notifies 
{
    unique_lock<mutex> lock(mtx);
    cv.wait(lock, [] { return !ingredients_to_prepare.empty(); });

    for (int i = 0; i < ingredients_to_prepare.size(); i++)
    {
        ingredients_cooked.push_back(ingredients_to_prepare[i]);

        cout << "currently cooking" << endl; 
        this_thread::sleep_for(chrono::seconds(1));
        cout << "the ingredient " << ingredients_to_prepare[i] << " is cooked" << std::endl;
    }

    ingredients_to_prepare.clear();

    cv.notify_one();
}

void Chief()// the chief puts the final meal together
{
    unique_lock<mutex> lock(mtx);
    cv.wait(lock, [] { return !ingredients_cooked.empty(); });

    for (int i = 0; i < ingredients_cooked.size(); i++)
    {
        final_meal+= to_string(ingredients_cooked[i]);
    }

    cout << "preparing the final meal" << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "the final meal is " << final_meal << std::endl;
    ingredients_cooked.clear();

    cv.notify_one();
}

namespace SimpleRestaurant
{
    void PlayService()
    {
        cout << "----------------" << endl;
        cout << "Simple Restaurant" << endl;

        std::thread customerThread(Customer);
        std::thread waiterThread(Waiter);
        std::thread cookThread(Cook);
        std::thread chiefThread(Chief);

        customerThread.join();
        waiterThread.join();
        cookThread.join();
        chiefThread.join();
    }
}