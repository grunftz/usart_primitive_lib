#ifndef serial_h
#define serial_h


#define delay for(int i=0;i<=5000;i++);

extern char buffer[];

class serial{
	
	private:
		int usart1;
		int usart2;
		int usart3;
		int speed1;
		int speed2;
		int speed3;
	public:
	
		serial();
		void SerialPort(int Port);
		void BaudRate(int BaudRate, int Port);
		void Begin(int Port);
		void println(char *msg, ...);
		//~serial();
};

#endif


