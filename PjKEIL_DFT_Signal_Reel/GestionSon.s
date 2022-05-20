	PRESERVE8
	THUMB   
		
	import LongueurSon
	import Son
	export CallbackSon
	export StartSon
	export decalageSon
	export SortieSon
		
	include Driver/DriverJeuLaser.inc
; ====================== zone de réservation de données,  ======================================
;Section RAM (read only) :
	area    mesdata,data,readonly
	

;Section RAM (read write):
	area    maram,data,readwrite
		
SortieSon dcd 0
decalageSon dcd LongueurSon

; ===============================================================================================
	


		
;Section ROM code (read only) :		
	area    moncode,code,readonly
; écrire le code ici	


StartSon proc		
		ldr r0, =decalageSon
		mov r1, #0
		str r1, [r0]
		
		endp
	


CallbackSon proc
		push {lr, r4-r6}
		
		ldr r1, =Son
		ldr r2, =decalageSon
		ldr r3, [r2]
		ldr r4, =LongueurSon
		ldr r5, [r4]
		ldr R6, =SortieSon


		; si on est à la fin...
		cmp r3, r5
		bge endcallback
		
		
		ldrsh r0, [r1, r3, lsl #1]
		mov r1, #720
		add r0, #32768
		mul r0, r0, r1
		asr r0, #16
		str r0, [r6]
		
		add r3, #1
		str r3, [r2]
		
		bl PWM_Set_Value_TIM3_Ch3

		
endcallback
		pop {lr, r4-r6}
		bx lr
		endp
		
	END	