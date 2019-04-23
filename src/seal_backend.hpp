#include <iostream>

#include "backend.hpp"

#ifndef _MORPHINE_SEAL_BACKED_H_
#define _MORPHINE_SEAL_BACKED_H_

namespace Morphine 
{
  class SealBackend : public Backend
  {
    public:
      ~SealBackend();
  };
}

#endif