/*
  Name: Temitope Oladimeji Samuel Adebayo
  Date: 2023-09-24

  I have done all the coding by myself and only copied the code that my professor provided 
  to complete my workshops and assignments.
*/

#include "Timer.h" 

using namespace std; 
using namespace chrono;

namespace sdds
{
  void Timer::start()
  {
    m_startTime = steady_clock::now();
  }

  long long Timer::stop()
  {
    m_endTime = steady_clock::now();
    auto duration = duration_cast<nanoseconds>(m_endTime - m_startTime);

    return duration.count();
  }
}