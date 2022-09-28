#include "msp430.h"
#include "ports.h"
#include "wheels.h"
#include "sm.h"
#include <string.h>
#include "adc.h"
#include "timers.h"
#include "detectors.h"
#include "pid.h"

extern volatile unsigned char display_changed;
extern char display_line[4][11];


void StateMachine(void) {

}
