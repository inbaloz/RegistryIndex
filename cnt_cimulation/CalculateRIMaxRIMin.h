#ifndef __CalculateRIMaxRIMin__
#define __CalculateRIMaxRIMin__

#include "Constants_and_libraries.h"
#include "Rotate.h"
#include "FindInteracting.h"
#include <math.h>

void CalculateRIMaxRIMin(double* RIMax, double* RIMin, Atom *surfaceLattice, int surfaceN, 
						 Atom* tube, int tubeN, double teta,
					 	 int tubeType, int latticeType, aVec T, aVec Ch, int tubeUnitN,
						 int unitcellN, double radius);

#endif