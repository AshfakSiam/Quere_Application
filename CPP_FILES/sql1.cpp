// practicing connect to database and retrieve the airport data
// Examples 
// 1. using fixed query for running only IST code
// 2. getting code from the user
// 3. getting starting code from the user
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
  
// getting input for example 2 and 3
  // std::string code;
  // std::cout << "Enter an airport code:";
  // std::cin >> code;

//   query << "SELECT name, code, city, country "
//   << "FROM Airports "
  // example 1
 // << "WHERE code = 'IST'";
  // example 2
 // << "WHERE code = '" << code << "';";
  // example 3
//   <<"WHERE code LIKE '" << code << "%';";
    
    



  query.parse();
  mysqlpp::StoreQueryResult result = query.store();
  // print the header of table
  std::cout << std::left <<std::setw(40)<< "Name" <<
  std::setw(5)<< "Code" << std::setw(20)<<"City" <<
  std::setw(20)<<"Country" << std::endl;
  std::cout <<
  "-------------------------------------------------------------------------------"
  <<std::endl;
  // print the result
  for (const auto & row : result) {
    std::cout <<std::left<<std::setw(40)<< row[0].c_str() 
    << std::setw(5) << row[1] 
    << std::setw(20) << row[2].c_str()
    <<std::setw(20)<<row[3].c_str() << std::endl;
  } // done printing results
  return 0;
}
