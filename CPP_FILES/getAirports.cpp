/*
 * This program shows how to use the MySQL++ wrapper for the MySQL C APIs.
 * It connects to a MySQL database, executes a SELECT SQL statement and displays the results.
 * Author: Z.Sevkli
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

void PageHTMLHeader(){
    cout << "Content-type: text/html" << endl << endl;
    cout << "<html> <head> <meta charset=\"UTF-8\">" <<endl;
    cout << "<style> body { " <<
            "font-family: \"Arial\", sans-serif;" <<
            "background-color: #6fa8dc;" <<
            " max-width: 600pt;" <<
            " padding: 72pt;} " <<
        "table {" <<
            "margin: 0 auto;" << 
            "background-color: #ff9900; " <<
            "border-spacing: 0;" <<
            "border-collapse: collapse;" <<
            "width: 100%; " <<
       " } .title { color: #2832c0; text-align:center; font-size: 26pt; font-weight: 700; margin-bottom: 3pt;}" <<
       ".nav-links {color: #0838e4; font-weight: 700; text-decoration: none; text-align: center;}" <<
       "</style></head>" << endl;

    
    cout << "<body>" << endl;
    cout << "<table> " <<
        "<tr>" <<
            "<td>" <<
                "<p class=\"title\">An Airport Query Application</p>" <<
                "<p class=\"nav-links\">" << 
                "<a href=\"http://os1.csi.miamioh.edu/~sevkliaz/AirportQueryApplicationLinks.html\"> QueryPage </a>" <<
                " | <a href=\"http://os1.csi.miamioh.edu/~sevkliaz/formAirport.html\"> GoBack </a> </p>" <<

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
        cout << "<h2> Here is  the result for country = " << country << "</h2>" << endl;
    } else {
        cout << "<p>Fill out the from and press submit"<<endl;
    }
    // Connect to database with: database, server, userID, password
    mysqlpp::Connection conn; // Exceptions suppressed to keep code simple
    if(conn.connect("cse278_Fall2023", "localhost", "cse278_Fall2023", "rubrikPenguin")) {

        // Create a query
        mysqlpp::Query query = conn.query();
        query << "SELECT name, code, city, country FROM Airports WHERE country LIKE \"%" << country <<"%\";";

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
           cout   << "<th> Name </th>"
                  << "<th> Code </th>"
                  << "<th> City </th>"
                  << "<th> Country </th> </tr>" << endl;
	

            // Get each row in result set, and print its contents
            for (int i = 0; i < result.num_rows(); ++i) {
                cout <<"<tr>" <<"<td>"<< result[i]["name"] <<"</td>" <<
                        "<td>" << result[i]["code"] <<"</td>" <<
                        "<td>" <<  result[i]["city"] <<"</td>" <<
                        "<td>" << result[i]["country"] << "</td> </tr>" << endl;
            }
	        cout <<"</table>"<<endl;
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
}
 
