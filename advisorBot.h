#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "CSVReader.h"
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include "Wallet.h"

class advisorBot 
{
private:
    /* data */
    std::vector<OrderBookEntry>entities=CSVReader::readCSV("20200601.csv");


public:
    advisorBot();
    void help();
    void botResponse(std::string);
    void botResponse2(std::string);
    std::vector<std::string> productList();
    std::vector<OrderBookEntry> getOrders(OrderBookType type,std::string product,std::string timestamp);
    std::vector<double> Range(std::string product,OrderBookType type, std::string range, int time);
    void Range1(std::string product,OrderBookType type, std::string range,int number);
    std::string typeTostring(OrderBookType);
    std::string getcurrentTimstep();
    std::string getNextTimestep(std:: string currentTime);
    void predictNext(std::string product,OrderBookType type, std::string range);
    bool verifyInput(std::string range);
    bool verifyInput1(std::string range);

    std::vector<std::string> products;
    std::vector<std::string> k;
    std::vector<std::string> getTimestamps(int time);
    std::string timestamp;
    std::vector<std::string> timestamps;
    std::string currentTime;

};