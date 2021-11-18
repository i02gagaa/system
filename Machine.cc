#include "Machine.h"

#include <string>
using namespace std;

Machine::Machine():id_("defaultMId"){
    resources_.cores=0;
    resources_.ram=0;
}

Machine::~Machine()
{
}
