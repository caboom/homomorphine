#ifndef _HOMOMORPHINE_BACKEND_H_
#define _HOMOMORPHINE_BACKEND_H_

#include <string>
#include <map>
#include <iostream>
#include <utility>
#include <exception>
#include <boost/algorithm/string.hpp>

using namespace std;

namespace homomorphine 
{
  
  class Backend
  {
    protected:
      map<string, string> params;

    public:
      virtual ~Backend() {}
      virtual void setAlgorithm(string algorithm) {}
      virtual void init() {}
      virtual string generateEncodedPublicKey() = 0;
      virtual string generateEncodedSecretKey() = 0;
      virtual pair<string, string> generateEncodedKeys() = 0;
      virtual vector<string> encrypt(string encoded_public_key, vector<int> values) = 0; 

      map<string, string> getParams();
      void setParams(map<string, string> &params); 
      string getParam(string key);
      void  setParam(string &key, string &value);
  };

  class BackendException : public std::exception 
  {
	  private:
      const char* msg;

    public:
      BackendException(const char* msg);

      const char* getMessage();
  };

}

#endif