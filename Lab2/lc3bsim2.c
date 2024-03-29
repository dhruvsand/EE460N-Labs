/*
    Remove all unnecessary lines (including this one) 
    in this comment.
    REFER TO THE SUBMISSION INSTRUCTION FOR DETAILS

    Name 1: Dhruv Sandesara
    Name 2: Ayush Srivastava
    UTEID 1: djs3967
    UTEID 2: as79973
*/

/***************************************************************/
/*                                                             */
/*   LC-3b Instruction Level Simulator                         */
/*                                                             */
/*   EE 460N                                                   */
/*   The University of Texas at Austin                         */
/*                                                             */
/***************************************************************/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***************************************************************/
/*                                                             */
/* Files: isaprogram   LC-3b machine language program file     */
/*                                                             */
/***************************************************************/

/***************************************************************/
/* These are the functions you'll have to write.               */
/***************************************************************/

void process_instruction();

/***************************************************************/
/* A couple of useful definitions.                             */
/***************************************************************/
#define FALSE 0
#define TRUE  1

/***************************************************************/
/* Use this to avoid overflowing 16 bits on the bus.           */
/***************************************************************/
#define Low16bits(x) ((x) & 0xFFFF)
#define Low8bits(x) ((x) & 0xFF)
#define SignedExtend (val,bits) ((val<<(32-bits))>>(32-bits))

/***************************************************************/
/* Main memory.                                                */
/***************************************************************/
/* MEMORY[A][0] stores the least significant byte of word at word address A
   MEMORY[A][1] stores the most significant byte of word at word address A 
*/

#define WORDS_IN_MEM    0x08000 
int MEMORY[WORDS_IN_MEM][2];

/***************************************************************/

/***************************************************************/

/***************************************************************/
/* LC-3b State info.                                           */
/***************************************************************/
#define LC_3b_REGS 8

int RUN_BIT;	/* run bit */


typedef struct System_Latches_Struct{

  int PC,		/* program counter */
    N,		/* n condition bit */
    Z,		/* z condition bit */
    P;		/* p condition bit */
  int REGS[LC_3b_REGS]; /* register file. */
} System_Latches;

/* Data Structure for Latch */

System_Latches CURRENT_LATCHES, NEXT_LATCHES;

/***************************************************************/
/* A cycle counter.                                            */
/***************************************************************/
int INSTRUCTION_COUNT;

/***************************************************************/
/*                                                             */
/* Procedure : help                                            */
/*                                                             */
/* Purpose   : Print out a list of commands                    */
/*                                                             */
/***************************************************************/
void help() {                                                    
  printf("----------------LC-3b ISIM Help-----------------------\n");
  printf("go               -  run program to completion         \n");
  printf("run n            -  execute program for n instructions\n");
  printf("mdump low high   -  dump memory from low to high      \n");
  printf("rdump            -  dump the register & bus values    \n");
  printf("?                -  display this help menu            \n");
  printf("quit             -  exit the program                  \n\n");
}

/***************************************************************/
/*                                                             */
/* Procedure : cycle                                           */
/*                                                             */
/* Purpose   : Execute a cycle                                 */
/*                                                             */
/***************************************************************/
void cycle() {                                                

  process_instruction();
  CURRENT_LATCHES = NEXT_LATCHES;
  INSTRUCTION_COUNT++;
}

/***************************************************************/
/*                                                             */
/* Procedure : run n                                           */
/*                                                             */
/* Purpose   : Simulate the LC-3b for n cycles                 */
/*                                                             */
/***************************************************************/
void run(int num_cycles) {                                      
  int i;

  if (RUN_BIT == FALSE) {
    printf("Can't simulate, Simulator is halted\n\n");
    return;
  }

  printf("Simulating for %d cycles...\n\n", num_cycles);
  for (i = 0; i < num_cycles; i++) {
    if (CURRENT_LATCHES.PC == 0x0000) {
	    RUN_BIT = FALSE;
	    printf("Simulator halted\n\n");
	    break;
    }
    cycle();
  }
}

