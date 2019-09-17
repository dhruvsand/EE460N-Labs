
touch add.o
touch data.o
touch except_unaligned.o
touch int.o
touch except_prot.o
touch except_unknown.o
touch vector_table.o
touch dumpsim

dos2unix add.asm
dos2unix data.asm 
dos2unix except_unaligned.asm
dos2unix int.asm
dos2unix except_prot.asm
dos2unix except_unknown.asm
dos2unix vector_table.asm

./assembler.linux add.asm add.o
./assembler.linux data.asm data.o
./assembler.linux except_unaligned.asm except_unaligned.o
./assembler.linux int.asm int.o
./assembler.linux except_prot.asm except_prot.o
./assembler.linux except_unknown.asm except_unknown.o
./assembler.linux vector_table.asm vector_table.o


gcc -std=c99 -Wall -Wextra -ansi -o simulate -g lc3bsim4.c

./simulate ucode4 add.o data.o except_prot.o except_unaligned.o except_unknown.o int.o vector_table.o

submit-ee360n add.asm except_unaligned.asm int.asm ucode4 dumpsim vector_table.asm except_prot.asm except_unknown.asm lc3bsim4.c data.asm
