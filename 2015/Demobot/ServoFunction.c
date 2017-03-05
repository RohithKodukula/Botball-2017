void setServoSlow(int port, int newPos)
{
	int currentPos = get_servo_position(port);
	while(currentPos>newPos+2)
	{
		currentPos=currentPos-2;
		set_servo_position(port,currentPos);
		msleep(20);
	}
	while(currentPos < newPos - 2)
	{
		currentPos=currentPos+2;
		set_servo_position(port,currentPos);
		msleep(20);
	}
}
