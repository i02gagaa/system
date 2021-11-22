#include "System.h"
#include "Limit.h"
#include "Machine.h"
#include "Reservation.h"
#include "User.h"
#include "date.h"



#include <string>
#include <list>
#include <iostream>
using namespace std;


void System::testSetup(){
    int inputInt;
    Reservation reservation;
    Machine machine;
    Machine machineLowRes;
    User user;
    Limit limit;
    struct resource testResources;
    testResources.cores=10;
    testResources.ram=10;
    struct resource testResourcesReserved;
    struct resource testResourcesLow;
    testResourcesReserved.cores=5;
    testResourcesReserved.ram=5;
    int nDaysReserved =1;
    testResourcesLow.cores=1;
    testResourcesLow.ram=1;
    clearScreen("Test Setup");

    

    machine.setId_("m4");
    machine.setResources_(testResources);
    machineLowRes.setId_("m5");
    machineLowRes.setResources_(testResourcesLow);

    limit.setId_("l1");
    limit.setMaxDays_(10);
    limit.setMaxResources_(testResources);

    user.setId_("u2");
    cout<<"Introduzca el tipo de usuario que desea para el test (tipo 0, 1 o 2)\n";
    cin>>inputInt;
    user.setUserType_(inputInt);
    cout<<"Desea que el usuario tenga limites asociados por defecto? (1 o 0)\n";
    cin>>inputInt;
    if(inputInt==1){user.setLimitId_(limit.getId_());}
    

    reservation.setId_("r3");
    reservation.setFirstDay_(today());
    reservation.setLastDay_(today()+nDaysReserved);
    reservation.setMachineId_(machine.getId_());
    reservation.setResources_(testResourcesReserved);
    reservation.setUserId_(user.getId_());


    reservations_.push_back(reservation);
    users_.push_back(user);
    limits_.push_back(limit);
    machines_.push_back(machine);
    machines_.push_back(machineLowRes);
    
}

//A partir de un string userId busca el usuario en la lista de usuarios, cuando lo encuentra lo devuelve como objeto, !!SI NO EXISTE VA A IMPRIMIR UN MENSAJE DE ERROR Y ACABARA EJECUCION!!    
User System::findUser(const string &userId){

    list <User>::iterator i = users_.begin();
    while (i!=users_.end())
    {
        if((i->getId_())==userId) return *i;
        else i++;
    }

    cout<<"Fatal Error:findUser: El usuario "<<userId<<" no esta en el sistema\nAbortando ejecucion\n";
    exit(EXIT_FAILURE);    
}

//Muestra los elementos del sistema por terminal, para debugging
void System::showObjects(){
    
    cout<<"\n---------------------------------------------\n";
    cout<<"->Machines: "<<machines_.size()<<"-{ ";
    list <Machine>::iterator m=machines_.begin();
    while (m!=machines_.end()){ cout<<m->getId_()<<", "; m++;}

    cout<<"}\n->Users: "<<users_.size()<<"-{ ";
    list <User>::iterator u=users_.begin();
    while (u!=users_.end()){ cout<<u->getId_()<<", "; u++;}

    cout<<"}\n->Reservations: "<<reservations_.size()<<"-{ ";
    list <Reservation>::iterator r=reservations_.begin();
    while (r!=reservations_.end()){ cout<<r->getId_()<<", "; r++;}

    cout<<"}\n->Limits: "<<limits_.size()<<"-{ ";
    list <Limit>::iterator l=limits_.begin();
    while (l!=limits_.end()){ cout<<l->getId_()<<", "; l++;}
    cout<<"}\n---------------------------------------------\n";
    
}


//Devuelve el struct recurso libre de una maquina para un dia especifico
struct resource System::availableResources(const string &machine, const int day){
    //Copia lista reservas
    list <Reservation> reservations;

    list <Reservation>:: iterator i = reservations.begin();

    //Creamos una lista a partir del total de las reservas en la que debemos tener las reservas que sean de la maquina y (diaInicio<=dia<= diaFinal)

