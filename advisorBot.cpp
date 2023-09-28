#include"advisorBot.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <map>
#include <iomanip>
#include <ctype.h>
#include <sstream>
#include <cmath>
#include <numeric>



advisorBot::advisorBot() {

};

//code for help menu display
void advisorBot::help() {
  std::string input;
  std::cout << "advisorbot>Please enter a command, or help for a list of commands" << std::endl;
  std::getline(std::cin, input);
  if (input == "help")

  {
    // 1 print help
    std::cout << "1: help " << std::endl;
    // 2 help with commands
    std::cout << "2: help <cmd>" << std::endl;
    // 3 list available products
    std::cout << "3: prod " << std::endl;
    // 4 find minimum bid or ask 
    std::cout << "4: min " << std::endl;
    // 5  find maximum bid or ask 
    std::cout << "5: max " << std::endl;
    // 6 average ask or bid time steps   
    std::cout << "6: avg " << std::endl;
    // 7 predict max/min for ask or bid 
    std::cout << "7: predict" << std::endl;
    // 8 time in dataset
    std::cout << "8: time" << std::endl;
    // 8 move to next time step
    std::cout << "9: step" << std::endl;
    // 10 exit to main menu
    std::cout << "10: exit" << std::endl;
    std::cout << "=================" << std::endl;

    advisorBot::botResponse(input);
    //code for error handling
  } else {
    std::cout << "advisorbot>Bad input!" << std::endl;
    advisorBot::help();
  }
}


//command parsing code of user input on help menu selection
void advisorBot::botResponse(std::string input) {
  
  //function to taken in user input and writes to string
  std::getline(std::cin, input);

  //conditional logic calling different functions based on selected user input
  if (input == "1") {
    std::cout << "you chose 1" << std::endl;
    advisorBot::help();
  } else if (input == "2" || input == "help <cmd>") {
    std::cout << "you chose 2" << std::endl;
    advisorBot::botResponse2(input);
  } else if (input == "3" || input == "prod") {
    std::cout << "you chose 3 or entered 'prod' command" << std::endl;
    advisorBot::productList();
    for (auto & e: products) std::cout << e.data() << std::endl;
  } else if (input == "4" || input == "min") {
    std::cout << "you chose 4 or entered 'min' command" << std::endl;
    advisorBot::verifyInput("min");
  } else if (input == "5" || input == "max") {
    std::cout << "you chose 5 or entered 'max' command" << std::endl;
    advisorBot::verifyInput("max");
  } else if (input == "6" || input == "avg") {
    std::cout << "you chose 6 or entered 'avg' command" << std::endl;
    advisorBot::verifyInput1("avg");
  } else if (input == "7" || input == "predict") {

    std::cout << "you chose 7 or entered 'predict' command" << std::endl;
    advisorBot::verifyInput1("predict");
  } else if (input == "8" || input == "time") {
    advisorBot::currentTime = getcurrentTimstep();
    std::cout << currentTime << std::endl;
  } else if (input == "9" || input == "step") {
    currentTime = getcurrentTimstep();
    currentTime = getNextTimestep(currentTime);
    std::cout << currentTime << std::endl;
  } else if (input == "10" || input == "exit") {
    std::cout << "advisorBot> you are now returned to main menu" << std::endl;

    //code for error handling/throws error message on bad user input
  } else {
    std::cout << " ======================================================" << std::endl;
    std::cout << " ******Bad Input! you have entered :" << input + "********" << std::endl;
    advisorBot::help();

  }
}


