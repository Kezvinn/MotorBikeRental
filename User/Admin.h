#ifndef ADMIN_H
#define ADMIN_H
#include <bits/stdc++.h>
#include "User.h"
class Admin : public User {
   public:
      Admin();
      Admin(std::string adUsername, std::string adPassword);
      friend class System;
};
#endif