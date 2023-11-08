#ifndef TIMER0_INTERFACE_H_
#define TIMER0_INTERFACE_H_


// timer 0 init
void T0_voidInit(void);
// timer 0 start
void T0_voidStart(void);
// timer stop
void T0_voidStop(void);
// Set callback OVF
void T0_voidSetCallBackOVF(v_P2F_v copy_LP2F);
// Set callback CTC
void T0_voidSetCallBackCTC(v_P2F_v copy_LP2F);
void T0_voidSetCompMatchVal(u8 copy_CTCVal);

void T0_voidDelay_ms_CTC(u32 copy_MS);


void T0_voidSetDytyCycle_PWM(u8 copy_u8DytyCycle);


#endif /* TIMER0_INTERFACE_H_ */