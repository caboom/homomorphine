#ifndef _HOMOMORPHINE_API_H_
#define _HOMOMORPHINE_API_H_

#include <map>
#include <vector>
#include <string>
#include <utility>
#include <iostream>

#include <boost/log/trivial.hpp>
#include <boost/lexical_cast.hpp>
#include <cpprest/http_listener.h>

#include "arithmetic_backend.hpp"
#include "arithmetic_backend_factory.hpp"

using namespace std;
using namespace web;
using namespace web::http;

namespace homomorphine 
{
  /*! /brief RESTFul API response.
   *  
   *  Simple API response wrapper used by Homomorphine RESTFul API
   */
  class ApiResponse
  {
    private:
      status_code status = status_codes::OK; /*!< API response status code */
      json::value content;                   /*!< API response content in JSON format */

    public:

      /*!
       * Returns the status of the response.
       * 
       * \return response status code
       */
      status_code getStatus();

      /*!
       * Sets the status of the response.
       * 
       * \param status API response status code
       */
      void setStatus(status_code status);

      /*!
       * Returns the full JSON content of the API response .
       * 
       * \return JSON object of API response
       */
      json::value getContent();
      
      /*!
       * Sets the content of the API response in the format of JSON object.
       * 
       * \param content JSON object 
       */
      void setContent(json::value &content);
  };

  /*! /brief Provides a RESTFul API interface.
   *   
   * This class provides a RESTFul API interface for Homomorphine,
   * it is very simple and does not expose a full functionality of 
   * Homomorphine, but rather selected group of functionalities. 
   * It is not advised to use this interface except for testing 
   * Homomorphine functionalities (RESTFul interface will be provided
   * by the Golang wrapper around Homomorphine).
   */
  class Api
  {
    private:
      /*!
       * Extracts the vector of values from JSON array.
       *  
       * \param values JSON array of values
       * \return vector of values extracted from JSON array
       */
      vector<long> extractJSONValues(json::array values);
      /*!
       * Packages JSON array from the vector of vcalues.
       *  
       * \param values vector of values
       * \return vector JSON array packaged from the vector of values
       */
      json::value packageJSONValues(vector<long> values);

    public:

      /*!
       * Handler for processing GET HTTP requests.
       * 
       * \param path full path of the HTTP request
       * \return API response
       */
      ApiResponse get(vector<string> &path);

      /*!
       * Handler for processing POST HTTP requests.
       * 
       * \param path full path of the HTTP request
       * \param body content of the body of HTTP requrest
       * \return API response
       */
      ApiResponse post(vector<string> &path, string body);
  };
}

#endif