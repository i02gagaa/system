#include "date.h"
#include "System.h"
#include "Limit.h"
#include "Machine.h"
#include "Reservation.h"
#include "User.h"


#include <iostream>



//Menu de gestion de reservas
void reservationManagementMenu(System &system, User &currentUser);

//Menu de gestion de usuarios
void userManagementMenu(System &system, User &currentUser);

//Menu de gestion de limites
void limitsManagementMenu(System &system, User &currentUser);

//Menu de gestion de maquinas
void machineManagementMenu(System &system, User &currentUser);

//menu general para usuarios estandar
void userType0Menu(System &system, User &currentUser);

//menu general para administradores de maquinas
void userType1Menu(System &system, User &currentUser);

//Menu general para administradores de usuarios
void userType2Menu(System &system, User &currentUser);


using namespace std;

int main(){
    //Creacion del system, ejecuta el constructor, cargando los objetos de disco duro en memoria
    System system;

    //Autenticacion -> Obtenemos el objeto ususario correspondiente al ususario que haya iniciado sesion
    //Descomentar cuando authenticateUser()  este implementada
    User currentUser = system.authenticateUser();

    //Como no esta implementada la funcion authenticateUser(), haremos un testSetup() y asignaremos el primer usuario de la lista al currentUser para que el sistema tenga funcionalidad
    //Comentar las siguientes 4 lineas cuando athenticateUser() este implementada
    if(currentUser.getId_()=="noImplementado"){
        system.testSetup();
        currentUser = system.getUsers().front();
    }
    

    switch (currentUser.getUserType_())
    {
    case 0:
        //Usuario estandar
        userType0Menu(system,currentUser);
        break;

    case 1:
        //Administrador de maquinas
        userType1Menu(system,currentUser);
        break;

    case 2:
        //Administrador de usuarios
        userType2Menu(system,currentUser);
        break;
    
    default:
        cout<<"Fatal error: Main\n\tEl usuario "<<currentUser.getId_()<<", con login: "<<currentUser.getLogin_()<<" tiene un USERTYPE INVALIDO User.usertype_= "<<currentUser.getUserType_()<<"\n";
        exit(EXIT_FAILURE);        
    }

    //Fin de programa, ejecuta el destructor, pasando las listas de objetos a disco
    return 0;
}



//menu general para usuarios estandar
void userType0Menu(System &system, User &currentUser){
    //Los usuarios estandar solo acceden al menu de gestion de reservas
    reservationManagementMenu(system,currentUser);
}

//menu general para administradores de maquinas
void userType1Menu(System &system, User &currentUser){

    bool stayInMenu=true;

    //Los administradores de maquinas pueden acceder al la gestion de reservas y a la de maquinas
    while (stayInMenu)
    {
        system.clearScreen("Menu de Administradores de Maquinas");

        cout<<" [0] Acceder a gestion de Reservas\n";
        cout<<" [1] Acceder a gestion de Maquinas\n";
        cout<<" [2] Guardar y salir\n";

        int inputInt;
        cout<<"\n->Elija una opcion: ";
        cin>>inputInt;

        switch (inputInt)
        {
        case 0:
            //Se pretende acceder al menu de gestion de reservas
            reservationManagementMenu(system,currentUser);
            break;

        case 1:
            //Se pretende acceder al menu de gestion de maquinas
            machineManagementMenu(system,currentUser);
            break;
        default:
            stayInMenu=false;
        }
    }
}

//Menu general para administradores de usuarios
void userType2Menu(System &system, User &currentUser){

    bool stayInMenu=true;

    //Los administradores de usuarios pueden acceder al la gestion de reservas, a la de usuarios y a la de limites
    while (stayInMenu)
    {
        system.clearScreen("Menu de Administradores de Usuarios");

        cout<<" [0] Acceder a gestion de Reservas\n";
        cout<<" [1] Acceder a gestion de Usuarios\n";
        cout<<" [2] Acceder a gestion de Limites\n";
        cout<<" [3] Guardar y salir\n";

        int inputInt;
        cout<<"\n->Elija una opcion: ";
        cin>>inputInt;

        switch (inputInt)
        {
        case 0:
            //Se pretende acceder al menu de gestion de reservas
            reservationManagementMenu(system,currentUser);
            break;

        case 1:
            //Se pretende acceder al menu de gestion de usuario
            userManagementMenu(system,currentUser);
            break;

        case 2:
            //Se pretende acceder al menu de gestion de limites
            limitsManagementMenu(system,currentUser);
            break;

        default:
            stayInMenu=false;
        }
    }
}