//code to display a list of help on individual commands
void advisorBot::botResponse2(std::string input) {
  std::cout << "you chose 2 or entered help<cmd>" << std::endl;
  std::cout << "Enter one of the following help commands for information on using commands. " << std::endl;
  std::cout << "============================================================================ " << std::endl;
  std::cout << "help prod- for help on prodcut list" << std::endl;
  std::cout << "help min - for help on finding minimum bid or ask " << std::endl;
  std::cout << "help max-  for help on finding minimum bid or ask" << std::endl;
  std::cout << "help avg-  for help on finding average ask or bid" << std::endl;
  std::cout << "help predict- for help on predicting maximum or minimum bid or ask" << std::endl;
  std::cout << "help step- for help to move to next time step" << std::endl;
  std::cout << "help time -for help on current time in datastep " << std::endl;
  std::cout << "help exit -for help on return to main menu " << std::endl;

  std::getline(std::cin, input);

   //conditional logic to display help on individual commands upon user input
  if (input == "help prod") {
    std::cout << "advisorbot> Enter 'prod'  to list all products e.g, prod->ETH/BTC,DOGE/BTC" << std::endl;
  } else if (input == "help min") {
    std::cout << "Enter min product bid or ask e.g, min ETH/BTC ask->The min ask for ETH/BTC is 1.0" << std::endl;
  } else if (input == "help max") {
    std::cout << "Enter max product  bid or ask e.g, max ETH/BTC ask->The max ask for ETH/BTC is 1.0" << std::endl;
  } else if (input == "help avg") {
    std::cout << "Enter avg product ask/bid timesteps e.g, avg ETH/BTC ask 10" << std::endl;
  } else if (input == "help predict") {
    std::cout << "Enter predict max/min product ask/bid e.g, predict max ETH/BTC bid" << std::endl;
  } else if (input == "help step") {
    std::cout << "Enter 'step' e.g, step ->now at 2020/03/17 17:01:30" << std::endl;
  } else if (input == "help time") {
    std::cout << "Enter 'time' e.g, time ->2020/03/17 17:01:24" << std::endl;
  } else if (input == "help exit") {
    std::cout << "Enter 'exit' to return to main menu";
  } else {
    std::cout << " ======================================================" << std::endl;
    std::cout << " ******Bad Input! you have entered :" << input + "********" << std::endl;
    advisorBot::botResponse2(input);
  }
}


//function to return vector of available products for trading.
std::vector < std::string > advisorBot::productList()

{
  std::string currency;
  for (int i = 0; i < entities.size(); i++) {
    currency = (entities[i].product);
    products.push_back(currency);
  }
  std::map < std::string, int > prodMap;
  
  //code mapping similar products into a mapping vector
  for (auto & e: products) {
    if (prodMap.count(e) == 0) prodMap.emplace(e, 1);
  }
  products.clear();
  std::cout << "advisorBot>" << std::endl;
  for (auto & e: prodMap) {
   
    products.push_back(e.first);
     
  }
  return products;
}


//function returning vector of orderbook entries that match Orderbook type, product & timestamp arguments
std::vector < OrderBookEntry > advisorBot::getOrders(OrderBookType type, std::string product, std::string timestamp) {

  std::vector < OrderBookEntry > orders_sub;
  for (OrderBookEntry & e: entities) {
    if (e.orderType == type &&
      e.product == product &&
      e.timestamp == timestamp) {
      orders_sub.push_back(e);
    }
  }
  return orders_sub;
}


//function computes min/max bids/asks for a selected product also predicts min or max for a product for next timestep
std::vector < double > advisorBot::Range(std::string product, OrderBookType type, std::string range, int time) {

  std::string orderType = typeTostring(type);
  std::vector < std::string > timestep = getTimestamps(time);
  double Price;
  std::vector < double > prices;
  std::vector < OrderBookEntry > asks;
  std::vector < OrderBookEntry > bids;
  //Nested loop to match orderbook entries to function arguments
  for (int i = 0; i < entities.size(); ++i) {
    for (int j = 0; j < timestep.size(); ++j) {

      //conditional logic computing min, max & predicted min and max prices for asks
      if (entities[i].timestamp == timestep[j] && entities[i].product == product && entities[i].orderType == type) {
        if (type == OrderBookType::ask) {
          if (range == "min" || "premin") {
            asks = getOrders(entities[i].orderType, entities[i].product, entities[i].timestamp);
            //sorting function sorting asks in descending price order
            std::sort(asks.begin(), asks.end(), OrderBookEntry::compareByPriceDesc);
            Price = asks[asks.size() - 1].price;
            prices.push_back(Price);
          } else if (range == "max" || "premax") {
            asks = getOrders(entities[i].orderType, entities[i].product, entities[i].timestamp);
            //sorting function sorting asks in ascending price order
            std::sort(asks.begin(), asks.end(), OrderBookEntry::compareByPriceAsc);
            Price = asks[asks.size() - 1].price;
            prices.push_back(Price);
          }
          //conditional logic computing min, max & predicted min and max prices for bids
        } else if (type == OrderBookType::bid) {
          if (range == "min" || "premin") {
            bids = getOrders(entities[i].orderType, entities[i].product, entities[i].timestamp);
            //sorting function sorting bids in descending price order
            std::sort(bids.begin(), bids.end(), OrderBookEntry::compareByPriceDesc);
            Price = bids[bids.size() - 1].price;
            prices.push_back(Price);
          } else if (range == "max" || "premax") {
            bids = getOrders(entities[i].orderType, entities[i].product, entities[i].timestamp);
            //sorting function sorting bids in ascending price order
            std::sort(bids.begin(), bids.end(), OrderBookEntry::compareByPriceAsc);
            Price = bids[bids.size() - 1].price;
            prices.push_back(Price);
          }
        }
      }

    }

  }
   //coditional to print bot response to only min or max user commands 
  if (range == "min" || range == "max") {
    std::cout << std::fixed;
    std::cout << "advisorBot> " << range << " " << product << " " << orderType << " is " << std::setprecision(8) << Price << std::endl;
  }

  return prices;
}


