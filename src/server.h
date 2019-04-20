#include <string>
#include <iostream>

#include "config.h"

#ifndef _MORPHINE_SERVER_H_
#define _MORPHINE_SERVER_H_

using namespace std;

namespace Morphine 
{
  class Server {
    private:
      Config config;

    public:
      void init(Config &config);
      void run();
  };
}

#endif