/***************************************************************/
/*                                                             */
/* Procedure : go                                              */
/*                                                             */
/* Purpose   : Simulate the LC-3b until HALTed                 */
/*                                                             */
/***************************************************************/
void go() {                                                     
  if (RUN_BIT == FALSE) {
    printf("Can't simulate, Simulator is halted\n\n");
    return;
  }

  printf("Simulating...\n\n");
  while (CURRENT_LATCHES.PC != 0x0000)
    cycle();
  RUN_BIT = FALSE;
  printf("Simulator halted\n\n");
}

/***************************************************************/ 
/*                                                             */
/* Procedure : mdump                                           */
/*                                                             */
/* Purpose   : Dump a word-aligned region of memory to the     */
/*             output file.                                    */
/*                                                             */
/***************************************************************/
void mdump(FILE * dumpsim_file, int start, int stop) {          
  int address; /* this is a byte address */

  printf("\nMemory content [0x%.4x..0x%.4x] :\n", start, stop);
  printf("-------------------------------------\n");
  for (address = (start >> 1); address <= (stop >> 1); address++)
    printf("  0x%.4x (%d) : 0x%.2x%.2x\n", address << 1, address << 1, MEMORY[address][1], MEMORY[address][0]);
  printf("\n");

  /* dump the memory contents into the dumpsim file */
  fprintf(dumpsim_file, "\nMemory content [0x%.4x..0x%.4x] :\n", start, stop);
  fprintf(dumpsim_file, "-------------------------------------\n");
  for (address = (start >> 1); address <= (stop >> 1); address++)
    fprintf(dumpsim_file, " 0x%.4x (%d) : 0x%.2x%.2x\n", address << 1, address << 1, MEMORY[address][1], MEMORY[address][0]);
  fprintf(dumpsim_file, "\n");
  fflush(dumpsim_file);
}

/***************************************************************/
/*                                                             */
/* Procedure : rdump                                           */
/*                                                             */
/* Purpose   : Dump current register and bus values to the     */   
/*             output file.                                    */
/*                                                             */
/***************************************************************/
void rdump(FILE * dumpsim_file) {                               
  int k; 

  printf("\nCurrent register/bus values :\n");
  printf("-------------------------------------\n");
  printf("Instruction Count : %d\n", INSTRUCTION_COUNT);
  printf("PC                : 0x%.4x\n", CURRENT_LATCHES.PC);
  printf("CCs: N = %d  Z = %d  P = %d\n", CURRENT_LATCHES.N, CURRENT_LATCHES.Z, CURRENT_LATCHES.P);
  printf("Registers:\n");
  for (k = 0; k < LC_3b_REGS; k++)
    printf("%d: 0x%.4x\n", k, CURRENT_LATCHES.REGS[k]);
  printf("\n");

  /* dump the state information into the dumpsim file */
  fprintf(dumpsim_file, "\nCurrent register/bus values :\n");
  fprintf(dumpsim_file, "-------------------------------------\n");
  fprintf(dumpsim_file, "Instruction Count : %d\n", INSTRUCTION_COUNT);
  fprintf(dumpsim_file, "PC                : 0x%.4x\n", CURRENT_LATCHES.PC);
  fprintf(dumpsim_file, "CCs: N = %d  Z = %d  P = %d\n", CURRENT_LATCHES.N, CURRENT_LATCHES.Z, CURRENT_LATCHES.P);
  fprintf(dumpsim_file, "Registers:\n");
  for (k = 0; k < LC_3b_REGS; k++)
    fprintf(dumpsim_file, "%d: 0x%.4x\n", k, CURRENT_LATCHES.REGS[k]);
  fprintf(dumpsim_file, "\n");
  fflush(dumpsim_file);
}

