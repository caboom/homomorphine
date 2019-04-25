#ifndef _HOMOMORPHINE_INTERFACE_H_
#define _HOMOMORPHINE_INTERFACE_H_

#include <string>
#include <iostream>

using namespace std;

namespace Homomorphine 
{
  class Interface {
    private:
      string host;
      int port;
      string protocol;
      string backend;

      friend std::ostream& operator<<(std::ostream&, const Interface&);

    public:
      string getHost();
      void setHost(string host);
      int getPort();
      void setPort(int port);
      string getProtocol();
      void setProtocol(string protocol); 
      string getBackend();
      void setBackend(string backend);
  };
}

#endif