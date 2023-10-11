#include "Request.h"
std::string rqstIDGenerate(){
   srand(time(NULL));
   int num = rand() % 1001; //random number form 0-1000
   return ("Rqst-" + std::to_string(num));
}

Request::Request(){};
Request::Request(std::string i_requestID, std::string i_renterID, std::string i_rentBikeID,
                 std::string i_startDate, std::string i_endDate, std::string i_rqst_status)
    : requestID(i_requestID), renterID(i_renterID), rentbikeID(i_rentBikeID),
      startDate(i_startDate), endDate(i_endDate), rqst_status(i_rqst_status){};

