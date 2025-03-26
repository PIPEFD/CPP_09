/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 19:04:25 by dbonilla          #+#    #+#             */
/*   Updated: 2025/03/25 19:50:11 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <deque>
#include <list>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cstdlib>
#include <ctime>



class PmergeMe
{

    
    private:
        std::deque<int> _deque;
        std::list<int> _list;
        void mergeInsertionSortDeque(std::deque<int> &seq);
        void binaryInsertDeque(std::deque<int>& sorted, int value);
        void mergeInsertionSortList(std::list<int> &seq);
        void linearInsertList(std::list<int> &sorted, int value);
        void cloneInput(int argc, char **argv);  
        void printDeque(const std::deque<int> &seq) const;
        void printList(const std::list<int> &seq) const;
        
    public:
        PmergeMe();
        PmergeMe(int argc, char **argv);
        PmergeMe(const PmergeMe &other);
        PmergeMe &operator=(const PmergeMe &other);
        ~PmergeMe();

        void process();
        double getTimeForDeque();
        double getTimeForList();
        
};

#endif