/*
 Name:		BluetoothAnalogController.ino
 Created:	11/28/2015 5:18:47 PM
 Author:	XRC_7331
*/

#include <SoftwareSerial.h>
#include "controller\ArrowController.h"
#include "interruptor\WaitInterruptor.h"
#include "bluetooth\BluetoothModule.h"

#define REQUEST_DIRECTION "0"

ArrowController testController;
BluetoothModule bluetooth;

// the setup function runs once when you press reset or power the board
void setup() {
	//testController.interruptor = new WaitInterruptor(300);

	bluetooth.SendMessage(REQUEST_DIRECTION);
}

// the loop function runs over and over again until power down or reset
void loop() {

	if (bluetooth.IsDataAvailable())
	{
		char data;
		while (bluetooth.IsDataAvailable())
			data = bluetooth.GetNextData();

		/*switch (data)
		{
		case 1:
			testController.dir = MoveDir::FORWARD;
			break;
		case 2:
			testController.dir = MoveDir::LEFT;
			break;
		case 3:
			testController.dir = MoveDir::RIGHT;
			break;
		case 4:
			testController.dir = MoveDir::BACKWARD;
			break;
		default:
			testController.dir = MoveDir::UNDEF;
			break;
		}*/

		if (data < 0 || data > 4)
			data = 0;
		testController.dir = static_cast<MoveDir>(data);

		testController.Move();

		bluetooth.SendMessage(REQUEST_DIRECTION);
	}
	delay(200);
}

