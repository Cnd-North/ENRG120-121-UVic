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

typedef enum SystemStateType {
  Idle_State = 0,
  Brake_State,
  Accel_State,
  Skid_State
} SystemStateType;

// Main code loop of the controller.
task main() {

  // State variable.
  SystemStateType SystemState = Idle_State;

  while(1) {
    int AccelP = AccelPedalReading();
    int BrakeP = BrakePedalReading();
    bool Skid  = SkidDetector();

    switch(SystemState) {
      case Idle_State:
        // Implementation of Idle State.
        AccelControl(0);
        BrakeControl(0);
        ABS(false);

        if ( ( AccelP > 0 ) && ( BrakeP == 0 ) ) {
          SystemState = Accel_State;
        }

        if ( ( AccelP == 0 ) && ( BrakeP > 0 ) ) {
          SystemState = Brake_State;
        }
        break;
      
      
      case Brake_State:
		
		AccelControl(0);         // Set throttle to zero.
		
		/* Might want to put in a delay, and check speed, or below some threshold 
		before applying Brake control, and determine how hard to apply the brakes depending on the speed,
		unless this is build into brake control function, otherwise a skid could occur very easily.  */
		
		BrakeControl(BrakeP);   // Set the brake actuator.
		ABS(false);             // Set ABS to OFF
		Skid  = SkidDetector()  // Check if skidding
		
		if ( Skid  == true )   // Go to Skid state if skidding
		{
          
          SystemState = Skid_State;
          
        }
		
		
		if ( ( AccelP == 0 ) && ( BrakeP == 0 ) )   // Go to Idle state
		{
          
          SystemState = Idle_State;
          
        }


        break;
        
        
      case Accel_State:

		BrakeControl(0);       // Set the brake actuator to zero.
		AccelControl(AccelP);  // Set the throttle.
		
		/*Personally, I would check for skidding and possibly enter skid state, 
		  just in case, you never know what could happen. */
		
		
		if ( ( BrakeP > 0 ) )   // Go to Brake state
		{
          
          SystemState = Brake_State;
          
        }
		
		
		if ( ( AccelP == 0 ) && ( BrakeP == 0 ) )   // Go to Idle state
		{
          
          SystemState = Idle_State;
          
        }

        break;
      
      
      case Skid_State:

		AccelControl(0);         // Set throttle to zero.
		BrakeControl(BrakeP);   // Set the brake actuator.
		ABS(true);             // Set ABS to ON - we are skidding people.
		Skid  = SkidDetector()  // Check if skidding
		
		/* You will maybe think that this first statement is not necessary, 
		but if the ABS does not correct the skid, instead of going to brake state 
		and then checking for a skid, we can save time (milliseconds, which could make a difference)
		by entering the Skid_State immediately  */
		
		
		if ( Skid  == true )   // Go to Skid state if skidding
		{
          
          SystemState = Skid_State;
          
        }
        
        if ( Skid  == false )   // Go to Brake state if not skidding
		{
          
          SystemState = Brake_State;
          
        }
		


        break;
    }
  }
}
