#include "stm32f10x.h"                  // Device header
#include "serial.h"  
#include <stdio.h>													
#include <stdint.h>
#include "string.h"													//string lib
#include "stdlib.h"													//standarad functions lib
#include "stdarg.h"													//standard arguments lib

serial::serial()
{
	usart1=1;
	usart2=2;
	usart3=3;
	
	speed1=2400;
	speed2=9600;
	speed3=19200;
	
}


void serial::println (char *msg, ...)
{
	va_list args; 														//get the list of arguments
	va_start(args,msg);												//extract argumets from message, reformat message
	vsprintf(buffer,msg,args);								//formating message acording to passed arguments

	//fill the buffer
	
	for(int i=0; i<strlen(buffer); i++)
	{
		USART1->DR=buffer[i];										//byte by byte filing sending data via TX
		
		while(!(USART1->SR & USART_SR_TXE)); 		//fill the array until the TX registar is empty
		
	}
}

void serial::Begin(int Port)
	
{
			switch (Port)
		
	{
	case 1:
			
		USART1->CR1 |=USART_CR1_RE| USART_CR1_TE | USART_CR1_UE; 
	
	break;
	
	case 2:
		USART2->CR1 |=USART_CR1_RE| USART_CR1_TE | USART_CR1_UE; 
	
	break;
	
	case 3:
		USART3->CR1 |=USART_CR1_RE| USART_CR1_TE | USART_CR1_UE; 
	
	break;
	}
}


void serial::BaudRate(int Baudrate, int Port)
{
	switch (Baudrate)
	{
		case 2400:
				if(Port==usart1){USART1->BRR =(72000000/(16*Baudrate));}; //2400
				if(Port==usart2){USART2->BRR= (72000000/(16*Baudrate));}; //2400
				if(Port==usart3){USART3->BRR= (72000000/(16*Baudrate));}; //2400
		break;
		
		case 9600:
				if(Port==usart1){USART1->BRR = 0x1D4C;}; //9600
				if(Port==usart2){USART2->BRR= (72000000/(16*Baudrate));}; //9600
				if(Port==usart3){USART3->BRR= (72000000/(16*Baudrate));}; //9600
			
		break;
		
		case 19200:
				if(Port==usart1){USART1->BRR =(72000000/(16*Baudrate));}; //19200
				if(Port==usart2){USART2->BRR= (72000000/(16*Baudrate));}; //19200
				if(Port==usart3){USART3->BRR= (72000000/(16*Baudrate));}; //19200
		break;
		
	
	}
		
}

void serial::SerialPort(int Port)
{

	if (Port==usart1)
	{
		//gpio A clock enabled //enabling  USART1
		RCC->APB2ENR |=RCC_APB2ENR_IOPAEN | RCC_APB2ENR_USART1EN;		
		//PA9 TX pin Alternative push pull 50MHz output  -> 1011
		GPIOA->CRH |=GPIO_CRH_MODE9 |GPIO_CRH_CNF9_1;
		GPIOA->CRH &=~GPIO_CRH_CNF9_0;      
		//PA10 RX pin floating input  -> 0100 //default state of GPIO	
	}
	
		if (Port==usart2)
	{
		//gpio A clock enabled //enabling  USART2
		RCC->APB2ENR |=RCC_APB2ENR_IOPAEN | RCC_APB1ENR_USART2EN;		
		//pin konfiguration for uart rx/tx
		//PA2 TX pin Alternative push pull 50MHz output  -> 1011
		GPIOA->CRL |=GPIO_CRL_MODE2  |GPIO_CRL_CNF2_1;
		GPIOA->CRL &=~GPIO_CRL_CNF2_0;      
		//PA3 RX pin floating input  -> 0100 //default state of GPIO	
	}
	
	if (Port==usart3)
	{
		//gpio B clock enabled //enabling  USART3
		RCC->APB2ENR |=RCC_APB2ENR_IOPBEN | RCC_APB1ENR_USART3EN;
		//pin konfiguration for uart rx/tx
		//PB10 TX pin Alternative push pull 50MHz output  -> 1011
		GPIOB->CRH |=GPIO_CRH_MODE10  | GPIO_CRH_CNF10_1;
		GPIOB->CRH &=~GPIO_CRH_CNF10_0;      
		//PB11 RX pin floating input  -> 0100 //default state of GPIO
	}

}
