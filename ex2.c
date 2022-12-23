//Group15
#include <avr/io.h>

#define FOSC 16000000
#define BAUD_RATE 9600
#define UBRR_VALUE FOSC/16/BAUD_RATE-1 //ubbr = 103.16
 

//initialize usart
void usart_init(long ubrr)
{
	//Set baud rate 
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;

    //Enable tx and rx
	UCSR0B = (1<<TXEN0)| (1<<RXEN0);

    //setting the asycrounus mode
	UCSR0C &= ~((1<<UMSEL00)| (1<< UMSEL01));

    //set the size of the data transmitting as 8bit
	UCSR0C |= ((1<<UCSZ01) | (1<<UCSZ00));	  
    //set no parity
	UCSR0C &= ~((1<<UPM01) | (1<<UPM00));     
    //stop bit
	UCSR0C &= ~(1<<USBS0);			 
}

//function to send a character
void usart_send( unsigned char data)
{
	//wait until buffer is empty 
	while (!(UCSR0A & (1<<UDRE0)));
  
	//write the data into the UDR0 register 
	UDR0 = data;
}

//function to receive a received character
unsigned char usart_receive( void )
{
	//wait until one character is recieved
	while (!(UCSR0A & (1<<RXC0)));
  
	//return data received from UDR0 register 
	return UDR0;
}

int main(void)
{
	//initialize 
	usart_init(UBRR_VALUE);

    char ch;
	while(1){
        //recieve the characters
        ch=usart_receive();

        // ignore non ASCII char
        if (ch<0 || ch>255){
          continue;
        }

        //encrypt uppercase alphabetic letters
        if(ch >= 'a' && ch <= 'z'){
                ch = ch+3;
                if(ch > 'z')
                    ch = ch-'z'+'a'-1;
        }

        //encrypt uppercase alphabetic letters
        else if(ch >= 'A' && ch <= 'Z'){
                ch = ch+3;
                if(ch > 'Z')
                    ch = ch-'Z'+'A'-1;
        }
        
        // pass it on the buffer
        usart_send(ch);
		
		
	}
}


