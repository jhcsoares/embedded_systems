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
    MUL R4, R0, R1       ; R4 = width * height
    MOV R5, #65535
    CMP R4, R5
    MOVHS R0, #0
    BHS EightBitHistogram_ASM_end
    
    ; Initialize p_histogram to zero for 256 entries (16-bit each)
    MOV R6, #0            ; Initialize to zero
    MOV R7, R3            ; R7 = p_histogram base address
    ADD R5, R7, #512      ; R5 = p_histogram + 512 bytes (256 * 16-bit)
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
    ADD R5, R3, R8        ; R5 = address of histogram entry for pixel value
    LDRH R6, [R5]         ; Load current histogram value
    ADD R6, R6, #1        ; Increment histogram value
    STRH R6, [R5]         ; Store incremented value back
    CMP R7, R2            ; Check if we reached the end of image
    BNE p_histogram_completion

    ; Return image size
    MOV R0, R4            ; Set return value to image size

EightBitHistogram_ASM_end
    BX LR                 ; Return

    ALIGN
	END