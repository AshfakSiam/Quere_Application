/*
 * A Customer Query Application
 *
 * This C++ program connects to a MySQL database using the MySQL++ wrapper.
 * It handles a web form submission, extracts a country name, and queries the database
 * to retrieve and display customer information for the specified country.
 *
 * Author: K M Ashfak Alam Siam
 *
 * Usage:
 * - The program assumes form input via the GET method.
 * - It expects a parameter named "country_text" containing the country name.
 * - Connects to the "cse278_Fall2023" database on localhost with the provided credentials.
 * - Executes a SELECT query on the "Customers" table based on the provided country.
 * - Displays the retrieved customer information in an HTML table.
 *
 * Note: The program is designed to be part of a CGI script for web applications.
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
    cout << "<table> " <<
        "<tr>" <<
            "<td>" <<
                "<p class=\"title\">A Customer Query Application</p>" <<
                "<p class=\"nav-links\">" <<
                "<a href=\"http://os1.csi.miamioh.edu/~siamk/CustomerQueryApplicationLinks.html\"> QueryPage </a>" <<
                " | <a href=\"http://os1.csi.miamioh.edu/~siamk/fromCustomers.html\"> GoBack </a> </p>" <<
            "</td>" <<
        "</tr>" <<
    "</table>" << endl;
}

int main(int argc, char *argv[]) {

    PageHTMLHeader();
    // create a map object to access to form objects with their names depends on the POST or GET request from the html form
    std::map<std::string,std::string> Get;
    // call the following methods from getpost.h to initialize the map object.
    //initializePost(Get);
    initializeGet(Get);

    std::string country;
    if (Get.find("country_text")!=Get.end()) {
        
        country = Get["country_text"];
        cout << "<h2> Here is  the result for customers from " << country << "</h2>" << endl;
    } else {
        cout << "<p>Fill out the from and press submit"<<endl;
    }
    // Connect to database with: database, server, userID, password
    mysqlpp::Connection conn; // Exceptions suppressed to keep code simple
    if(conn.connect("cse278_Fall2023", "localhost", "cse278_Fall2023", "rubrikPenguin")) {

        // Create a query
        mysqlpp::Query query = conn.query();
        query << "SELECT customerName, city, state, country FROM Customers WHERE country = '" << country <<"' ORDER BY customerName;";

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
           cout   << "<th> Customer Name </th>"
                  << "<th> City </th>"
                  << "<th> State </th>"
                  << "<th> Country </th> </tr>" << endl;
	

            // Get each row in result set, and print its contents
            for (int i = 0; i < result.num_rows(); ++i) {
                cout <<"<tr>" <<"<td>"<< result[i]["customerName"] <<"</td>" <<
                        "<td>" << result[i]["city"] <<"</td>" <<
                        "<td>" <<  result[i]["state"] <<"</td>" <<
                        "<td>" << result[i]["country"] << "</td> </tr>" << endl;
            }
	        cout <<"</table>"<<endl;
            cout << "</body></html>" << endl;
        } else {
            cout << "<p> Query does not return any records. Enter a valid country name" << query.error() <<"</p>"<< endl;
            cout << "</body></html>" << endl;
        }
        return(0);
    } else {
        cout << "<p> Connection failed: " << conn.error() <<"</p>"<< endl;
        cout << "</body></html>" << endl;
        return(1);
    }
}
 
