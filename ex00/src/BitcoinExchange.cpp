/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 11:36:05 by dbonilla          #+#    #+#             */
/*   Updated: 2025/03/25 01:11:10 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : _data(other._data)
{
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &rhs)
{
    if (this != &rhs)
    {
        _data = rhs._data;
    }
    return (*this);
}

BitcoinExchange::~BitcoinExchange()
{
    std::cout << "BitcoinExchange destructor called" << std::endl;
}

const char *BitcoinExchange::ExceptionNotOpenFile::what() const throw()
{
    return ("Could not open file");
}

const char *BitcoinExchange::ExceptionBadFormat::what() const throw()
{
    return ("Bad format in database file.");
}

const char *BitcoinExchange::ExceptionNoEarlyDataAvaliable::what() const throw()
{
    return ("No earlier date available.");
}
const char *BitcoinExchange::ExceptionDayToEarlyFuture::what() const throw()
{
    return (" date is too early or too far in the future.");
}

void BitcoinExchange::loadDatabase(const std::string &filename) {
    std::ifstream file(filename.c_str());
    if (!file)
        throw ExceptionNotOpenFile();

    std::string line;
    std::getline(file, line); // skip header

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string date, rateStr;
        if (std::getline(ss, date, ',') && std::getline(ss, rateStr)) {
            float rate = std::atof(rateStr.c_str());
            _data[date] = rate;
        } else {
            throw ExceptionBadFormat();
        }
    }
}

float BitcoinExchange::getExchangeRate(const std::string &date) const
{
    std::map<std::string, float>::const_iterator it = _data.lower_bound(date);
    if (it != _data.end())
        return (it->second);
    if (it == _data.begin())
        throw ExceptionNoEarlyDataAvaliable();
    it--;
    return (it->second);

}

bool BitcoinExchange::isValidDate(const std::string &date) 
{
    if (date.length() != 10 || date[4] != '-' || date[7] != '-')
        return (0);

    int year = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day = std::atoi(date.substr(8, 2).c_str());

    if ((year < 2009 || month < 1 || month > 12 || day < 1 )||((year > 2022 || month > 3 || day > 29)))
        return(0);
        // throw BitcoinExchange::ExceptionDayToEarlyFuture();
    int daysInMonth[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0))
        daysInMonth[2] = 29;

    if (day > daysInMonth[month])
        return (0);

    return (1);
}

bool BitcoinExchange::parseInputLine(const std::string &line, std::string &date, float& value) {
    std::istringstream ss(line);
    std::cout << line << std::endl;
    std::string separator;
    if (!(ss >> date >> separator >> value)) {
        std::cerr << "Error: bad input => " << line << std::endl;
        return (0);
    }
    if (separator != "|") {
        std::cerr << "Error: bad input => " << line << std::endl;
        return (0);
    }
    if (!isValidDate(date)) {
        std::cerr << "Error: bad input => " << line << std::endl;
        return (0);
    }
    if (value < 0) {
        std::cerr << "Error: not a positive number." << std::endl;
        return (0);
    }
    if (value > 1000) {
        std::cerr << "Error: too large a number." << std::endl;
        return (0);
    }
    return (1);
}

void BitcoinExchange::process(const std::string& inputFile) {
    loadDatabase("data.csv");

    std::ifstream infile(inputFile.c_str());
    if (!infile)
        throw ExceptionNotOpenFile();

    std::string line;
    std::getline(infile, line);

    while (std::getline(infile, line)) {
        if (line.empty())
            continue;

        std::string date;
        float value;
        if (!parseInputLine(line, date, value))
            continue;

        try {
            float rate = getExchangeRate(date);
            float result = value * rate;
            std::cout << date << " => " << value << " = " << result << std::endl;
        } catch (const std::exception &e) {
            std::cerr << "Error: " << e.what() << " for date " << date << std::endl;
        }
    }
}