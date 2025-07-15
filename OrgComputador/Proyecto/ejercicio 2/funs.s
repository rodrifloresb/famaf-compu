.equ SCREEN_WIDTH, 		640
.equ SCREEN_HEIGH, 		480
.equ BITS_PER_PIXEL,  		32

// para modificar delay +/- registro x9

delay:
	movz x9, 0xfff,lsl 16 
	movk x9, 0xffff, lsl 00
	loop:
	sub x9, x9, 1
	cbnz x9, loop
	br lr

delay2:
	movz x9, 0xff,lsl 16 
	movk x9, 0xffff, lsl 00
loopD2:
	sub x9, x9, 1
	cbnz x9, loopD2
	br lr
	

Calcularpixel:                          // parametros : x3 = x , x4 = y
 
 	sub sp, sp, #8 			// Guardo el puntero en el stack
	stur lr, [sp]
	mov x0, 640			//x0 = 640
	mul x0, x0, x4			// x0 = 640 * y	
	add x0, x0, x3			// x0 = (640 * y) + x	
	lsl x0, x0, 2			// x0 = 4 * [x + (640 * y)] 
	add x0, x0, x20			// x0 = direccion-framebuffer +  4 * [x + (640 * y)]
	
 	ldur lr, [sp] 			// Recupero el puntero del stack
    add sp, sp, #8 
    br lr
     
dibujarcielo:  				// parametros : x3 = x , x4 = y , w10 = color
 
	sub sp, sp, #8 		
    stur lr, [sp]
 	mov x12, x0    		// x12 = direccion del pixel N
 	mov x8, x2		// x8 = tamano Y
 	
loopaC:
    mov x9, x1	        	// x9 = tamano X
    mov x11, x12		// x11 = x12 = direccion del pixel N                    //x11 auxiliar
     	 
colorearC:	
	stur w10,[x12]          // coloreo el pixel N
	add x12,x12,4	   	// siguiente pixel
	sub x9,x9,1	  	// resto contador X
	cbnz x9,colorearC	// si no termino la fila, realizo el salto colorear
	add x10, x10, 1
	mov x12, x11   		// x12 = direccion del pixel N
	sub x8, x8, 1		// decremento contador Y
	add x12, x12,2560	// x12 = voy hacia el pixel de abajo del pixel N
	cbnz x8,loopaC		// si no es la ultima fila, hago el salto loopa
	
 	ldur lr, [sp] 		
    add sp, sp, #8 
	br lr  
 
estrella:   		// parametro : x0 = direccion

	sub sp, sp, #8 		
    stur lr, [sp]	
    mov x7,x0      
	
	movz x10, 0xfc,lsl 16
	movk x10, 0xb814, lsl 00	
	mov x1, 2
	mov x2, 10
	bl dibujarcuadrado
	
	mov x1, 6
	mov x2, 6
	mov x7,2000
	lsl x7,x7,1
	add x7,x7,1112
	add x0,x0,x7
	bl dibujarcuadrado
	
	mov x1, 10
	mov x2, 2
	mov x7,2000
	lsl x7,x7,1
	add x7,x7,1112
	add x0,x0,x7
	bl dibujarcuadrado
	
	ldur lr, [sp] 		
    add sp, sp, #8 
	br lr
    

dibujarcuadrado:  // parametros: x3 = x , x4 = y , w10 = color
 
 	sub sp, sp, #8 
    stur lr, [sp]
 	mov x12, x0    		// x12 = direccion del pixel N
 	mov x8, x2		// x8 = tamano Y
 	
loopa:
	mov x9, x1	        // x9 = tamano X
   	mov x11, x12		// x11 = x12 = direccion del pixel N                   
     	 
colorear:	
	stur w10,[x12]          // coloreo el pixel N
	add x12,x12,4	        // siguiente pixel
	sub x9,x9,1	        // resto contador X
	cbnz x9,colorear        // si no termino la fila, realizo el salto colorear
    mov x12, x11           // x12 = direccion del pixel N
	sub x8, x8, 1		// decremento contador Y
	add x12, x12,2560	// x12 = voy hacia el pixel de abajo del pixel N
	cbnz x8,loopa		// si no es la ultima fila, hago el salto loopa
	
 	ldur lr, [sp] 
    add sp, sp, #8 
	br lr
      
      
