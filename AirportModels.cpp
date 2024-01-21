/*
  Name: Temitope Oladimeji Samuel Adebayo
  Date: 2023-09-24

  I have done all the coding by myself and only copied the code that my professor provided 
  to complete my workshops and assignments.
*/

#include <iomanip>
#include <fstream>
#include <cstring>
#include "AirportModels.h"

using namespace std;

namespace sdds {
  // Airport class implementation

  void Airport::setAll(const string& code, const string& name, const string& city, 
            const string& state, const string& country, double latitude, 
            double longitude) {
    this->m_code = code;
    this->m_name = name;
    this->m_city = city;
    this->m_state = state;
    this->m_country = country;
    this->m_latitude = latitude;
    this->m_longitude = longitude;
  }

  Airport::Airport() {
    setAll("", "", "", "", "", 0.0, 0.0);
  }

  Airport::Airport (const string& code, const string& name, const string& city, 
            const string& state, const string& country, double latitude, 
            double longitude) {
    setAll(code, name, city, state, country, latitude, longitude);
  }

  void Airport::display(std::ostream& os) const {
    // check if the object is empty
    if (m_code[0] == '\0') {
      os << "Empty Airport";
    } else {
      os << setw(20) << setfill('.') << right << "Airport Code" << " : " << left << setfill('.') << setw(30) << m_code << std::endl;
      os << setw(20) << setfill('.') << right << "Airport Name" << " : " << left << setfill('.') << setw(30) << m_name << std::endl;
      os << setw(20) << setfill('.') << right << "City" << " : " << left << setfill('.') << setw(30) << m_city << std::endl;
      os << setw(20) << setfill('.') << right << "State" << " : " << left << setfill('.') << setw(30) << m_state << std::endl;
      os << setw(20) << setfill('.') << right << "Country" << " : " << left << setfill('.') << setw(30) << m_country << std::endl;
      os << setw(20) << setfill('.') << right << "Latitude" << " : " << left << setfill('.') << setw(30) << m_latitude << std::endl;
      os << setw(20) << setfill('.') << right << "Longitude" << " : " << left << setfill('.') << setw(30) << m_longitude << std::endl;
    }
  }

  std::ostream& operator<<(std::ostream& os, const Airport& src) {
    src.display(os);
    return os;
  }

  // AirportLog class implementation

  AirportLog::AirportLog() {
    m_airports = nullptr;
    m_noOfAirports = 0;
  }

  AirportLog::AirportLog(const char* filename) {
    ifstream file(filename);

    int num = 0;
    string tempCode = "";
    string tempName = "";
    string tempCity = "";
    string tempState = "";
    string tempCountry = "";
    double tempLatitude = 0.0;
    double tempLongitude = 0.0;

    // check if the file is open
    if (file.is_open()) {
      string line;

      // get the number of lines in the file
      while (getline(file, line) && !file.eof()) {
        num++;
      }

      m_noOfAirports = num - 1;
      m_airports = new Airport[m_noOfAirports];

      file.clear();
      file.seekg(0, ios::beg);

      // clear the first line
      getline(file, line);

      for (size_t i = 0; i < m_noOfAirports; i++) {
        getline(file, tempCode, ',');
        getline(file, tempName, ',');
        getline(file, tempCity, ',');
        getline(file, tempState, ',');
        getline(file, tempCountry, ',');
        file >> tempLatitude;
        file.ignore();
        file >> tempLongitude;
        file.ignore();

        m_airports[i].setAll(tempCode, tempName, tempCity, tempState, tempCountry, tempLatitude, tempLongitude);
      }

      // close the file
      file.close();
    }
  }

  AirportLog::AirportLog(const AirportLog& src) {
      m_airports = nullptr;
      *this = src;
  }

  AirportLog& AirportLog::operator=(const AirportLog& src) {
      if (this != &src) {
          delete[] m_airports;

          m_noOfAirports = src.m_noOfAirports;

          if (src.m_airports != nullptr) {
            m_airports = new Airport[m_noOfAirports];

            for (size_t i = 0; i < m_noOfAirports; i++) {
              m_airports[i] = src.m_airports[i];
            }
          } else {
            m_airports = nullptr;
          }
      }
      return *this;
  }

  AirportLog::AirportLog(AirportLog&& src) {
    m_airports = nullptr;
    *this = std::move(src);
  }

  AirportLog& AirportLog::operator=(AirportLog&& src) {
    if (this != &src) {
      delete[] m_airports;

      m_noOfAirports = src.m_noOfAirports;
      m_airports = src.m_airports;

      src.m_noOfAirports = 0;
      src.m_airports = nullptr;
    }
    return *this;
  }

  void AirportLog::addAirport(const Airport& src) {
    Airport* temp = nullptr;

    temp = new Airport[m_noOfAirports + 1];

    for (size_t i = 0; i < m_noOfAirports; i++) {
      temp[i] = m_airports[i];
    }

    temp[m_noOfAirports] = src;

    delete[] m_airports;
    m_airports = temp;
    m_noOfAirports++;

    temp = nullptr;
  }

  

  AirportLog AirportLog::findAirport(const char* state, const char* country) {
    AirportLog temp;

    // create a temporary state and country
    char* tempState = nullptr;
    char* tempCountry = nullptr;

    for (size_t i = 0; i < m_noOfAirports; i++) {
      tempState = new char[m_airports[i].getState().length() + 1];
      strcpy(tempState, m_airports[i].getState().c_str());

      tempCountry = new char[m_airports[i].getCountry().length() + 1];
      strcpy(tempCountry, m_airports[i].getCountry().c_str());

      if (strcmp(tempState, state) == 0 && strcmp(tempCountry, country) == 0) {
        temp.addAirport(m_airports[i]);
      }

      // delete the temporary state and country
      delete[] tempState;
      tempState = nullptr;

      delete[] tempCountry;
      tempCountry = nullptr;
    }

    return temp;
  }

  Airport AirportLog::operator[](size_t index) const {
    // check if the index is greater than the number of airports
    if (index < m_noOfAirports) {
      return m_airports[index];
    } else {
      // create an empty airport
      Airport empty;

      return empty;
    }
  }

  AirportLog::operator size_t() const {
    return m_noOfAirports;
  }

  AirportLog::~AirportLog() {
    delete[] m_airports;
    m_airports = nullptr;
  }
}