/***************************************************************/
/*                                                             */
/* Procedure : get_command                                     */
/*                                                             */
/* Purpose   : Read a command from standard input.             */  
/*                                                             */
/***************************************************************/
void get_command(FILE * dumpsim_file) {                         
  char buffer[20];
  int start, stop, cycles;

  printf("LC-3b-SIM> ");

  scanf("%s", buffer);
  printf("\n");

  switch(buffer[0]) {
  case 'G':
  case 'g':
    go();
    break;

  case 'M':
  case 'm':
    scanf("%i %i", &start, &stop);
    mdump(dumpsim_file, start, stop);
    break;

  case '?':
    help();
    break;
  case 'Q':
  case 'q':
    printf("Bye.\n");
    exit(0);

  case 'R':
  case 'r':
    if (buffer[1] == 'd' || buffer[1] == 'D')
	    rdump(dumpsim_file);
    else {
	    scanf("%d", &cycles);
	    run(cycles);
    }
    break;

  default:
    printf("Invalid Command\n");
    break;
  }
}

/***************************************************************/
/*                                                             */
/* Procedure : init_memory                                     */
/*                                                             */
/* Purpose   : Zero out the memory array                       */
/*                                                             */
/***************************************************************/
void init_memory() {                                           
  int i;

  for (i=0; i < WORDS_IN_MEM; i++) {
    MEMORY[i][0] = 0;
    MEMORY[i][1] = 0;
  }
}

/**************************************************************/
/*                                                            */
/* Procedure : load_program                                   */
/*                                                            */
/* Purpose   : Load program and service routines into mem.    */
/*                                                            */
/**************************************************************/
void load_program(char *program_filename) {                   
  FILE * prog;
  int ii, word, program_base;

  /* Open program file. */
  prog = fopen(program_filename, "r");
  if (prog == NULL) {
    printf("Error: Can't open program file %s\n", program_filename);
    exit(-1);
  }

  /* Read in the program. */
  if (fscanf(prog, "%x\n", &word) != EOF)
    program_base = word >> 1;
  else {
    printf("Error: Program file is empty\n");
    exit(-1);
  }

  ii = 0;
  while (fscanf(prog, "%x\n", &word) != EOF) {
    /* Make sure it fits. */
    if (program_base + ii >= WORDS_IN_MEM) {
	    printf("Error: Program file %s is too long to fit in memory. %x\n",
             program_filename, ii);
	    exit(-1);
    }

    /* Write the word to memory array. */
    MEMORY[program_base + ii][0] = word & 0x00FF;
    MEMORY[program_base + ii][1] = (word >> 8) & 0x00FF;
    ii++;
  }

  if (CURRENT_LATCHES.PC == 0) CURRENT_LATCHES.PC = (program_base << 1);

  printf("Read %d words from program into memory.\n\n", ii);
}

/************************************************************/
/*                                                          */
/* Procedure : initialize                                   */
/*                                                          */
/* Purpose   : Load machine language program                */ 
/*             and set up initial state of the machine.     */
/*                                                          */
/************************************************************/
void initialize(char *program_filename, int num_prog_files) { 
  int i;

  init_memory();
  for ( i = 0; i < num_prog_files; i++ ) {
    load_program(program_filename);
    while(*program_filename++ != '\0');
  }
  CURRENT_LATCHES.Z = 1;  
  NEXT_LATCHES = CURRENT_LATCHES;
    
  RUN_BIT = TRUE;
}

/***************************************************************/
/*                                                             */
/* Procedure : main                                            */
/*                                                             */
/***************************************************************/
int main(int argc, char *argv[]) {                              
  FILE * dumpsim_file;
//    argc=2;
//    argv[1]= "ThisFileOut.obj";

  /* Error Checking */
  if (argc < 2) {
    printf("Error: usage: %s <program_file_1> <program_file_2> ...\n",
           argv[0]);
    exit(1);
  }

  printf("LC-3b Simulator\n\n");

  initialize(argv[1], argc - 1);

  if ( (dumpsim_file = fopen( "dumpsim", "w" )) == NULL ) {
    printf("Error: Can't open dumpsim file\n");
    exit(-1);
  }

  while (1)
    get_command(dumpsim_file);
    
}

/***************************************************************/
/* Do not modify the above code.
   You are allowed to use the following global variables in your
   code. These are defined above.

   MEMORY

   CURRENT_LATCHES
   NEXT_LATCHES

   You may define your own local/global variables and functions.
   You may use the functions to get at the control bits defined
   above.

   Begin your code here 	  			       */

