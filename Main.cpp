#include "Transport.h"
#include <memory>

typedef std::shared_ptr<Transport> T_ptr;

int main()
{
	T_ptr t = std::make_shared<Transport>();
	
	t->setup();
	cout << "passed setup" << endl;
	t->runTransport();
	t->output();
	
	return 0;
}