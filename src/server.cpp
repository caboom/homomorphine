#include "server.hpp"

namespace Morphine 
{
  void Server::init(Config &config) 
  {
    this->config = config;
  }

  void Server::run() 
  {
    BOOST_LOG_TRIVIAL(info) << "Starting " << this->config.interfacesSize() << " interfaces...";

    // initialize and start all the service listeners 
    for (auto& [name, interface] : this->config.getInterfaces()) {
      BOOST_LOG_TRIVIAL(info) << "Initializing interface: " << name;
      this->listeners[name] = this->startService(interface);
    }
  }

  void Server::stop() {
    // stop all the service listeners
    for(auto& [name, listener]: this->listeners) {
      BOOST_LOG_TRIVIAL(info) << "Stopping service: " << name;
      this->stopService(listener);
    }

    this->listeners.clear();
  }

  http_listener Server::startService(Interface &interface) 
  {
    string uri = interface.getProtocol() + "://" + 
        interface.getHost() + ":" + 
        to_string(interface.getPort());

    BOOST_LOG_TRIVIAL(info) << "Starting service at: " << uri;

    http_listener listener(U(uri));
	  listener.open().wait();

    return listener;
  }

  void Server::stopService(http_listener &listener) 
  {
    listener.close().wait();
  }
}