dibujarLuna:
    
	sub sp, sp, #8 
   	stur lr, [sp]
	mov x7, x3
	mov x8, x4
	add x5, x4,x1		// con x5 me fijo si llego a final de Y
	add x6, x3,x1		// con x6 me fijo si llega al final de X			          
	mov x15, x3
	mov x16, x4
	sub x3, x3, x1      	// Inicio X		
		
resetYL:
	cmp x3, x6
	b.gt end
	sub x4, x5, x1
	sub x4, x4, x1  	// Inicio Y

cirloopL:
	cmp x4,x5
	b.eq next_fila

	sub x9, x3, x15			   
	mul x9, x9, x9				// x9 = (x0.fila - x3)**2 	
		
	sub x11, x4, x16			   
	mul x11, x11, x11			// x11 = (x0.columna - x4)**2

	add x13, x9, x11			// x13 = (x0.fila - x1)*2 + (x0.columna - x2)*2

	mov x12, x1
	mul x12, x12, x12			// x12 = radio**2

	cmp x12, x13
	
	b.ge color					//si x13 <= x12 
	b skip
colorL:		
	bl Calcularpixel	// then pintar pixel
	stur w10,[x0]
	
	
	
skipL:
	add x4, x4, #1
	                         // avanza pixel
	b cirloop
next_filaL:
	add x3, x3, #1
	b resetY
	
endL: 
	mov x3, x7
	mov x4, x8
	
	
	ldur lr, [sp] // Recupero el puntero de retorno del stack
    add sp, sp, #8 
    br lr
	ret
	
 
dibujarCirculo:     

	sub sp, sp, #8 
    stur lr, [sp]

	mov x7, x3
	mov x8, x4
	add x5, x4,x1		// con x5 me fijo si llego a final de Y
	add x6, x3,x1		// con x6 me fijo si llega al final de X
					          
	mov x15, x3
	mov x16, x4
	sub x3, x3, x1      // Inicio X		
		
resetY:
	cmp x3, x6
	b.gt end
	sub x4, x5, x1
	sub x4, x4, x1      // Inicio Y
cirloop:
	cmp x4,x5
	b.eq next_fila

	sub x9, x3, x15			   
	mul x9, x9, x9				// x9 = (x0.fila - x3)**2 	
		
	sub x11, x4, x16			   
	mul x11, x11, x11			// x11 = (x0.columna - x4)**2

	add x13, x9, x11			// x13 = (x0.fila - x1)*2 + (x0.columna - x2)*2

	mov x12, x1
	mul x12, x12, x12			// x12 = radio**2

	cmp x12, x13
	b.ge color				//si x13 <= x12 
	b skip
color:		
	bl Calcularpixel			// then pintar pixel
	stur w10,[x0]	
skip:
	add x4, x4, #1				// avanza pixel
	b cirloop
next_fila:
	add x3, x3, #1
	b resetY
end:
	mov x3, x7
	mov x4, x8
	
    ldur lr, [sp] 
    add sp, sp, #8 
    br lr


dibujartriangulo: 
 	
	sub sp, sp, #8 
    stur lr, [sp]
 	mov x8, x2    
 	mov x5, 1
loopat:
    mov x9, x5
    mov x11, x0 
coloreart:	
	stur w10,[x0]	   
	add x0,x0,4	   
	sub x9,x9,1	  
	cbnz x9,coloreart
	mov x0, x11   
	sub x8, x8, 1
	sub x0, x0, 2564
	add x5, x5, 2
	cbnz x8,loopat
	
 	ldur lr, [sp] 
 	add sp, sp, #8  
    br lr
 
 
dibujartrianguloparte2: 
 
 	sub sp, sp, #8 
    stur lr, [sp]

 	mov x8, x2
 	mov x5, 1
loopat2:
    	mov x9, x5
    	mov x11, x0 
coloreart2:	
	stur w10,[x0]	   
	add x0,x0,4	   
	sub x9,x9,1	  
	cbnz x9,coloreart2
	mov x0, x11   
	sub x8, x8, 1
	add x0, x0, 2556
	add x5, x5, 2
	cbnz x8,loopat2
	
 	ldur lr, [sp] 
    add sp, sp, #8
    br lr        



