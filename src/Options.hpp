#include <iostream> 
#include <unordered_map> 
#include <boost/algorithm/string.hpp>

#ifndef _MORPHINE_OPTIONS_H_
#define _MORPHINE_OPTIONS_H_

using namespace std;

namespace Morphine 
{
  class Options 
  {
    private:
      unordered_map<string, string> options;

    public:
      string getOption(string option) {
        return options[option];
      }

      void setOption(string option, string value) {
        options[option] = value;
      }
  };
}

#endif