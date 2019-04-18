#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "MorphineInfo.h"
 
int main (int argc, char *argv[])
{
  fprintf(stdout,"%s Version %d.%d\n",
          argv[0],
          MORPHINE_VERSION_MAJOR,
          MORPHINE_VERSION_MINOR);
}