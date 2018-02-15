
#include "filter.h"

int nrBeforeAveraging;

float FilterClass::smoothing(float average, int size, float value) {
  nrBeforeAveraging ++;
  if (nrBeforeAveraging > size){
       return (size * average + value ) / (size + 1);
  } else {
    return value;
  }
}

FilterClass FILTER;
