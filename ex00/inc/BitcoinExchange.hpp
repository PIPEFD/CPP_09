/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 11:30:21 by dbonilla          #+#    #+#             */
/*   Updated: 2025/03/25 01:10:44 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <map>
# include <cstdlib>
# include <exception>
#include <stdexcept>
# include <fstream>
# include <sstream>

class BitcoinExchange
{
  private:
	std::map<std::string, float> _data;

  public:
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange &other);
	BitcoinExchange &operator=(const BitcoinExchange &rhs);
	~BitcoinExchange();

	class ExceptionNotOpenFile : public std::exception
	{
		public:
		virtual const char *what() const throw();
	};
    class ExceptionBadFormat : public std::exception
    {
        public:
        virtual const char *what() const throw();
    };

    class ExceptionNoEarlyDataAvaliable : public std::exception
    {
        public:
        virtual const char *what() const throw();
    };

    class ExceptionDayToEarlyFuture: public std::exception
    {
        public:
        virtual const char *what() const throw();
    };
    
    void process(const std::string& inputFile);
    void loadDatabase(const std::string &filename);
	float getExchangeRate(const std::string &date) const;
    bool parseInputLine(const std::string &line, std::string &date, float& value);
    bool isValidDate(const std::string &date);

};

#endif