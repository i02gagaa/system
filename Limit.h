#ifndef LIMIT_H
#define LIMIT_H

#include "Machine.h"//Para el strcut resource

#include <string>
using namespace std;


class Limit
{
private:
    string id_;



    int maxDays_;



    struct resource maxResources_;
public:
    Limit();
    ~Limit();
    
    inline string getId_() const {return this->id_;}
    inline void setId_(string id_) {this->id_ = id_; }
    
    inline int getMaxDays_() const {return this->maxDays_;}
    inline void setMaxDays_(int maxDays_) {this->maxDays_ = maxDays_;}

    inline struct resource getMaxResources_() const  {return this->maxResources_;}
    inline void setMaxResources_(struct resource maxResources_) {this->maxResources_ = maxResources_;}

};





#endif