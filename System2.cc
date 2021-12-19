#include "System.h"
#include "Limit.h"
#include "Machine.h"
#include "Reservation.h"
#include "User.h"



#include <string>
#include <list>
#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

//Constructor
System::System(){
//Reservas-------------------------------------
  ifstream file("reservations.csv");
  if(file.is_open()==false){
    reservations_.clear();
    cout << "No existe el archivo reservations.csv" << '\n'
  }
  else{
  reservations_.clear();//borra la lista
  struct resource reser;
  string Id,day1,dayf,cor,raM,UserID,MaquinaID;
    while (getline(file, Id,',')) {//lee hasta que encuentra una coma
      getline(file, day1,',');
      getline(file, dayf,',');
      getline(file, cor,',');
      getline(file, raM,',');
      getline(file, UserID,',');
      getline(file, MaquinaID,'\n');//lee hasta el final de la linea pues ya no hay mas elementos y pasa a la siguiente
      reser.cores=stoi(cor);
      reser.ram=stoi(raM);
      Reservation aux;
      aux.setId_(Id);
      aux.setFirstDay_(stoi(day1));
      aux.setLastDay_(stoi(dayf));
      aux.setResources_(reser);
      aux.setUserId_(UserID);
      aux.setMachineId_(MaquinaID);
      reservations_.push_back(aux);
    }
    file.close();
  }
//------------------------------------
//Limites-------------------------------------
  ifstream file2("limits.csv");
  if(file2.is_open()==false){
    limits_.clear();
    cout << "No existe el archivo limits.csv" << '\n'
  }
  else{
  limits_.clear();//borra la lista
  struct resource limi;
  string Lid,daymax,Lcor,LraM,;
    while (getline(file2, Lid,',')) {//lee hasta que encuentra una coma
      getline(file2, daymax,',');
      getline(file2, Lcor,',');
      getline(file2, LraM,'\n');//lee hasta el final de la linea pues ya no hay mas elementos y pasa a la siguiente
      limi.cores=stoi(Lcor);
      limi.ram=stoi(LraM);
      Limit aux2;
      aux2.setId_(Lid);
      aux2.setMaxDays_(stoi(daymax));
      aux2.setMaxResources_(limi);
      limits_.push_back(aux2);
    }
    file2.close();
  }
//------------------------------------
//Maquinas-------------------------------------
  ifstream file3("machines.csv");
  if(file3.is_open()==false){
    machines_.clear();
    cout << "No existe el archivo machines.csv" << '\n'
  }
  else{
  machines_.clear();//borra la lista
  struct resource maq;
  string Maqid,Mcor,MraM;
    while (getline(file3, Maqid,',')) {
      getline(file3, Mcor,',');//lee hasta que encuentra una coma
      getline(file3, MraM,'\n');//lee hasta el final de la linea pues ya no hay mas elementos y pasa a la siguiente
      maq.cores=stoi(Mcor);
      maq.ram=stoi(MraM);
      Machine aux3;
      aux3.setId_(Maqid);
      aux3.setResources_(maq);
      machines_.push_back(aux3);
    }
    file3.close();
  }
//------------------------------------
//Usuarios-------------------------------------
  ifstream file4("users.csv");
  if(file4.is_open()==false){
    users_.clear();
    cout << "No existe el archivo users.csv" << '\n'
    cout << "Se crea un administrador de tipo 2 con login y contrasena default" << '\n';
    User adm2;
    adm2.setId_("u1");
    adm2.setUserType_(2);
    adm2.setName_("Admin2");
    adm2.setLogin_("default");
    adm2.setPassword_("default");
    adm2.setLimitId_("l1");
    users_.push_back(adm2);
  }
  else{
  users_.clear();//borra la lista
  string Uid,adm,nam,logi,passwor,limID;
    while (getline(file4, Uid,',')) {//lee hasta que encuentra una coma
      getline(file4, adm,',');
      getline(file4, nam,',');
      getline(file4, logi,',');
      getline(file4, passwor,',');
      getline(file4, limID,'\n');//lee hasta el final de la linea pues ya no hay mas elementos y pasa a la siguiente
      User aux4;
      aux4.setId_(Uid);
      aux4.setUserType_(stoi(adm));
      aux4.setName_(nam);
      aux4.setLogin_(logi);
      aux4.setPassword_(passwor);
      aux4.setLimitId_(limID);
      users_.push_back(aux4);
    }
    file4.close();
  }
//------------------------------------
}


