#pragma once

#include <vector>
#include "OrderBookEntry.h"
#include "Wallet.h"
#include "OrderBook.h"
#include "CSVReader.h"





class MerkelMain
{
    public:
        MerkelMain();
        /** Call this to start the sim */
        std::string currentTime;
        void init();
    private: 
        void printMenu();
        void printHelp();
        void printMarketStats();
        void enterAsk();
        void enterBid();
        void printWallet();
        void gotoNextTimeframe();
        int getUserOption();
        void processUserOption(int userOption);

        

//       OrderBook orderBook{"20200317.csv"};
	     OrderBook orderBook{"20200601.csv"};
         Wallet wallet;
         advisorBot advisorbot;

};
