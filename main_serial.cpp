
#include "stm32f10x.h"                  // Device header
#include "serial.h"

serial UsartSerComm;

char buffer [255];		//buffer for messages
int i;
int main(void)
{
	UsartSerComm.SerialPort(1); 			//Set USART1 ON
	UsartSerComm.BaudRate(9600, 1);		//SET baudrate on selected port
	UsartSerComm.Begin(1);

	while(1)
	{
		i++;
		UsartSerComm.println("hallo %d \n", i);    //print message with arguments
		delay;
	}


}