/***************************************************************/



void process_instruction(){
  /*  function: process_instruction
   *  
   *    Process one instruction at a time  
   *       -Fetch one instruction
   *       -Decode 
   *       -Execute
   *       -Update NEXT_LATCHES
   */
    NEXT_LATCHES=CURRENT_LATCHES;

    int instruction = Low8bits(MEMORY[CURRENT_LATCHES.PC>>1][1]);
    instruction=instruction<<8;
    instruction+= Low8bits(MEMORY[CURRENT_LATCHES.PC>>1][0]);

    NEXT_LATCHES.PC=Low16bits(CURRENT_LATCHES.PC)+2;

    int opcode = instruction>>12;


    int dr = (instruction&0x0FFF)>>9;
    int sr1= (instruction&0x01FF)>>6;
    int sr2= (instruction&0x0007);
    int abit=(instruction&0x003F)>>5;

    int pcOffset9 = (instruction&0x01FF);
    pcOffset9=pcOffset9<<23;
    pcOffset9=pcOffset9>>22;//so that its word addresible

    int pcOffset11 = (instruction&0x07FF);
    pcOffset11=pcOffset11<<21;
    pcOffset11=pcOffset11>>20;//so that it is word addressible

    int amount4 = instruction&0x000F;
    int trapvector8 = (instruction&0x00FF)<<1;

    int imm5 = (instruction&0x001F);
    imm5=imm5<<27;
    imm5=imm5>>27;

    int boffset6 = (instruction&0x003F);
    boffset6=boffset6<<26;
    boffset6=boffset6>>26;

    int offset6 = boffset6<<1;




    int n = (instruction&0x0FFF)>>11;
    int z = (instruction&0x07FF)>>10;
    int p = (instruction&0x03FF)>>9;

    int setCC=0;
    int val1;
    int val2;
    int memAddress;
    int finalVal;
    int temp;


    switch (opcode){
        case 0://BR
            if((n&&CURRENT_LATCHES.N)||(z&&CURRENT_LATCHES.Z)||(p&&CURRENT_LATCHES.P)){
                NEXT_LATCHES.PC = Low16bits(NEXT_LATCHES.PC+pcOffset9);//if branch taken
            }
            break;
        case 1://ADD
            val1 = (Low16bits(CURRENT_LATCHES.REGS[sr1])<<16)>>16;//make it a signed number
            val2 = (abit)? imm5:(Low16bits(CURRENT_LATCHES.REGS[sr2])<<16)>>16;// according to the a bit chose immediate 5 or sext sr2
            setCC=1;//set condition code
            NEXT_LATCHES.REGS[dr] = Low16bits(val1+val2);//store to dr
            break;
        case 2://LDB
            setCC=1;//set cc
            memAddress = Low16bits(CURRENT_LATCHES.REGS[sr1])+ boffset6;//get the new Address
            finalVal = MEMORY[memAddress>>1][memAddress%2];
            finalVal= Low8bits(finalVal);//get value from address
            finalVal = (finalVal<<24)>>24; //sext it
            finalVal = Low16bits(finalVal);//narrow down to reg size
            NEXT_LATCHES.REGS[dr]=finalVal;//store the value


            break;
        case 3://STB
            memAddress = Low16bits(CURRENT_LATCHES.REGS[sr1])+ boffset6;//get the new Address
            MEMORY[memAddress>>1][memAddress%2]=Low8bits(CURRENT_LATCHES.REGS[dr]);//store the lower 8 bits of the source register
            break;
        case 4://JSR
            temp = Low16bits(NEXT_LATCHES.PC);
            if(instruction&0x0800){//sext
                NEXT_LATCHES.PC = Low16bits(temp+pcOffset11);
            } else{
                NEXT_LATCHES.PC = Low16bits(CURRENT_LATCHES.REGS[sr1]);
            }
            NEXT_LATCHES.REGS[7]= Low16bits(temp);

            break;
        case 5://AND
            val1 = (Low16bits(CURRENT_LATCHES.REGS[sr1])<<16)>>16;//sext the val1
            val2 = (abit)? imm5:(Low16bits(CURRENT_LATCHES.REGS[sr2])<<16)>>16;//get the val 2 depending on a bit either sext sr2 or immd5
            setCC=1;//set cc
            NEXT_LATCHES.REGS[dr] = Low16bits(val1&val2);//logical and the two numbers
            break;
        case 6://LDW
            setCC=1;//set cc
            memAddress = Low16bits(Low16bits(CURRENT_LATCHES.REGS[sr1])+ offset6);//get mem address
            finalVal = Low8bits(MEMORY[memAddress>>1][1]);//get msb 8
            finalVal=finalVal<<8;//left shift to msb positions
            finalVal+= Low8bits(MEMORY[memAddress>>1][0]);//add the lsb bits

            finalVal= Low16bits(finalVal);
            finalVal = (finalVal<<16)>>16;//sext the number
            finalVal = Low16bits(finalVal);
            NEXT_LATCHES.REGS[dr]=finalVal;//store it in the dr
            break;
        case 7://STW
            memAddress = Low16bits(Low16bits(CURRENT_LATCHES.REGS[sr1])+ offset6);//get the address
            MEMORY[memAddress>>1][1]=Low16bits(CURRENT_LATCHES.REGS[dr])>>8;//put msb
            MEMORY[memAddress>>1][0]=Low8bits(CURRENT_LATCHES.REGS[dr]);//put lsb
            break;
        case 8://RTI Don't need to do this
            break;
        case 9://XOR
            val1 = (Low16bits(CURRENT_LATCHES.REGS[sr1])<<16)>>16;//sext val1
            val2 = (abit)? imm5:(Low16bits(CURRENT_LATCHES.REGS[sr2])<<16)>>16;//get val 2 based on abit on either immediat 5 or sext sr2
            setCC=1;//setcc
            NEXT_LATCHES.REGS[dr] = Low16bits(val1^val2);//xor the values
            break;
        case 10://Don't need to do this
            break;
        case 11://Don't need to do this
            break;
        case 12://JMP
            NEXT_LATCHES.PC= Low16bits(CURRENT_LATCHES.REGS[sr1]);//just change the pc with the sr1 value
            break;
        case 13://SHF
            setCC=1;//set cc
            finalVal = Low16bits(CURRENT_LATCHES.REGS[sr1]);//get the value we are trying to shift
            if(instruction&0x0010){//This is a right shift

                if(instruction&0x0020){//Arithmetic shift
                    finalVal=finalVal<<16;
                    finalVal=finalVal>>16;//sext the number
                    finalVal=finalVal>>amount4;//right shift by amount
                } else{//Logical Shift
                    finalVal=finalVal>>amount4;//just do unsigned right shift
                }

            } else{//This is a left shift
                finalVal=finalVal<<amount4;//do unsigned left shift
            }
            NEXT_LATCHES.REGS[dr]= Low16bits(finalVal);//store in dr
            break;
        case 14://LEA
            memAddress = Low16bits(Low16bits(NEXT_LATCHES.PC)+ pcOffset9);//get new address
            NEXT_LATCHES.REGS[dr]=Low16bits(memAddress);//store new address in dr
            break;
        case 15://TRAP
            NEXT_LATCHES.REGS[7]= NEXT_LATCHES.PC;
            finalVal = Low8bits(MEMORY[trapvector8>>1][1]);//get the msb
            finalVal=finalVal<<8;//left shift to their position
            finalVal+= Low8bits(MEMORY[trapvector8>>1][0]);//add the lsb
            NEXT_LATCHES.PC=Low16bits(finalVal);
            break;
    }

    if(setCC){
        NEXT_LATCHES.Z=0;
        NEXT_LATCHES.P=0;
        NEXT_LATCHES.N=0;
        if(NEXT_LATCHES.REGS[dr]==0)
            NEXT_LATCHES.Z=1;
        else{
            int drVal= NEXT_LATCHES.REGS[dr]>>15;//looking at 16th bit
            if(drVal){
                NEXT_LATCHES.N=1;
            } else{
                NEXT_LATCHES.P=1;
            }
        }
    }
}
