#include <string>
#include <boost/algorithm/string.hpp>

using namespace std;

#ifndef _MORPHINE_BACKEND_H_
#define _MORPHINE_BACKEND_H_

namespace Morphine 
{

  class Backend
  {
    public:
      virtual ~Backend() {}
  };

}

#endif