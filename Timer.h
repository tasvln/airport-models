/*
  Name: Temitope Oladimeji Samuel Adebayo
  Date: 2023-09-24

  I have done all the coding by myself and only copied the code that my professor provided 
  to complete my workshops and assignments.
*/

#ifndef SDDS_TIMER_H
#define SDDS_TIMER_H

#include <iostream>
#include <chrono>

namespace sdds {
  class Timer {
    std::chrono::steady_clock::time_point m_startTime; 
    std::chrono::steady_clock::time_point m_endTime;

    public: 
      void start();
      long long stop();
  };
}

#endif