 
 
 
 
 



















 



#pragma system_include



























 


  #pragma system_include









 


  #pragma system_include

#pragma language=save
#pragma language=extended





 

typedef unsigned short __istate_t;

 
typedef __istate_t istate_t;


  __intrinsic void __no_operation(void);
  __intrinsic void __enable_interrupt(void);
  __intrinsic void __disable_interrupt(void);

  __intrinsic __istate_t __get_interrupt_state(void);
  __intrinsic void       __set_interrupt_state(__istate_t);

  __intrinsic void __op_code(unsigned short);

  __intrinsic unsigned short __swap_bytes(unsigned short);

  __intrinsic long __code_distance(void);

  __intrinsic void           __bic_SR_register(unsigned short);
  __intrinsic void           __bis_SR_register(unsigned short);
  __intrinsic unsigned short __get_SR_register(void);

  __intrinsic void           __bic_SR_register_on_exit(unsigned short);
  __intrinsic void           __bis_SR_register_on_exit(unsigned short);
  __intrinsic unsigned short __get_SR_register_on_exit(void);

  __intrinsic unsigned short     __bcd_add_short(unsigned short,
                                                 unsigned short);

  __intrinsic unsigned long      __bcd_add_long (unsigned long,
                                                 unsigned long);

  __intrinsic unsigned long long __bcd_add_long_long(unsigned long long,
                                                     unsigned long long);

  







 

  __intrinsic unsigned short __even_in_range(unsigned short __value,
                                             unsigned short __bound);

   
  __intrinsic void __delay_cycles(unsigned long __cycles);

  


 

  __intrinsic unsigned short __get_R4_register(void);
  __intrinsic void           __set_R4_register(unsigned short);

  __intrinsic unsigned short __get_R5_register(void);
  __intrinsic void           __set_R5_register(unsigned short);

  __intrinsic unsigned short __get_SP_register(void);
  __intrinsic void           __set_SP_register(unsigned short);


  



 
  __intrinsic int __low_level_init(void);


  

 

  









 

  __intrinsic void __data20_write_char (unsigned long  __addr,
                                        unsigned char  __value);

  __intrinsic void __data20_write_short(unsigned long  __addr,
                                        unsigned short __value);

  __intrinsic void __data20_write_long (unsigned long  __addr,
                                        unsigned long  __value);

  __intrinsic unsigned char  __data20_read_char (unsigned long __addr);
  __intrinsic unsigned short __data20_read_short(unsigned long __addr);
  __intrinsic unsigned long  __data20_read_long (unsigned long __addr);

  


 
  __intrinsic void __data16_write_addr (unsigned short __addr,
                                        unsigned long  __value);

  __intrinsic unsigned long  __data16_read_addr (unsigned short __addr);







 




 











 





 







#pragma language=restore


#pragma language=save
#pragma language=extended




 


  

 
  __intrinsic unsigned short _BIS_SR(unsigned short);

  

 
  __intrinsic unsigned short _BIC_SR(unsigned short);

  

 
  __intrinsic unsigned short _BIS_SR_IRQ(unsigned short);

  

 
  __intrinsic unsigned short _BIC_SR_IRQ(unsigned short);

  
 
  __intrinsic unsigned short _BIS_NMI_IE1(unsigned short);





 

 

 

 

 

 


 

 

#pragma language=restore

#pragma language=save
#pragma language=extended








 




 


 






 



 

__no_init volatile unsigned char IE1 @ (0x0000u);

__no_init volatile unsigned char IFG1 @ (0x0002u);

__no_init volatile unsigned char IE2 @ (0x0001u);

__no_init volatile unsigned char IFG2 @ (0x0003u);



 

__no_init volatile unsigned char ADC10DTC0 @ (0x0048u);
__no_init volatile unsigned char ADC10DTC1 @ (0x0049u);
__no_init volatile unsigned char ADC10AE0 @ (0x004Au);
__no_init volatile unsigned char ADC10AE1 @ (0x004Bu);

