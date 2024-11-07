;EightBitHistogram_ASM.s
; Desenvolvido para a placa EK-TM4C1294XL

; -------------------------------------------------------------------------------
        THUMB                        ; Instruções do tipo Thumb-2
; -------------------------------------------------------------------------------

; -------------------------------------------------------------------------------
        AREA DATA, ALIGN = 2
		EXPORT IMAGE_SIZE [DATA, SIZE = 16]
IMAGE_SIZE SPACE 16
		
		AREA |.text|, CODE, READONLY, ALIGN = 2
        EXPORT EightBitHistogram_ASM
		EXPORT IMAGE_SIZE
; -------------------------------------------------------------------------------
EightBitHistogram_ASM
	MUL R4, R0, R1; ;R4 <- width * height
	
	MOV R5, #65535;
	CMP R4, R5;
	MOVHS R0, #0;
	BHS EightBitHistogram_ASM_end;
	
	MOV R7, R3;
	ADD R5, R7, #512;
p_image_initialization
	MOV R6, #0; 0 value initialization for *p_histogram
	STRH R6, [R7], #2; ;R7 is the *p_histogram address
	CMP R5, R7;
	BNE p_image_initialization;
	
	MOV R9, #2;
	ADD R7, R2, R4; R7 = p_image + image_size
p_histogram_completion
	LDRB R8, [R2]; r = p_image
	MUL R8, R8, R9;
	ADD R5, R3, R8;
	LDRH R6, [R5];
	ADD R6, R6, #1;,
	STRH R6, [R5];
	ADD R2, R2, #1;
	CMP R7, R2;
	BNE p_histogram_completion;
	
	MOV R0, R4; return value
	
EightBitHistogram_ASM_end
	BX LR
	
	ALIGN                           
 END  