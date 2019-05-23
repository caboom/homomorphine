#ifndef _HOMOMORPHINE_INTERFACE_H_
#define _HOMOMORPHINE_INTERFACE_H_

#include <string>
#include <iostream>

using namespace std;

namespace homomorphine 
{
  /*! /brief RESTFul service network interface configuration.
   *
   * This class provides the network interface configuration for
   * Homomorphine RESTFul interface.
   */
  class Interface {
    private:
      string host;     /*!< interface host */
      int port;        /*!< interface port */
      string protocol; /*!< interface protocol */
      string backend;  /*!< interface backend (i.e. SEAL, HELib, etc.) */

      friend std::ostream& operator<<(std::ostream&, const Interface&);

    public:
      /*!
       * Returns interface host(name), or IP
       * 
       * \return interfafce host
       */
      string getHost();

      /*!
       * Sets the interface host
       * 
       * \param host interface host
       */
      void setHost(string host);

      /*!
       * Returns interface port
       * 
       * \return interface port
       */
      int getPort();

      /*!
       * Sets the interface port
       * 
       * \param port interface port
       */
      void setPort(int port);

      /*!
       * Returns interface protocol
       * 
       * \return interface protocol
       */
      string getProtocol();

      /*!
       * Sets the interface protocol
       * 
       * \param protocol interface protocol
       */
      void setProtocol(string protocol); 

      /*!
       * Returns interface backend
       * 
       * \return interface backend
       */
      string getBackend();

      /*!
       * Sets the interface backend
       * 
       * \param backend interface backend
       */
      void setBackend(string backend);
  };
}

#endif