__no_init volatile unsigned short ADC10CTL0 @ (0x01B0u);
__no_init volatile unsigned short ADC10CTL1 @ (0x01B2u);
__no_init volatile unsigned short ADC10MEM @ (0x01B4u);
__no_init volatile unsigned short ADC10SA @ (0x01BCu);

 


 






 



 

__no_init volatile unsigned char DCOCTL @ (0x0056u);
__no_init volatile unsigned char BCSCTL1 @ (0x0057u);
__no_init volatile unsigned char BCSCTL2 @ (0x0058u);
__no_init volatile unsigned char BCSCTL3 @ (0x0053u);














 

__no_init volatile unsigned short FCTL1 @ (0x0128u);
__no_init volatile unsigned short FCTL2 @ (0x012Au);
__no_init volatile unsigned short FCTL3 @ (0x012Cu);








 

__no_init volatile unsigned char OA0CTL0 @ (0x00C0u);
__no_init volatile unsigned char OA0CTL1 @ (0x00C1u);
__no_init volatile unsigned char OA1CTL0 @ (0x00C2u);
__no_init volatile unsigned char OA1CTL1 @ (0x00C3u);








 

const __no_init volatile unsigned char P1IN @ (0x0020u);
__no_init volatile unsigned char P1OUT @ (0x0021u);
__no_init volatile unsigned char P1DIR @ (0x0022u);
__no_init volatile unsigned char P1IFG @ (0x0023u);
__no_init volatile unsigned char P1IES @ (0x0024u);
__no_init volatile unsigned char P1IE @ (0x0025u);
__no_init volatile unsigned char P1SEL @ (0x0026u);
__no_init volatile unsigned char P1REN @ (0x0027u);

const __no_init volatile unsigned char P2IN @ (0x0028u);
__no_init volatile unsigned char P2OUT @ (0x0029u);
__no_init volatile unsigned char P2DIR @ (0x002Au);
__no_init volatile unsigned char P2IFG @ (0x002Bu);
__no_init volatile unsigned char P2IES @ (0x002Cu);
__no_init volatile unsigned char P2IE @ (0x002Du);
__no_init volatile unsigned char P2SEL @ (0x002Eu);
__no_init volatile unsigned char P2REN @ (0x002Fu);



 

const __no_init volatile unsigned char P3IN @ (0x0018u);
__no_init volatile unsigned char P3OUT @ (0x0019u);
__no_init volatile unsigned char P3DIR @ (0x001Au);
__no_init volatile unsigned char P3SEL @ (0x001Bu);
__no_init volatile unsigned char P3REN @ (0x0010u);

const __no_init volatile unsigned char P4IN @ (0x001Cu);
__no_init volatile unsigned char P4OUT @ (0x001Du);
__no_init volatile unsigned char P4DIR @ (0x001Eu);
__no_init volatile unsigned char P4SEL @ (0x001Fu);
__no_init volatile unsigned char P4REN @ (0x0011u);



 

const __no_init volatile unsigned short TAIV @ (0x012Eu);
__no_init volatile unsigned short TACTL @ (0x0160u);
__no_init volatile unsigned short TACCTL0 @ (0x0162u);
__no_init volatile unsigned short TACCTL1 @ (0x0164u);
__no_init volatile unsigned short TACCTL2 @ (0x0166u);
__no_init volatile unsigned short TAR @ (0x0170u);
__no_init volatile unsigned short TACCR0 @ (0x0172u);
__no_init volatile unsigned short TACCR1 @ (0x0174u);
__no_init volatile unsigned short TACCR2 @ (0x0176u);

 
 





 

 



 

const __no_init volatile unsigned short TBIV @ (0x011Eu);
__no_init volatile unsigned short TBCTL @ (0x0180u);
__no_init volatile unsigned short TBCCTL0 @ (0x0182u);
__no_init volatile unsigned short TBCCTL1 @ (0x0184u);
__no_init volatile unsigned short TBCCTL2 @ (0x0186u);
__no_init volatile unsigned short TBR @ (0x0190u);
__no_init volatile unsigned short TBCCR0 @ (0x0192u);
__no_init volatile unsigned short TBCCR1 @ (0x0194u);
__no_init volatile unsigned short TBCCR2 @ (0x0196u);

 




 





 

 



 

