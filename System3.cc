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

  //Vamos a establecer el id del usuario para esto vemos si la lista de usuarios esta vacia, si es asi, su id sera u1, si no, lo escribimos nosotros
  string newusId="u";
  int newusIdNumber=1;
  if(users_.empty()){newusId+=to_string(newusIdNumber);}
  else{
      cout << "Introduzca el numero del identificador:" << '\n';
      cin>>newusIdNumber;
      newusId+=to_string(newusIdNumber);
  }
  list<User>::iterator r;
  for (r = users_.begin(); r != users_.end(); r++) {
    if(r->getId_()==newusId){
      cout << "Error,ese usuario ya existe" << '\n';
      exit(EXIT_FAILURE);
    }
  }
  newUser.setId_(newusId);
  clearScreen("Creacion de Usuarios");

  int userT;
//Tipo de usuario
  cout<<"\n->Introduzca el tipo de nuevo usuario:";
  do{
      isInputOk = true;
      cin>>userT;
      if( (userT<0) || (userT>2) ){
          cout<<"\nTipo de usuario incorrecto, vuelva a introducirlo:";
          isInputOk=false;
        }
  }while(!isInputOk);
  newUser.setUserType_(userT);
  clearScreen("Creacion de Usuarios");

  //Nombre del usuario
  string name;
  cout<<"\n->Introduzca el nombre del nuevo Usuario:";
  cin >> name;
  newUser.setName_(name);
  clearScreen("Creacion de Usuarios");

  //login del usuario
  string login;
  cout<<"\n->Introduzca el login del nuevo Usuario:";
  list <User>::iterator f;
  do{//comprueba que el login no este repetido
      isInputOk = true;
      cin >> login;
      for (f = users_.begin(); f != users_.end(); f++) {
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
  list <User>::iterator i;
  do{//comprueba que el login no este repetido
      isInputOk = true;
      cin >> contrasena;
      for (i = users_.begin(); i != users_.end(); i++) {
        if((i->getPassword_())==contrasena){
          cout << "Error,esa contrasena ya existe" << '\n';
          isInputOk=false;
        }
      }
  }while(!isInputOk);
  newUser.setPassword_(contrasena);
  clearScreen("Creacion de Usuarios");

  //Vamos a establecer el id del limite del usuario para esto vemos si la lista de limites esta vacia, si es asi, su id sera l1, si no, tomaremos el identificador de la ultima reserva de la lista y le sumaremos una unidad a su parte de digitos
  string newLId="l";
  int newLIdNumber=1;
  if(users_.empty()){newLId+=to_string(newLIdNumber);
  }else{
      string previoLId=(users_.back().getId_());
      newLIdNumber=stoi(previoLId.substr(1));
      newLIdNumber++;
      newLId+=to_string(newusIdNumber);
  }
  newUser.setLimitId_(newLId);
  clearScreen("Creacion de Usuarios");

  //Preguntamos por la confirmacion del usuario
  int inputInt;
  cout<<"\n--->Datos del nuevo usuario:";
  cout<<"\nID: "<<newUser.getId_()<<"\nTipo de Usuario: "<<newUser.getUserType_()<<"\nNombre del Usuario: "<<newUser.getName_()<<"\nLogin del Usuario: "<<newUser.getLogin_()<<"\nContrasena del Usuario: "<<newUser.getPassword_()<<"\nID de limite del Usuario: "<<newUser.getLimitId_();
  cout<<"\nEsta satisfecho con el usuario?\n->Introduzca 1 para confirmar, 0 para cancelar:";
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
  cout << "Escriba el ID del usuario que desea modificar:" << '\n';
  string userModID;
  cin >> userModID;
  currentUser = findUser(userModID);//comprobamos si el ID es correcto

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

bool System::addMachine(const string &userId){
  clearScreen("Creacion de Maquinas");
  User currentUser = findUser(userId);
  if (currentUser.getUserType_()!=1) {
    std::cout << "Error,solo los usuarios de tipo 1 pueden crear nuevos maquinas" << '\n';
    exit(EXIT_FAILURE);
  }
  Machine newMachine;

  //ID de la maquina
  string newMId="m";
  int newMIdNumber=1;
  if(machines_.empty()){newMId+=to_string(newMIdNumber);}
  else{
      cout << "Introduzca el numero del identificador:" << '\n';
      cin>>newMIdNumber;
      newMId+=to_string(newMIdNumber);
  }
  list<Machine>::iterator m;
  for (m = machines_.begin(); m != machines_.end(); m++) {
    if(m->getId_()==newMId){
      cout << "Error,esa maquina ya existe" << '\n';
      exit(EXIT_FAILURE);
    }
  }
  newMachine.setId_(newMId);
  clearScreen("Creacion de Maquinas");

  struct resource aux;
  int nu;
  int ra;
  cout << "Introduzca el numero de nucleos de su maquina:" << '\n';
  cin >>nu;
  aux.cores=nu;
  cout << "Introduzca la cantidad de ram de su maquina:" << '\n';
  cin >>ra;
  aux.ram=ra;
  newMachine.setResources_(aux);
  clearScreen("Creacion de Maquinas");

  //Preguntamos por la confirmacion del usuario
  int inputInt;
  cout<<"\n--->Datos de la nueva maquina:";
  cout<<"\nID: "<<newMachine.getId_()<<"\nNucleos: "<<newMachine.getResources_().cores<<", RAM: "<<newMachine.getResources_().ram;
  cout<<"\nEsta satisfecho con la maquina?\n->Introduzca 1 para confirmar, 0 para cancelar:";
  cin>>inputInt;
  if (inputInt==1)
  {
      machines_.push_back(newMachine);
      cout<<"\nMaquina Confirmada";
      return true;
  } else{
      cout<<"\nMaquina Cancelada";
      return false;
  }
}

bool System::deleteMachine(const string &userId){//el Id es de la maquina a borrar
  if(machines_.empty()){//la lista esta vacia
    cout << "Error, la lista esta vacia" << '\n';
    return false;
  }
  list<Machine>::iterator it;
  list<Reservation>::iterator ir;
  for (it = machines_.begin(); it != machines_.end(); it++) {

    if(it->getId_()==userId){
      for (ir = reservations_.begin(); ir != reservations_.end(); ir++) {
        if(ir->getMachineId_()==userId){
          if( deleteReservation( ir->getId_() )==false ){//comprobamos si se pueden borrar las reservas y lo hacemos
            cout << "Error,no se ha podido eliminar las reservas de la maquina" << '\n';
            return false;
          }
        }
      }
      //si la maquina no tuviera reservas se pasaria directamente a eliminar sus datos
      machines_.erase(it);//borramos la maquina
      return true;
    }
  }
  return false;//si no encuentra la maquina a borrar,devuelve false
}//Debe borrar las reservas a su nombre con deleteReservation(reservationId) antes de borrar el usuario

bool System::modifyMachine(const string &userId){
  clearScreen("Modificacion de Maquina");
  User currentUser = findUser(userId);
  if (currentUser.getUserType_()!=1) {
    std::cout << "Error,solo los usuarios de tipo 1 pueden modificar maquinas" << '\n';
    exit(EXIT_FAILURE);
  }
  showMachines(userId);
  cout << "Escriba el ID de la maquina que desea modificar:" << '\n';
  string MachineModID;
  cin >> MachineModID;
  int a=0;
  list<Machine>::iterator ma;
  for (ma = machines_.begin(); ma != machines_.end(); ma++) {
    if(ma->getId_()==MachineModID){
      a++;
    }
  }
  if(a==0){
    cout<<"Fatal Error: La maquina "<<MachineModID<<" no esta en el sistema\nAbortando ejecucion\n";
    exit(EXIT_FAILURE);
  }//comprobamos si existe la maquina

  int option;
  cout << "¿Se desea modificar o borrar la maquina?" << '\n';
  cout << "1-Modificar la maquina" << '\n';
  cout << "2-Borrar la maquina" << '\n';
  cin >> option;
  if(option==1){//borramos y creamos usuario para modificarlo con el mismo id

    if(deleteMachine(MachineModID)==false){
      return false;
    }
    if(addMachine(userId)==false){
      return false;
    }

    return true;
  }

  else if(option==2){
    if(deleteMachine(MachineModID)==false){
      return false;
    }

    return true;
  }

  else{
    cout << "Error,Debe escoger entre la opcion 1 o la opcion 2" << '\n';
    return false;
  }
}
