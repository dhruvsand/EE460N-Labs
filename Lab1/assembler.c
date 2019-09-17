/*
	Name 1: Dhruv Sandesara
	Name 2: Ayush Srivastava
	UTEID 1: djs3967
	UTEID 2: as7793
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h> /* standard input/output library */
#include <stdlib.h> /* Standard C Library */
#include <string.h> /* String operations library */
#include <ctype.h> /* Library for useful character operations */
#include <limits.h> /* Library for definitions of common variable type characteristics */
#include <math.h>

#define MAX_LINE_LENGTH 255
#define MAX_SYMBOLS 255

FILE* infile = NULL;
FILE* outfile = NULL;
enum
{
    DONE, OK, EMPTY_LINE
};

typedef struct {
    char *name;
    int value; /* i for int, s for string ... */

} symbol;
symbol stable[MAX_SYMBOLS];
int symbolCount=0;

char* isOpcode(char *lPtr);
void regToBin(char * Reg, char* reg);
void intToBin(int i, int len, char* res);

int readAndParse( FILE * pInfile, char * pLine, char ** pLabel, char ** pOpcode, char ** pArg1, char ** pArg2, char ** pArg3, char ** pArg4) {
    char * lRet, * lPtr;
    int i =0;

    if( !fgets( pLine, MAX_LINE_LENGTH, pInfile ) )
        return( DONE );
    for( i = 0; i < strlen( pLine ); i++ )
        pLine[i] = (char) tolower(pLine[i] );

    /* convert entire line to lowercase */
    *pLabel = *pOpcode = *pArg1 = *pArg2 = *pArg3 = *pArg4 = pLine + strlen(pLine);

    /* ignore the comments */
    lPtr = pLine;

    while( *lPtr != ';' && *lPtr != '\0' &&
           *lPtr != '\n' )
        lPtr++;

    *lPtr = '\0';
    if( !(lPtr = strtok( pLine, "\t\n ," ) ) )
        return( EMPTY_LINE );

    if( strcmp(isOpcode( lPtr ),"-1")==0 && lPtr[0] != '.' ) /* found a label */
    {
        *pLabel = lPtr;
        if( !( lPtr = strtok( NULL, "\t\n ," ) ) ) return( OK );
    }

    *pOpcode = lPtr;

    if( !( lPtr = strtok( NULL, "\t\n ," ) ) ) return( OK );

    *pArg1 = lPtr;

    if( !( lPtr = strtok( NULL, "\t\n ," ) ) ) return( OK );

    *pArg2 = lPtr;
    if( !( lPtr = strtok( NULL, "\t\n ," ) ) ) return( OK );

    *pArg3 = lPtr;

    if( !( lPtr = strtok( NULL, "\t\n ," ) ) ) return( OK );

    *pArg4 = lPtr;

    return( OK );
}

int toNum( char * pStr ) {
    char * t_ptr;
    char * orig_pStr;
    int t_length,k;
    int lNum, lNeg = 0;
    long int lNumLong;

    orig_pStr = pStr;
    if( *pStr == '#' )				/* decimal */
    {
        pStr++;
        if( *pStr == '-' )				/* dec is negative */
        {
            lNeg = 1;
            pStr++;
        }
        t_ptr = pStr;
        t_length = (int) strlen(t_ptr);
        for(k=0;k < t_length;k++)
        {
            if (!isdigit(*t_ptr))
            {
                printf("Error: invalid decimal operand, %s\n",orig_pStr);
                exit(4);
            }
            t_ptr++;
        }
        lNum = (int) strtol(pStr, NULL, 10);
        if (lNeg)
            lNum = -lNum;

        return lNum;
    }
    else if( *pStr == 'x' )	/* hex     */
    {
        pStr++;
        if( *pStr == '-' )				/* hex is negative */
        {
            lNeg = 1;
            pStr++;
        }
        t_ptr = pStr;
        t_length = (int) strlen(t_ptr);
        for(k=0;k < t_length;k++)
        {
            if (!isxdigit(*t_ptr))
            {
                printf("Error: invalid hex operand, %s\n",orig_pStr);
                exit(4);
            }
            t_ptr++;
        }
        lNumLong = strtol(pStr, NULL, 16);    /* convert hex string into integer */
        lNum = (int) ((lNumLong > INT_MAX) ? INT_MAX : lNumLong);
        if( lNeg )
            lNum = -lNum;
        return lNum;
    }
    else
    {
        printf( "Error: invalid operand, %s\n", orig_pStr);
        exit(4);  /* This has been changed from error code 3 to error code 4, see clarification 12 */
    }
}

