#include "pch.h"
#include "ImprovedBakeryLock.h"


ImprovedBakeryLock::ImprovedBakeryLock() 
{
}

ImprovedBakeryLock::~ImprovedBakeryLock()
{
}

void ImprovedBakeryLock::lock()
{
  if (next_ticket == APPROX_BOUND_VALUE - 1) locked = true;

  while (locked) {
    std::this_thread::yield();
  }

  std::size_t thread_ticket = next_ticket.fetch_add(1, std::memory_order_acquire);
  while (thread_ticket != now_serving) {
    std::this_thread::yield();
  }
}

void ImprovedBakeryLock::unlock()
{
  now_serving++;
  if (now_serving == next_ticket) {
    restrictTickets();
    locked = false;
  }
}

void ImprovedBakeryLock::restrictTickets()
{
  next_ticket = 0;
  now_serving = 0;
}
