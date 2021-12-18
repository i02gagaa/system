#include "System.h"
#include "Limit.h"
#include "Machine.h"
#include "Reservation.h"
#include "User.h"



#include <string>
#include <list>
#include <iostream>
using namespace std;


bool System::addUser(const string &userId){
  clearScreen("Creacion de Usuarios");
  User currentUser = findUser(userId);
  if (currentUser.getUserType_()!=2) {
    std::cout << "Error,solo los usuarios de tipo 2 pueden crear nuevos usuarios" << '\n';
    exit(EXIT_FAILURE);
  }
  User newUser;
  bool isInputOk;

  //ID
  //Vamos a establecer el id del usuario para esto vemos si la lista de usuarios esta vacia, si es asi, su id sera u1, si no, tomaremos el identificador de la ultima reserva de la lista y le sumaremos una unidad a su parte de digitos
  string newusId="u";
  int newusIdNumber=1;
  if(users_.empty()){newusId+=to_string(newusIdNumber);
  }else{
      string previousId=(users_.back().getId_());
      newusIdNumber=stoi(previousId.substr(1));
      newusIdNumber++;
      newusId+=to_string(newusIdNumber);
  }
  newUser.setId_(newusId);
  clearScreen("Creacion de Usuarios");

  int userT;
//Tipo de usuario
  cout<<"\n->Introduzca el tipo de nuevo usuario";
  do{
      isInputOk = true;
      cin>>userT;
      if( (userT<0) || (userT>2) ){
          cout<<"\nTipo de usuario incorrecto, vuelva a introducirlo: ";
          isInputOk=false;
        }
  }while(!isInputOk);
  newUser.setUserType_(userT);
  clearScreen("Creacion de Usuarios");

//Nombre del usuario
  string name;
  cout<<"\n->Introduzca el nombre del nuevo Usuario:";
  cin >> name;
  list <User>::iterator i = users_.begin();
  do{//comprueba que el nombre no este repetido
    isInputOk = true;
    while (i!=users_.end()){
        if((i->getName_())==name){
        isInputOk=false;
        }
    }
  }while(!isInputOk);
  newUser.setName_(name);
  clearScreen("Creacion de Usuarios");

  //login del usuario
  string login;
  cout<<"\n->Introduzca el login del nuevo Usuario:";
  cin >> login;
  list <User>::iterator f = users_.begin();
  do{//comprueba que el nombre no este repetido
      isInputOk = true;
      while (f!=users_.end()){
          if((f->getLogin_())==login){
          isInputOk=false;
          }
      }
  }while(!isInputOk);
  newUser.setLogin_(login);
  clearScreen("Creacion de Usuarios");

  //contrasena del usuario
  string contrasena;
  cout<<"\n->Introduzca la contrasena del nuevo Usuario:";
  cin >> contrasena;
  newUser.setPassword_(contrasena);
  clearScreen("Creacion de Usuarios");

  //Vamos a establecer el id del limite del usuario para esto vemos si la lista de limites esta vacia, si es asi, su id sera l1, si no, tomaremos el identificador de la ultima reserva de la lista y le sumaremos una unidad a su parte de digitos
  string newLId="l";
  int newLIdNumber=1;
  if(users_.empty()){newLId+=to_string(newLIdNumber);
  }else{
      string previoLId=(users_.back().getId_());
      newLIdNumber=stoi(previousId.substr(1));
      newLIdNumber++;
      newLId+=to_string(newusIdNumber);
  }
  newUser.limitId_(newLId);
  clearScreen("Creacion de Usuarios");

  //Preguntamos por la confirmacion del usuario
  int inputInt;
  cout<<"\n--->Datos del nuevo usuario:";
  cout<<"\nID: "<<newUser.getId_()<<"\nTipo de Usuario: "<<newUser.getUserType_()<<"\nNombre del Usuario: "<<newUser.getName_()<<"\nLogin del Usuario: "<<newUser.getLogin_()<<"\nContrasena del Usuario: "<<newUser.getPassword_()<<"\nID de limite del Usuario: "<<newUser.getLimitId_();
  cout<<"\nEsta satisfecho con la reserva?\n->Introduzca 1 para confirmar, 0 para cancelar:";
  cin>>inputInt;
  if (inputInt==1)
  {
      users_.push_back(newUser);
      cout<<"\nUsuario Confirmado";
      return true;
  } else{
      cout<<"\nUsuario Cancelado";
      return false;
  }
}

bool System::deleteUser(const string &userId){
  if(users_.empty()){//la lista esta vacia
    cout << "Error, la lista esta vacia" << '\n';
    return false;
  }
  list<User>::iterator it;
  list<Reservation>::iterator ir;
  for (it = users_.begin(); it != users_.end(); it++) {

    if(it->getId_()==userId){
      for (ir = reservations_.begin(); ir != reservations_.end(); ir++) {
        if(ir->getUserId_()==userId){
          if( deleteReservation( ir->getId_() )==false ){//comprobamos si se pueden borrar las reservas y lo hacemos
            cout << "Error,no se ha podido eliminar las reservas del usuario" << '\n';
            return false;
          }
        }
      }
      //si el usuario no tuviera reservas se pasaria directamente a eliminar sus datos
      users_.erase(it);//borramos el usuario
      return true;
    }
  }
  return false;//si no encuentra el usuario a borrar,devuelve false
}//Debe borrar las reservas a su nombre con deleteReservation(reservationId) antes de borrar el usuario

bool System::modifyUser(const string &userId){
  clearScreen("Modificacion de Usuarios");
  User currentUser = findUser(userId);
  if (currentUser.getUserType_()!=2) {
    std::cout << "Error,solo los usuarios de tipo 2 pueden modificar usuarios" << '\n';
    exit(EXIT_FAILURE);
  }
  showUsers(userId);
  cout << "Escriba el ID del usuario que desea modificar" << '\n';
  string userModID;
  cin >> userModID;

  int option;
  cout << "¿Se desea modificar o borrar al usuario?" << '\n';
  cout << "1-Modificar al usuario" << '\n';
  cout << "2-Borrar al usuario" << '\n';
  cin >> option;
  if(option==1){//borramos y creamos usuario para modificarlo con el mismo id

    if(deleteUser(userModID)==false){
      return false;
    }
    if(addUser(userId)==false){
      return false;
    }

    return true;
  }

  else if(option==2){
    if(deleteUser(userModID)==false){
      return false;
    }
    
    return true;
  }

  else{
    cout << "Error,Debe escoger entre la opcion 1 o la opcion 2" << '\n';
    return false;
  }
}

bool System::addMachine(const string &userId){cout<<"No Implementada\n";return false;}
bool System::deleteMachine(const string &userId){cout<<"No Implementada\n";return false;}//Debe borrar las reservas a su nombre con deleteReservation(reservationId) antes de borrar el usuario
bool System::modifyMachine(const string &userId){cout<<"No Implementada\n";return false;}