char binToHexChar(char* bin){
    if(strcmp(bin,"0000")==0){
        return '0';
    } else if(strcmp(bin, "0001") == 0){
        return '1';
    }
    else if(strcmp(bin,"0010")==0){
        return '2';
    }
    else if(strcmp(bin,"0011")==0){
        return '3';
    }
    else if(strcmp(bin,"0100")==0){
        return '4';
    }
    else if(strcmp(bin,"0101")==0){
        return '5';
    }
    else if(strcmp(bin,"0110")==0){
        return '6';
    }else if(strcmp(bin,"0111")==0){
        return '7';
    }
    else if(strcmp(bin,"1000")==0){
        return '8';
    }else if(strcmp(bin,"1001")==0){
        return '9';
    }else if(strcmp(bin,"1010")==0){
        return 'A';
    }else if(strcmp(bin,"1011")==0){
        return 'B';
    }else if(strcmp(bin,"1100")==0){
        return 'C';
    }else if(strcmp(bin,"1101")==0){
        return 'D';
    }
    else if(strcmp(bin,"1110")==0){
        return 'E';
    }
    else if(strcmp(bin,"1111")==0){
        return 'F';
    } else{
        exit(4);
    }
}

void binToHex(char* bin, char* Hex){
    Hex[4]='\0';

    char substr[5];
    substr[4] ='\0';

    strncpy(substr, bin, 4);
    Hex[0] = binToHexChar(substr);

    strncpy(substr, bin+4, 4);
    Hex[1] = binToHexChar(substr);

    strncpy(substr, bin+8, 4);
    Hex[2] = binToHexChar(substr);

    strncpy(substr, bin+12, 4);
    Hex[3] = binToHexChar(substr);

}

