#include <string>
#include <iostream>

#ifndef _MORPHINE_INTERFACE_H_
#define _MORPHINE_INTERFACE_H_

using namespace std;

namespace Morphine 
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