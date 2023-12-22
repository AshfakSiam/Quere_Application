/*
 * Customer Order Status Query Application
 *
 * This C++ program demonstrates the use of the MySQL++ wrapper for the MySQL C APIs.
 * It functions as a CGI script, connecting to a MySQL database and executing a SELECT SQL statement.
 * The program retrieves and displays the count of orders with a specific status based on form input.
 *
 * Author: K M Ashfak Alam Siam
 *
 * Usage:
 * - The program assumes form input via the POST method.
 * - It expects a parameter named "attr" containing the order status.
 * - Connects to the "cse278_Fall2023" database on localhost with the provided credentials.
 * - Executes a SELECT query on the "Orders" table, counting orders with the specified status.
 * - Displays the count of orders and their status in an HTML table.
 *
 * Note: This program is intended to be part of a web application and designed for CGI execution.
 */

#define MYSQLPP_MYSQL_HEADERS_BURIED
#include <mysql++/mysql++.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <iomanip>
#include "getpost.h"

using std::cout;
using std::cerr;
using std::endl;
void PageHTMLHeader() {
    cout << "Content-type: text/html" << endl << endl;
    cout << "<html> <head> <meta charset=\"UTF-8\">" << endl;
    cout << "<link rel=\"stylesheet\" type=\"text/css\" href=\"path/to/your/styles.css\">" << endl;
    cout << "</head>" << endl;

    cout << "<body>" << endl;
}

int main(int argc, char *argv[]) {
    PageHTMLHeader();
    // create a map object to access to form objects with their names
    std::map<std::string,std::string> Get;
    // call the following methods from getpost.h to initialize the map object.
    // What method (POST or GET) are using in the form, you should call appropriate initialize Method below 
    initializePost(Get);
    // initializeGet(Get);

//     std::string column;
// if (Get.find("attr")!= Get.end()) {
//     column = Get["attr"];
//  }
    std::string status;
    if (Get.find("attr")!= Get.end()) {
        status = Get["attr"];
    }
    // Connect to database with: database, server, userID, password
    mysqlpp::Connection conn; // Exceptions suppressed to keep code simple
    try {
        if(conn.connect("cse278_Fall2023", "localhost", "cse278_Fall2023", "rubrikPenguin")) {

            // Create a query
            mysqlpp::Query query = conn.query();
            query << "SELECT COUNT(*) AS Orders, status FROM Orders  WHERE status ='"
                << status << "' GROUP BY status" <<" ;";

            // Check the query for correctness
            query.parse();

            // Run the query and get the result
            mysqlpp::StoreQueryResult result = query.store();

            // Always check for errors
            if(result.num_rows()>0) {
            // display result in table  
            cout <<"<table border= \"1\" width=\"600\">";
            
            // cout.setf(std::ios::left);
                // Display header
            cout   << "<tr> <th> Orders </th>"
                    << "<th> Status </th> </tr>" << endl;
        

                // Get each row in result set, and print its contents
                for (int i = 0; i < result.num_rows(); ++i) {
                    cout <<"<tr>" <<"<td>"<< result[i]["Orders"] <<"</td>" <<
                            "<td>" << result[i]["status"] << "</td> </tr>" << endl;
                }
                cout <<"</table>"<< endl;
                cout << "</body></html>" << endl;
            } else {
                cout << "<p> Query does not return any records" << query.error() <<"</p>"<< endl;
                cout << "</body></html>" << endl;
            }
            return(0);
        } else {
            cout << "<p> Connection failed: " << conn.error() <<"</p>"<< endl;
            cout << "</body></html>" << endl;
            return(1);
        }
    } catch (std::exception e) {
        cout << "<p>" << e.what() << "</p>" << endl;
        cout << "</body></html>" << endl;
        return 0;
    }
}
 
