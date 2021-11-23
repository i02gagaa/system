#ifndef SYSTEM_H
#define SYSTEM_H



#include "Machine.h"
#include "Reservation.h"
#include "User.h"

#include <string>
#include <list>
using namespace std;

class System
{
private:
    list <User> users_;
    list <Limit> limits_;
    list <Reservation> reservations_;
    list <Machine> machines_;

    User findUser(const string &userId);    //A partir de un string userId lo busca en la lista de usuarios, cuando lo encuentra lo devuelve, !!SI NO EXISTE VA A IMPRIMIR UN MENSAJE DE ERROR Y ACABARA EJECUCION!!   
    struct resource availableResources(const string &machine, const int day); //Devuelve el struct recurso libre de una maquina para un dia especifico
    

public:
    System();//Constructor
    ~System();//Destructor

    inline list <User> getUsers() const {return users_;}
    inline list <Limit> getLimits() const {return limits_;}
    inline list <Reservation> getReservations() const {return reservations_;}
    inline list <Machine> getmachines() const {return machines_;}


    User authenticateUser();
    //Anade una reserva nueva, devolviendo true si el ususario la confirma, pide los datos de la nueva reserva por terminal
    bool addReservation(const string &userId);
    //Busca en la lista de reservas la reserva correspondiente al id pasado y la elimina, si no la encuentra, devuelve falso
    bool deleteReservation(const string &userId);

    void showReservations(const string &userId);
    bool modifyReservation(const string &reservationId);
    bool addUser(const string &userId);
    bool deleteUser(const string &userId);
    bool modifyUser(const string &userId);
    void showUsers(const string &userId);
    bool addMachine(const string &userId);
    bool deleteMachine(const string &userId);
    bool modifyMachine(const string &userId);
    //Muestra la lista de maquinas con sus recursos totales por pantalla si el usuario tiene los permisos
    void showMachines(const string &userId);
    bool addLimit(const string &userId);
    bool deleteLimit(const string &userId);
    void showLimits(const string &userId);
    
    
    //Muestra los elementos del sistema por terminal, para debugging
    void showObjects();
    void testSetup();
    //Limpia la terminal y en caso de que se introduzca un titulo de seccion, lo imprimira como cabecera de seccion
    void clearScreen (const string &sectionTitle="");



    



};















#endif