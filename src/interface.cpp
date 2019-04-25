#include "interface.hpp"

namespace Homomorphine 
{

  string Interface::getHost() 
  {
    return this->host;
  }
  
  void Interface::setHost(string host) 
  {
    this->host = host;
  }

  int Interface::getPort() 
  {
    return this->port;
  }
      
  void Interface::setPort(int port) 
  {
    this->port = port;
  }
    
  string Interface::getProtocol()
  {
    return this->protocol;
  }
    
  void Interface::setProtocol(string protocol) 
  {
    this->protocol = protocol;
  }
      
  string Interface::getBackend() 
  {
    return this->backend;
  }
      
  void Interface::setBackend(string backend) 
  {
    this->backend = backend;
  }

  std::ostream& operator<<(std::ostream &strm, const Interface &interface) 
  {
    strm << "-- host: " << interface.host << endl;
    strm << "-- port: " << interface.port << endl;
    strm << "-- protocol: " << interface.protocol << endl;
    strm << "-- backend: " << interface.backend << endl;

    return strm;
  } 
}