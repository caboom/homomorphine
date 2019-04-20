#include "server.hpp"

namespace Morphine 
{
  void Server::init(Config &config) 
  {
    this->config = config;
  }

  void Server::run() 
  {
    BOOST_LOG_TRIVIAL(info) << "Starting service interfaces...";

    for (auto& [key, value] : config.getInterfaces()) {
      
    }
  }
}