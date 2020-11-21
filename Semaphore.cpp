#include "Semaphore.h"
/*! \class Semaphore
  \brief A Semaphore Implementation
  Uses C++11 features such as mutex and condition variables to implement Semaphore
*/
/*! \fn Wait
  \brief Tell the current thread to claim control of a resource, if not available, the thread waits.
  \brief As Wait() decrements m_uiCount, if m_uiCount becomes negative, the process that caused that to happen is blocked.
  \brief A process that is blocked is added to the queue and waits for rescources to become available.
*/
void Semaphore::Wait()
{
      std::unique_lock< std::mutex > lock(m_mutex);
      m_condition.wait(lock,[&]()->bool{ return m_uiCount>0; });
      --m_uiCount;
}
template< typename R,typename P >
bool Semaphore::Wait(const std::chrono::duration<R,P>& crRelTime)
{
      std::unique_lock< std::mutex > lock(m_mutex);
      if (!m_condition.wait_for(lock,crRelTime,[&]()->bool{ return m_uiCount>0; })){
 return false;
      }
      --m_uiCount;
      return true;
}
/*! \fn Signal
  \brief A Process calls this function when it is done using a resource and other processes may use it.
  \brief The Signal() causes m_uiCount to increment.
  \brief If after increment m_uiCount is less than or equal to zero, A process on the queue is given the right to run.
*/
void Semaphore::Signal()
{
      std::unique_lock< std::mutex > lock(m_mutex);
      ++m_uiCount;
      m_condition.notify_one();
}
