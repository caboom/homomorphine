#ifndef _HOMOMORPHINE_SERVER_H_
#define _HOMOMORPHINE_SERVER_H_

#include <cpprest/http_listener.h>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup.hpp>

#include "api.hpp"
#include "config.hpp"
#include "interface.hpp"

using namespace std;
using namespace web::http::experimental::listener;
using namespace web::http;
using namespace web;

namespace homomorphine 
{
  /*! /brief Homomorphine RESTFul service
   *
   * This class implements a RESTFul service that can be used to
   * test various aspects of Homomorphine functionalities. This
   * service is not intended for a production usage.
   */
  class Server {
    private:
      Config config;                                                   /*!< service configuration */
      map<string, http_listener> listeners;                            /*!< active service HTTP listeners */
      vector<string> get_methods {"public_key", "secret_key", "keys"}; /*!< supported GET paths */

      /*!
       * Starts the HTTP service on a specific interface
       * 
       * \param interface HTTP interface
       * \return HTTP listener
       */ 
      http_listener startService(Interface &interface);  

      /*!
       * Stops the HTTP service on a specific listener
       * 
       * \param listener HTTP listener
       */                
      void stopService(http_listener &listener);

      /*!
       * Implements a HTTP GET handler
       * 
       * \param message HTTP request message
       */
      void handle_get(http_request message);

      /*!
       * Implements a HTTP POST handler
       * 
       * \param message HTTP request message
       */
      void handle_post(http_request message);

      /*!
       * Basic validation of a HTTP request
       * 
       * \param message HTTP request GET path
       * \return validation result
       */
      pair<status_code, string> checkRequest(vector<string> &path);

    public:

      /*!
       * Initialization of Homomorphine RESTFul service
       * 
       * \param config service configuration
       */
      void init(Config &config);

      /*!
       * Start RESTFul service
       */
      void run();

      /*!
       * Stop RESTFul service
       */
      void stop();
  };
}

#endif