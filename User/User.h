#ifndef USER_H
#define  USER_H
#include <bits/stdc++.h>
class User {
   private:
      std::string username;
      std::string password;
   public:
      User();
      User(std::string i_username, std::string i_password);
      std::string get_username();
      std::string get_password();
      // friend class System;
      // friend class Member;
};

#endif // USER_H