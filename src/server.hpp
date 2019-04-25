#include <cpprest/http_listener.h>

#include "config.hpp"
#include "interface.hpp"

#ifndef _HOMOMORPHINE_SERVER_H_
#define _HOMOMORPHINE_SERVER_H_

using namespace std;
using namespace web::http::experimental::listener;
using namespace web::http;
using namespace web;

namespace Homomorphine 
{
  class Server {
    private:
      Config config;
      map<string, http_listener> listeners;

      http_listener startService(Interface &interface);
      void stopService(http_listener &listener);

      void handle_get(http_request message);
      void handle_put(http_request message);
      void handle_post(http_request message);

    http_listener m_listener;

    public:
      void init(Config &config);
      void run();
      void stop();
  };
}

#endif