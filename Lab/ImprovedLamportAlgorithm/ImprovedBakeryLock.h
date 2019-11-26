#pragma once
#include "../Lamport_algorithm/FixnumLock.h"

#include <atomic>
#include <vector>
#include <map>
#include <thread>
#include <mutex>

class ImprovedBakeryLock : public FixnumLock{

private:
  std::atomic<size_t> next_ticket = 0;
  std::atomic<size_t> now_serving = 0;
  std::atomic<bool> locked = false;
  const size_t APPROX_BOUND_VALUE = 100;

public:
  ImprovedBakeryLock();
  virtual ~ImprovedBakeryLock();

  virtual void lock() override;
  virtual void unlock() override;
  virtual bool tryLock() override;

private:
  void restrictTickets();
};

