.ORIG x3000
LEA R1, twenty;
LDW R1, R1, #0 ;
LEA R0, dataloc;
LDW R0, R0, #0;
AND R2, R2, #0 ;
LOOP  LDB R3, R0, #0;
ADD R0, R0, #1;
ADD R2, R2, R3 ;
ADD R1, R1, #-1 ;
BRp LOOP        ;
STW R2, R0, #0  ;
JMP R2;
HALT;
twenty .FILL #20;
dataloc .FILL xC000;
.END;