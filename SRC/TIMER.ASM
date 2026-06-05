; **************************************************************************
; ! This is the MOST PRECISE and most convenient timing routine ever on PC !
; **************************************************************************
; Although this is real working code, it's not one of those cut-and-paste
; hi-tech-extra-portable stuff so you probably need to modify or rewrite
; it for your own compiler to work. The main idea is:
;
; PIT hardware resolution is cca 1.2MHz. It's clear that this is maximum
; precision timing you can pump from your PC. This stuff does exactly that!
; Your code can (or I should write 'could') run for 2479 years(!) and you
; still get 0.9 micro-second resolution timing. Cool, huh?
;
; Well, you say, I can do that! I set PIT counter to 1 and my handler
; gets called at 1.2MHz. Haha, nice try BUT the processor will then be
; interrupted cca 1 200 000 times per second! That's not the way.
;
; My way:
; Set PIT to cca 20Hz, install your int08 handler that increments some tick
; variable and when you need to read elapsed time not only check the
; tick_variable but also READ the timer. Simply READ the internal timer
; counter that decrements every 0.8 micro-second.
; I did it and it works fine. My function ReadTimer returns 32-bit word
; Higher word contains tick_variable (integer time)
; Lower word contains PIT_counter converted to .16 fixed point
; At the end you get 16.16 fixed point word, ie. for 20Hz PIT
; 3.25 means that 0.1625s elapsed. Simple and powerful.
;
; Perfect for FPS, joystick and profiling stuff.
; If you require extra-precise timing you should
;  1. Set this timer to the lowest frequency possible (19Hz) YES!!
;  2. Ensure no annoying interrupts occur during timing
;  3. Remove BIOS interrupt call from timer handler
;
; Have fun!
; This little piece of code was brought to you by
; -= Sayza =- (Maros Sandor) of 7Gods demo group (see the end of this file)
; All this is emailware, or , if you just can't thank for code you'll use
; consider this one freeware. Don't distribute modified versions, ok?! Thanx.
; ***************************************************************************
; tested with TASM 3.1, TLINK, BC++ 3.1
; ************ read on for more info ****************************************

; set appropriate model here, processor should be 386+
.MODEL SMALL
.386

;// PIT frequency (high and low word)
FREQUENCYlow EQU  34DDh
FREQUENCYhigh EQU 12h

;// DATA segment
.DATA
ALIGN 4
__tc DD 0               ; incremented at every IRQ 0 (integer time)
timconst DW 0           ; PIT DIV given_frequency
biosticks DW 0          ; BIOS is called when this overflows

.CODE
; all routines expect DS set to data segment !
; IRQ0 handler, increments __tc AND calls BIOS if needed
ALIGN 4
thandler PROC FAR
        push ax ds
        mov  ax,@data
        mov  ds,ax

        inc  __tc
        mov      ax,biosticks
        add      ax,timconst
        mov      biosticks,ax
        jc   ops_bios
        mov al,20h
        out 20h,al
        pop     ds ax
        iret
ops_bios:
;// we love BIOS, don't we?
        pop      ds ax
        DB       0EAh                   ;// jmp far
oldint08 DW 0,0
thandler ENDP

;// Sets PIT to desired frequency and installs our handler
PUBLIC _IniTimer
_IniTimer PROC
ARG freq:WORD
        push bp
        mov bp,sp

        mov             ax,FREQUENCYlow
        mov             dx,FREQUENCYhigh
        div             [freq]
        mov             timconst,ax
;// set new IRQ0 handler
        mov             ax,3508h
        int             21h
        mov     cs:oldint08,bx
        mov     cs:oldint08+2,es

        mov             ax,2508h
        push    ds cs
        pop             ds
        mov             dx,OFFSET cs:thandler
        int             21h
        pop             ds
;// ax = new PIT constant
        cli
        mov     al,34h
        out     43h,al
        mov ax,timconst
        out 40h,al
        mov al,ah
        out 40h,al
        sti

        pop     bp
        ret
_IniTimer ENDP

;// ~IniTimer
PUBLIC _ShutTimer
_ShutTimer PROC
;// set timer back to 18.2Hz
        cli
        mov     al,34h
        out     43h,al
        xor     ax,ax
        out 40h,al
        out 40h,al
        sti
;// we love BIOS, don't we?
        mov             ax,2508h
        push    ds
        mov             ds,cs:oldint08+2
        mov             dx,cs:oldint08
        int             21h
        pop             ds
        ret
_ShutTimer ENDP

; returns elapsed time since last call to ResetTimer in
; DX:AX (16.16 fixed point)
; Example: if PIT was set to 20Hz and 0.24s elapsed, then
; DX = 4       0.24*20              because 4 interrupts occured
; AX = 52428   (0.24*20 - DX)*65536 because we need .16 fixed point
PUBLIC _ReadTimer
_ReadTimer PROC
        xor             al,al
        out             43h,al
        in              al,40h
        mov             ah,al
        in              al,40h
        mov             dx,timconst
        xchg    al,ah
        sub             dx,ax
        xor             ax,ax
        div             [timconst]
        mov             dx,WORD PTR __tc
        ret
_ReadTimer ENDP

;// clears ticker __tc to ZERO AND resets internal PIT counter (fake)
PUBLIC _ResetTimer
_ResetTimer PROC
		cli
		mov     al,34h
		out     43h,al
		mov ax,timconst
		out 40h,al
		mov al,ah
		out 40h,al
		mov             __tc,0
		sti
		ret
_ResetTimer ENDP
END
; *************************************************************************
; If you find some use of this, send me E-mail, i'll be pleased ...
; 	sandorm@hron.fei.tuke.sk
; *************************************************************************