//Destructor
System::~System(){
//Reservas-------------------------------------
  ofstream file("reservations.csv");
  if(file.is_open()==false){
    cout << "Error,no se pudo abrir/editar el archivo" << '\n';
    exit(EXIT_FAILURE);
  }
  list<Reservation>::iterator it;
  for (it = reservations_.begin(); it != reservations_.end(); it++) {
    file<<it->getId_()<<","<<
    it->getFirstDay_()<<","<<
    it->getLastDay_()<<","<<
    it->getResources_().cores<<","<<
    it->getResources_().ram<<","<<
    it->getUserId_()<<","<<
    it->getMachineId_()<<endl;
  }
  file.close();
//------------------------------------
//Limites-------------------------------------
  ofstream file2("limits.csv");
  if(file2.is_open()==false){
    cout << "Error,no se pudo abrir/editar el archivo" << '\n';
    exit(EXIT_FAILURE);
  }
  list<Limit>::iterator i;
  for (i = limits_.begin(); i != limits_.end(); i++) {
    file2<<i->getId_()<<","<<
    i->getMaxDays_()<<","<<
    i->getMaxResources_().cores<<","<<
    i->getMaxResources_().ram<<endl;
  }
  file2.close();
//------------------------------------
//Maquinas-------------------------------------
  ofstream file3("machines.csv");
  if(file3.is_open()==false){
    cout << "Error,no se pudo abrir/editar el archivo" << '\n';
    exit(EXIT_FAILURE);
  }
  list<Machine>::iterator im;
  for (im = machines_.begin(); im != machines_.end(); im++) {
    file3<<im->getId_()<<","<<
    im->getResources_().cores<<","<<
    im->getResources_().ram<<endl;
  }
  file3.close();
//------------------------------------
//Usuarios-------------------------------------
  ofstream file4("users.csv");
  if(file4.is_open()==false){
    cout << "Error,no se pudo abrir/editar el archivo" << '\n';
    exit(EXIT_FAILURE);
  }
  list<User>::iterator iu;
  for (iu = users_.begin(); iu != users_.end(); iu++) {
    file4<<iu->getId_()<<","<<
    iu->getUserType_()<<","<<
    iu->getName_()<<","<<
    iu->getLogin_()<<","<<
    iu->getPassword_()<<","<<
    iu->getLimitId_()<<endl;
  }
  file4.close();
//------------------------------------
}


User System::authenticateUser(){
  clearScreen("Autenticacion de Usuario");
  list <User>::iterator i = users_.begin();
  string log;
  string pas;
  do{
    cout<<"Introduzca el login del usuario\n";
    cin>>log;
    cout<<"Introduzca la contrasena del usuario\n";
    cin >>pas;
    for (i = users_.begin(); i != users_.end(); r++) {
      if(i->getLogin_()==log){
        if(i->getPassword_()==pas){
          return *i;
        }
      }
    }
    cout << "Debe introducir el login y la contrasena correctos" << '\n';
  }while(true);
}

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

bool System::addLimit(const string &userId){//ID del usuario al que le vamos a incluir limites
  clearScreen("Creacion de Limites");
  User currentUser = findUser(userId);
  list<User>::iterator it;
  string Idlim="zero";
  Limit newLimit;
  for (it = users_.begin(); it != users_.end(); it++) {
      if(it->getId_()==userId){
        Idlim=it->getLimitId_();
      }
  }
  if(Idlim=="zero"){
    cout << "Error,no se ha encontrado el identificador del limite" << '\n';
    return false;
  }
  newLimit.setId_(Idlim);
  int maxD;
  //acabar........

}

void System::showLimits(const string &userId) {
  clearScreen("Creacion de Limites");
  User currentUser = findUser(userId);
  list<Limit>::iterator it;
  for (it = limits_.begin(); it != limits_.end(); it++) {
    cout << "ID del limite: " << users_.getId_() << '\n';
    cout << "Maximos dias posibles: " << users_.getMaxDays_() << '\n';
    cout << "Maximo numero de nucleos: " << users_.getMaxResources_().cores << '\n';
    cout << "Maxima cantidad de RAM: " << users_.getMaxResources_().ram << '\n';
  }
}

bool System::deleteLimit(const string &userId){
  clearScreen("Creacion de Limites");
  User currentUser = findUser(userId);
  showLimits(userId);
  cout << "Debe escoger el limite que desea borrar:" << '\n';
  //unir l+numero,acabar...........

 }//Debe mostrar por pantalla la lista de limites (Id, rescursos maximos y dias maximos), solicitar al usuario que elija uno y borrarlo de limits_