    for(i=reservations_.begin();i!=reservations_.end();i++){

        int firstDay=i->getFirstDay_();
        int lastDay=i->getLastDay_();

        if(  (i->getMachineId_()==machine) &&   (firstDay<=day) && (day<=lastDay) ) reservations.push_back(*i);
    }


    //Ya tenemos unicamente en la lista las reservas de esta maquina que comprenden el dia indicado, recorremos la lista y acumulamos los recursos reservados en ese dia
    struct resource resourcesAcc;
    resourcesAcc.cores=0;
    resourcesAcc.ram=0;

    i=reservations.begin();
    while (i!=reservations.end())
    {
        struct resource iteratorResouces = i->getResources_();
        resourcesAcc.cores+=iteratorResouces.cores;
        resourcesAcc.ram+=iteratorResouces.ram;
        i++;
    }
    

    //Restamos los recursos acumulados a los que tiene la maquina y devolvemos la diferencia
    struct resource available, machineResources;
    list <Machine>:: iterator m = machines_.begin();
    
    while ((m!=machines_.end())&&((m->getId_())!=machine)){m++;}//Recorreremos la lista de maquinas para localizar la maquina buscada y averiguar sus recursos
    if(m==machines_.end()){//Hemos llegado al final de la lista y no hemos encontrado la maquina ERROR FATAL
        cout<<"Fatal Error:availableResources: La maquina "<<machine<<" no esta en el sistema\nAbortando ejecucion\n";
        exit(EXIT_FAILURE);
    }
    //Si existe la maquina m la esta apuntando
    machineResources=m->getResources_();
    available.cores=(machineResources.cores-resourcesAcc.cores);
    available.ram=(machineResources.ram-resourcesAcc.ram);

    //Hacemos una comprobacion de que los recursos disponibles sean >=0, en caso de que esto no fuera asi, habrian mas recursos reservados de los que la maquina tiene y los datos del programa estarian corruptos
    if((available.cores<0)||(available.ram<0)){
        cout<<"Fatal Error:availableResources: Hay mas recursos reservados en el dia "<<intToDate(day)<<" de los que la maquina "<<machine<<" tiene \n->DATOS CORRUPTOS - Abortando ejecucion\n";
        exit(EXIT_FAILURE);
    }

    //Todo correcto, devolvemos recursos
    return available;      
}



