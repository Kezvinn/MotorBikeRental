#include "Admin.h"
Admin::Admin(){
    std::cout << "Admin default constructor" << std::endl;
};
Admin::Admin(std::string adUsername, std::string adPassword)
    : User(adUsername, adPassword){};