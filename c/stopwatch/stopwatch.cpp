#include <chrono>

struct Stopwatch {
  using ClockType    = std::chrono::high_resolution_clock;
  using Milliseconds = std::chrono::duration<double, std::milli>;
  using Seconds      = std::chrono::duration<double>;

  bool                  isStopped = false;
  ClockType::time_point timePoint = ClockType::now();
  ClockType::duration   counter   = ClockType::duration::zero();

  void start() {
    this->isStopped = false;
    this->timePoint = ClockType::now();
    this->counter   = ClockType::duration::zero();
  }

  void stop() {
    const auto now = ClockType::now();
    this->counter += (now - this->timePoint);
    this->isStopped = true;
  }

  void resume() {
    if(!this->isStopped) {
      return;
    }

    const auto now = ClockType::now();
    this->timePoint = now;
    this->isStopped = false;
  }

  double milliseconds() const {
    if(this->isStopped) {
      return Milliseconds(this->counter).count();
    }

    return Milliseconds(ClockType::now() - this->timePoint + this->counter).count();
  }

  double seconds() const {
    if(this->isStopped) {
      return Seconds(this->counter).count();
    }
  
    return Seconds(ClockType::now() - this->timePoint + this->counter).count();
  }
};

