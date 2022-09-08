/*

COPYRIGHT (C) Angelo Indre (4680213) All rights reserved
Data Structures List Project
Author. Angelo Indre
        adi19@zips.uakron.edu
Purpose. Research performance of a selected data structure

*/

#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <algorithm>

#include "MyQueue.h"
#include "Complexity_Timer.hpp"
#include "Complexity_Recorder.hpp"

void timeAppendMyQueue(std::vector<recorder<timer> >&, bool);
void timeAppendList(std::vector<recorder<timer> >&, bool);
void timeAppendVector(std::vector<recorder<timer> >&);
void timeAppendQueue(std::vector<recorder<timer> >&, bool);

void comparingDiff(bool);
void comparingSame(bool);

int main()
{
    bool andUnwind = false;
    int choice = 1;
    while (choice == 1 || choice == 2)
    {
        std::cout << "test for just appending? Or append and pop_front?\n";
        std::cout << "1: append only\n";
        std::cout << "2: append and pop_front\n";
        std::cout << "Anything Else: quit\n";
        std::cin >> choice;

        if (choice == 1 || choice == 2)
        {
            if (choice == 1)
                andUnwind = false;
            else
                andUnwind = true;

            comparingDiff(andUnwind);
            std::cin.get();
            comparingSame(andUnwind);
            std::cin.get();
        }
    }

    return 0;
}

void timeAppendMyQueue(std::vector<recorder<timer> >& stats, bool y)
{

    //Helper Vars
    int containerSize = 50000;
    int entry =  0;

    //Timer declaration
    timer stopWatch;

    for (int j = 0; j < 6; j++)
    {
        MyQueue quesef;
        stopWatch.restart();
        for (int i = 0; i < containerSize; i++)
        {
            quesef.enqueue(i);
        }
        stopWatch.stop();
        stats[entry].record(stopWatch);
        containerSize *= 2;
        entry++;
        if (y)
            quesef.clear();
    }
}
void timeAppendList(std::vector<recorder<timer> >& stats, bool y)
{
    //Helper Vars
    int containerSize = 50000;
    int entry =  7;

    //Timer declaration
    timer stopWatch;

    for (int j = 0; j < 6; j++)
    {
        std::list<int> samuel;
        stopWatch.restart();
        for (int i = 0; i < containerSize; i++)
        {
            samuel.push_back(i);
        }
        stopWatch.stop();
        stats[entry].record(stopWatch);
        containerSize *= 2;
        entry++;
        if (y)
        {
            while (!samuel.empty())
                samuel.pop_front();
        }

    }
}
void timeAppendVector(std::vector<recorder<timer> >& stats)
{
    //Helper Vars
    int containerSize = 50000;
    int entry =  14;

    //Timer declaration
    timer stopWatch;

    for (int j = 0; j < 6; j++)
    {
        std::vector<int> victor;
        stopWatch.restart();
        for (int i = 0; i < containerSize; i++)
        {
            victor.push_back(i);
        }
        stopWatch.stop();
        stats[entry].record(stopWatch);
        containerSize *= 2;
        entry++;
    }

    return;
}
void timeAppendQueue(std::vector<recorder<timer> >& stats, bool y)
{

    //Helper Vars
    int containerSize = 50000;
    int entry =  7;

    //Timer declaration
    timer stopWatch;

    for (int j = 0; j < 6; j++)
    {
        std::queue<int> quesef;
        stopWatch.restart();
        for (int i = 0; i < containerSize; i++)
        {
            quesef.push(i);
        }
        stopWatch.stop();
        stats[entry].record(stopWatch);
        containerSize *= 2;
        entry++;
        if (y)
        {
            while (!quesef.empty())
            {
                quesef.pop();
            }
        }
    }
}

void comparingDiff(bool y)
{
    std::cout << "trial 1 compares 3 different data structures\n\n";
    std::vector<recorder<timer> > stats(50);
    timeAppendMyQueue(stats, y);
    timeAppendList(stats, y);
    timeAppendVector(stats);

    std::cout << "# of entries      |Enqueue         |Push_back       |Push_back\n";
    std::cout << " x10000           |(Queue)         |(List)          |(Vector)\n";
    std::cout << "                  |                |                |\n";

    int containerSize = 5;
    for (int i = 0; i < 6; i++)
    {
        std::cout << std::setw(12);
        std::cout << containerSize;
        stats[i + 00].report(cout, 1);
        stats[i + 07].report(cout, 1);
        if (!y)
        {
            stats[i + 14].report(cout, 1);
        }
        else
        {
            std::cout << "       No Pop Front";
        }
        std::cout << "\n";
        containerSize *= 2;
    }

}
void comparingSame(bool y)
{
    std::cout << "Trial 2 compares MyQueue to the std::queue\n\n";
    std::vector<recorder<timer> > stats(50);
    timeAppendMyQueue(stats, y);
    timeAppendQueue(stats, y);

    std::cout << "# of entries      |Enqueue         |Push_back\n";
    std::cout << " x10000           |(MyQueue)       |(std::queue)\n";
    std::cout << "                  |                |\n";

    int containerSize = 5;
    for (int i = 0; i < 6; i++)
    {
        std::cout << std::setw(12);
        std::cout << containerSize;
        stats[i + 00].report(cout, 1);
        stats[i + 07].report(cout, 1);
        std::cout << "\n";
        containerSize *= 2;
    }
}


