#include "api.hpp"

namespace homomorphine
{
  ApiResponse::~ApiResponse()
  {
    this->header.clear();
  }
      
  status_code ApiResponse::getStatus()
  {
    return this->status;
  }

  void ApiResponse::setStatus(status_code status)
  {
    this->status = status;
  }
  
  string ApiResponse::getContent()
  {
    return this->content;
  }

  void ApiResponse::setContent(string content)
  {
    this->content = content;
  }
      
  string ApiResponse::getHeaderElement(string &key)
  {
    return this->header[key];
  }
  
  void ApiResponse::setHeaderElement(string &key, string& value)
  {
    this->header[key] = value;
  }
      
  map<string, string> ApiResponse::getHeader()
  {
    return this->header;
  }

  ApiResponse Api::get(vector<string> &path) {
    Backend* backend;
    ApiResponse response;

    try 
    {
      backend = BackendFactory::create(path[0]);  
      backend->setAlgorithm(path[1]);
      backend->init();

      if (path[2] == "public_key") {
        response.setStatus(status_codes::OK);
        response.setContent(backend->generateEncodedPublicKey());
      }
      else if (path[2] == "secret_key") {
        response.setStatus(status_codes::OK);
        response.setContent(backend->generateEncodedSecretKey());
      }
      else if (path[2] == "keys") {
        response.setStatus(status_codes::OK);
        pair<string, string> keys = backend->generateEncodedKeys();
        response.setContent(keys.first + "\n\n" + keys.second);
      }
      else {
        response.setStatus(status_codes::NotFound);
        response.setContent("Unknown method " + path[2]);
      }
    } catch(BackendException& e)
    {
      BOOST_LOG_TRIVIAL(error) << "Failed to create backend: " << path[0]; 
      response.setStatus(status_codes::BadRequest);
      response.setContent("Failed to create backend");
    } catch (exception& e) {
      BOOST_LOG_TRIVIAL(error) << "Failed to create backend: " << path[0];
      response.setStatus(status_codes::BadRequest);
      response.setContent("Failed to create backend");
    }

    return response;
  }

}