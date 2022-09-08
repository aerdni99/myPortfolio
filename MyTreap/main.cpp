/*

COPYRIGHT (C) Angelo Indre (4680213) All rights reserved
Data Structures Treap Project
Author. Angelo Indre
        adi19@zips.uakron.edu

main.cpp

implementation file for Treap testing

*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <iomanip>
#include "MyTreap.hpp"
#include "Trie.hpp"
#include "Complexity_Timer.hpp"


int menu(std::vector<double>& stats);
void timeTreapInsert(std::vector<double>& stats);
void timeTrieInsert(std::vector<double>& stats, size_t length);
void timeTreapSearch(std::vector<double>& stats);
void timeTrieSearch(std::vector<double>& stats);
void timeTreapRemove(std::vector<double>& stats);
void timeTrieRemove(std::vector<double>& stats);
void timeTreapLopsided(std::vector<double>& stats);
void timeTrieLopsided(std::vector<double>& stats);

int main()
{                               // while loop is broken if a non-menu item is chosen
    int choice = 2;             // choice determines what functions are called in the menu function, and
    while (choice != 0)         // and how to output the results in the main function
    {                           // output could be moved to its own function, but thats not the project purpose
        std::vector<double> stats;      // Holds the times of measure

        choice = menu(stats);
        if ((choice >= 1 && choice <= 3) || choice == 5)        // output results
        {
            std::cout << "                   treap         trie\n";
            for (int i = 0; i < 6; i++)
            {
                std::cout << std::setw(8) << pow(2, i) * 25000;
                std::cout << " inserts:";
                std::cout << std::setw(8) << stats[i] << "      ";
                std::cout << std::setw(8) << stats[i + 6] << "\n";
            }
            std::cout << std::endl << std::endl;
            std::cin.get();
            std::cin.get();
        }
        if (choice == 4)
        {
            std::cout << "                   trie\n";
            for (int i = 0; i < 6; i++)
            {
                std::cout << std::setw(8) << pow(2, i) * 25000;
                std::cout << " inserts:";
                std::cout << std::setw(8) << stats[i] << "\n";
            }
            std::cout << std::endl << std::endl;
            std::cin.get();
            std::cin.get();
        }
    }
    return 0;
}

int menu(std::vector<double>& stats)
{
    int choice = 0;
    std::cout << "Pick a test\n";
    std::cout << "1. inserting\n";
    std::cout << "2. searching\n";
    std::cout << "3. removing\n";
    std::cout << "4. vary trie length\n";
    std::cout << "5. insert Lopsided\n";
    std::cout << "anything else to quit...\n";
    std::cin >> choice;

    if (choice < 1 || choice > 5)
        return 0;
    if (choice == 1)
    {
        std::cout << "Inserting...\n";
        timeTreapInsert(stats);
        timeTrieInsert(stats, 10);
    }
    if (choice == 2)
    {
        std::cout << "Searching...\n";
        timeTreapSearch(stats);
        timeTrieSearch(stats);
    }
    if (choice == 3)
    {
        std::cout << "Removing...\n";
        timeTreapRemove(stats);
        timeTrieRemove(stats);
    }
    if (choice == 4)
    {
        bool valid = false;
        size_t length = 0;
        while (!valid)
        {
            std::cout << "What is the desired length?\n";
            std::cout << "Limited 1-20. or put 0 for random\n";
            std::cin >> length;
            if (length >= 0 && length <= 20)
            {
                valid = true;
            }
            else
            {
                std::cout << "Limited 1-20. or put 0 for random\n";
            }
        }
        std::cout << "inserting...\n";
        timeTrieInsert(stats, length);
    }
    if (choice == 5)
    {
        std::cout << "Lopsiding...\n";
        timeTreapLopsided(stats);
        timeTrieLopsided(stats);
    }
    return choice;

}

void timeTreapInsert(std::vector<double>& stats)
{
    timer stopwatch;

    for (int i = 1; i < 7; i ++)        // 6 tests of different sizes
    {
        MyTreap treap;
        int size = pow(2, i) * 25000;   // 6 tests of different sizes
        stopwatch.restart();
        for (int i = 0; i < size; i++)
        {
            treap.insert(rand() % 200); // random key inserted
        }
        stopwatch.stop();
        stats.push_back(stopwatch.time());
    }
}

void timeTrieInsert(std::vector<double>& stats, size_t length)
{
    timer stopwatch;
    bool randomLength = (length == 0);

    for (int i = 1; i < 7; i++)
    {
        Trie testTrie;
        stopwatch.restart();
        int size = pow(2, i) * 2500;
        for (int j = 0; j < size; j++)
        {
            if (randomLength)
                length = rand() % 20 + 1;
            std::string word;
            while (word.size() < length)            // random word generation for insertion (adds to time)
            {
                word.push_back(rand() % 26 + 'a');
            }
            testTrie.Insert(word);
        }
        stopwatch.stop();
        stats.push_back(stopwatch.time());
    }
}

void timeTreapSearch(std::vector<double>& stats)
{
    timer stopwatch;

    for (int i = 1; i < 7; i ++)
    {
        MyTreap treap;
        int size = pow(2, i) * 25000;
        for (int i = 0; i < size; i++)
        {
            treap.insert(rand());
        }
        stopwatch.restart();
        for (int i = 0; i < 100000; i ++)   // same insertion logic, add 100000 insertion calls
        {
            treap.search(rand());
        }
        stopwatch.stop();
        stats.push_back(stopwatch.time());
    }
}

void timeTrieSearch(std::vector<double>& stats)
{

    timer stopwatch;

    for (int i = 1; i < 7; i++)
    {
        Trie testTrie;
        int size = pow(2, i) * 2500;
        for (int j = 0; j < size; j++)
        {
            std::string word;
            while (word.size() < 10)
            {
                word.push_back(rand() % 26 + 'a');
            }
            testTrie.Insert(word);
        }
        stopwatch.restart();
        for (int i = 0; i < 100000; i++)
        {
            std::string word;
            while (word.size() < 10)
            {
                word.push_back(rand() % 26 + 'a');
            }
            testTrie.Search(word);
        }
        stopwatch.stop();
        stats.push_back(stopwatch.time());
    }
}

void timeTreapRemove(std::vector<double>& stats)
{
    timer stopwatch;

    for (int i = 1; i < 7; i ++)
    {
        std::vector<int> contents;
        MyTreap treap;
        int size = pow(2, i) * 25000;
        for (int i = 0; i < size; i++)
        {
            int ins = rand();
            treap.insert(ins);
            contents.push_back(ins);
        }
        stopwatch.restart();
        for (int i = 0; i < size; i++)      //same insertion logic, add vector to hold all values and remove each value at the end
        {
            treap.remove(contents[i]);
        }
        stopwatch.stop();
        stats.push_back(stopwatch.time());
    }
}

void timeTrieRemove(std::vector<double>& stats)
{

    timer stopwatch;

    for (int i = 1; i < 7; i++)
    {
        Trie testTrie;
        std::vector<std::string> contents;
        int size = pow(2, i) * 2500;
        for (int j = 0; j < size; j++)
        {
            std::string word;
            while (word.size() < 10)
            {
                word.push_back(rand() % 26 + 'a');
            }
            testTrie.Insert(word);
            contents.push_back(word);

        }
        stopwatch.restart();
        for (int j = 0; j < size; j++)
        {
            testTrie.Delete(contents[j]);
        }
        stopwatch.stop();
        stats.push_back(stopwatch.time());
    }
}

void timeTreapLopsided(std::vector<double>& stats)
{
    timer stopwatch;

    for (int i = 1; i < 7; i ++)
    {
        MyTreap treap;
        int size = pow(2, i) * 25000;
        stopwatch.restart();
        for (int i = 0; i < size; i++)
        {
            treap.insert(i);                // using the index as the key results in increasing ordered insertion
        }
        stopwatch.stop();
        stats.push_back(stopwatch.time());
    }
}

void timeTrieLopsided(std::vector<double>& stats)
{
    timer stopwatch;

    for (int i = 1; i < 7; i++)
    {
        Trie testTrie;
        stopwatch.restart();
        int size = pow(2, i) * 250;
        std::string word;                       // declare a word outside the loop and append inside to increase
        for (int j = 0; j < size; j++)          // length for every isert
        {
            word.push_back(rand() % 26 + 'a');
            testTrie.Insert(word);
        }
        stopwatch.stop();
        stats.push_back(stopwatch.time());
    }
}