//function code to print average min or max for a product over a specific time steps
void advisorBot::Range1(std::string product, OrderBookType type, std::string range, int number) {
  double average;
  std::string orderType = typeTostring(type);
  std::vector < double > prices;
  std::vector < std::string > timestep = getTimestamps(number);

  std::string g = typeTostring(type);
  //nested loop to match orderbook entries to specific time stamps
  for (int i = 0; i < entities.size(); ++i) {
    for (int j = 0; j < timestep.size() - 1; ++j) {
      //conditional checking orderbook entries that match function arguments and pushing them to a vector
      if (entities[i].product == product && entities[i].orderType == type && entities[i].timestamp == timestep[j]) {
        average = entities[i].price;
        prices.push_back(average);
      }
    }

  }
  //average calculated for the elements of the vector
  average = std::accumulate(prices.begin(), prices.end(), 0.0) / prices.size();
  std::cout << "advisorBot> the average " << product << " " << orderType << " price over last " << number << " timesteps was " << average << std::endl;
}


//function code to calculate average of the min/max asks/bids from a returned vector from Range function,to predict 
//min or max for a product for next time step
void advisorBot::predictNext(std::string product, OrderBookType type, std::string range) {

  double average;
  std::string minMax;
  std::string orderType = typeTostring(type);
  std::vector < double > prices;
  //function call to return a vector of min or max for a product over last 10 time steps
  prices = Range(product, type, range, 9);
  //average calculation from returned vector
  average = std::accumulate(prices.begin(), prices.end(), 0.0) / prices.size();
  if (range == "premin") minMax = "min";
  else if (range == "premax") minMax = "max";
  std::cout << " The average " << product << " " << minMax << " " << orderType << " price over the last 10 timesteps was " <<
    average << std::endl;

}


//function to convert Orderbook type to string.
std::string advisorBot::typeTostring(OrderBookType type) {
  std::string returnString;
  if (type == OrderBookType::ask) returnString = "ask";
  else if (type == OrderBookType::bid) returnString = "bid";
  return returnString;
}


//function call for returning date in dataset
std::string advisorBot::getcurrentTimstep() {

  currentTime = entities[0].timestamp;

  return currentTime;
}


//function call to move to next timestep in dataset
std::string advisorBot::getNextTimestep(std::string time) {
  std::string next_timestamp = "";
  for (OrderBookEntry & e: entities) {
    if (e.timestamp > time) {
      next_timestamp = e.timestamp;
      break;
    }
  }
  if (next_timestamp == "") {
    next_timestamp = entities[0].timestamp;
  }
  return next_timestamp;
}


//function returning vector of timestamps 
std::vector < std::string > advisorBot::getTimestamps(int time) {
  std::map < std::string, int > prodMap;
  int n = 1;

  for (auto & e: entities) {
    if (prodMap.count(e.timestamp) == 0) prodMap.emplace(e.timestamp, 1);

  }

  for (auto & e: prodMap) {
    e.second = n++;
    timestamps.push_back(e.first);

    if (timestamps.size() == (time + 1)) {

      return timestamps;
      break;
    }

  }

  return timestamps;
}


//function or command parsing code for min,max commands
bool advisorBot::verifyInput(std::string range) {
  if (range == "min") std::cout << "advisorBot> Enter min product bid or ask" << std::endl;
  else if (range == "max") std::cout << "advisorBot> Enter max product bid or ask" << std::endl;
  std::string s;
  //function to take user input and writes to string
  getline(std::cin, s);
  char b = ' ';
  //user input string tokeniser function
  k = CSVReader::tokenise(s, b);
  advisorBot::productList();

  //conditional logic to check length of user input
  if (k.size() != 3) {
    std::cout << "Bad input! you typed : " << s << ", please refer to help on commands" << std::endl;
    return false;
  } else if (k.size() == 3) {
    //loop and conditional logic to validating 1st and 3rd strings of user input
    for (int i = 0; i < k.size(); ++i) {
      if (i == 0 && k[i] != range) {
        std::cout << "Bad Input!! you entered : " << s << ", enter " << range << " in your command" << std::endl;
        return false;
      } else if (i == 2 && k[i] != "bid" && k[i] != "ask") {
        std::cout << "Bad Input!! you entered : " << s << ", enter bid or ask in your command" << std::endl;
        return false;
      }
    }
  }
  //loop and conditional logic validating 2nd string of user input against available products.
  for (int j = 0; j < products.size(); ++j) {

    if (k[1] == products[j] && k[0] == range) {
      std::cout << "you typed : " << s << std::endl;
      //function call to range passing user input strings as arguments upon successful validation of user input
      Range(k[1], OrderBookEntry::stringToOrderBookType(k[2]), k[0], 0);
      return true;
    }
    if (k[1].data() != products[j] && j < products.size() - 1) {
      continue;
    } else if (k[1].data() != products[j] && j == products.size() - 1) {
      std::cout << "Bad Input!! you entered : " << s << std::endl;
      return false;
    }
  }

  return true;

}



