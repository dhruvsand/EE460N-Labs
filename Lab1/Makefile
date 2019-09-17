CC=-std=c99
FILE=assembler.c
OFILE=assemble

INP=ThisGoesIn.asm
OUTP=ThisComesOut.obj


assemblemake: ${FILE}
	gcc ${CC} -o ${OFILE} ${FILE}

run: ${OFILE}
	./${OFILE} ${INP} ${OUTP}

clean: ${OFILE}
	rm ${OFILE}
