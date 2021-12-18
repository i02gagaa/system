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

void System::showUsers(const string &userId){
  clearScreen("Lista de Usuarios");
  User currentUser = findUser(userId);//comprobamos que el usuario que pide mostrar los datos existe
  if (currentUser.getUserType_()!=2) {//y nos aseguramos de que es administrador de tipo 2
    std::cout << "Error,solo los usuarios de tipo 2 pueden mostrar los datos de los usuarios" << '\n';
    exit(EXIT_FAILURE);
  }
  list<User>::iterator it;
  for (it = users_.begin(); it != users_.end(); it++) {
    cout << "ID del usuario: " << users_.getId_() << '\n';
    cout << "Tipo de Usuario: " << users_.getUserType_() << '\n';
    cout << "Nombre del Usuario: " << users_.getName_() << '\n';
    cout << "Login del Usuario: " << users_.getLogin_() << '\n';
    cout << "Contrasena del Usuario: " << users_.getPassword_() << '\n';
    cout << "ID del limite del Usuario: " << users_.getLimitId_() << '\n';
  }

}//Debe mostrar por pantalla la lista de usuarios con login, tipo de usuario, password, id, limitId y nombre

bool System::addLimit(const string &userId){cout<<"No Implementada\n";return false;}
bool System::deleteLimit(const string &userId){cout<<"No Implementada\n"; return false;}//Debe mostrar por pantalla la lista de limites (Id, rescursos maximos y dias maximos), solicitar al usuario que elija uno y borrarlo de limits_
void System::showLimits(const string &userId) {cout<<"No Implementada\n";}
