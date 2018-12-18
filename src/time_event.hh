#include "event.hh"

namespace eve
{

class time_event : public event
{

  public:
    struct timeval timeout;

  public:
    time_event(event_base *base);
    ~time_event() {}

    void set_timer(int sec, int usec);

    void add();
    void del();
};

} // namespace eve
