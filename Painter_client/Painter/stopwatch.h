#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <chrono>

class StopWatch
{
public:
   typedef std::chrono::steady_clock clock;
   typedef std::chrono::microseconds microseconds;
   typedef std::chrono::milliseconds milliseconds;
   typedef std::chrono::seconds seconds;

   StopWatch(): mStart(clock::now())
   {
   };
   StopWatch(const StopWatch& other): mStart(other.mStart) { }
   StopWatch& operator=(const StopWatch& rhs)
   {
      mStart = rhs.mStart;
      return *this;
   }

   uint64_t ElapsedUs() const
   {
      return std::chrono::duration_cast<microseconds>(clock::now() - mStart).count();
   }
   uint64_t ElapsedMs() const
   {
      return std::chrono::duration_cast<milliseconds>(clock::now() - mStart).count();
   }
   uint64_t ElapsedSec() const
   {
      return std::chrono::duration_cast<seconds>(clock::now() - mStart).count();
   }

   std::chrono::steady_clock::time_point Restart()
   {
      mStart = clock::now();
      return mStart;
   }

private:
   clock::time_point mStart;
};

#endif // STOPWATCH_H
