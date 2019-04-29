#include "server.hpp"

namespace homomorphine 
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

    listener.support(methods::GET, std::bind(&Server::handle_get, this, std::placeholders::_1));
    listener.support(methods::POST, std::bind(&Server::handle_post, this, std::placeholders::_1));

    return listener;
  }

  void Server::stopService(http_listener &listener) 
  {
    listener.close().wait();
  }

  void Server::handle_get(http_request message)
  {
    Api api;
    auto path = http::uri::split_path(http::uri::decode(message.relative_uri().path()));
    auto [status, content] = checkRequest(path);

    if (status != status_codes::OK) {
      message.reply(status, content);
    }
    else {
      BOOST_LOG_TRIVIAL(info) << "GET request: " << path[0] << " -> " << path[1];

      ApiResponse response = api.get(path);
      message.reply(response.getStatus(), response.getContent());
    }
  }

  void Server::handle_post(http_request message)
  {
    Api api;
    auto path = http::uri::split_path(http::uri::decode(message.relative_uri().path()));
    auto [status, content] = checkRequest(path);

    if (status != status_codes::OK) {
      message.reply(status, content);
    }
    else {
      BOOST_LOG_TRIVIAL(info) << "GET request: " << path[0] << " -> " << path[1];

      ApiResponse response = api.post(path, message.extract_string().get());
      message.reply(response.getStatus(), response.getContent());
    }
  }

  pair<status_code, string> Server::checkRequest(vector<string> &path)
  {
    if (path.size() < 1) {
      return std::make_pair(status_codes::NotFound, "Backend not set");
    }
    else if (path.size() < 2) {
      return std::make_pair(status_codes::NotFound, "Algorithm not set");
    }
    else if (path.size() < 3) {
      return std::make_pair(status_codes::NotFound, "Method not set");
    }

    return std::make_pair(status_codes::OK, "");
  }

}