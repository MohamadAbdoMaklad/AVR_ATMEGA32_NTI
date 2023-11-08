#include "LIB_STD.h"
#include "LIB_BIT_MATH.h"

#include "GI_Private.h"
#include "GI_Interface.h"

void GI_voidEnable(void)
{
	SET_BIT(GI_SREG,GI_SREG_IBIT);
}

void GI_voidDisable(void)
{
	CLEAR_BIT(GI_SREG,GI_SREG_IBIT);
}
