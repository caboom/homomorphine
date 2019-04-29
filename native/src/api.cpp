#include "api.hpp"

namespace homomorphine
{

  //
  // ApiResponse class implementation
  //

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

  //
  // Api class implementation
  //

  ApiResponse Api::get(vector<string> &path) {
    Backend* backend;
    ApiResponse response;

    try 
    {
      backend = BackendFactory::create(path[0]);  
      backend->setAlgorithm(path[1]);
      backend->init();

      // generate a public key
      if (path[2] == "public_key") {
        response.setStatus(status_codes::OK);
        response.setContent(backend->generateEncodedPublicKey());
      }
      // generate a secret key
      else if (path[2] == "secret_key") {
        response.setStatus(status_codes::OK);
        response.setContent(backend->generateEncodedSecretKey());
      }
      // generate both public and secret keys
      else if (path[2] == "keys") {
        response.setStatus(status_codes::OK);
        pair<string, string> keys = backend->generateEncodedKeys();
        response.setContent(keys.first + "\n\n" + keys.second);
      }
      // i don't know what are you actually trying to do ... 
      else {
        response.setStatus(status_codes::NotFound);
        response.setContent("Unknown method " + path[2]);
      }
    } 
    // error when initializing backend - return error
    catch(BackendException& e)
    {
      BOOST_LOG_TRIVIAL(error) << "Failed to create backend: " << path[0]; 
      response.setStatus(status_codes::BadRequest);
      response.setContent("Failed to create backend");
    } 
    // whoops, now this is tricky...
    catch (int e) 
    {
      BOOST_LOG_TRIVIAL(error) << "Failed to create backend: " << path[0];
      response.setStatus(status_codes::BadRequest);
      response.setContent("Failed to create backend");
    }

    return response;
  }

  ApiResponse Api::post(vector<string> &path, string body) {
    Backend* backend;
    ApiResponse response;
    json::value obj = json::value::parse(body);

    try 
    {
      if (path[2] == "encrypt") {
        response.setStatus(status_codes::OK);
        response.setContent(backend->generateEncodedPublicKey());
      }
    } 
    catch(BackendException& e)
    {
      BOOST_LOG_TRIVIAL(error) << "Failed to create backend: " << path[0]; 
      response.setStatus(status_codes::BadRequest);
      response.setContent("Failed to create backend");
    } 
    catch (exception& e) 
    {
      BOOST_LOG_TRIVIAL(error) << "Failed to create backend: " << path[0];
      response.setStatus(status_codes::BadRequest);
      response.setContent("Failed to create backend");
    }

    return response;
  }

}