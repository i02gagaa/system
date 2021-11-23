#include "System.h"
#include "Limit.h"
#include "Machine.h"
#include "Reservation.h"
#include "User.h"



#include <string>
#include <list>
#include <iostream>
using namespace std;

//Constructor
System::System(){cout<<"Construye\n";cout<<"No Implementada\n";}


//Destructor
System::~System(){cout<<"Destruye\n";cout<<"No Implementada\n";}


User System::authenticateUser(){cout<<"No Implementada\n";User userNoImplementado; userNoImplementado.setId_("noImplementado"); return userNoImplementado;}
void System::showUsers(const string &userId){cout<<"No Implementada\n";}//Debe mostrar por pantalla la lista de usuarios con login, tipo de usuario, password, id, limitId y nombre
bool System::addLimit(const string &userId){cout<<"No Implementada\n";return false;}
bool System::deleteLimit(const string &userId){cout<<"No Implementada\n"; return false;}//Debe mostrar por pantalla la lista de limites (Id, rescursos maximos y dias maximos), solicitar al usuario que elija uno y borrarlo de limits_
void System::showLimits(const string &userId) {cout<<"No Implementada\n";}