int main(int argc, char* argv[]) {

    char *prgName   = NULL;
    char *iFileName = NULL;
    char *oFileName = NULL;

//    argv[0]= "assemble";
//    argv[1]= "ThisGoesIn.asm";
//    argv[2]= "ThisComesOut.obj";

    prgName   = argv[0];
    iFileName = argv[1];
    oFileName = argv[2];


    printf("program name = '%s'\n", prgName);
    printf("input file name = '%s'\n", iFileName);
    printf("output file name = '%s'\n", oFileName);


    /* open the source file */
    infile = fopen(argv[1], "r");
    outfile = fopen(argv[2], "w");

//    char *c;
//    fgets(c,255,lInfile);
//    printf("%s",c);

    if (!infile) {
        printf("Error: Cannot open file %s\n", argv[1]);
        exit(4);
    }
    if (!outfile) {
        printf("Error: Cannot open file %s\n", argv[2]);
        exit(4);
    }

    /* Do stuff with files */


    char lLine[MAX_LINE_LENGTH + 1], *lLabel, *lOpcode, *lArg1,
            *lArg2, *lArg3, *lArg4;

    int lRet;

    int current_Address=0;

    char res[16];
    intToBin(3,4,res);
    printf(res);

//    FIRST PASS
    do {
        lRet = readAndParse( infile, lLine, &lLabel, &lOpcode, &lArg1, &lArg2, &lArg3, &lArg4 );
        if( lRet != DONE && lRet != EMPTY_LINE )
        { printf("%s,     %s,    %s,    %s,    %s,    %s \n",lLabel,lOpcode,lArg1,lArg2,lArg3,lArg4);

            if(strcmp(lOpcode,".orig")==0){
                current_Address = toNum(lArg1);
                if(current_Address%2)
                    exit(3);
                current_Address-=1;//.fill doesnt count
            }
            if(*lLabel!='\0'){
                for(int i=0; i<symbolCount; i++){
                    if(strcmp(lLabel, stable[i].name)==0)
                        exit(4);
                }
                char * newLable= malloc(MAX_LINE_LENGTH);
                strcpy(newLable,lLabel);
                stable[symbolCount].value=current_Address;
                stable[symbolCount].name=newLable;
                symbolCount+=1;
            }
            current_Address+=1;
        }
    } while( lRet != DONE );



    rewind(infile);



    for(int i=0; i<symbolCount;i++){
        printf("The stables value: %d and the name:  %s \n", stable[i].value,stable[i].name);
        for(int k=0;k<strlen(stable[i].name);k++) {
            if (!isalnum(stable[i].name[k]))
                exit(4);
        }
        if(stable[i].name[0]=='x'||isdigit(stable[i].name[0]))
            exit(4);

    }

    //2ND PASS


    current_Address=0;//reset for the .orig

    do {
        lRet = readAndParse( infile, lLine, &lLabel, &lOpcode, &lArg1, &lArg2, &lArg3, &lArg4 );
        if( lRet != DONE && lRet != EMPTY_LINE )
        { printf("%s,     %s,    %s,    %s,    %s,    %s \n",lLabel,lOpcode,lArg1,lArg2,lArg3,lArg4);

            if(strcmp(isOpcode(lOpcode),"-1")==0){
                //is an assembler directive
                if(strcmp(lOpcode,".orig")==0){
                    current_Address = toNum(lArg1);
                    fprintf( outfile, "0x%.4X\n", current_Address );

                } else if(strcmp(lOpcode,".fill")==0){
                    current_Address = toNum(lArg1);
                    fprintf( outfile, "0x%.4X\n", current_Address );

                }else if(strcmp(lOpcode,".end")==0){
//                    fclose(outfile);
                } else{
                    exit(2);
                }



            } else {
                fprintf(outfile,"0x");
                char * instruction = malloc(17);

                strcpy(instruction,isOpcode(lOpcode));
                instruction[16]= '\0';



                //THis is where we add the other part of the instruction

                if(strcmp(lOpcode,"add")==0||strcmp(lOpcode,"and")==0||strcmp(lOpcode,"xor")==0){
                    regToBin(lArg1,&instruction[4]);
                    regToBin(lArg2,&instruction[7]);

                    if(*lArg3=='r'){
                        strcpy(&instruction[10],"000");
                        regToBin(lArg3,&instruction[13]);
                    }
                    else if(*lArg3=='#'||*lArg3=='x'){
                        strcpy(&instruction[10],"1");
                        intToBin(toNum(lArg3),5,&instruction[11]);
                    }
                    else{
                        exit(4);
                    }
                }
                else if(strcmp(lOpcode,"br")==0){
                    strcpy(&instruction[4],"111");
                    for(int i=0; i<symbolCount;i++){
                        if(strcmp(stable[i].name,lArg1)!=0&&i==symbolCount-1)
                            exit(1);
                        if(strcmp(stable[i].name,lArg1)==0){
                            int value = stable[i].value-current_Address;
                            intToBin(value,9,&instruction[7]);
                            break;
                        }
                    }
                }
                else if(strcmp(lOpcode,"brn")==0){
                    strcpy(&instruction[4],"100");
                    for(int i=0; i<symbolCount;i++){
                        if(strcmp(stable[i].name,lArg1)!=0&&i==symbolCount-1)
                            exit(1);
                        if(strcmp(stable[i].name,lArg1)==0){
                            int value = stable[i].value-current_Address;
                            intToBin(value,9,&instruction[7]);
                            break;
                        }
                    }
                }
                else if(strcmp(lOpcode,"brz")==0){
                    strcpy(&instruction[4],"010");
                    for(int i=0; i<symbolCount;i++){
                        if(strcmp(stable[i].name,lArg1)!=0&&i==symbolCount-1)
                            exit(1);
                        if(strcmp(stable[i].name,lArg1)==0){
                            int value = stable[i].value-current_Address;
                            intToBin(value,9,&instruction[7]);
                            break;
                        }
                    }
                }
                else if(strcmp(lOpcode,"brp")==0){
                    strcpy(&instruction[4],"001");
                    for(int i=0; i<symbolCount;i++){
                        if(strcmp(stable[i].name,lArg1)!=0&&i==symbolCount-1)
                            exit(1);
                        if(strcmp(stable[i].name,lArg1)==0){
                            int value = stable[i].value-current_Address;
                            intToBin(value,9,&instruction[7]);
                            break;
                        }
                    }
                }
                else if(strcmp(lOpcode,"brnz")==0){
                    strcpy(&instruction[4],"110");
                    for(int i=0; i<symbolCount;i++){
                        if(strcmp(stable[i].name,lArg1)!=0&&i==symbolCount-1)
                            exit(1);
                        if(strcmp(stable[i].name,lArg1)==0){
                            int value = stable[i].value-current_Address;
                            intToBin(value,9,&instruction[7]);
                            break;
                        }
                    }
                }
                else if(strcmp(lOpcode,"brnp")==0){
                    strcpy(&instruction[4],"101");
                    for(int i=0; i<symbolCount;i++){
                        if(strcmp(stable[i].name,lArg1)!=0&&i==symbolCount-1)
                            exit(1);
                        if(strcmp(stable[i].name,lArg1)==0){
                            int value = stable[i].value-current_Address;
                            intToBin(value,9,&instruction[7]);
                            break;
                        }
                    }
                }
                else if(strcmp(lOpcode,"brzp")==0){
                    strcpy(&instruction[4],"011");
                    for(int i=0; i<symbolCount;i++){
                        if(strcmp(stable[i].name,lArg1)!=0&&i==symbolCount-1)
                            exit(1);
                        if(strcmp(stable[i].name,lArg1)==0){
                            int value = stable[i].value-current_Address;
                            intToBin(value,9,&instruction[7]);
                            break;
                        }
                    }
                }
                else if(strcmp(lOpcode,"brnzp")==0){
                    strcpy(&instruction[4],"111");
                    for(int i=0; i<symbolCount;i++){
                        if(strcmp(stable[i].name,lArg1)!=0&&i==symbolCount-1)
                            exit(1);
                        if(strcmp(stable[i].name,lArg1)==0){
                            int value = stable[i].value-current_Address;
                            intToBin(value,9,&instruction[7]);
                            break;
                        }
                    }
                }
                else if(strcmp(lOpcode,"jmp")==0||strcmp(lOpcode,"jsrr")==0){
                    strcpy(&instruction[4],"000");
                    regToBin(lArg1,&instruction[7]);
                    strcpy(&instruction[10],"000000");
                }
                else if(strcmp(lOpcode,"jsr")==0){
                    strcpy(&instruction[4],"1");
                    for(int i=0; i<symbolCount;i++){
                        if(strcmp(stable[i].name,lArg1)!=0&&i==symbolCount-1)
                            exit(1);
                        if(strcmp(stable[i].name,lArg1)==0){
                            int value = stable[i].value-current_Address;
                            intToBin(value,11,&instruction[5]);
                            break;
                        }
                    }
                }
                else if(strcmp(lOpcode,"ldb")==0||strcmp(lOpcode,"ldw")==0||strcmp(lOpcode,"stb")==0||strcmp(lOpcode,"stw")==0){
                    regToBin(lArg1,&instruction[4]);
                    regToBin(lArg2,&instruction[7]);
                    intToBin(toNum(lArg3),6,&instruction[10]);

                }
                else if(strcmp(lOpcode,"lea")==0){
                    regToBin(lArg1,&instruction[4]);
                    for(int i=0; i<symbolCount;i++){
                        if(strcmp(stable[i].name,lArg2)!=0&&i==symbolCount-1)
                            exit(1);
                        if(strcmp(stable[i].name,lArg2)==0){
                            int value = stable[i].value-current_Address;
                            intToBin(value,9,&instruction[7]);
                            break;
                        }
                    }
                }
                else if(strcmp(lOpcode,"not")==0){
                    regToBin(lArg1,&instruction[4]);
                    regToBin(lArg2,&instruction[7]);
                    strcpy(&instruction[10],"111111");
                }
                else if(strcmp(lOpcode,"ret")==0){
                    strcpy(&instruction[4],"000111000000");
                }
                else if(strcmp(lOpcode,"rti")==0){
                    strcpy(&instruction[4],"000000000000");
                }
                else if(strcmp(lOpcode,"lshf")==0){
                    regToBin(lArg1,&instruction[4]);
                    regToBin(lArg2,&instruction[7]);
                    strcpy(&instruction[10],"00");
                    intToBin(toNum(lArg3),4,&instruction[12]);
                }
                else if(strcmp(lOpcode,"rshfl")==0){
                    regToBin(lArg1,&instruction[4]);
                    regToBin(lArg2,&instruction[7]);
                    intToBin(toNum(lArg3),4,&instruction[12]);
                }
                else if(strcmp(lOpcode,"rshfa")==0){
                    regToBin(lArg1,&instruction[4]);
                    regToBin(lArg2,&instruction[7]);
                    strcpy(&instruction[10],"11");
                    intToBin(toNum(lArg3),4,&instruction[12]);
                }
                else if(strcmp(lOpcode,"trap")==0){
                    strcpy(&instruction[4],"0000");
                    if(*lArg1!='x'&&*lArg1!='X')
                        exit(4);
                    intToBin(toNum(lArg1),8,&instruction[8]);
                }
                else if(strcmp(lOpcode,"halt")==0){
                    strcpy(&instruction[4],"0000");
                    intToBin(toNum("x25"),8,&instruction[8]);
                }
                else if(strcmp(lOpcode,"nop")==0){
                    instruction="0000000000000000";
                }


                char hex[5];
                binToHex(instruction,hex);
                fprintf(outfile,hex);
                fprintf(outfile, "\n");
                free(instruction);
            }
            current_Address+=1;
        }
    } while( lRet != DONE );

    for(int i=0; i<symbolCount;i++){
        free(stable[i].name);


    }

    fclose(infile);
    fclose(outfile);
}

