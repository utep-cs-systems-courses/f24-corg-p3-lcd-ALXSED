    .text
    .global sound
    .extern buzzer_set_period

sound:
    cmp #1, R12
    JEQ wee

woo:
    mov #800, R12
    CALL #buzzer_set_period 
    RET                     

wee:
    mov #400, R12
    CALL #buzzer_set_period 
    RET                     

