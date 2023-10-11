#ifndef REQUEST_H
#define REQUEST_H
#include <bits/stdc++.h>
std::string static RQST_STATUS[3] = {"Pending", "Accepted", "Declined"};
class Request {
   private:
      std::string requestID;
      std::string renterID;
      std::string rentbikeID;
      std::string startDate;
      std::string endDate;
      std::string rqst_status;
   public:
      Request();
      Request(std::string i_requestID, std::string i_renterID, std::string i_rentBikeID,
              std::string i_startDate, std::string i_endDate, std::string i_rqst_status);
      friend class Member;
};
std::string rqstIDGenerate();

#endif