__no_init volatile unsigned char UCA0CTL0 @ (0x0060u);
__no_init volatile unsigned char UCA0CTL1 @ (0x0061u);
__no_init volatile unsigned char UCA0BR0 @ (0x0062u);
__no_init volatile unsigned char UCA0BR1 @ (0x0063u);
__no_init volatile unsigned char UCA0MCTL @ (0x0064u);
__no_init volatile unsigned char UCA0STAT @ (0x0065u);
const __no_init volatile unsigned char UCA0RXBUF @ (0x0066u);
__no_init volatile unsigned char UCA0TXBUF @ (0x0067u);
__no_init volatile unsigned char UCA0ABCTL @ (0x005Du);
__no_init volatile unsigned char UCA0IRTCTL @ (0x005Eu);
__no_init volatile unsigned char UCA0IRRCTL @ (0x005Fu);



__no_init volatile unsigned char UCB0CTL0 @ (0x0068u);
__no_init volatile unsigned char UCB0CTL1 @ (0x0069u);
__no_init volatile unsigned char UCB0BR0 @ (0x006Au);
__no_init volatile unsigned char UCB0BR1 @ (0x006Bu);
__no_init volatile unsigned char UCB0I2CIE @ (0x006Cu);
__no_init volatile unsigned char UCB0STAT @ (0x006Du);
const __no_init volatile unsigned char UCB0RXBUF @ (0x006Eu);
__no_init volatile unsigned char UCB0TXBUF @ (0x006Fu);
__no_init volatile unsigned short UCB0I2COA @ (0x0118u);
__no_init volatile unsigned short UCB0I2CSA @ (0x011Au);








































 

__no_init volatile unsigned short WDTCTL @ (0x0120u);
 


 
 
 
 
 
 

 
 
 
 



 


const __no_init volatile unsigned char CALDCO_16MHZ @ (0x10F8u);
const __no_init volatile unsigned char CALBC1_16MHZ @ (0x10F9u);
const __no_init volatile unsigned char CALDCO_12MHZ @ (0x10FAu);
const __no_init volatile unsigned char CALBC1_12MHZ @ (0x10FBu);
const __no_init volatile unsigned char CALDCO_8MHZ @ (0x10FCu);
const __no_init volatile unsigned char CALBC1_8MHZ @ (0x10FDu);
const __no_init volatile unsigned char CALDCO_1MHZ @ (0x10FEu);
const __no_init volatile unsigned char CALBC1_1MHZ @ (0x10FFu);




 




 
#pragma language=restore


 
 

  #pragma system_include

 
 

 

  #pragma system_include






 















 












 






 
 


  #pragma system_include

 
 

 

  #pragma system_include






 















 





                 



  

                 













 

   



                 



























 


  #pragma system_include

 
 
 


  #pragma system_include

 

   

 
 
 









 

 


 












 












 




















 










 




















































































































 


 










 





















 















 













 








 












 











 










 









 











 









 









 









 









 














 














 
















 












 








 











 










 









 









 









 









 









 









 









 









 







 




 









 




 





 
















































 













 






 







 





 




 



 





 




 



 












 
   






 
  #pragma language = save 
  #pragma language = extended
  #pragma language = restore






 





 




 





 








                 




















 


                 

 

 
 

 

 

 

 



                 






 
 


  #pragma system_include

 
 

 

  #pragma system_include






 















 




 
 





 

                                 





                                 








                 

                 

                 

                 
                 



                 
                                 


  #pragma language=save
  #pragma language=extended
  typedef long long _Longlong;
  typedef unsigned long long _ULonglong;
  #pragma language=restore

  typedef unsigned short int _Wchart;
  typedef unsigned short int _Wintt;



                 

typedef signed int  _Ptrdifft;
typedef unsigned int     _Sizet;

 

                 

  typedef struct __va_list
  {
    char  *_Ap;
  } __va_list;
  typedef __va_list __Va_list;


__intrinsic __nounwind void __iar_Atexit(void (*)(void));


  typedef struct
  {        
    unsigned long _Wchar;       
    unsigned long _State;       
  } _Mbstatet;





