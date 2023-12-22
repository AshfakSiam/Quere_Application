#define MYSQLPP_MYSQL_HEADERS_BURIED
#include <mysql++/mysql++.h>
#include <string>
#include <iostream>

// %0 %1 %2
int main(int argc, char* argv[]) {
  // Connect to database with: database, server, userID, password
    mysqlpp::Connection myDB("cse278_Fall2023", "localhost", "cse278_Fall2023",
    "rubrikPenguin");
  // Create a query
  mysqlpp::Query query = myDB.query();
  
  std::string country;
  std::cout << "Enter a country name:";
  std::cin >> country;

query << "SELECT country , COUNT(*) "
      << " FROM Customers "
      << "WHERE country = '"<< country << "'"
      << " ORDER BY customerName DESC";

         
  query.parse();
  mysqlpp::StoreQueryResult result = query.store();
  // print the header of table
  std::cout << std::left <<std::setw(40)<< "Country" <<
  std::setw(5)<< "Total Number " << std::endl;
  std::cout <<
  "-------------------------------------------------------------------------------"
  <<std::endl;
  // print the result
  for (const auto & row : result) {
    std::cout <<std::left<<std::setw(40)<< row[0].c_str() 
    << std::setw(5) << row[1] << std::endl;
  } // done printing results
  return 0;
}
