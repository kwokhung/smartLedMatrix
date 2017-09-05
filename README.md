# smartLedMatrix

git clone https://github.com/kwokhung/smartLedMatrix.git

#define TIMER2_COMPA_vect _VECTOR(7)   /* Timer/Counter2 Compare Match A */

ISR(TIMER2_COMPA_vect)
{
    LedMatrix::scan();
};

#  define ISR(vector, ...)            \
    extern "C" void vector (void) __attribute__ ((signal,__INTR_ATTRS)) __VA_ARGS__; \
    void vector (void)

extern "C" void _VECTOR(7) (void) __attribute__ ((signal,__INTR_ATTRS));
void _VECTOR(7) (void) {
    // something here
}

extern "C" void __vector_7 (void) __attribute__ ((signal,__INTR_ATTRS));
void __vector_7 (void) {
    // something here
}    