grietas:  				   
	sub sp, sp, #8 
    stur lr, [sp]
	movz x10, 0x00, lsl 16 
    movk x10, 0x0000, lsl 00
	mov x12, x0
pinto:
	stur w10,[x12]
	add x12,x12,641
	sub x5,x5,1
	cbnz x5,pinto 
	ldur lr, [sp] 
    add sp, sp, #8 
	br lr

dibujarmario:    			// x0 = direccion 

	sub sp, sp, #8 
    stur lr, [sp]	
    mov x7,x0      
      		
    // cuerpo mario
	movz x10, 0xff,lsl 16
	movk x10, 0x0000, lsl 00	
	mov x1, 30
	mov x2, 23
	bl dibujarcuadrado
	
	// brazo izquierdo		
	movz x10, 0x99,lsl 16
	movk x10, 0x4c00, lsl 00
	mov x1, 13
	mov x2, 13
	sub x0,x0,32
	bl dibujarcuadrado
        		
    // brazo derecho
    add x0,x0,132	
	bl dibujarcuadrado
        	
    	// muneca derecha	
    mov x1, 5
	mov x2, 13       	
    mov x7,5
    mov x6,4000
    mul x6,x6,x7
    add x6,x6,528
	add x0,x0,x6	
	bl dibujarcuadrado
	
	// muneca izquierda        	
    sub x0,x0,196	
	bl dibujarcuadrado
        	
    	// cara        	
	movz x10, 0xff,lsl 16
	movk x10, 0xb401, lsl 00
	mov x1, 20
	mov x2, 25		
	mov x8,42
	mov x6,2000
	mul x6,x6,x8
	add x6,x6,412		
	sub x0,x0,x6		
	bl dibujarcuadrado
		
	// ojos		
	movz x10, 0xffff,lsl 16
	movk x10, 0xffff, lsl 00	
	mov x1,5
	mov x2,5	
	mov x5,2000
	mov x6,5
	mul x5,x5,x6
	add x5,x5,280		
	add x0,x0,x5		
	bl dibujarcuadrado
		
	// pelo		
	movz x10, 0x0,lsl 16
	movk x10, 0x0000, lsl 00
	mov x1,15
	mov x2,5	
	sub x0,x0,92	
	bl dibujarcuadrado
		
	// orejas,nariz	
	movz x10, 0xff,lsl 16
	movk x10, 0xb401, lsl 00	
	mov x1,32
	mov x2,6		
	mov x5,5000
	lsl x5,x5,1
	add x5,x5,264
	add x0,x0,x5		
	bl dibujarcuadrado
		
	// gorro
	movz x10, 0xff,lsl 16
	movk x10, 0x0000, lsl 00	
	mov x1, 40
	mov x2, 6		
	mov x5,4000
	mov x6,6
	mul x5,x5,x6
	add x5,x5,1612		
	sub x0,x0,x5		
	bl dibujarcuadrado
		
	// gorro-arriba		
	mov x1, 25
	mov x2, 6
	mov x5,4000
	mov x6,3
	mul x5,x5,x6
	add x5,x5,772		
	sub x0,x0,x5		
	bl dibujarcuadrado
	

	// pierna izquierda
	mov x1,10
	mov x2,17
	mov x5,2000
	mov x6,70		
	mul x5,x5,x6
	add x5,x5,832		
	add x0,x0,x5
	sub x0,x0,40	
	bl dibujarcuadrado
	
	// pierna derecha	
	add x0,x0,80	
	bl dibujarcuadrado
	
	// zapas-derecha
	movz x10, 0x0,lsl 16
	movk x10, 0x0000, lsl 00
	mov x1,10
	mov x2,7
	mov x8,3600
	mov x9,7		
	mul x8,x8,x9
	add x8,x8,400	
	add x0,x0,x8	
	bl dibujarcuadrado
	
	// zapas-izquierda
	sub x0,x0,80
	bl dibujarcuadrado
	
    ldur lr, [sp] // Recupero el puntero de retorno del stack
    add sp, sp, #8 
	br lr


