; Parâmetros de entrada
; R0 = width R1 = height R2 = p_image R3 = p_histogram

	THUMB
	AREA    |.text|, CODE, READONLY, ALIGN=2
	EXPORT EightBitHistogramV2
	
EightBitHistogramV2
    PUSH	{LR}
    MUL     R4, R0, R1              
    CMP     R4, #65536              
    BHI     Error                   
    MOV     R5, #0          ; R5 = zero
    MOV     R6, #256        ; R6 = tamanho do histograma
    MOV     R7, R3          ; R7 = endereço do histograma
	MOV		R11, #0					
    BL      Clear          
    
Loop
    CMP     R4, #0                  
    BEQ     Break                    
   
    LDRB    R8, [R2], #1            
    LSL     R8, R8, #1
    ADD     R9, R3, R8              
    LDRH    R10, [R9]               
    ADD     R10, R10, #1            
    STRH    R10, [R9]               
    SUB     R4, R4, #1              
	ADD		R11, R11, #1
    B       Loop                    

Break
    MOV     R0, R11         ; R0 = width*height
	POP 	{LR}
    BX      LR                      

Error
    MOV     R0, #0			; Retorna 0 
	POP		{LR}	
    BX      LR				

Clear
    STRH    R5, [R7], #2            
    SUB     R6, R6, #1              
    CMP     R6, #0                  
    BNE     Clear           
    BX      LR             
		
    ALIGN                        		
    END                          		