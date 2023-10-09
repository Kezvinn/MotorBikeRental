#include "User.h"

User::User(){
    std::cout << "User default constructor" << std::endl;
};
User::User(std::string i_username, std::string i_password)
    : username(i_username), password(i_password){};