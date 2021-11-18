#include "date.h"
#include "System.h"
#include "Limit.h"
#include "Machine.h"
#include "Reservation.h"
#include "User.h"


#include <iostream>


int main(){
    //Creacion del system
    System system;
    cout<<"\nAntes del test setup";
    system.showObjects();
    system.testSetup();
    cout<<"\nDespues del test setup";
    system.showObjects();
    system.showReservations(system.getUsers().front().getId_());
    system.showMachines(system.getUsers().front().getId_());
    for (int i = 0; i < 3; i++)
    {
        system.addReservation(system.getUsers().front().getId_());
        cout<<"\nDespues de anadir";
        system.showObjects();
    }
    system.modifyReservation(system.getUsers().front().getId_());
    cout<<"\nDespues de primera modificacion";
    system.showObjects();
    system.modifyReservation(system.getUsers().front().getId_());
    cout<<"\nDespues de segunda modificacion";
    system.showObjects();
    
    
    
    
    cout<<"Todo Ok\n";
    return 0;
}