//Group 15
#include <avr/io.h>
#define FOSC 16000000
#define BAUD_RATE 9600
//ubbr = 103.16
#define UBRR_VALUE 103.16
 

//initialize usart
void usart_init(long ubrr)
{
	// Set the Baud Rate
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;

    //Enable TX and RX
	UCSR0B = (1<<TXEN0)| (1<<RXEN0);

    //Set up asynchronous mode, and set the size of the data transmitting as 8bit
	UCSR0C &= ~((1<<UMSEL00)| (1<< UMSEL01)); 
  UCSR0C |= ((1<<UCSZ01) | (1<<UCSZ00));	  


	UCSR0C &= ~((1<<UPM01) | (1<<UPM00));     //No parity

	UCSR0C &= ~(1<<USBS0);// 1 stop bit			 
}

//function to send a character
void usart_send( unsigned char data)
{
	//wait until buffer is empty 
	while (!(UCSR0A & (1<<UDRE0)));
  
	//write the data into the UDR0 register 
	UDR0 = data;
}

//function to receive a character
unsigned char usart_receive( void )
{
	//wait until one character is recieved
	while (!(UCSR0A & (1<<RXC0)));
  
	//return data received from UDR0 register 
	return UDR0;
}


int main(void)
{
	//call the initialize function
	usart_init(UBRR_VALUE);

    char string[39] = "E/18/128 Hariharan E/18/366 Thulasiyan";

    int  i = 0;
    char ch;
    
    //send each charecter in data
	while((ch=string[i])!='\0'){
		usart_send(ch);
        i++;
	}
    
    return 0;
}


