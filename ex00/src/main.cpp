/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:42:41 by dbonilla          #+#    #+#             */
/*   Updated: 2025/03/25 16:15:00 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/BitcoinExchange.hpp"


int main(int argc, char **argv) {
    if (argc != 2) 
    {
        std::cerr << "Error: could not open file." << std::endl;
        return (1);
    }
    try 
    {
        BitcoinExchange btc;
        btc.process(argv[1]);
    } 
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return (1);
    }
    return (0);
}
