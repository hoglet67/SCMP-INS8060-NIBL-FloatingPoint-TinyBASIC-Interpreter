B34_CYCLES = CYCLES_PER_BIT - 97
TTY_B3     = calc_delay_a(B34_CYCLES)
TTY_B4     = calc_delay_d(B34_CYCLES)

B12_CYCLES = 3 * CYCLES_PER_BIT / 2 - calc_delay_cycles(TTY_B3, TTY_B4) - 66
TTY_B1     = calc_delay_a(B12_CYCLES)
TTY_B2     = calc_delay_d(B12_CYCLES)

B5_CYCLES  = CYCLES_PER_BIT / 2
TTY_B5     = 1 + calc_delay_d(B5_CYCLES)

        LDI     0x08            ; SET COUNT
        ST      -21(P2)                                         ;
GWAIT:  CSA                     ; WAIT FOR START BIT            ;        5*0.5
        ANI     S_SENSEB                                        ;       10*0.5
        JNZ     GWAIT                                           ;        9*0.5
        LDI     TTY_B1          ; DELAY 1/2 BIT TIME            ;       10
        DLY     TTY_B2          ; (TTY_B1=C2 AND TTY_B2=00)     ;        0
        CSA                     ; IS START BIT STILL THERE?     ;        5
        ANI     S_SENSEB                                        ;       10
        JNZ     GWAIT           ; NO                            ;        9
GINP:   LDI     TTY_B3          ; DELAY BIT TIME                ;  10   10
        DLY     TTY_B4          ; (TTY_B3=76 AND TTY_B4=01)     ;   0    0
        CSA                     ; GET BIT (SENSEB)              ;   5   --
        ANI     S_SENSEB                                        ;  10   66 (=>D12_CYCLES)
        JZ      GZERO                                           ;  10  (9+11)*0.5
        LDI     1                                               ;   5  (10+0)*0.5
GZERO:  RRL                     ; ROTATE INTO LINK              ;   5
        XAE                                                     ;   7
        SRL                     ; SHIFT INTO CHARACTER          ;   5
        XAE                     ; RETURN CHAR TO E              ;   7
        DLD     -21(P2)         ; DECREMENT BIT COUNT           ;  22
        JNZ     GINP            ; LOOP UNTIL 0                  ;  11
        DLY     TTY_B5          ; SET DELAY (TTY_B5=01)         ;  --
        LDE                     ; LOAD CHARACTER FROM E         ;  97 (=>D34_CYCLES)
        ANI     0x7F            ; MASK PARITY BIT
        XAE
        LDE
