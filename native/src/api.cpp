#include "api.hpp"

namespace homomorphine
{

  //
  // ApiResponse class implementation
  //
      
  status_code ApiResponse::getStatus()
  {
    return this->status;
  }

  void ApiResponse::setStatus(status_code status)
  {
    this->status = status;
  }
  
  json::value ApiResponse::getContent()
  {
    return this->content;
  }

  void ApiResponse::setContent(json::value &content)
  {
    this->content = content;
  }

  //
  // Api class implementation
  //

  ApiResponse Api::get(vector<string> &path) {
    Backend* backend;
    ApiResponse response;
    json::value response_body;

    try 
    {
      backend = BackendFactory::create(path[0]);  
      backend->setAlgorithm(path[1]);
      backend->init();

      // generate a public key
      if (path[2] == "public_key") {
        response_body[U("public_key")] = json::value(backend->generateEncodedPublicKey());

        response.setStatus(status_codes::OK);
        response.setContent(response_body);
      }
      // generate a secret key
      else if (path[2] == "secret_key") {
        response_body[U("secret_key")] = json::value(backend->generateEncodedSecretKey());

        response.setStatus(status_codes::OK);
        response.setContent(response_body);
      }
      // generate both public and secret keys
      else if (path[2] == "keys") {
        pair<string, string> keys = backend->generateEncodedKeys();
        response_body[U("public_key")] = json::value(keys.first);
        response_body[U("secret_key")] = json::value(keys.second);

        response.setStatus(status_codes::OK);
        response.setContent(response_body);
      }
      // i don't know what are you actually trying to do ... 
      else {
        response_body[U("error")] = json::value(U("Unknown method " + path[2]));

        response.setStatus(status_codes::NotFound);
        response.setContent(response_body);
      }
    } 
    // error when initializing backend - return error
    catch(BackendException& e)
    {
      response_body[U("error")] = json::value(U("Failed to create backend"));
      BOOST_LOG_TRIVIAL(error) << "Failed to create backend: " << path[0]; 

      response.setStatus(status_codes::BadRequest);
      response.setContent(response_body);
    } 
    // whoops, now this is tricky...
    catch (exception& e) 
    {
      response_body[U("error")] = json::value(U("Failed to process the request"));
      BOOST_LOG_TRIVIAL(error) << "Failed to process the request";

      response.setStatus(status_codes::BadRequest);
      response.setContent(response_body);
    }

    return response;
  }

  ApiResponse Api::post(vector<string> &path, string body) {
    Backend* backend;
    ApiResponse response;
    json::value response_body;

    try 
    {
      json::value obj = json::value::parse(body);

      backend = BackendFactory::create(path[0]);  
      backend->setAlgorithm(path[1]);
      backend->init();

      // encrypt the value using a public key
      if (path[2] == "encrypt") {
        backend->setPublicKey(obj[U("public_key")].as_string());

        response_body[U("encrypted_value")] = json::value(
          backend->encryptValue(
            obj[U("value")].as_integer()
        ));

        response.setStatus(status_codes::OK);
        response.setContent(response_body);
      }
      // decrypt the value using a secret key
      if (path[2] == "decrypt") {
        backend->setPublicKey(obj[U("secret_key")].as_string());
        backend->setEncodedCipher(obj[U("encrypted_value")].as_string());

        response_body[U("value")] = json::value(backend->decrypt());
        response.setStatus(status_codes::OK);
        response.setContent(response_body);
      }
    } 
    catch(BackendException& e)
    {
      response_body[U("error")] = json::value(U("Failed to create backend"));
      BOOST_LOG_TRIVIAL(error) << "Failed to create backend: " << path[0]; 

      response.setStatus(status_codes::BadRequest);
      response.setContent(response_body);
    } 
    catch (exception& e) 
    {
      response_body[U("error")] = json::value(U("Failed to process the request"));
      BOOST_LOG_TRIVIAL(error) << "Failed to process the request: " << e.what();

      response.setStatus(status_codes::BadRequest);
      response.setContent(response_body);
    }

    return response;
  }

}