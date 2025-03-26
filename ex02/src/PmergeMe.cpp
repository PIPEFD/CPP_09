/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 19:04:43 by dbonilla          #+#    #+#             */
/*   Updated: 2025/03/26 03:20:10 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/PmergeMe.hpp"

#include <ctime>
PmergeMe::PmergeMe()
{
    std::cout << "Constructor called" << std::endl;
}

PmergeMe::PmergeMe(int argc, char **argv)
{
    std::cout << "Constructor called" << std::endl;
    cloneInput(argc, argv);
    process();
}
PmergeMe::PmergeMe(const PmergeMe &other) : _deque(other._deque), _list(other._list)
{
    std::cout << "Copy constructor called" << std::endl;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    if (this != &other)
    {
        _deque = other._deque;
        _list = other._list;
    }
    return (*this);
}

PmergeMe::~PmergeMe()
{
    std::cout << "Destructor called" << std::endl;
}
void PmergeMe::cloneInput(int argc, char **argv)
{
    for (int i = 1; i < argc; i++)
    {
        int value = std::atoi(argv[i]);
        _deque.push_back(value);
        _list.push_back(value);
    }
}
void PmergeMe::binaryInsertDeque(std::deque<int> &sorted, int value)
{
    int low = 0;
    int high = sorted.size();
    while (low < high)
    {
        int mid = (low + high) / 2;
        if (value < sorted[mid])
            high = mid;
        else
            low = mid + 1;
    }
    sorted.insert(sorted.begin() + low, value);
}

void PmergeMe::linearInsertList(std::list<int> &sorted, int value)
{
    std::list<int>::iterator it = sorted.begin();
    while (it != sorted.end() && *it < value)
        ++it;
    sorted.insert(it, value);
}

void PmergeMe::mergeInsertionSortDeque(std::deque<int> &seq)
{
    if (seq.size() <= 1)
        return;

    std::deque<int> winners;
    std::deque<int> losers;
    size_t i = 0;
    while (i + 1 < seq.size())
    {
        int a = seq[i];
        int b = seq[i + 1];
        if (a < b)
        {
            winners.push_back(b);
            losers.push_back(a);
        }
        else
        {
            winners.push_back(a);
            losers.push_back(b);
        }
        i += 2;
    }
    if (i < seq.size())
    {
        winners.push_back(seq[i]);
    }
    mergeInsertionSortDeque(winners);
    for (size_t j = 0; j < losers.size(); ++j)
    {
        binaryInsertDeque(winners, losers[j]);
    }
    seq = winners;
}

void PmergeMe::mergeInsertionSortList(std::list<int> &seq)
{
    std::cout << "HOLA" << std::endl;
    if (seq.size() <= 1)
        return;

    std::list<int> winners;
    std::list<int> losers;
    std::list<int>::iterator it = seq.begin();

    while (it != seq.end())
    {

        std::list<int>::iterator first = it;

        std::list<int>::iterator second = it;
        ++second;

        if (second != seq.end())
        {

            if (*first < *second)
            {
                winners.push_back(*second);
                losers.push_back(*first);
            }
            else
            {
                winners.push_back(*first);
                losers.push_back(*second);
            }

            it = second;
            ++it;
        }
        else
        {

            winners.push_back(*first);
            break;
        }
    }

    mergeInsertionSortList(winners);

    for (std::list<int>::iterator lit = losers.begin(); lit != losers.end(); ++lit)
    {
        linearInsertList(winners, *lit);
    }

    seq = winners;
}

void PmergeMe::printDeque(const std::deque<int> &seq) const
{
    for (std::deque<int>::const_iterator it = seq.begin(); it != seq.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
}

void PmergeMe::printList(const std::list<int> &seq) const
{
    for (std::list<int>::const_iterator it = seq.begin(); it != seq.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
}

double PmergeMe::getTimeForDeque()
{
    std::deque<int> copyDeque = _deque;
    clock_t start_deque = clock();
    mergeInsertionSortDeque(copyDeque);
    clock_t end_deque = clock();
    double elapsed_deque = double(end_deque - start_deque) / CLOCKS_PER_SEC * 1e6;
    return elapsed_deque;
}

double PmergeMe::getTimeForList()
{
    std::list<int> copyList(_list);
    clock_t start_list = clock();
    mergeInsertionSortList(copyList);
    clock_t end_list = clock();
    double elapsed_list = double(end_list - start_list) / CLOCKS_PER_SEC * 1e6;
    return elapsed_list;
}

void PmergeMe::process()
{
    std::cout << "Process called" << std::endl;
    printDeque(_deque);
    printList(_list);

    std::deque<int> copyDeque = _deque;
    clock_t start_deque = clock();
    mergeInsertionSortDeque(copyDeque);
    clock_t end_deque = clock();
    double elapsed_deque = double(end_deque - start_deque) / CLOCKS_PER_SEC * 1e6;

    std::list<int> copyList(_list);
    clock_t start_list = clock();
    mergeInsertionSortList(copyList);
    clock_t end_list = clock();
    double elapsed_list = double(end_list - start_list) / CLOCKS_PER_SEC * 1e6;

    std::cout << "After sorting with deque:" << std::endl;
    printDeque(copyDeque);
    std::cout << "After sorting with list:" << std::endl;
    printList(copyList);
    std::cout << "Time to process a range of " << copyDeque.size() << " elements with std::deque : "
              << elapsed_deque << " us" << std::endl;
    std::cout << "Time to process a range of " << copyList.size() << " elements with std::list : "
              << elapsed_list << " us" << std::endl;
}