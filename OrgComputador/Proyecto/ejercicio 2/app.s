	.equ SCREEN_WIDTH,   640
	.equ SCREEN_HEIGH,   480
	.equ BITS_PER_PIXEL, 32

	.equ GPIO_BASE,    0x3f200000
	.equ GPIO_GPFSEL0, 0x00
	.equ GPIO_GPLEV0,  0x34
	
	.include "funs.s"
	.globl main

main:
	
					// x0 contiene la direccion base del framebuffer
	mov x20, x0 			// Guarda la dirección base del framebuffer en x20
    mov x27,0     
    							  
    bl fondoNoche
	
	mov x3, 0
	mov x4, 410
	bl Calcularpixel
	bl portalparametrizado

    // MARIO
    mov x3, 305
    mov x4, 400
    bl Calcularpixel
    bl dibujarmario

	// Pos inicial pj
    mov x28, x3 		// eje x
	mov x29, x4 		// eje y
	    	
    
loop1:    	
	mov x9, GPIO_BASE                //direccion del GPIO a x9
	str wzr, [x9, GPIO_GPFSEL0]     //GPIO como solo lectura
	ldr w10, [x9, GPIO_GPLEV0]
	
	// Filtrado de teclas
	and w27,w10,0b10		// w27 : w
	and w13,w10,0b100		// w13 : a 
	and w25,w10,0b1000		// w25 : s
	and w14,w10,0b10000		// w14 : d	
	and w26,w10,0b100000		// w26 : espacio

	cmp w27, 0
	b.ne teclaW
	
	cmp w13,0
	b.ne teclaA 
	
	cmp w25,0
	b.ne teclaS
	
	cmp w14,0
	b.ne teclaD

	cmp w26,0
	b.ne saltar
	b.eq loop1


teclaW:       
	bl delay2
    bl fondoNoche

	// recuperando la posicion
	mov x3, x28
    mov x4, x29

    // MARIO 
	sub x4, x4, 1
	cmp x4, 350
	b.le funcionW
    bl Calcularpixel
    bl dibujarmario
	mov x28, x3
	mov x29, x4
	mov x3, 0
	mov x4, 410
	bl Calcularpixel
	bl portalparametrizado
										
	b loop1
	
teclaS:
	bl delay2
    bl fondoNoche

	// recuperando la posicion
	mov x3, x28
	mov x4, x29

    // MARIO 
	add x4, x4, 1
	cmp x4, 440
	b.ge funcionS
    bl Calcularpixel
    bl dibujarmario
	mov x28, x3
	mov x29, x4
	mov x3, 0
	mov x4, 410
	bl Calcularpixel
	bl portalparametrizado
	mov x3, 640

	b loop1	
	
teclaA:
	bl delay2
    bl fondoNoche

	// recuperando la posicion
	mov x3, x28
	mov x4, x29

    // MARIO 
	sub x3, x3, 1
    bl Calcularpixel
    bl dibujarmario

	mov x28, x3
	mov x29, x4
		
	mov x3, 0
	mov x4, 410
	bl Calcularpixel
	bl portalparametrizado
										
	b loop1									
	
teclaD: 
	bl delay2
    bl fondoNoche

	// recuperando la posicion

	mov x3, x28
	mov x4, x29

    	// MARIO
	add x3, x3, 1
    bl Calcularpixel
    bl dibujarmario
	mov x28, x3
	mov x29, x4
	mov x3, 0
	mov x4, 410
	bl Calcularpixel
	bl portalparametrizado

	b loop1		
	
saltar:
	bl delay2	
    bl fondoNoche

	// recuperando la posicion
	mov x3, x28
	mov x4, x29
	sub x4, x4, 40
    bl Calcularpixel
    bl dibujarmario

	mov x3, 0
	mov x4, 410
	bl Calcularpixel
	bl portalparametrizado
    
	bl delay 			//Espera antes de volver al piso
     
    bl fondoNoche
	mov x3, x28
	mov x4, x29
	bl Calcularpixel
	bl dibujarmario

	mov x28, x3
	mov x29, x4

	mov x3, 0
	mov x4, 410
	bl Calcularpixel
	bl portalparametrizado
				
	b loop1
	
	
	
funcionW:

	bl delay2
    bl fondoNoche
        
	// recuperando la posicion
	mov x3, x28
    mov x4, x29

    // MARIO 
    bl Calcularpixel
    bl dibujarmario
	mov x28, x3
	mov x29, x4
	mov x3, 0
	mov x4, 410
	bl Calcularpixel
	bl portalparametrizado
									
	b loop1
	
funcionS:
	bl delay2
    bl fondoNoche

	// recuperando la posicion
	mov x3, x28
	mov x4, x29

    // MARIO 
    bl Calcularpixel
    bl dibujarmario
	mov x28, x3
	mov x29, x4
	mov x3, 0
	mov x4, 410
	bl Calcularpixel
	bl portalparametrizado
								
	b loop1	
	
InfLoop:
	b InfLoop
