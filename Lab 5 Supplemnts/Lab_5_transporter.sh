FNAME1=lc3bsim5.c
FNAME2=ucode5
#FNAME1=pagetable.asm
#FNAME2=pagetable.o

cd ~/Desktop

scp ${FNAME1} ${FNAME2} dsandesara@kamek.ece.utexas.edu:~/EE460N/lab5

ssh dsandesara@kamek.ece.utexas.edu

#cd EE460N/lab2

#./${FNAME1} ${FNAME2} ${FNAME3}

#exit