fondoNoche:

	sub sp, sp, #8 
    stur lr, [sp]

	movz x10, 0x00, lsl 16
    movk x10, 0x0033, lsl 00
    	
    	// CIELO
    	mov x1, 640  		//Tamaño X
    	mov x2, 120		// Tamaño Y
    	mov x3, 0  		//Posicion X
    	mov x4, 0 		//Posicion Y     
    	bl Calcularpixel
    	bl dibujarcielo
        
    	// LUNA2
		movz x10, 0x00, lsl 16 
    	movk x10, 0x0000, lsl 00
    	mov x1, 41 
    	mov x3, 70
    	mov x4, 50	
    	
    	bl Calcularpixel		
    	bl dibujarLuna    
     
	// MEDIA LUNA (LUNA TAPADA)
    	movz x10, 0xc0, lsl 16  
    	movk x10, 0xc0c0, lsl 00
		mov x4, 50  
    	mov x3, 70	
    	mov x1, 38  	
    	bl Calcularpixel			
   		bl dibujarLuna
    
    	// crater
		movz x10, 0xa0, lsl 16  
		movk x10, 0xa0a0, lsl 00
    	mov x4, 30
   		mov x3, 70	
    	mov x1, 4
    	bl Calcularpixel		
   		bl dibujarLuna
    
    	// crater 2
    	mov x4, 50
    	mov x3, 70
    	mov x1, 3
    	bl Calcularpixel		
    	bl dibujarLuna
    
    	// crater 3
    	mov x4, 80
   		mov x3, 65	
    	bl Calcularpixel		
    	bl dibujarLuna
    
    	// crater 4
    	mov x4, 60
    	mov x3, 83	
    	mov x1, 4
    	bl Calcularpixel		
    	bl dibujarLuna
    
	// crater 5
    	mov x4, 40
    	mov x3, 85
    	bl Calcularpixel		
    	bl dibujarLuna
    
	// crater 6
    	mov x4, 30
    	mov x3, 50
    	mov x1, 3
    	bl Calcularpixel		
    	bl dibujarLuna
    
    	// crater 7
    	mov x4, 70
    	mov x3, 50
    	bl Calcularpixel		
    	bl dibujarLuna
    
    	// crater 8
    	mov x4, 55
    	mov x3, 55
    	bl Calcularpixel		
    	bl dibujarLuna

    	// Estrella
    	mov x3 , 130
    	mov x4, 32
    	bl Calcularpixel
    	bl estrella

    	mov x3 , 500
    	mov x4, 60
    	bl Calcularpixel
    	bl estrella

    	mov x3 , 340
    	mov x4, 70
    	bl Calcularpixel
    	bl estrella

    	mov x3 , 250
    	mov x4, 23
    	bl Calcularpixel
    	bl estrella
		
    	mov x3 , 400
    	mov x4, 35
    	bl Calcularpixel
    	bl estrella
    
    	// EDI 1 
    	movz x10, 0xe5, lsl 16 
    	movk x10, 0xaa7a, lsl 00
    	mov x1, 210   //Tamaño X
    	mov x2, 260 // Tamaño Y
    	mov x3, 0  //Posicion X
    	mov x4, 120  //Posicion Y
    	bl Calcularpixel
    	bl dibujarcuadrado
    
    	// EDI 2
		movz x10, 0x2f, lsl 16 
    	movk x10, 0x3699, lsl 00
    	mov x1, 220   //Tamaño X
    	mov x2, 290 // Tamaño Y
    	mov x3, 210  //Posicion X
    	mov x4, 90  //Posicion Y
    	bl Calcularpixel
    	bl dibujarcuadrado 
          
    	// EDI 3
    	movz x10, 0x78, lsl 16 
    	movk x10, 0x0828, lsl 00
    	mov x1, 210   //Tamaño X
    	mov x2, 260 // Tamaño Y
    	mov x3, 430 //Posicion X
    	mov x4, 120  //Posicion Y
    	bl Calcularpixel
    	bl dibujarcuadrado
    
	// CONTORNOS DE LOS EDIFICIOS
    	movz x10, 0x00, lsl 16 
    	movk x10, 0x0000, lsl 00
    	mov x1, 210   //Tamaño X
    	mov x2, 5 // Tamaño Y
    	mov x3, 0 //Posicion X
    	mov x4, 120  //Posicion Y
    	bl Calcularpixel
    	bl dibujarcuadrado

    	mov x1, 230   //Tamaño X
    	mov x2, 5 // Tamaño Y
    	mov x3, 205 //Posicion X
    	mov x4, 90  //Posicion Y
    	bl Calcularpixel
    	bl dibujarcuadrado

    	mov x1, 210 //Tamaño X
    	mov x2, 5 // Tamaño Y
    	mov x3, 430 //Posicion X
    	mov x4, 120  //Posicion Y
    	bl Calcularpixel
    	bl dibujarcuadrado

    	mov x1, 5  //Tamaño X
    	mov x2, 290 // Tamaño Y
    	mov x3, 210 //Posicion X
    	mov x4, 90  //Posicion Y
    	bl Calcularpixel
    	bl dibujarcuadrado
	
    	mov x1, 5  //Tamaño X
    	mov x2, 290 // Tamaño Y
    	mov x3, 425 //Posicion X
    	mov x4, 90  //Posicion Y
    	bl Calcularpixel
    	bl dibujarcuadrado
       
    	// TECHO EDI 3
    	mov x1, 85  
    	mov x2, 85  
    	mov x3, 550 
    	mov x4, 40
    	bl Calcularpixel
    	bl dibujartrianguloparte2

    	movz x10, 0x78, lsl 16 
    	movk x10, 0x0828, lsl 00
    	mov x1, 75  
    	mov x2, 75  
    	mov x3, 550 
    	mov x4, 50
    	bl Calcularpixel
    	bl dibujartrianguloparte2

    	// VENTANAS
    	
    	// VENTANA EDI 1
    	movz x10, 0x00, lsl 16 
    	movk x10, 0x0000, lsl 00
    	mov x1, 105  			
    	mov x2, 80 			
    	mov x3, 52 			
    	mov x4, 180			
    	bl Calcularpixel
    	bl dibujarcuadrado

    	movz x10, 0xff, lsl 16 
    	movk x10, 0xf200, lsl 00
    	mov x1, 95  			
    	mov x2, 70 			
    	mov x3, 57 			
    	mov x4, 185			
    	bl Calcularpixel
    	bl dibujarcuadrado

    	// VENTANA EDI 2 
    	movz x10, 0x00, lsl 16 
    	movk x10, 0x0000, lsl 00
    	mov x1, 105  			
    	mov x2, 100 			
    	mov x3, 265 			
    	mov x4, 155			
    	bl Calcularpixel
    	bl dibujarcuadrado

    	movz x10, 0xff, lsl 16 
    	movk x10, 0xf200, lsl 00
    	mov x1, 95  	//Tamaño X
    	mov x2, 90 	// Tamaño Y
    	mov x3, 270 	//Posicion X
    	mov x4, 160	//Posicion Y
    	bl Calcularpixel
    	bl dibujarcuadrado

    	movz x10, 0x00, lsl 16 
    	movk x10, 0x0000, lsl 00
    	mov x1, 125  	//Tamaño X
    	mov x2, 20 	// Tamaño Y
    	mov x3, 255 	//Posicion X
    	mov x4, 255	//Posicion Y
    	bl Calcularpixel
    	bl dibujarcuadrado

    	// VENTANA EDI 3
    	mov x4, 210 	// posicion Y
    	mov x1, 50  	// radio		
    	mov x3, 550	// posicion X
    	bl Calcularpixel			
    	bl dibujarCirculo

    	movz x10, 0xff, lsl 16
    	movk x10, 0xf200, lsl 00
    	mov x4, 210 	// posicion Y
    	mov x1, 45  	// radio		
    	mov x3, 550	// posicion X
    	bl Calcularpixel			
    	bl dibujarCirculo

    	movz x10, 0x00, lsl 16 
    	movk x10, 0x0000, lsl 00
    	mov x1, 5  	//Tamaño X
    	mov x2, 99 	// Tamaño Y
    	mov x3, 549 	//Posicion X
    	mov x4, 161	//Posicion Y
    	bl Calcularpixel
    	bl dibujarcuadrado

    	mov x1, 99  	//Tamaño X
    	mov x2, 5 	// Tamaño Y
    	mov x3, 501 	//Posicion X
    	mov x4, 210	//Posicion Y
    	bl Calcularpixel
    	bl dibujarcuadrado

    	//CALLE
    	movz x10, 0x40, lsl 16 
    	movk x10, 0x4040, lsl 00
    	mov x1, 640   	//Tamaño X
    	mov x2, 100  	// Tamaño Y
    	mov x3, 0    	//Posicion X
    	mov x4, 380   	//Posicion Y
    	bl Calcularpixel
    	bl dibujarcuadrado

	// CONTORNO CALLE 
    	movz x10, 0x00, lsl 16 
    	movk x10, 0x0000, lsl 00
    	mov x1, 640   	//Tamaño X
    	mov x2, 5  	// Tamaño Y
    	mov x3, 0    	//Posicion X
    	mov x4, 380   	//Posicion Y
    	bl Calcularpixel
    	bl dibujarcuadrado

	// Linea calle 
    	movz x10, 0xff, lsl 16 
    	movk x10, 0xe02e, lsl 00
    	mov x1, 113   	//Tamaño X
    	mov x2, 5  	// Tamaño Y
    	mov x3, 140  	//Posicion X
    	mov x4, 450   	//Posicion Y
    	bl Calcularpixel
    	bl dibujarcuadrado

    	mov x1, 113 	//Tamaño X
    	mov x2, 5  	// Tamaño Y
    	mov x3, 273     //Posicion X
    	mov x4, 450  	//Posicion Y
    	bl Calcularpixel
    	bl dibujarcuadrado


    	mov x1, 113   	//Tamaño X
    	mov x2, 5  	// Tamaño Y
    	mov x3, 406   	//Posicion X
    	mov x4, 450   	//Posicion Y
    	bl Calcularpixel
    	bl dibujarcuadrado
    	
    	       
	//contorno puerta1
       	movz x10, 0x00, lsl 16 
       	movk x10, 0x0000, lsl 00
       	mov x1, 80   	//Tamaño X
       	mov x2, 110 	// Tamaño Y
       	mov x3, 60 	//Posicion X
       	mov x4, 270  	//Posicion Y
       	bl Calcularpixel
       	bl dibujarcuadrado
	       
       	//puerta1
       	movz x10, 0x66, lsl 16 
       	movk x10, 0x3300, lsl 00
       	mov x1, 70   	//Tamaño X
       	mov x2, 100	// Tamaño Y
       	mov x3, 70  	//Posicion X
       	mov x4, 280  	//Posicion Y
       	bl Calcularpixel
       	bl dibujarcuadrado
	 
       	// picaporte
        movz x10, 0x99, lsl 16
    	movk x10, 0x4c00, lsl 00
    	mov x4, 335 	// posicion Y
    	mov x1, 4  	// radio		
    	mov x3, 76	// posicion X
    	bl Calcularpixel			
    	bl dibujarCirculo

	//contorno puerta2
       	movz x10, 0x00, lsl 16 
       	movk x10, 0x0000, lsl 00
       	mov x1, 80   	//Tamaño X
       	mov x2, 100 	// Tamaño Y
       	mov x3, 280 	//Posicion X
       	mov x4, 280  	//Posicion Y
       	bl Calcularpixel
       	bl dibujarcuadrado
       
       	//puerta2
       	movz x10, 0x66, lsl 16 
       	movk x10, 0x3300, lsl 00
       	mov x1, 70   	//Tamaño X
       	mov x2, 90	// Tamaño Y
       	mov x3, 290  	//Posicion X
       	mov x4, 290  	//Posicion Y
       	bl Calcularpixel
       	bl dibujarcuadrado
       
	// picaporte2
        movz x10, 0x99, lsl 16
    	movk x10, 0x4c00, lsl 00
    	mov x4, 335 	// posicion Y
    	mov x1, 4  	// radio		
    	mov x3, 300	// posicion X
    	bl Calcularpixel			
    	bl dibujarCirculo
    	
    	
    	//contorno puerta3
       	movz x10, 0x00, lsl 16 
       	movk x10, 0x0000, lsl 00
       	mov x1, 90   	//Tamaño X
       	mov x2, 100 	// Tamaño Y
       	mov x3, 500 	//Posicion X
       	mov x4, 280  	//Posicion Y
       	bl Calcularpixel
       	bl dibujarcuadrado
       
       	//puerta3
      	movz x10, 0x66, lsl 16 
       	movk x10, 0x3300, lsl 00
       	mov x1, 80   	//Tamaño X
       	mov x2, 90	// Tamaño Y
       	mov x3, 510  	//Posicion X
       	mov x4, 290  	//Posicion Y
       	bl Calcularpixel
       	bl dibujarcuadrado
       
       	// picaporte3
        movz x10, 0x99, lsl 16
    	movk x10, 0x4c00, lsl 00
    	mov x4, 335 	// posicion Y
    	mov x1, 4  	// radio		
    	mov x3, 520	// posicion X
    	bl Calcularpixel			
    	bl dibujarCirculo

       	//vereda
       	movz x10, 0x80, lsl 16 
       	movk x10, 0x8080, lsl 00
       	mov x1, 640   	//Tamaño X
       	mov x2, 25	// Tamaño Y
       	mov x3, 0  	//Posicion X
       	mov x4, 383  	//Posicion Y
       	bl Calcularpixel
       	bl dibujarcuadrado
       	mov x5,100	// largo de la diagonal	
       	bl grietas
    
       	//contorno vereda
       	movz x10, 0x00, lsl 16 
       	movk x10, 0x0000, lsl 00
       	mov x1, 640   	//Tamaño X
       	mov x2, 10 	// Tamaño Y
       	mov x3, 0 	//Posicion X
       	mov x4,  408 	//Posicion Y
       	bl Calcularpixel
       	bl dibujarcuadrado

		ldur lr, [sp] 		
    	add sp, sp, #8 
		br lr


