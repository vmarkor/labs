;; Registers EAX, ECX, and EDX are caller-saved, and the rest are callee-saved. (cdecl)
; Works slow for big primes.
global fact
section .text 

; ebp+8 — number
; ebp+12 — callback function
fact:
    push ebp
    mov ebp, esp
    
    push edi
    push ebx
    push esi

    ; let i = 2
    ; step 0: if number == 1 or 0 - pass number to callback and stop 
    ; step 1: divide number by i (2 at start)
    ;         if rem equal zero, pass i to callback. if number = 1, stop. else go to step 1
    ;         if its not zero, i++ and go to step 1

    mov eax, [ebp+8]    ; number
    mov edi, [ebp+12]   ; callback function

    ; -- step 0 --
    ; Check if number is more than 1, otherwise pass to callback and stop
    cmp eax, 1
    ja .greater_one

    ; Pass number to callback function
    push eax
    call edi
    add esp, 4
    jmp .exit

    .greater_one:
    ; -- step 1 --
    mov ebx, 2
    .factor_loop:
        mov esi, eax
        xor edx, edx
        div ebx
        cmp edx, 0
        je .callback
        inc ebx
        mov eax, esi
    jmp .factor_loop

    .callback:
        ; Save number since eax is reg for return
        mov esi, eax    

        ; Call callback function
        push ebx        
        call edi        
        add esp, 4      
        
        ; Check if callback returned correctly
        cmp eax, 0      
        jne .exit

        ; Restore saved number and if its not 1, get back in factor loop
        mov eax, esi
        cmp eax, 1
        je .exit_no_err

        jmp .factor_loop

    .exit_no_err
    mov eax, 0
    
    .exit:
    pop esi
    pop ebx
    pop edi

    pop ebp 
    ret 