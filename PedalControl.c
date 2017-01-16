// Pedal Control Code.
// Example of badly written state-space code.

// Sensor Reading functions
int	BrakePedalReading()
{
	int value = 0;
	// Brake reading code would go here.
  return(value);
}

int	AccelPedalReading()
{
	int value = 0;
	// Accelerator reading code would go here.
	return(value);
}

bool	SkidDetector()
{
	bool value = false;
  // Skid detection code would go here.
	return(value);
}

// Braking System Actuator
// After this function is called, the brake actuator
// is set the value of the parameter passed to this
// function. The brake control will remain at this
// value until this function is called again.
void	BrakeControl(int BrakeSetting)
{
	// Code to convert brake setting to action goes here.
}

// Accelerator System Control
// After this function is called, the accelerator or
// throttle actuator is set to the value of the
// parameter passed to this function.
// The accelerator control will remain at this
// setting until this function is called again.
void 	AccelControl(int AccelSetting)
{
	// Code to convert accelerator setting to action goes here.
}

// Anti-Lock Brake System Control
// If control is true, the ABS system is active.
// If control is false, the ABS system is made inactive.
void	ABS(bool control)
{
	// Code to operate ABS system goes here.
}


// Main code loop of the controller.
task main() {
  int AccelP;
  int BrakeP;
  bool Skid;

  // Clear the ABS system
  ABS(false);

  // System stays in an infinite loop...
  while(1) {

    // Read the pedal sensors.
    AccelP = AccelPedalReading();
    BrakeP = BrakePedalReading();

    // Check the skid sensor.
    Skid   = SkidDetector();

    if ( ( BrakeP > 0 )  && ( AccelP == 0 ) ) {

      // Brake pedal is being pushed, process it.

      // Set the brake actuator.
      BrakeControl(BrakeP);

		/* For starters, I think it would be safer to set the throttle to zero first, before applying the brakes, as this could easily cause a skid.   */


      // Set throttle to zero.
      AccelControl(0);


		/* There is not actual checking if the vehicle is encountering a skid before setting the ABS to the appropriate setting, this code just automatically turns on the ABS, which could be detrimental. */


      // Turn on ABS system if vehicle skidding.
      ABS(Skid);

    } else if ( AccelP > 0 ) {

	/* The code doesn't check if the brakes are set to zero, doesn't even set the brakes to zero, just goes straight to setting the throttle.  This is not good. As indicated in the FSM diagram, you would want to check if the brake actuator to zero before entering the Accel_State.  */

      // Accelerator pedal is being pushed.
      AccelControl(AccelP);
      
      
      /* The code is now going to loop back, and it is going tobe very difficult to determine what is going to happen next, never mind if the vehicle is being properly controlled on the first time around of the loop. */

    }

  }
}