typedef struct
{        
  long _Off;     
  _Mbstatet _Wstate;
} _Fpost;




                 














 


  #pragma system_include





 






















































































 

 


   



  
  typedef void *__iar_Rmtx;
  











                 


                 

                 


                 







 


 
  typedef signed char   int8_t;
  typedef unsigned char uint8_t;

  typedef signed int   int16_t;
  typedef unsigned int uint16_t;

  typedef signed long int   int32_t;
  typedef unsigned long int uint32_t;

  #pragma language=save
  #pragma language=extended
  typedef signed long long int   int64_t;
  typedef unsigned long long int uint64_t;
  #pragma language=restore


 
typedef signed char   int_least8_t;
typedef unsigned char uint_least8_t;

typedef signed int   int_least16_t;
typedef unsigned int uint_least16_t;

typedef signed long int   int_least32_t;
typedef unsigned long int uint_least32_t;

 
  #pragma language=save
  #pragma language=extended
  typedef signed long long int int_least64_t;
  #pragma language=restore
  #pragma language=save
  #pragma language=extended
  typedef unsigned long long int uint_least64_t;
  #pragma language=restore



 
typedef signed char   int_fast8_t;
typedef unsigned char uint_fast8_t;

typedef signed int   int_fast16_t;
typedef unsigned int uint_fast16_t;

typedef signed long int   int_fast32_t;
typedef unsigned long int uint_fast32_t;

  #pragma language=save
  #pragma language=extended
  typedef signed long long int int_fast64_t;
  #pragma language=restore
  #pragma language=save
  #pragma language=extended
  typedef unsigned long long int uint_fast64_t;
  #pragma language=restore

 
#pragma language=save
#pragma language=extended
typedef signed long long int   intmax_t;
typedef unsigned long long int uintmax_t;
#pragma language=restore


 
typedef signed int   intptr_t;
typedef unsigned int uintptr_t;

 
typedef int __data16_intptr_t; typedef unsigned int __data16_uintptr_t;

 

























 














 

 
 





 





enum DIRECTION
{
    FORWARD = 1, 
    REVERSE = -1 
};

enum MOTOR
{
    MOTOR_1, 
    MOTOR_2  
};







uint8_t MotorInit(void);





void MotorStop(void);






void MotorSet(int8_t speed, enum MOTOR motor);





inline void MotorSetBoth(int8_t speed)
{
    MotorSet(speed, MOTOR_1);
    MotorSet(speed, MOTOR_2);
}






inline void MotorFullSpeed(enum DIRECTION dir)
{
    MotorSetBoth(dir * 100);
}






inline void MotorHalfSpeed(enum DIRECTION dir)
{
    MotorSetBoth(dir * 50);
}






inline void MotorSpin(int8_t speed)
{
    MotorSet(speed, MOTOR_1);
    MotorSet(-speed, MOTOR_2);
}








uint8_t MotorInit(void)
{
    P3SEL = 0x30;           
    UCA0CTL1 |= (0x80);   
    UCA0BR0 = 104;          
    UCA0BR1 = 0;            
    UCA0MCTL = (0x02);      
    UCA0CTL1 &= ~(0x01);   
    return 0;
}

void MotorStop(void)
{
    
    while (!(IFG2 & (0x02)));
    
    UCA0TXBUF = 0;
}

void MotorSet(int8_t speed,  enum MOTOR motor)
{
    speed = -speed; 
    
    
    switch (motor)  
    {
        case MOTOR_1:
        {
            
            uint8_t motorSpeed = ((((speed) + 100 )*100/(200)) * (127 - 1)) / 100 + 1;

            while (!(IFG2 & (0x02)));
            UCA0TXBUF = motorSpeed; 
            break;
        }

        case MOTOR_2:
        {
            
            uint8_t motorSpeed = ((((speed) + 100 )*100/(200)) * (255 - 128)) / 100 + 128;

            while (!(IFG2 & (0x02)));
            UCA0TXBUF = motorSpeed; 
            break;
        }
    }
}