//Anade una reserva nueva, devolviendo true si el ususario la confirma, pide los datos de la nueva reserva por terminal
bool System::addReservation(const string &userId){


    clearScreen("Creacion de Reservas");    
    User currentUser = findUser(userId);
    //Rellenamos nuevo objeto reserva
    Reservation newReservation;
    bool isInputOk;
    string input;
    //Fecha de inicio
    cout<<"\n->Introduzca el dia de inicio de la nueva reserva (formato dd/mm/aaaa):";
    do{
        isInputOk = true;
        cin>>input;
        if(!isDateFormatOk(input)){
            cout<<"\nFormato de fecha incorrecto, vuelva a introducirlo: ";
            isInputOk=false;
        }else if(inThePast(input)){
            cout<<"\nFecha pasada, debe de ser hoy o un dia posterior, vuelva a introducirlo: ";
            isInputOk=false;
        }
    }while(!isInputOk);
    newReservation.setFirstDay_(dateToInt(input));

    clearScreen("Creacion de Reservas"); 
    //Fecha final
    cout<<"\n->Introduzca el dia final de reserva (formato dd/mm/aaaa):";
    do{
        isInputOk = true;
        cin>>input;
        if(!isDateFormatOk(input)){
            cout<<"\nFormato de fecha incorrecto, vuelva a introducirlo: ";
            isInputOk=false;
        }else if(inThePast(input)){
            cout<<"\nFecha pasada, debe de ser hoy o un dia posterior, vuelva a introducirlo: ";
            isInputOk=false;
        }else if(dateToInt(input)<(newReservation.getFirstDay_())){
            cout<<"\nFecha anterior a la fecha inicial, debe de ser la misma que la inicial o un dia posterior, vuelva a introducirlo: ";
            isInputOk=false;
        }
    }while(!isInputOk);
    newReservation.setLastDay_(dateToInt(input));

    clearScreen("Creacion de Reservas"); 
    //Recursos de reserva
    struct resource newReservationResources;
    cout<<"\n->Introduzca el numero de nucleos a reservar:";
    int inputInt;
    do{
        isInputOk = true;
        cin>>inputInt;
        if(inputInt<1){
            cout<<"\nEl numero de nucleos reservados no puede ser menor que uno, vuelva a introducirlos: ";
            isInputOk = false;
        }
        
    }while(!isInputOk);
    newReservationResources.cores=inputInt;
    cout<<"\n->Introduzca la cantidad de ram a reservar:";
    do{
        isInputOk = true;
        cin>>inputInt;
        if(inputInt<1){
            cout<<"\nLa cantidad minima de ram a reservar es de 1 gb, vuelva a introducirla: ";
            isInputOk = false;
        }
    }while(!isInputOk);
    newReservationResources.ram=inputInt;
    newReservation.setResources_(newReservationResources);

    //Creamos lista auxiliar de reservas con solo las del usuario
    list <Reservation> reservations;
    list <Reservation>::iterator i;
    for(i= reservations_.begin(); i!=reservations_.end(); i++){
        if(i->getUserId_()==currentUser.getId_()) reservations.push_back(*i);
    }

    //Acumulamos los recursos ya reservados y el numero de dias reservados
    int accDays=0;
    struct resource accResources;
    accResources.cores=0;
    accResources.ram=0;
    i = reservations.begin();
    int daySpan;//Para almacenar diferencia de dias entre final e inicio de la reserva que estemos analizando
    while (i!=reservations.end())
    {
        daySpan=((i->getLastDay_())-(i->getFirstDay_()));
        accDays+=daySpan;
        accResources.cores+=(i->getResources_()).cores;
        accResources.ram+=(i->getResources_()).ram;   
        i++;     
    }
    //Sumamos a los acumulados los que pretendemos reservar y comprobamos que no sobrepasen los limites
    daySpan=(newReservation.getLastDay_()-newReservation.getFirstDay_());

    accDays+=daySpan;
    accResources.cores+=newReservationResources.cores;
    accResources.ram+=newReservationResources.ram;

    //Obtenemos los limites asociados al usuario solo si existen, es decir, su campo de LimitId no esta vacio

    if(currentUser.getLimitId_()!="defaultLId"){

        //Obtenemos los limites asociados al usuario
        list <Limit>::iterator l;
        for(l = limits_.begin();(l!=limits_.end())&&(l->getId_()!=currentUser.getLimitId_());l++){ }
        
        if(l==limits_.end()){
            clearScreen("Creacion de Reservas"); 
            cout<<"Fatal Error:addReservation: El limite "<<currentUser.getLimitId_()<<" del usuario "<<currentUser.getId_()<<" no esta en el sistema\nAbortando ejecucion\n";
            exit(EXIT_FAILURE);
        }

        int maxDays= l->getMaxDays_();
        struct resource maxResources = l->getMaxResources_();

        //Comprobamos que los recursos y dias acumulados no sobrepasen la reserva
        if((accDays>maxDays)||(accResources.cores>maxResources.cores)||(accResources.ram>maxResources.ram)) {
            //Se pretenden reservar mas de los posibles
            clearScreen("Creacion de Reservas"); 
            cout<<"\n--->Se pretenden reservar mas recursos de los posibles, su periodo maximo de dias es "<<maxDays<<" su cantidad de nucleos maxima es "<<maxResources.cores<<" y su cantidad maxima de RAM es "<<maxResources.ram<<"\nPara cambiar sus limites contacte con el administrador";
            cout<<"\nActualmente tiene un periodo total de "<<(accDays-daySpan)<<" dias reservados y "<<(accResources.cores-newReservationResources.cores)<<" nucleos con "<<(accResources.ram-newReservationResources.ram)<<"GB de RAM reservados";
            cout<<"\nCancelando reserva";
            return false;
        }
    }




    //UserId
    //Si seguimos la reserva es posible, anadimos el id del usuario a la reserva
    newReservation.setUserId_(currentUser.getId_());

    //MachineID
    //Creamos lista de maquinas validas que puedan satisfacer la reserva y si una maquina es valida la imprimimos por pantalla
    list <Machine> machines;
    list <Machine>::iterator m ;
    

    if (!machines_.empty()) {clearScreen("Creacion de Reservas");}
    int count =0; 


    for(m=machines_.begin();m!=machines_.end();m++){
        struct resource machineAvailableResources ;
        bool isMachineValid = true;
        struct resource machineIntervalAvailableResources = m->getResources_();//Recursos minimos libres durante el intervalo, en un principio se inicializan a los de la maquina
        

        //Para cada maquina comprobamos que tenga los recursos necesarios cada dia que comprendera la reserva
        for(int day = newReservation.getFirstDay_(); ((day<=(newReservation.getLastDay_()))&&(isMachineValid)); day++){

            machineAvailableResources=availableResources(m->getId_(),day);
            if(machineAvailableResources.cores<machineIntervalAvailableResources.cores) machineIntervalAvailableResources.cores= machineAvailableResources.cores;
            if(machineAvailableResources.ram<machineIntervalAvailableResources.ram) machineIntervalAvailableResources.ram= machineAvailableResources.ram;
            
            if((machineAvailableResources.cores<newReservationResources.cores)||(machineAvailableResources.ram<newReservationResources.ram)) isMachineValid=false;
        }

        if(isMachineValid) {
            machines.push_back(*m);
            cout<<"\n["<<count<<"] ->"<<m->getId_()<<" - Recursos libres: {Nucleos: "<<machineIntervalAvailableResources.cores<<", RAM: "<<machineIntervalAvailableResources.ram<<"}";
            count ++;
        }
    }

    //Si no hay ninguna maquina que pueda cumplir los requisitos se cancela la reserva
    if(machines.empty()){
        clearScreen("Creacion de Reservas"); 
        cout<<"\n--->No existe ninguna maquina que pueda cumplir sus requisitos en el espacio de tiempo indicado";
        cout<<"\nCancelando reserva";
        return false;
    }
    

    cout<<"\n->Introduzca el numero que acompana a la maquina que desee reservar en la lista superior:";
    do{
        isInputOk = true;
        cin>>inputInt;
        
        if ((inputInt<0)||(inputInt>=(machines.size()))){
            cout<<"\nNumero incorrecto (por ejemplo si en la lista aparece <[0] ->m1> y desea la maquina m1, introduzca 0)"<<"\nVuelva a seleccionar maquina: ";
            isInputOk=false;
        }
    }while(!isInputOk);

    //El usuario ha seleccionado la maquina en posicion inputInt, adelantamos el iterador m inputInt veces
    m = machines.begin();
    for(count=0; count<inputInt; count++) m++;
    //m apunta la maquina deseada, anadimos su identificador a la reserva
    newReservation.setMachineId_(m->getId_()); 


    //ID
    //Vamos a establecer el id de la reserva para esto vemos si la lista de reservas esta vacia, si es asi, su id sera r1, si no, tomaremos el identificador de la ultima reserva de la lista y le sumaremos una unidad a su parte de digitos
    string newId="r";
    int newIdNumber=1;
    if(reservations_.empty()){newId+=to_string(newIdNumber);
    }else{
        string previousId=(reservations_.back().getId_());
        newIdNumber=stoi(previousId.substr(1));
        newIdNumber++;
        newId+=to_string(newIdNumber);    
    }
    newReservation.setId_(newId);

    clearScreen("Creacion de Reservas"); 

    //Preguntamos por la confirmacion del usuario
    cout<<"\n--->Resumen de la reserva:";
    cout<<"\nMaquina: "<<newReservation.getMachineId_()<<"\nDia inicio: "<<intToDate(newReservation.getFirstDay_())<<"\nDia finalizacion: "<<intToDate(newReservation.getLastDay_())<<"\nNucleos: "<<newReservation.getResources_().cores<<", RAM: "<<newReservation.getResources_().ram;
    cout<<"\nEsta satisfecho con la reserva?\n->Introduzca 1 para confirmar, 0 para cancelar:";
    cin>>inputInt;
    if (inputInt==1)
    {
        reservations_.push_back(newReservation);
        cout<<"\nReserva confirmada";
        return true;
    } else{
        cout<<"\nReserva Cancelada";
        return false;
    } 
}

