#pragma once
#include "../FixnumLock/Lockable.h"

#include <atomic>
#include <vector>
#include <map>
#include <thread>
#include <mutex>

class ImprovedBakeryLock : public Lockable<100>{

private:
  std::atomic<std::size_t> next_ticket = 0;
  std::atomic<std::size_t> now_serving = 0;
  std::atomic<bool> locked = false;
  const std::size_t APPROX_BOUND_VALUE = 100;

public:
  ImprovedBakeryLock();
  virtual ~ImprovedBakeryLock();

  virtual void lock() override;
  virtual void unlock() override;

private:
  void restrictTickets();
};

