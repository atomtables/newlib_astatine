[bits 32]
section .text
global _start

; Below is a simple implementation of crt0.s for x86_64. 
; It assumes that the program loader has put *argv and *envp on the stack, 
; and that %rdi contains argc, %rsi contains argv, %rdx contains envc, and %rcx contains envp 

; extern initialize_standard_library
extern main
extern exit
extern _init
_start:
    ; Set up end of the stack frame linked list.
    mov     ebp, 0
    push    ebp        ; rip = 0
    push    ebp        ; rbp = 0
    mov     ebp, esp

    ; We need those in a moment when we call main.
    push    esi
    push    edi

    ; Run the global constructors.
    call    _init

    ; Restore argc and argv.
    pop     edi
    pop     esi

    ; Run main.
    call    main

    ; Terminate the process with the exit code.
    push    eax
    call    exit
