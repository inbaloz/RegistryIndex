#include "Constants_and_libraries.h"
#include "LatticeCreator.h"
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// input: a pointer to a atom array, and the 2d minimal size requirments.
// tubeOrLattice: 0 for tube, 1 for lattice

// output: the array pointed array lattice is filled with atoms, and
// an integer containing the amount of atoms in the lattice.

int LatticeCreator(Atom** lattice, double xMin, double yMin, double xMax, double yMax, 
				   int tubeOrLattice, int materialType)
{
	int i, j;					// Counters;
	int minLayer, maxLayer;		// The index of the first and last layer.
	int startLayer, endLayer;	// The index of the first and last pair of atmos in each layer.
	int firstAtom=0, secondAtom=0; // the types of the first and second atoms in the lattice that 
								// will make the tube (CNT or hBN).

	double materialHeight, materialHorizDistance, materialHorizShift, materialBondLength;

	// The amount of atoms in the lattice before cutting (the 2 stands for
	// placing the atoms in pairs):
	int latticeN;				
	int count = 0; 				// Counter for the atoms later on.

	if (tubeOrLattice == 0) {
		materialHeight = TUBE_HIGHT;
		materialHorizDistance = TUBE_HORIZD;
		materialHorizShift = TUBE_HORIZS;
		materialBondLength = TUBE_BL;
	} else {
		materialHeight = LATTICE_HIGHT;
		materialHorizDistance = LATTICE_HORIZD;
		materialHorizShift = LATTICE_HORIZS;
		materialBondLength = LATTICE_BL;
	}

	minLayer	 = 2 * (int)( (yMin / materialHeight) - 1.0 );
	maxLayer	 = 2 * (int)( (yMax / materialHeight) + 1.0 );
	startLayer	 = (int)( (xMin / materialHorizDistance) - 1.0 );
	endLayer	 = (int)( ( (xMax + materialHorizShift) / materialHorizDistance) + 1.0 ); 	// The end of layer condition
																// should be satisfied even for
																// the shifted layers.
	latticeN = 2 * (maxLayer - minLayer + 1) * (endLayer - startLayer + 1);
	*lattice = malloc(latticeN * sizeof(Atom));
	if (*lattice == NULL)
	{
		printf("A malloc has failed in the function Lattice_creator.\n");
		exit(1);
	}
	
	// To create the lattice we are scanning the hight (y axis),
	// in each hight layer we are placing the atoms in pairs.
	// Note that in each odd layer there needs to be a shift
	// in the horizontal axis (x axis) by materialHorizShift equals 1.5materialBondLength.

	// The function enables us to create CNTs and hBN tubes.

	if (materialType == 0) { // if tube is CNT
		firstAtom = C_type;
		secondAtom = C_type;
	} else if (materialType == 1) { // if tube is BN
		firstAtom = B_type;
		secondAtom = N_type;
	}

	for (i = minLayer; i <= maxLayer; i++)
	{
		for (j = startLayer; j <= endLayer; j++)
		{
			// First atom in the pair:
			(*lattice)[count].y = i * materialHeight / 2;
			(*lattice)[count].x = j * materialHorizDistance - ( (ABS(i) % 2) * (materialHorizShift) );
			(*lattice)[count].z = 0;
			(*lattice)[count].type = firstAtom;
			count++;
			// Second atom in the pair:
			(*lattice)[count].y = i * materialHeight / 2;
			(*lattice)[count].x = j * materialHorizDistance + materialBondLength - ( (ABS(i) % 2) * (materialHorizShift) );
			(*lattice)[count].z = 0;
			(*lattice)[count].type = secondAtom;
			count++;
		}
	}
	return latticeN;
}
