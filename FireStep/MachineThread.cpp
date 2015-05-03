#ifdef CMAKE
#include <cstring>
#endif
#include "Arduino.h"
#include "AnalogRead.h"
#include "version.h"
#include "MachineThread.h"

using namespace firestep;

void MachineThread::setup() {
    id = 'M';
#ifdef THROTTLE_SPEED
    ADC_LISTEN8(ANALOG_SPEED_PIN);
#endif
    Thread::setup();
}

MachineThread::MachineThread()
    : status(STATUS_IDLE) {
}

void MachineThread::displayStatus() {
    switch (status) {
	case STATUS_OK:
// don't change anything
break;
    case STATUS_IDLE:
    case STATUS_SERIAL_EOL_WAIT:
		machine.pDisplay->setStatus(DISPLAY_IDLE);
        break;
    case STATUS_JSON_PARSED:
    case STATUS_PROCESSING:
		machine.pDisplay->setStatus(DISPLAY_PROCESSING);
        break;
	case STATUS_OPERATOR:
		machine.pDisplay->setStatus(DISPLAY_OPERATOR);
		break;
    default:	// errors
		machine.pDisplay->setStatus(DISPLAY_ERROR);
        break;
    }

	machine.pDisplay->show();
}

void MachineThread::Heartbeat() {
#ifdef THROTTLE_SPEED
    controller.speed = ADCH;
    if (controller.speed <= 251) {
        ThreadEnable(false);
        for (byte iPause = controller.speed; iPause <= 247; iPause++) {
            for (byte iIdle = 0; iIdle < 10; iIdle++) {
                DELAY500NS;
                DELAY500NS;
            }
        }
        ThreadEnable(true);
    }
#endif
	
    switch (status) {
    case STATUS_IDLE:
        if (Serial.available()) {
            command.clear();
            status = command.parse();
        }
        break;
    case STATUS_SERIAL_EOL_WAIT:
        if (Serial.available()) {
            status = command.parse();
        }
        break;
    case STATUS_JSON_PARSED:
    case STATUS_PROCESSING:
        status = controller.process(machine, command);
        break;
    default:	// errors
    case STATUS_OK:
        command.response().printTo(Serial);
        Serial.println();
        status = STATUS_IDLE;
        break;
    }

	displayStatus();

    nextHeartbeat.ticks = 0;
}
