#include <iostream>
#include <iomanip>
#include <sstream>
#include <thread>
#include <chrono>
#include <ctime>
#include <cpprest/http_listener.h>

#include "config.hpp"

#ifndef _MORPHINE_SERVER_H_
#define _MORPHINE_SERVER_H_

using namespace std;
using namespace web::http::experimental::listener;
using namespace web::http;
using namespace web;

namespace Morphine 
{
  class Server {
    private:
      Config config;

    public:
      void init(Config &config);
      void run();
  };
}

#endif