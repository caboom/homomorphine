#include <iostream>

#ifndef _MORPHINE_SEAL_BACKED_H_
#define _MORPHINE_SEAL_BACKED_H_

#include "backend.hpp"

namespace Morphine 
{
  class SealBackend : public Backend
  {
    public:
      ~SealBackend();
  };
}

#endif