//Busca en la lista de reservas la reserva correspondiente al id pasado y la elimina, si no la encuentra, devuelve falso
bool System::deleteReservation(const string &reservationId){
    //recorremos la lista de reservas hasta que encontremos la reserva
    list <Reservation>::iterator i;
    for(i=reservations_.begin();i!=reservations_.end();i++){
        if(i->getId_()==reservationId){
            //Encontramos reserva a borrar
            reservations_.erase(i);
            return true;
        }
    }

    //Si hemos recorrido la lista entera y no existe, la reserva no existe en el sistema
    return false;


}

bool System::modifyReservation(const string &userId){
    clearScreen("Modificacion de Reservas");
    User currentUser=findUser(userId);

    //Creamos una lista con todas las reservas a las que tenga acceso el usuario a partir de las del sistema
    //Cualquier tipo de administrador (userType >0) podra modificar las reservas del todos los usuarios
    list <Reservation> reservations;
    list <Reservation>:: iterator i;

    for ( i = reservations_.begin(); i!=reservations_.end(); i++)
    {
        if(currentUser.getUserType_()>0){//Somos administrador de cualquier tipo
            reservations.push_back(*i);
        }else if(i->getUserId_()==userId) reservations.push_back(*i); //Somos usuario estandar y la reserva es nuestra
    }
    //Si no tenemos acceso a ninguna reserva terminamos modificacion
    if(reservations.empty()){
        cout<<"No tiene ninguna reserva a la que pueda acceder\n";
        return false;
    }
    //ya tenemos la lista con las reservas a las que tenemos acceso, la mostramos por pantalla
    cout<<"Lista de reservas a las que tiene acceso:\n";
    int count=0;
    for ( i = reservations.begin(); i!=reservations.end(); i++)
    {
        if(currentUser.getUserType_()>0){//Consulta un administrador y debemos mostrarle el login asociado a cada reserva, tenemos que obtener el login asociado a ese userId de la reserva
            User currentreservationUser = findUser(i->getUserId_());
            cout<<" ["<<count<<"] -{ Id reserva:"<<i->getId_()<<", Maquina:"<<i->getMachineId_()<<", Fecha inicio:"<<intToDate(i->getFirstDay_())<<", Fecha final:"<<intToDate(i->getLastDay_())<<", Nucleos:"<<i->getResources_().cores<<", RAM:"<<i->getResources_().ram<<", User:"<<currentreservationUser.getLogin_()<<"}\n";
        }else{
            //Vista de usuario normal 
            cout<<" ["<<count<<"] -{ Id reserva:"<<i->getId_()<<", Maquina:"<<i->getMachineId_()<<", Fecha inicio:"<<intToDate(i->getFirstDay_())<<", Fecha final:"<<intToDate(i->getLastDay_())<<", Nucleos:"<<i->getResources_().cores<<", RAM:"<<i->getResources_().ram<<"n";
        }  
        count++;      
    }
    cout<<"->Introduzca el numero que acompana a la reserva que desee seleccionar en la lista superior:";
    bool isInputOk;
    int inputInt;
    do{
        isInputOk = true;
        cin>>inputInt;
        
        if ((inputInt<0)||(inputInt>=(reservations.size()))){
            cout<<"Numero incorrecto (por ejemplo si en la lista aparece <[0] ->r1> y desea la reserva r1, introduzca 0)"<<"\nVuelva a seleccionar reserva: ";
            isInputOk=false;
        }
    }while(!isInputOk);

    clearScreen("Modificacion de Reservas");
    //El usuario ha seleccionado la reserva en posicion inputInt, adelantamos el iterador i inputInt veces;
    i=reservations.begin();
    for(count = 0; count<inputInt; count++) i++;
    //Tenemos al iterador apuntando a la reserva seleccionada
    cout<<"Id de la reserva seleccionada: "<<i->getId_()<<"\nSeleccione si quiere modificarla->0, borrarla->1 o cancelar la operacion->2: ";
    cin >> inputInt;
    if(inputInt==0){
        //Se desea modificar, borramos la reserva actual y mandamos al usuario al proceso de crear una nueva
        if(deleteReservation(i->getId_())) {
            addReservation(currentUser.getId_());
            return true;
        }
        else {
            cout<<"Ha habido un problema, no se ha acometido ningun cambio\n";
            return false;
        }
    } else if (inputInt==1){
        //Se desea unicamente borrar
        if(deleteReservation(i->getId_())){
            cout<<"Su reserva ha sido borrada correctamente\n";
            return true;
        }
        else {
            cout<<"Ha habido un error en el borrado de la reserva\n";
            return false;
        }
    }else{
        //Se desea cancelar la operacion
        cout<<"Operacion cancelada\n";
        return false;
    }
    
}


