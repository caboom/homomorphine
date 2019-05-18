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
        backend->generateKeys();
        response_body[U("public_key")] = json::value(backend->getPublicKey());

        response.setStatus(status_codes::OK);
        response.setContent(response_body);
      }
      // generate a secret key
      else if (path[2] == "secret_key") {
        backend->generateKeys();
        response_body[U("secret_key")] = json::value(backend->getSecretKey());

        response.setStatus(status_codes::OK);
        response.setContent(response_body);
      }
      // generate both public and secret keys
      else if (path[2] == "keys") {
        backend->generateKeys();
        response_body[U("public_key")] = json::value(backend->getPublicKey());
        response_body[U("secret_key")] = json::value(backend->getSecretKey());

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
        vector<uint64_t> values = this->extractJSONValues(obj[U("values")].as_array());

        response_body[U("encrypted_value")] = json::value(backend->encrypt(values));

        response.setStatus(status_codes::OK);
        response.setContent(response_body);
      }
      // decrypt the value using a secret key
      if (path[2] == "decrypt") {
        backend->setPublicKey(obj[U("secret_key")].as_string());
        backend->setCipher(obj[U("encrypted_value")].as_string());
        
        response_body[U("values")] = this->packageJSONValues(backend->decryptValues());
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

  vector<uint64_t> Api::extractJSONValues(json::array values)
  {
    vector<uint64_t> result;

    for (int i = 0; i< values.size(); i++) {
      result.push_back(stoull(values[i].as_string()));
    }

    return result; 
  }

  json::value Api::packageJSONValues(vector<uint64_t> values)
  {
    json::value result = json::value::array();

    for(int i = 0; i < values.size(); i++) {
      result[i] = json::value::string(U(boost::lexical_cast<std::string>(values.at(i))));
    }

    return result;
  }

}