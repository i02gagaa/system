#ifndef MACHINE_H
#define MACHINE_H


#include <string>
using namespace std;

struct resource
{
    int cores;
    int ram;
};


class Machine
{
private:
    string id_;
    struct resource resources_;

public:
    Machine();
    ~Machine();
    inline string getId_()const {return this->id_;}
    inline void setId_(string id_){    this->id_ = id_;}
    inline struct resource getResources_()const {    return this->resources_;}
    inline void setResources_(struct resource resources_){    this->resources_ = resources_;}
};










#endif