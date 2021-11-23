#include "System.h"
#include "Limit.h"
#include "Machine.h"
#include "Reservation.h"
#include "User.h"



#include <string>
#include <list>
#include <iostream>
using namespace std;


bool System::addUser(const string &userId){cout<<"No Implementada\n";return false;}
bool System::deleteUser(const string &userId){cout<<"No Implementada\n";return false;}//Debe borrar las reservas a su nombre con deleteReservation(reservationId) antes de borrar el usuario
bool System::modifyUser(const string &userId){cout<<"No Implementada\n";return false;}
bool System::addMachine(const string &userId){cout<<"No Implementada\n";return false;}
bool System::deleteMachine(const string &userId){cout<<"No Implementada\n";return false;}//Debe borrar las reservas a su nombre con deleteReservation(reservationId) antes de borrar el usuario
bool System::modifyMachine(const string &userId){cout<<"No Implementada\n";return false;}
