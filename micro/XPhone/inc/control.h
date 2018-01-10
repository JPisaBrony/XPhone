// the XPhone boots up in STOP mode.
// If the user holds the ARM button for a bit of time, the XPhone enters ARMED mode.
// In ARMED mode, the XPhone is waiting for one of three events:
// - if a key is hit, 				the SongTime is set to 0, and the mode is changed to RECORD.
// - if the pedal is stepped on, 	the SongTime is set to 0, and the mode is changed to RECORD.
// - if the ARM button is held for a bit of time again, this will disarm the XPhone. It will return to the last mode it was in (either STOP or PLAY).
// In RECORD mode, the XPhone keeps track of keys hit and saves them in the songCurrent.
// The XPhone will exit RECORD mode into PLAY mode. This happens one of two ways:
// - the pedal it stepped on
// - the ARM button is pressed
// When the XPhone is in PLAY mode, it just loops the songCurrent.
// In PLAY mode, if the user holds the ARM button, it will bypass ARMED mode, and enter directly into RECORD mode, allowing the user to play notes over the existing song (adding/layering/building more notes into the existing song interactively).
	
#ifndef CONTROL_H_DEF
	#define CONTROL_H_DEF
	#include <inttypes.h>
	#include "key.h"
	#include "GPIO.h" 
	#include "debug.h"
	#include "song.h"

	#define ctrlType 				uint8_t
	#define CTRL_MODE_STOP			(0)					// nothing happens in this state. default state.
	#define CTRL_MODE_ARMED			(1)
	#define CTRL_MODE_RECORD		(2)
	#define CTRL_MODE_PLAY			(3)
	#define CTRL_MODE_CAL			(4)
	#define CTRL_ARM_DBC_TIME		((KeyTimeType)500)	// milliseconds that the use must hold the ARM button down for it to arm the XPhone.
	#define CTRL_PEDAL_DBC_TIME		((KeyTimeType)500)	// milliseconds that the use must hold the ARM button down for it to arm the XPhone.
	#define CTRL_LED_BLINK_PERIOD	((KeyTimeType)500)	// milliseconds it takes for the LED to turn on and off when in a blinking mode (record / armed).
	#define CTRL_CAL_HOLD_TIME		((KeyTimeType)3000)	// milliseconds it takes for the calibration routine to be activated
	#define CTRL_CLEAR_HOLD_TIME	((KeyTimeType)1000)	// milliseconds it takes for the clear to respond to user telling the device it needs to clear the song.

	#define CTRL_IN_INACTIVE		(0)					// this indicates the input is inactive (off).
	#define CTRL_IN_ACTIVE_NEW		(1)					// this indicates the input JUST changed state.
	#define CTRL_IN_ACTIVE_OLD		(2)					// this indicates the input has been active for a while.

	ctrlType ctrlMode; 									// default mode is stopped.
	KeyTimeType ctrlModeTimeAdder;						// keeps track of when the last mode change was (useful for making the LED blink ON when the mode change happens - this gives VERY fast visual feedback.
	
	ctrlType ctrlArm;									// this tells us the user intended to press the arm button.
	KeyTimeType ctrlArmDBC;								// this is the debounce counter for the arm control input.
	ctrlType ctrlPedal;									// this tells us when the user intended to step on the floor pedal.
	KeyTimeType ctrlPedalDBC;							// this id the debounce counter for the floor pedal.
	ctrlType ctrlKeyHit;									// this tells us if a key was just hit by the user.
	ctrlType ctrlCal;									// this tells us if the user wants to do a calibration.
	KeyTimeType ctrlCalDBC;								// this tells us how long the cal button has been held down for
	ctrlType ctrlClear;									// this tells you if the user wants to clear the current song.
	ctrlType ctrlClearDBC;								// this tells you how long the user has been holding the clear button.
	
	//==============================================================================
	// input/output control functions
	//==============================================================================
	
	void ctrl_init();
	void ctrl_mode_set(ctrlType mode);
	void ctrl_in_debounce();
	void ctrl_mode_manage();
	void ctrl_LED();
	
	
#endif