;
; © [2026] Microchip Technology Inc. and its subsidiaries.
; 
;    Subject to your compliance with these terms, you may use Microchip 
;    software and any derivatives exclusively with Microchip products. 
;    You are responsible for complying with 3rd party license terms  
;    applicable to your use of 3rd party software (including open source  
;    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
;    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
;    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
;    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
;    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
;    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
;    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
;    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
;    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
;    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
;    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
;    THIS SOFTWARE.


.section .text

.global fmul_FP16xU16
; C prototype:
; uint16_t fmul_FP16xU16(fixp16_t a, uint16_t b);
;     params: R25:R24=a, R23:R22=b
;     retval: R25:R24
;  temporary: R25:R24:R23:R22 tempresult
; arg copies: R19:R18 R21:R20 a, b copies
; fmul only works with r16-r23
fmul_FP16xU16:
    movw    r18, r24  ;   r25:r24 -> r19:r18  a
    movw    r20, r22  ;   r23:r22 -> r21:r20  b
    clr     r26       ;  temporary zero
    fmul    r19, r21  ; r19*r21*2 -> r1:r0  ; (ah * bh) << 1
    movw    r24, r0   ;     r1:r0 -> r25:r24
    fmul    r18, r20  ; r18*r20*2 -> r1:r0  ; (al * bl) << 1
    movw    r22, r0   ;     r1:r0 -> r23:r22
    adc     r24, r26  ;   0+r24+C -> r24+C
    fmul    r19, r20  ; r19*r20*2 -> r1:r0  ; (ah * bl) << 1
    add     r23, r0   ;    r23+r0 -> r23+C
    adc     r24, r1   ;  r24+r1+C -> r24+C
    adc     r25, r26  ;   0+r25+C -> r25
    fmul    r18, r21  ; r18*r21*2 -> r1:r0  ; (al * bh) << 1
    add     r23, r0   ;    r23+r0 -> r23+C
    adc     r24, r1   ;  r24+r1+C -> r24+C
    adc     r25, r26  ;   0+r25+C -> r25
    clr     r1        ; restore zero reg
    ret

