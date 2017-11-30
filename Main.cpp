#include "Transport.h"
#include <memory>

typedef std::shared_ptr<Transport> T_ptr;

int main()
{
	cout << "starting!" << endl;
	T_ptr t = std::make_shared<Transport>();
	cout << "good so far" << endl;
	
	
	cout << "sending to setup" << endl;
	t->setup();
	cout << "passed setup" << endl;
	t->runTransport();
	t->output();
	
	return 0;
}