void intToBin(int num, int base, char* res){
    int temp=num;
    int bnum[base];
    if(num<0) {
        if(base==8)
            exit(3);
        num = 0 - num;
        if(pow(2,base-1)<num) {
            if(base>=9)
                exit(4);
            exit(3);
        }
        num =num-1;
        intToBin(num,base,res);
        for(int j = 0; j<base;j++){
            if(res[j]=='0')
                res[j]='1';
            else
                res[j]='0';
        }
    }

    if(base==8||base==4||base==3){
        if(pow(2,base)<=num)
            exit(3);

    } else {
        if (pow(2, base - 1) <= num) {
            if (base >= 9)
                exit(4);
            exit(3);
        }
    }
    int i=0;


    if(temp<0){

        return;
    }

    while (temp>0) {
        bnum[i] = temp % 2;
        temp = temp / 2;
        i++;
    }
    int len=i;
    i--;

    for (int k = 0; k < base; k++) {
        if (k < base - len)
            res[k] = '0';
        else {
            res[k] = (char)('0'+bnum[i]);
            i--;
        }
    }

    res[base]='\0';
}

void regToBin(char * Reg, char *reg){
    if(Reg[0]!='r'||strlen(Reg)!=2||((Reg[1]!='0')&&(Reg[1]!='1')&&(Reg[1]!='2')&&(Reg[1]!='3')&&(Reg[1]!='4')&&(Reg[1]!='5')&&(Reg[1]!='6')&&(Reg[1]!='7')))
        exit(4);
    else
        intToBin(Reg[1]-'0',3,reg);
}

