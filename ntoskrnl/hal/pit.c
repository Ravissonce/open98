#include "hal.h"

ULONG64 ulTick = 0;

VOID
Sleep(
	LONG Seconds
)
{
	UINT lTick;
	lTick = ulTick + ( Seconds * 100 );

	while ( ulTick < lTick )
		;
}

ULONG64
KiGetTickCount(

)
{
	return ulTick;
}

STATIC VOID
KiUpdateTick(
	struct interrupt_registers *reg
)
{
	ulTick++;
}

VOID
HalInitPIT(

)
{
	HalRegisterInterrupt(
		IRQ0,
		KiUpdateTick
	);
	

	ULONG64 ulDivisor = ( ULONG64 )( 1193180 / 1000 );

	UCHAR ucLow = ( UCHAR )( ulDivisor & 0xFF );
	UCHAR ucHigh = ( UCHAR )( ( ulDivisor >> 8 ) & 0xFF );

	outb( 0x43, 0x36 );

	outb( 0x40, ucLow );
	outb( 0x40, ucHigh );

	void( *term_write )( const char *string, UINT length ) = term_write_ptr;
	term_write( "Initialized PIT\n", 17 );
}