//Menu de gestion de reservas
void reservationManagementMenu(System &system, User &currentUser){
    bool stayInMenu=true;
    while (stayInMenu)
    {
        system.clearScreen("Gestion de Reservas");

        cout<<" [0] Mostrar Reservas\n";
        cout<<" [1] Acceder a la Creacion de Reservas\n";
        cout<<" [2] Acceder a la Modificacion de Reservas\n";
        cout<<" [3] Salir\n";

        int inputInt;
        cout<<"\n->Elija una opcion: ";
        cin>>inputInt;

        switch (inputInt)
        {
        case 0:
            //Se pretende mostrar las reservas
            system.showReservations(currentUser.getId_());
            break;

        case 1:
            //Se pretende acceder a la Creacion de Reservas
            system.addReservation(currentUser.getId_());
            break;

        case 2:
            //Se pretende acceder a la Modificacion de Reservass
            system.modifyReservation(currentUser.getId_());
            break;

        default:
            stayInMenu=false;
        }
    }
}

//Menu de gestion de usuarios
void userManagementMenu(System &system, User &currentUser){
    bool stayInMenu=true;
    while (stayInMenu)
    {
        system.clearScreen("Gestion de Usuarios");

        cout<<" [0] Mostrar Usuarios\n";
        cout<<" [1] Acceder a la Creacion de Usuarios\n";
        cout<<" [2] Acceder a la Modificacion de Usuarios\n";
        cout<<" [3] Atras\n";

        int inputInt;
        cout<<"\n->Elija una opcion: ";
        cin>>inputInt;

        switch (inputInt)
        {
        case 0:
            //Se pretende mostrar los usuarios
            system.showUsers(currentUser.getId_());
            break;

        case 1:
            //Se pretende acceder a la Creacion de Usuarios
            system.addUser(currentUser.getId_());
            break;

        case 2:
            //Se pretende acceder a la Modificacion de Usuarios
            system.modifyUser(currentUser.getId_());
            break;

        default:
            stayInMenu=false;
        }
    }
}

//Menu de gestion de limites
void limitsManagementMenu(System &system, User &currentUser){
    bool stayInMenu=true;
    while (stayInMenu)
    {
        system.clearScreen("Gestion de Limites");

        cout<<" [0] Mostrar Limites\n";
        cout<<" [1] Acceder a la Creacion de Limites\n";
        cout<<" [2] Acceder al Borrado de Limites\n";
        cout<<" [3] Atras\n";

        int inputInt;
        cout<<"\n->Elija una opcion: ";
        cin>>inputInt;

        switch (inputInt)
        {
        case 0:
            //Se pretende mostrar los limites
            system.showLimits(currentUser.getId_());
            break;

        case 1:
            //Se pretende acceder a la Creacion de limites
            system.addLimit(currentUser.getId_());
            break;

        case 2:
            //Se pretende acceder al Borrado de Limites
            system.deleteLimit(currentUser.getId_());
            break;

        default:
            stayInMenu=false;
        }
    }
}

//Menu de gestion de maquinas
void machineManagementMenu(System &system, User &currentUser){
    bool stayInMenu=true;
    while (stayInMenu)
    {
        system.clearScreen("Gestion de Maquinas");

        cout<<" [0] Mostrar Maquinas\n";
        cout<<" [1] Acceder a la Creacion de Maquinas\n";
        cout<<" [2] Acceder a la Modificacion de Maquinas\n";
        cout<<" [3] Atras\n";

        int inputInt;
        cout<<"\n->Elija una opcion: ";
        cin>>inputInt;

        switch (inputInt)
        {
        case 0:
            //Se pretende mostrar las maquinas
            system.showMachines(currentUser.getId_());
            break;

        case 1:
            //Se pretende acceder a la Creacion de Maquinas
            system.addMachine(currentUser.getId_());
            break;

        case 2:
            //Se pretende acceder a la Modificacion de Maquinas
            system.modifyMachine(currentUser.getId_());
            break;

        default:
            stayInMenu=false;
        }
    }
}