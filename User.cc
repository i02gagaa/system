#include "User.h"

#include <string>
using namespace std;


User::User():id_("defaultUId"),userType_(0),name_("default"),login_("default"),password_("default"),limitId_("defaultLId"){}

User::~User()
{
}