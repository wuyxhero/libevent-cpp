#include <time_event.hh>
#include <select_base.hh>
#include <iostream>

using namespace std;
using namespace eve;

void timeout_cb(short event, void *arg)
{
	time_event *timeout = (time_event *)arg;
	int newtime = time(NULL);

	cout << __func__ << ": called at " << newtime << endl;

	timeout->set_timer(3);
	timeout->add();
}

int main(int argc, char **argv)
{
	select_base base;
	base.priority_init(1);

	time_event timeout(&base);
	timeout.set_callback(timeout_cb);
	timeout.set_timer(5);
	timeout.add();

	base.loop(0);
}