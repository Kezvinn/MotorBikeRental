#ifndef REQUEST_H
#define REQUEST_H
#include <bits/stdc++.h>
std::string static RQST_STATUS[3] = {"Pending", "Accepted", "Declined"};
std::string static REV_STATUS[2]={"Not_Reviewed", "Reviewed"};
class Request {
   private:
      std::string requestID;
      std::string renterID;
      std::string rentbikeID;
      std::string startDate;
      std::string endDate;
      std::string rqst_status;   
      std::string memRevStatus;  //for mem review
      std::string bikeRevStatus; //for bike review
      int totalCost;
   public:
      Request(std::string i_requestID, std::string i_renterID, std::string i_rentBikeID,
              std::string i_startDate, std::string i_endDate,
              int i_totalCost, std::string i_rqst_status, 
              std::string i_memRevStatus, std::string i_bikeRevStatus);
      friend class Member;
};
std::string rqstIDGenerate();

#endif