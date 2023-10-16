#ifndef USER_H
#define  USER_H
#include <bits/stdc++.h>
class User {
   private:
      std::string username;
      std::string password;
   public:
      User(std::string i_username, std::string i_password);
      friend class System;
      friend class Member;
};

#endif // USER_H