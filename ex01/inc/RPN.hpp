/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:34:41 by dbonilla          #+#    #+#             */
/*   Updated: 2025/03/25 17:00:20 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef RPN_HPP
#define RPN_HPP
#include <iostream>
#include <stack>
#include <string>

enum    OperatorType
{
    OP_ADD,
    OP_SUBTRACT,
    OP_MULTIPLY,
    OP_DIVIDE,
    OP_UKNOWN
    
};

class RPN
{
    private:
        std::stack<int> _stack;
        OperatorType getOperatorType(char op) const;
        int applyOperation(OperatorType op, int a, int b) const;
    public:
        RPN();
        RPN(const RPN &other);
        RPN &operator=(const RPN &rhs);
        ~RPN();

        void evaluate(const std::string &expr);
       
        
};


#endif