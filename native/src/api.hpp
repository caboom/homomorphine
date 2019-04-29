#ifndef _HOMOMORPHINE_API_H_
#define _HOMOMORPHINE_API_H_

#include <map>
#include <vector>
#include <string>
#include <utility>
#include <iostream>

#include <boost/log/trivial.hpp>
#include <cpprest/http_listener.h>

#include "backend.hpp"
#include "backend_factory.hpp"

using namespace web::http;
using namespace web;

using namespace std;

namespace homomorphine 
{
  class ApiResponse
  {
    private:
      status_code status = status_codes::OK;
      json::value content;

    public:
      status_code getStatus();
      void setStatus(status_code status);
      json::value getContent();
      void setContent(json::value &content);
  };

  class Api
  {
    public:
      ApiResponse get(vector<string> &path);
      ApiResponse post(vector<string> &path, string body);
  };
}

#endif