#include "Reservation.h"

#include <string>
using namespace std;

Reservation::Reservation():id_("defaultRId"),firstDay_(0),lastDay_(0),userId_("defaultUId"),machineId_("defaultMId"){
    resources_.cores=0;
    resources_.ram=0;
}

Reservation::~Reservation()
{
}