char* isOpcode(char *lPtr) {

    if(strcmp(lPtr,"add")==0)
        return "0001";
    if(strcmp(lPtr,"and")==0)
        return "0101";
    if(strcmp(lPtr,"br")==0)
        return "0000";
    if(strcmp(lPtr,"jmp")==0)
        return "1100";
    if(strcmp(lPtr,"jsr")==0)
        return "0100";
    if(strcmp(lPtr,"jsrr")==0)
        return "0100";
    if(strcmp(lPtr,"ldb")==0)
        return "0010";
    if(strcmp(lPtr,"ldw")==0)
        return "0110";
    if(strcmp(lPtr,"lea")==0)
        return "1110";
    if(strcmp(lPtr,"not")==0)
        return "1001";
    if(strcmp(lPtr,"ret")==0)
        return "1100";
    if(strcmp(lPtr,"rti")==0)
        return "1000";
    if(strcmp(lPtr,"lshf")==0)
        return "1101";
    if(strcmp(lPtr,"rshfl")==0)
        return "1101";
    if(strcmp(lPtr,"rshfa")==0)
        return "1101";
    if(strcmp(lPtr,"stb")==0)
        return "0011";
    if(strcmp(lPtr,"stw")==0)
        return "0111";
    if(strcmp(lPtr,"trap")==0)
        return "1111";
    if(strcmp(lPtr,"halt")==0)
        return "1111";
    if(strcmp(lPtr,"xor")==0)
        return "1001";
    if(strcmp(lPtr,"brn")==0)
        return "0000";
    if(strcmp(lPtr,"brz")==0)
        return "0000";
    if(strcmp(lPtr,"brp")==0)
        return "0000";
    if(strcmp(lPtr,"brnz")==0)
        return "0000";
    if(strcmp(lPtr,"brnp")==0)
        return "0000";
    if(strcmp(lPtr,"brzp")==0)
        return "0000";
    if(strcmp(lPtr,"brnzp")==0)
        return "0000";
    if(strcmp(lPtr,"nop")==0)
        return "0000";

    return "-1";
}

/* Note: MAX_LINE_LENGTH, OK, EMPTY_LINE, and DONE are defined values */
