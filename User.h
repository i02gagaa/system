#ifndef USER_H
#define USER_H

#include "Limit.h"

#include <string>
using namespace std;

class User
{
private:
    string id_;
    int userType_;
    string name_;
    string login_;
    string password_;
    string limitId_;


public:
    User();
    ~User();

    inline string getId_() const {return this->id_;}
    inline void setId_(string id_) {this->id_ = id_;}

    inline int getUserType_() const {	return this->userType_;}
    void setUserType_(int userType_) {	this->userType_ = userType_;}

    inline string getName_() const {	return this->name_;}
    inline void setName_(string name_) {	this->name_ = name_;}

    inline string getLogin_() const {	return this->login_;}
    inline void setLogin_(string login_) {	this->login_ = login_;}

    inline string getPassword_()const  {	return this->password_;}
    inline void setPassword_(string password_) {	this->password_ = password_;}

    inline string getLimitId_() const {	return this->limitId_;}
    inline void setLimitId_(string limitId_) {	this->limitId_ = limitId_;}


};














#endif