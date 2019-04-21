#include <iostream>
#include <iomanip>
#include <sstream>
#include <thread>
#include <chrono>
#include <ctime>
#include <signal.h>
#include <cpprest/http_listener.h>

#include "config.hpp"
#include "interface.hpp"

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
      map<string, http_listener> listeners;

      http_listener startService(Interface &interface);
      void stopService(http_listener &listener);

    public:
      void init(Config &config);
      void run();
      void stop();
  };
}

#endif