portalparametrizado:

		sub sp, sp, #8 
    	stur lr, [sp]

	// PORTAL IZQ
	// CONTORNO PORTAL
	
		movz x10, 0x00, lsl 16 
    	movk x10, 0x0000, lsl 00
    	mov x1, 50 
    	mov x2, 70  
    	bl dibujarcielo
	
    	mov x1, 20 
    	mov x2, 80 
    	mov x18,4000
    	mov x19,6
    	mul x18,x18,x19
        add x18,x18,1400
    	sub x0,x0,x18 
    	bl dibujarcielo
    	
    	
		movz x10, 0x00, lsl 16 
    	movk x10, 0xff00, lsl 00
    	mov x1, 40 
    	mov x2, 60  	
    	mov x18,4000
    	mov x19,9
    	mul x18,x18,x19
    	add x18,x18,2220
    	add x0,x0,x18    	
    	bl dibujarcielo

		mov x1, 10 
    	mov x2, 70
    	mov x18,4000
    	mov x19,6
    	mul x18,x18,x19
        add x18,x18,1400
    	sub x0,x0,x18 
   		bl dibujarcielo

	// PORTAL DER
	// CONTORNO PORTAL
		movz x10, 0x00, lsl 16 
    	movk x10, 0x0000, lsl 00
    	mov x1, 50 
    	mov x2, 70
    	mov x19,3000
    	mov x18,4
    	mul x18,x18,x19
    	add x18,x18,2940
    	add x0,x0,x18  
    	bl dibujarcielo
    
    	mov x1, 20 
    	mov x2, 80
    	mov x18,4000
    	mov x19,6
    	mul x18,x18,x19
        add x18,x18,1680
    	sub x0,x0,x18       	
    	bl dibujarcielo
		
	// PORTAL
		movz x10, 0x00, lsl 16 
    	movk x10, 0xff00, lsl 00
    	mov x1, 40 
    	mov x2, 60      	
    	mov x18,4000
    	mov x19,9
    	mul x18,x18,x19
        add x18,x18,2500
    	add x0,x0,x18    	
    	bl dibujarcielo
	
		mov x1, 10 
    	mov x2, 70    	
    	mov x18,4000
    	mov x19,6
    	mul x18,x18,x19
        add x18,x18,1680
    	sub x0,x0,x18     	
    	bl dibujarcielo

	ldur lr, [sp] 		
    	add sp, sp, #8 
	br lr
