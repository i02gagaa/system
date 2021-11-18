#ifndef RESERVATION_H
#define RESERVATION_H

#include "User.h"
#include "Machine.h"

#include <string>
using namespace std;

class Reservation
{
private:
    string id_;
    int firstDay_;
    int lastDay_;
    struct resource resources_;
    string userId_;
    string machineId_;


public:
    Reservation();
    ~Reservation();



    inline string getId_()const {return this->id_;}
    inline void setId_(string id_){this->id_ = id_;}

    inline int getFirstDay_()const {return this->firstDay_;}
    inline void setFirstDay_(int firstDay_){this->firstDay_ = firstDay_;}

    inline int getLastDay_()const {return this->lastDay_;}
    inline void setLastDay_(int lastDay_){this->lastDay_ = lastDay_;}

    inline struct resource getResources_()const {return this->resources_;}
    inline void setResources_(struct resource resources_){this->resources_ = resources_;}

    inline string getUserId_()const {return this->userId_;}
    inline void setUserId_(string userId_){this->userId_ = userId_;}


    inline string getMachineId_()const {return this->machineId_;}
    inline void setMachineId_(string machineId_){this->machineId_ = machineId_;}
};












#endif