	IFNDEF BAUD
BAUD            = 2400
	ENDIF

; For SC/MP I, MICROCYCLE should be 2.0
; For SC/MP II (INS8060), MICROCYCLE should be 1.0
MICROCYCLE      = 1.0

CYCLES_PER_BIT  = INT(1000000.0/BAUD/MICROCYCLE)

calc_delay_cycles FUNCTION a,d,13+2*a+514*d
calc_delay_d      FUNCTION cycles,INT((cycles-13)/514)
calc_delay_a      FUNCTION cycles,INT(((cycles-13)#514)/2)

        IFNDEF S_FLAG0
S_FLAG0         = 0x01
        ENDIF

        IFNDEF S_SENSEB
S_SENSEB        = 0x20
        ENDIF