void System::clearScreen (const string &sectionTitle){
    cout<<"Pulse cualquier tecla para continuar\n";
    cin.get();
    cout << "\033[2J\033[0;0H";
   /* for(int i=0; i<200;i++){
        cout<<"\n";
    }*/
    //system("clear"); 
    if(sectionTitle!=""){
        for(int i=0; i<sectionTitle.size();i++)cout<<"-";
        cout<<"\n"<<sectionTitle<<"\n";
        for(int i=0; i<sectionTitle.size();i++)cout<<"-";
        cout<<"\n";
    }
}


void System::showMachines(const string &userId){
    User currentUser = findUser(userId);
    clearScreen("Lista de Maquinas del Sistema");
    //Solo los admin de tipo 1, usertype == 1 podran acceder a esta funcion
    if (currentUser.getUserType_()==1){

        int count=0;
        for(Machine &m: machines_){
            struct resource machineAvailableResources= m.getResources_();
            cout<<"["<<count<<"] ->"<<m.getId_()<<" - Recursos : {Nucleos: "<<machineAvailableResources.cores<<", RAM: "<<machineAvailableResources.ram<<"}\n";
            count++;
        }
    } else{
        cout<<"No tiene permisos para acceder al listado de maquinas\n";
    }



}

void System::showReservations(const string &userId){
    User currentUser = findUser(userId);
    //Creamos lista de reservas a las que el usuario tiene acceso teniendo en cuenta que los admin pueden verlas todas
    clearScreen("Lista de Reservas a las que tiene acceso");
    list <Reservation> reservations;
    list <Reservation>:: iterator i;

    for ( i = reservations_.begin(); i!=reservations_.end(); i++)
    {
        if(currentUser.getUserType_()>0){//Somos administrador de cualquier tipo
            reservations.push_back(*i);
        }else if(i->getUserId_()==userId) reservations.push_back(*i); //Somos usuario estandar y la reserva es nuestra
    }
    //Si no tenemos acceso a ninguna reserva terminamos modificacion
    if(reservations.empty()){
        cout<<"No tiene ninguna reserva a la que pueda acceder\n";
    }else{
    //ya tenemos la lista con las reservas a las que tenemos acceso, la mostramos por pantalla
        int count=0;
        for ( i = reservations.begin(); i!=reservations.end(); i++)
        {
            if(currentUser.getUserType_()>0){//Consulta un administrador y debemos mostrarle el login asociado a cada reserva, tenemos que obtener el login asociado a ese userId de la reserva
                User currentreservationUser = findUser(i->getUserId_());
                cout<<" ["<<count<<"] -{ Id reserva:"<<i->getId_()<<", Maquina:"<<i->getMachineId_()<<", Fecha inicio:"<<intToDate(i->getFirstDay_())<<", Fecha final:"<<intToDate(i->getLastDay_())<<", Nucleos:"<<i->getResources_().cores<<", RAM:"<<i->getResources_().ram<<", User:"<<currentreservationUser.getLogin_()<<"}\n";
            }else{
                //Vista de usuario normal 
                cout<<" ["<<count<<"] -{ Id reserva:"<<i->getId_()<<", Maquina:"<<i->getMachineId_()<<", Fecha inicio:"<<intToDate(i->getFirstDay_())<<", Fecha final:"<<intToDate(i->getLastDay_())<<", Nucleos:"<<i->getResources_().cores<<", RAM:"<<i->getResources_().ram<<"n";
            }  
            count++;      
        }
        cout<<"\n";
    }
}
