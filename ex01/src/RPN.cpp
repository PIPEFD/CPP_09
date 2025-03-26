/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:42:58 by dbonilla          #+#    #+#             */
/*   Updated: 2025/03/25 17:26:03 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/RPN.hpp"

#include <sstream>
#include <cstdlib>

RPN::RPN()
{
    std::cout << "RPN constructor called" << std::endl;
}

RPN::RPN(const RPN &other): _stack(other._stack)
{
    std::cout << "RPN copy constructor called" << std::endl;
}

RPN &RPN::operator=(const RPN &rhs)
{
    std::cout << "RPN assignation operator called" << std::endl;
    if (this != &rhs)
        _stack = rhs._stack;
    return (*this);
}

RPN::~RPN()
{
    std::cout << "RPN destructor called" << std::endl;
}

OperatorType RPN::getOperatorType(char op) const
{
    switch (op)
    {
    case    '+':
        return (OP_ADD);
    case    '-':
        return (OP_SUBTRACT);
    case    '*':
        return (OP_MULTIPLY);
    case    '/':
        return (OP_DIVIDE);
    default:
        return (OP_UKNOWN);
    }
}

int RPN::applyOperation(OperatorType op, int a, int b) const
{
    switch (op)
    {
    case    OP_ADD:
        return (a + b);
    case    OP_SUBTRACT:
        return (a - b);
    case    OP_MULTIPLY:
        return (a * b);
    case    OP_DIVIDE:
        if (b == 0)
        {
            std::cerr << "Error: division by zero" << std::endl;
            return (0);
        }
        std::cout << "a: " << a << " b: " << b << std::endl;
        return (a / b);
    default:
            return (0);
    }
}

void RPN::evaluate(const std::string &expr)
{
    std::istringstream iss(expr);
    std::string token;

    while (iss >> token)
    {
        if (token.length() == 1 && getOperatorType(token[0]) !=  OP_UKNOWN)
        {
            if (_stack.size() < 2)
            {
                std::cerr << "Error: not enough values in stack" << std::endl;
                return;
            }

            int b = _stack.top(); _stack.pop();
            int a = _stack.top(); _stack.pop();

            std::cout << "evaluate" << "a: " << a << " b: " << b << std::endl;
            OperatorType op = getOperatorType(token[0]);
            int result = applyOperation(op, a, b);
            _stack.push(result);
        }
        else
            {
                int value = std::atoi(token.c_str());
                _stack.push(value);
            }
        
        
    }
    if (_stack.size() != 1)
        std::cerr << "Error: too many values in stack" << std::endl;
    else
        std::cout << _stack.top() << std::endl;
}



