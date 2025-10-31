B67_CYCLES = 13 ; minium delay for DLY
TTY_B6     = calc_delay_a(B67_CYCLES)
TTY_B7     = calc_delay_d(B67_CYCLES)

B89_CYCLES = CYCLES_PER_BIT - 144
TTY_B8     = calc_delay_a(B89_CYCLES)
TTY_B9     = calc_delay_d(B89_CYCLES)

        ANI     0x7F            ; MASK OFF PARITY BIT
        XAE                     ; SAVE IN EXT
        ST      -127(P2)        ; STORE IN RAM
        LDI     TTY_B6          ; SET DELAY FOR START BIT
        DLY     TTY_B7          ; (TTY_B6=30 AND TTY_B7=03)
        CSA                     ; GET STATUS
        ORI     1               ; SET START BIT (INVERTED LOGIC)
        CAS                     ; SET STATUS
        LDI     9               ; GET BIT COUNT
        ST      -24(P2)         ; STORE IN RAM
PUTA1:  LDI     TTY_B8          ; SET DELAY FOR 1 BIT TIME      ; 10
        DLY     TTY_B9          ; (TTY_B8=5C AND TTY_B9=01)     ;  0
        DLD     -24(P2)         ; DECREMENT BIT COUNT           ; 22
        JZ      PUTA2                                           ;  9
        LDE                     ; PREPARE NEXT BIT              ;  6
        ANI     S_FLAG0                                         ; 10
        ST      -23(P2)                                         ; 18
        XAE                     ; SHIFT DATA RIGHT ONE BIT      ;  7
        RR                                                      ;  5
        XAE                                                     ;  7
        CSA                     ; SET UP OUTPUT BIT             ;  5
        ORI     S_FLAG0                                         ; 10
        XOR     -23(P2)                                         ; 18
        CAS                     ; PUT BIT TO TTY                ;  6
        JMP     PUTA1                                           ; 11
PUTA2:  CSA                     ; SET STOP BIT                  ;---
        ANI     0xFE                                            ;144
        CAS
