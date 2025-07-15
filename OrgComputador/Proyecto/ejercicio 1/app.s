	.equ SCREEN_WIDTH,   640
	.equ SCREEN_HEIGH,   480
	.equ BITS_PER_PIXEL, 32

	.equ GPIO_BASE,    0x3f200000
	.equ GPIO_GPFSEL0, 0x00
	.equ GPIO_GPLEV0,  0x34


	.include "funs.s"
    
	.globl main

main:
	mov x20, x0 		// Guarda la dirección base del framebuffer en x20	
    mov x13, 0 		// Para gpio  

fondoNoche:
	bl fondonoche

    // GPIO
    mov x24,0
      
loop1:
	mov x9, GPIO_BASE                
	str wzr, [x9, GPIO_GPFSEL0]     
	ldr w10, [x9, GPIO_GPLEV0]
	and w13, w10, 0b10
	cmp w27,w13
	b.eq loop1
	mov w27, w13
	cbz w27, loop1
	cmp w24,0
	b.eq fondoDia
	b.ne fondoNoche	
    
fondoDia:

	bl fondodia     
    
    mov x24, 1 	// PARA GPIO
    b loop1
    

InfLoop:
	b InfLoop
