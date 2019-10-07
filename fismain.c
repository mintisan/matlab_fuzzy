/*
 * Stand-alone codes for fuzzy inference systems.
 * J.-S. Roger Jang, 1994.
 * Copyright 1994-2002 The MathWorks, Inc.
 */


/* Start of the regular fismain.c */
#include "fis.h"

/***********************************************************************
 Main routine
 **********************************************************************/

int
main(int argc, char **argv)
{
	FIS *fis;
	int i, j;
	int debug = 1;

	DOUBLE **dataMatrix, **fisMatrix, **outputMatrix;
	char *fis_file, *data_file;
	int data_row_n, data_col_n, fis_row_n, fis_col_n;

    data_file = "/Users/mintisan/GitHub/matlab_fuzzy/dataMatrixFile.txt";
    fis_file = "/Users/mintisan/GitHub/matlab_fuzzy/fisMatrixFile.txt";

	/* obtain data matrix and FIS matrix */
    dataMatrix = returnDataMatrix(data_file, &data_row_n, &data_col_n);
	fisMatrix = returnFismatrix(fis_file, &fis_row_n, &fis_col_n);

	/* build FIS data structure */
	fis = (FIS *)fisCalloc(1, sizeof(FIS));
	fisBuildFisNode(fis, fisMatrix, fis_col_n, MF_POINT_N);

	/* error checking */
	if (data_col_n < fis->in_n) {
		PRINTF("Given FIS is a %d-input %d-output system.\n",
			fis->in_n, fis->out_n);
		PRINTF("Given data file does not have enough input entries.\n");
		fisFreeMatrix((void **)dataMatrix, data_row_n);
		fisFreeMatrix((void **)fisMatrix, fis_row_n);
		fisFreeFisNode(fis);
		fisError("Exiting ...");
	}

	/* debugging */
	if (debug)
		fisPrintData(fis);

	/* create output matrix */
	outputMatrix = (DOUBLE **)fisCreateMatrix(data_row_n, fis->out_n, sizeof(DOUBLE));

	/* evaluate FIS on each input vector */
	for (i = 0; i < data_row_n; i++)
		getFisOutput(dataMatrix[i], fis, outputMatrix[i]);

	/* print output vector */
	for (i = 0; i < data_row_n; i++) {
		for (j = 0; j < fis->out_n; j++)
			PRINTF("%.12f ", outputMatrix[i][j]);
		PRINTF("\n");
	}

	/* clean up memory */
	fisFreeFisNode(fis);
	fisFreeMatrix((void **)dataMatrix, data_row_n);
	fisFreeMatrix((void **)fisMatrix, fis_row_n);
	fisFreeMatrix((void **)outputMatrix, data_row_n);

	getchar();
	exit(0);
}
