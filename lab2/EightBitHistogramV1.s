	PRESERVE8
    AREA    EightBitHist, CODE
    EXPORT EightBitHistogramV1

EightBitHistogramV1
    MUL R0, R1
    MOV R12, #0xFFFF
    CMP R0, R12
    BHI Maior
	
	MOV R11, #0
    MOV R12, #0
    MOV R5, #0
    ORR R5, R3
LimpaHist
    LDR R6, [R5], #4
    STR R11, [R5]
    ADD R12, #1
    CMP R12, #127
    BNE LimpaHist

    MOV R12, #0
    MOV R5, #0
    ORR R5, R3
    MOV R6, #0
    ORR R6, R2
WriteHist
    LDRB R8, [R6], #1	
	MOV R9, #0
	ORR R9, R5
	ADD R9, R8
	ADD R9, R8
	LDRH R10, [R9]
	ADD R10, #1			
	STRH R10, [R9]		

    ADD R12, #1
    CMP R12, R0
    BNE WriteHist
    BX LR

Maior
    MOV R0, #0x00
    BX LR
	
	END