//----------------------------------------------------------------------------------------------------
// Name: driveEncoderDistance
//----------------------------------------------------------------------------------------------------
// Description:
// 	This function takes a left speed, right speed, rotations to move and the brake mode
// 	at the end and then drives at the speed for each motor for the number of rotations
// 	and then sets the brakes or coasts depending on the brake mode.
//----------------------------------------------------------------------------------------------------
//Inputs:
//	leftSpeed	Float	Speed of left wheel
//	rightSpeed	Float	Speed of the right wheel
//	rotations	Float	Distance to move
//	brakeMode	Bool	True = Turn on brakes at the end;  False = Coast at the end
//----------------------------------------------------------------------------------------------------
void driveEncoderDistance(float leftspeed, float rightSpeed, float rotationsToMove, bool brakeMode)
{

	float degreesToMove;


	// Always make sure rotations is positive.  If it is negative, ignore it.   Needs to have negative speed to go backwards. 
	if (rotationsToMove < 0)
	{
			rotationsToMove = -rotationsToMove;
	}

	// Compute the number of degrees to move.
	degreesToMove = 360 * rotationsToMove;


	// Remove the brakes if they are applied
	setDriveMotorsToCoast();


	// Reset the Motor Encoders
	resetDriveMotorEncoders();

	// Start Motors with the proper speed.
	setMotorSpeed(leftDrive, leftspeed);
	setMotorSpeed(rightDrive, rightSpeed);


	// Wait until the left motor encoder is greater than or equal to the degrees to move.
	while (abs(getLeftMotorEncoder()) <= degreesToMove)
	{

	}

	turnOffDriveMotors();


	setBrakeMode(brakeMode);


}



//----------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------
void driveStraightEncoderDistance(float speed, float rotationsToMove, bool brakeMode)
{

	float error;
	float correctionFactor;
	float speedLeft;
	float speedRight;
	float degreesToMove;


	// Always make sure rotations is positive.
	if (rotationsToMove < 0)
	{
			rotationsToMove = -rotationsToMove;
	}

	// Compute the number of degrees to move.
	degreesToMove = 360 * rotationsToMove;

	// Remove the brakes if they are applied
	setDriveMotorsToCoast();

	// Reset the Motor Encoders
	resetDriveMotorEncoders();

	while (abs(getLeftMotorEncoder()) <= degreesToMove)
	{
		error = abs(getLeftMotorEncoder()) - abs(getRightMotorEncoder());
		correctionFactor = error * .01;
		speedLeft = speed - correctionFactor;
		speedRight = speed + correctionFactor;

		setMotorSpeed(leftDrive, speedLeft);
		setMotorSpeed(rightDrive, speedRight);


	}

	turnOffDriveMotors();

	setBrakeMode(brakeMode);

}