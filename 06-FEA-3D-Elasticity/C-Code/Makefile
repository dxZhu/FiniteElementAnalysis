CFLAGS         = -I.
LIBS      = -lstdc++ -lm -llapack -lblas -lgfortran 
ARMA_DIR  = /software/armadillo_OpenBlas-4.400.1/usr/local/include/
ARMALIB   = -I ${ARMA_DIR} -DARMA_DONT_USE_WRAPPER

CC		= g++

DEPS		= MainFile.h
OBJ 		= MainFile.o \
		ReadInput.o \
		InitializeEquation.o\
		PrintEQNUM.o \
		AssembleModule.o \
		AssemblePrescribedDisplacement.o \
		AssembleGlobalForceVector.o \
		AssemblePrescribedTraction.o \
		ElementSurfaceTraction.o \
		GaussQuadrature.o \
		Quad2DShapeFunctions.o \
		AssembleGlobalStiffness.o \
		ElementAssemble.o \
		GetMaterialMatrix.o \
		PrintMatrices.o \
		SolveModule.o \
		PrintSolution.o \
		EvaluateFieldGradient.o \
		GetElementFluxVector.o \
		PrintPostProcessingResults.o	


%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) ${ARMALIB}

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) ${ARMALIB}

MainFile: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS) ${ARMALIB}

.PHONY: clean

clean:
	rm -f *.o *~ U*.dat P*.dat K*.dat EQNUM.dat



