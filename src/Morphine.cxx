#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "MorphineConfig.h"
 
int main (int argc, char *argv[])
{
  fprintf(stdout,"%s Version %d.%d\n",
          argv[0],
          Tutorial_VERSION_MAJOR,
          Tutorial_VERSION_MINOR);
}