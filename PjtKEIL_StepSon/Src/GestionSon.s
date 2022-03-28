	PRESERVE8
	THUMB   
		
	import LongueurSon
	import Son
	export CallbackSon
	export decalageSon
	export SortieSon
; ====================== zone de réservation de données,  ======================================
;Section RAM (read only) :
	area    mesdata,data,readonly
	

;Section RAM (read write):
	area    maram,data,readwrite
		
SortieSon dcd 0
decalageSon dcd 0

; ===============================================================================================
	


		
;Section ROM code (read only) :		
	area    moncode,code,readonly
; écrire le code ici		


CallbackSon proc
		push {lr, r3, r4, r5, r6}
		
		ldr r1, =Son
		ldr r2, =decalageSon
		ldr r3, [r2]
		ldr r4, =LongueurSon
		ldr r5, [r4]
		lsl r5, r5, #1
		ldr R6, =SortieSon
		
		; ldr R4, =FlagCligno
		; ldr R3, [R4]
		; cmp R3, #0
		
		; si on est à la première itération...
		cmp r3, #0
		bne pasZero
		
		ldrsh r0, [r1]
		mov r1, #720
		add r0, #32768
		mul r0, r0, r1
		asr r0, #16
		str r0, [r6]
		
		add r3, #2
		str r3, [r2]
		
		
		b endcallback
		
		
pasZero
		;si le son a fini d'etre lu, on sort
		cmp r3, r5
		bge endcallback
		
		;r0 contient l'échantillon
		;r1 est l'adresse du son
		;r2 est le décalage de l'adresse du son
		ldrsh r0, [r1, r3]
		mov r1, #720
		add r0, #32768
		mul r0, r0, r1
		asr r0, #16
		str r0, [r6]
		
		add r3, #2
		str r3, [r2]
				
		b endcallback


		
endcallback
		pop {r6, r5, r4, r3, lr}
		;jouer le son contenu dans r0
		bx lr
		endp
		
	END	