//function or command parsing code for avg and predict commands
bool advisorBot::verifyInput1(std::string range) {
  std::string s;
  int number;
  //function code to take user input and to write to string
  getline(std::cin, s);
  char b = ' ';
  //tokeniser function breaking user input into 4 strings and wrapping into vector
  k = CSVReader::tokenise(s, b);
  advisorBot::productList();

  //conditional logic checking length of user input
  if (k.size() != 4) {
    std::cout << "Bad input! you typed : " << s << " please refer to help" << std::endl;
    return false;
  } else if (k.size() == 4) {
    for (int i = 0; i < k.size(); ++i) {
      //conditional logic statements checking validity of strings
      if (i == 0 && k[i] != range) {
        std::cout << "Bad Input!! you entered : " << s << " enter " << range << " in your command" << std::endl;
        return false;
        //conditional logic checking validity of strings for avg command
      } else if (k[0] == "avg") {
        //error handling when 3rd string of avg command is neither bid or ask
        if (i == 2 && k[i] != "bid" && k[i] != "ask") {
          std::cout << "Bad Input!! you entered : " << s << " enter bid or ask in your command" << std::endl;
          return false;
          //conditional logic checking for integer part of the avg commands
        } else if (i == 3) {
          //code to convert 4th string into a integer and then to floor and get a absolute value, incase use enters 
          //negative or fractional values
          std::stringstream test;
          test << k[i];
          //check if its integer
          if (test >> number) {
            number = abs(floor(stoi(k[i])));

          } else {
            std::cout << "Bad Input! you entered : " << s << " please enter a number for timesteps in the command";
            return false;
          }
        }

        //code to validate min/max & bid/ask when predict command is used
      } else if (k[0] == "predict") {
        //
        if (i == 1 && k[i] != "min" && k[i] != "max") {
          std::cout << "Bad Input!! you entered : " << s << " enter min or max in your command" << std::endl;
          return false;
        } else if (i == 3 && k[i] != "bid" && k[i] != "ask") {
          std::cout << "Bad Input!! you entered : " << s << " enter bid or ask in your command" << std::endl;
          return false;
        }
      }
    }
     //loop and conditionals to validate the product part of the avg and predict commands
    for (int j = 0; j < products.size(); ++j) {

      //conditional checking product part of average command
       if (k[1] == products[j] && k[0] == "avg") {
        std::cout << "you typed : " << s << std::endl;
        //function call to compute average for the product with strings from the user input as arguments 
        Range1(k[1], OrderBookEntry::stringToOrderBookType(k[2]), k[0], number);
        return true;
        //conditional checking product part of predict command
      } else if (k[2] == products[j] && k[0] == "predict") {
        std::cout << "you typed : " << s << std::endl;
        if (k[1] == "min") k[1] = "premin";
        if (k[1] == "max") k[1] = "premax";
        //function call to compute predicted min/max for the product with strings from the user input as arguments 
        predictNext(k[2], OrderBookEntry::stringToOrderBookType(k[3]), k[1]);
        return true;
        //error handling code when avg command entered by user and has incorrect product string typed in command
      } else if (k[0] == "avg") {
        if (k[1].data() != products[j] && j < products.size() - 1) {
          continue;
        } else if (k[1].data() != products[j] && j == products.size() - 1) {
          std::cout << "Bad Input!! you entered : " << s << std::endl;
          return false;
        }
        //error handling code when predict command entered by user and has incorrect product string typed in command
      } else if (k[0] == "predict") {
        if (k[2].data() != products[j] && j < products.size() - 1) {
          continue;
        } else if (k[2].data() != products[j] && j == products.size() - 1) {
          std::cout << "Bad Input!! you entered : " << s << std::endl;
          return false;

        }
      }
    }
  }
  return true;

}