#include "User.h"
User::User(std::string i_username, std::string i_password)
    : username(i_username), password(i_password){};

std::string User::get_username(){
    return this->username;
}
std::string User::get_password(){
    return this->password;
}