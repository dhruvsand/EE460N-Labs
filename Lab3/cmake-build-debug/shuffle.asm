.ORIG x3000
LEA R0, VALUE
LDW R0,R0,X0;
LSHF R1,R0,#0   ;R1 WILL HAVE MOST SIGNIFICANT BITS
LSHF R2,R0,#8   ;R2 WILL HAVE LEAST SIGNIFICANT BITS
RSHFA R1,R1,#8;
RSHFA R2,R2,#8;
ADD R0,R1,R2;
LEA R3,ADDRESS;
LDW R3, R3,#0 ;
STW R0,R3,#0;
HALT
ADDRESS .FILL X3050;
VALUE   .FILL X1234;
.END
