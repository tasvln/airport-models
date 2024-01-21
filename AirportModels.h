/*
  Name: Temitope Oladimeji Samuel Adebayo
  Date: 2023-09-24

  I have done all the coding by myself and only copied the code that my professor provided 
  to complete my workshops and assignments.
*/

#ifndef SDDS_AIRPORTMODELS_H
#define SDDS_AIRPORTMODELS_H

#include <iostream>

namespace sdds {
  class Airport {
    std::string m_code;
    std::string m_name;
    std::string m_city;
    std::string m_state;
    std::string m_country;
    double m_latitude;
    double m_longitude;
  public:
    // constructors 
    Airport();
    Airport (const std::string& code, const std::string& name, const std::string& city, 
            const std::string& state, const std::string& country, double latitude, 
            double longitude);

    // query functions
    std::string getCode() const { return m_code; }
    std::string getName() const { return m_name; }
    std::string getCity() const { return m_city; }
    std::string getState() const { return m_state; }
    std::string getCountry() const { return m_country; }
    double getLatitude() const { return m_latitude; }
    double getLongitude() const { return m_longitude; }
    
    // modifier functions
    void setAll(const std::string& code, const std::string& name, const std::string& city, 
            const std::string& state, const std::string& country, double latitude, 
            double longitude);

    // display function to work with the overloaded insertion operator
    void display(std::ostream& os) const;
  };

  class AirportLog {
    Airport* m_airports;
    size_t m_noOfAirports;
  public:
    // constructors and destructor
    AirportLog();

    AirportLog(const char* filename);

    // copy constructor and copy assignment operator
    AirportLog(const AirportLog& src);
    AirportLog& operator=(const AirportLog& src);

    // move constructor and move assignment operator
    AirportLog(AirportLog&& src);
    AirportLog& operator=(AirportLog&& src);

    ~AirportLog();

    // addAirport: modifier that receives a constant reference to an Airport object and returns nothing
    void addAirport(const Airport& src);

    // findAirport: query that receives two constant C-style strings representing the state and country and returns an AirportLog object.
    AirportLog findAirport(const char* state, const char* country);

    // operator[](size_t): a query that will return the Airport in the dynamic array at the index provided
    Airport operator[](size_t index) const;

    // operator size_t(): a casting operator that will convert the current object to a size_t value.
    operator size_t() const;
  };

  std::ostream& operator<<(std::ostream& os, const Airport& src);
}

#endif