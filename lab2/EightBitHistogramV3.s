;EightBitHistogramV3.s

; -------------------------------------------------------------------------------
        THUMB                        ; Instruções do tipo Thumb-2
; -------------------------------------------------------------------------------

; -------------------------------------------------------------------------------
		PRESERVE8
		AREA |.text|, CODE, READONLY, ALIGN = 2
        EXPORT EightBitHistogramV3
; -------------------------------------------------------------------------------
EightBitHistogramV3
    MUL R4, R0, R1       ; R4 = width * height
    MOV R5, #65535
    CMP R4, R5
    MOVHS R0, #0
    BHS EightBitHistogram_ASM_end
    
    ; Initialize p_histogram to zero for 256 entries (16-bit each)
    MOV R6, #0            
    MOV R7, R3            
    ADD R5, R7, #512     
p_histogram_initialization
    STRH R6, [R7], #2     ; Store zero in each 16-bit entry, increment address by 2
    CMP R5, R7
    BNE p_histogram_initialization

    ; Fill the histogram based on p_image values
    MOV R9, #2            ; Multiplier for 16-bit addressing
    ADD R7, R2, R4        ; R7 = p_image + image_size (end of image data)
p_histogram_completion
    LDRB R8, [R2], #1     ; Load 8-bit pixel value from p_image and increment p_image pointer
    MUL R8, R8, R9        ; Calculate offset in p_histogram (R8 * 2)
    ADD R5, R3, R8        
    LDRH R6, [R5]         
    ADD R6, R6, #1        
    STRH R6, [R5]        
    CMP R7, R2           
    BNE p_histogram_completion

    MOV R0, R4            

EightBitHistogram_ASM_end
    BX LR                

    ALIGN
	END