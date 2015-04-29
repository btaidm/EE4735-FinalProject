 
 
 
 
 



















 



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
  











                 


                 

                 


                 







 
 
 


  #pragma system_include

 
 

 

  #pragma system_include






 















 






                 
typedef _Sizet size_t;

typedef unsigned int __data16_size_t;







                 

                 

_Pragma("function_effects = no_state, no_errno, no_write(1,2)")   __intrinsic __nounwind int        memcmp(const void *, const void *,
                                                size_t);
_Pragma("function_effects = no_state, no_errno, no_read(1), no_write(2), returns 1") __intrinsic __nounwind void *     memcpy(void *, 
                                                const void *, size_t);
_Pragma("function_effects = no_state, no_errno, no_read(1), no_write(2), returns 1") __intrinsic __nounwind void *     memmove(void *, const void *, size_t);
_Pragma("function_effects = no_state, no_errno, no_read(1), returns 1")    __intrinsic __nounwind void *     memset(void *, int, size_t);
_Pragma("function_effects = no_state, no_errno, no_write(2), returns 1")    __intrinsic __nounwind char *     strcat(char *, 
                                                const char *);
_Pragma("function_effects = no_state, no_errno, no_write(1,2)")   __intrinsic __nounwind int        strcmp(const char *, const char *);
_Pragma("function_effects = no_write(1,2)")     __intrinsic __nounwind int        strcoll(const char *, const char *);
_Pragma("function_effects = no_state, no_errno, no_read(1), no_write(2), returns 1") __intrinsic __nounwind char *     strcpy(char *, 
                                                const char *);
_Pragma("function_effects = no_state, no_errno, no_write(1,2)")   __intrinsic __nounwind size_t     strcspn(const char *, const char *);
                 __intrinsic __nounwind char *     strerror(int);
_Pragma("function_effects = no_state, no_errno, no_write(1)")      __intrinsic __nounwind size_t     strlen(const char *);
_Pragma("function_effects = no_state, no_errno, no_write(2), returns 1")    __intrinsic __nounwind char *     strncat(char *, 
                                                 const char *, size_t);
_Pragma("function_effects = no_state, no_errno, no_write(1,2)")   __intrinsic __nounwind int        strncmp(const char *, const char *, 
                                                 size_t);
_Pragma("function_effects = no_state, no_errno, no_read(1), no_write(2), returns 1") __intrinsic __nounwind char *     strncpy(char *, 
                                                 const char *, size_t);
_Pragma("function_effects = no_state, no_errno, no_write(1,2)")   __intrinsic __nounwind size_t     strspn(const char *, const char *);
_Pragma("function_effects = no_write(2)")        __intrinsic __nounwind char *     strtok(char *, 
                                                const char *);
_Pragma("function_effects = no_write(2)")        __intrinsic __nounwind size_t     strxfrm(char *, 
                                                 const char *, size_t);

  _Pragma("function_effects = no_write(1)")      __intrinsic __nounwind char *   strdup(const char *);
  _Pragma("function_effects = no_write(1,2)")   __intrinsic __nounwind int      strcasecmp(const char *, const char *);
  _Pragma("function_effects = no_write(1,2)")   __intrinsic __nounwind int      strncasecmp(const char *, const char *, 
                                                   size_t);
  _Pragma("function_effects = no_state, no_errno, no_write(2)")    __intrinsic __nounwind char *   strtok_r(char *, const char *, char **);
  _Pragma("function_effects = no_state, no_errno, no_write(1)")    __intrinsic __nounwind size_t   strnlen(char const *, size_t);



  _Pragma("function_effects = no_state, no_errno, no_write(1)")    __intrinsic __nounwind void *memchr(const void *_S, int _C, size_t _N);
  _Pragma("function_effects = no_state, no_errno, no_write(1)")    __intrinsic __nounwind char *strchr(const char *_S, int _C);
  _Pragma("function_effects = no_state, no_errno, no_write(1,2)") __intrinsic __nounwind char *strpbrk(const char *_S, const char *_P);
  _Pragma("function_effects = no_state, no_errno, no_write(1)")    __intrinsic __nounwind char *strrchr(const char *_S, int _C);
  _Pragma("function_effects = no_state, no_errno, no_write(1,2)") __intrinsic __nounwind char *strstr(const char *_S, const char *_P);


                 

                 

_Pragma("function_effects = no_state, no_errno, no_write(1)")    __intrinsic __nounwind void *__iar_Memchr(const void *, int, size_t);
_Pragma("function_effects = no_state, no_errno, no_write(1)")    __intrinsic __nounwind char *__iar_Strchr(const char *, int);
               __intrinsic __nounwind char *__iar_Strerror(int, char *);
_Pragma("function_effects = no_state, no_errno, no_write(1,2)") __intrinsic __nounwind char *__iar_Strpbrk(const char *, const char *);
_Pragma("function_effects = no_state, no_errno, no_write(1)")    __intrinsic __nounwind char *__iar_Strrchr(const char *, int);
_Pragma("function_effects = no_state, no_errno, no_write(1,2)") __intrinsic __nounwind char *__iar_Strstr(const char *, const char *);


                 
                 
    #pragma inline
    void *memchr(const void *_S, int _C, size_t _N)
    {
      return (__iar_Memchr(_S, _C, _N));
    }

    #pragma inline
    char *strchr(const char *_S, int _C)
    {
      return (__iar_Strchr(_S, _C));
    }

    #pragma inline
    char *strpbrk(const char *_S, const char *_P)
    {
      return (__iar_Strpbrk(_S, _P));
    }

    #pragma inline
    char *strrchr(const char *_S, int _C)
    {
      return (__iar_Strrchr(_S, _C));
    }

    #pragma inline
    char *strstr(const char *_S, const char *_P)
    {
      return (__iar_Strstr(_S, _P));
    }

  #pragma inline
  char *strerror(int _Err)
  {
    return (__iar_Strerror(_Err, 0));
  }









 
 
 

  #pragma system_include

 
 

 

  #pragma system_include






 















 






 
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

 

























 














 

 
 





 












static inline int8_t Sign32(int32_t num)
{
    return (num >> 31) | ((uint32_t) - num >> 31);
}







static inline int8_t Sign16(int16_t num)
{
    return (num >> 15) | ((uint16_t) - num >> 15);
}







static inline int8_t Sign8(int8_t num)
{
    return (num >> 7) | ((uint8_t) - num >> 7);
}


 
 





 





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


 
 





 


typedef struct
{
    struct
    {
        volatile unsigned char* out; 
        volatile unsigned char* dir; 
        uint8_t pin;    
    } trigger; 

    struct
    {
        volatile unsigned char* sel; 
        volatile unsigned char* dir; 
        uint8_t pin;    
    } echo; 
    volatile uint32_t echoTime; 
    uint8_t ledpin; 

} pinger_t;







void SetupPinger(pinger_t* pingerPtr);







void StartPinger(pinger_t* pingerPtr);















static const uint32_t CALIBRATING_DISTANCE = 1 * 64 * 30; 

static const uint32_t FOLLOWING_DISTANCE = 1 * 64 * 30; 

static const uint32_t DISTANCE_TOL = 64 * 10; 



static const uint8_t SPEED_SLOPE_FOR = 2; 
static const uint8_t SPEED_SLOPE_REV = 4; 

static const uint8_t SPEED_START_OFFSET_FOR = 9; 
static const uint8_t SPEED_START_OFFSET_REV = 19; 

static const uint8_t SPEED_LIMIT = 90; 



static const uint32_t PINGER_OFFSET_TOL_LOWER = 64 * 20; 

static const uint32_t PINGER_OFFSET_TOL_UPPER = 64 * 60; 

static const uint32_t PINGER_LIMIT = 64 * 400; 

static const uint8_t TURN_SPEED_SLOPE = 4; 

static const uint8_t TURN_SPEED_LOWER = 5; 

static const uint8_t TURN_SPEED_UPPER = 45; 


static uint8_t calibrationCount = 10;

static int32_t leftOffset = 0;

static int32_t rightOffset = 0;



uint32_t leftHist[3] = {0};

uint32_t rightHist[3] = {0};

uint8_t histCount = 0;


pinger_t leftPinger = { .trigger = { .out = &P2OUT, .dir = &P2DIR, .pin = 0},                         .echo = { .dir = &P2DIR, .sel = &P2SEL, .pin = 2},                         .echoTime = 0,                         .ledpin = 1
                      };


pinger_t rightPinger = { .trigger = { .out = &P2OUT, .dir = &P2DIR, .pin = 1},                          .echo = { .dir = &P2DIR, .sel = &P2SEL, .pin = 3},                          .echoTime = 0,                          .ledpin = 0
                       };


pinger_t* usePinger = &leftPinger;






static inline uint32_t GetMedian(uint32_t* hist)
{
    
    uint32_t max = hist[0];
    
    uint32_t med = 0;

    for (uint8_t i = 0; i < 3; i++)
    {
        
        if (hist[i] > max)
        {
            med = max; 
            max = hist[i]; 
        }
        else if (hist[i] > med) 
        {
            med = hist[i]; 
        }
    }
    return med;
}




static inline void PutValue(uint32_t* hist, uint8_t count, uint32_t value)
{
    
    hist[(count) % 3] = value;
}





_Pragma( "vector= (9 * 2u)" ) __interrupt void TimerA0ISR(void)
{
    
    static uint8_t edge1 = 0;
    
    static uint16_t reTime1 = 0;

    
    uint16_t currStamp = TACCR0;
    
    
    TACCTL0 ^= (0x8000u) | (0x4000u);

    switch (edge1)
    {
        case 0:
        {
            
            reTime1 = currStamp;
            
            edge1 = 1;
            break;
        }

        case 1:
        {
            
            edge1 = 0;
            
            uint32_t totalTime = 0;

            
            if (currStamp < reTime1)
            {
                totalTime = currStamp;
                currStamp = 0xFFFF;
            }
            
            
            totalTime += (currStamp - reTime1);
            
            
            leftPinger.echoTime = totalTime;

            
            usePinger = &rightPinger;

            
            TBCCTL0 |= (0x0010u);
            break;
        }
    }
}





_Pragma( "vector= (8 * 2u)" ) __interrupt void TimerA1ISR(void)
{
    switch (__even_in_range(TAIV, 10))
    {
        case (0x0002u):
        {
            TACCTL1 &= ~(0x0001u); 
            
            static uint8_t edge2 = 0;
            
            static uint16_t reTime2 = 0;

            
            uint16_t currStamp = TACCR1;

            
            TACCTL1 ^= (0x8000u) | (0x4000u);

            switch (edge2)
            {
                case 0:
                {
                    
                    reTime2 = currStamp;
                    
                    edge2 = 1;
                    break;
                }

                case 1:
                {
                    
                    edge2 = 0;
                    
                    uint32_t totalTime = 0;

                    
                    if (currStamp < reTime2)
                    {
                        totalTime = currStamp;
                        currStamp = 0xFFFF;
                    }

                    
                    totalTime += (currStamp - reTime2);
                    
                    rightPinger.echoTime = totalTime;
                    
                    
                    (__bic_SR_register_on_exit( (1<<4) | (1<<6) | (1<<7) | (1<<5)));
                    break;
                }
            }

            break;
        }

        case (0x0004u):
        case (0x000Au):
        default:
            break;
    }
}





_Pragma( "vector= (13 * 2u)" ) __interrupt void TimerB0ISR(void)
{
    TBCCTL0 &= ~(0x0010u); 
    StartPinger(usePinger); 
}

inline void SetupTimer(void)
{
    
    TACTL   = (2*0x100u) | (0*0x40u) | (2*0x10u);
    
    
    
    TACCTL0 = (1*0x4000u) | (1*0x1000u) | (0x0800u) | (0x0100u) | (0x0010u);
    TACCTL1 = (1*0x4000u) | (1*0x1000u) | (0x0100u) | (0x0800u) | (0x0010u);
    
    TBCTL =  (2*0x0100u) | (1*0x40u) | (1*0x10u);
    TBCCR0 =  35750; 
}

inline void SetupClock(void)
{
    BCSCTL1 = CALBC1_1MHZ; 
    DCOCTL  = CALDCO_1MHZ; 
}




static inline void Calibrate(void)
{
    
    int32_t newLeftOffset = CALIBRATING_DISTANCE - leftPinger.echoTime;
    int32_t newRightOffset = CALIBRATING_DISTANCE - rightPinger.echoTime;
    
    
    leftOffset += newLeftOffset;
    rightOffset += newRightOffset;

    
    if (calibrationCount == 0)
    {
        leftOffset /= 10;
        rightOffset /= 10;
    }
}





static inline void Drive(void)
{
    
    uint32_t newLeftEcho = leftPinger.echoTime + leftOffset;
    uint32_t newRightEcho = rightPinger.echoTime + rightOffset;
    
    
    PutValue(leftHist, histCount, newLeftEcho);
    PutValue(rightHist, histCount, newRightEcho);

    
    if (histCount == 254)
        histCount = 0;
    else
        histCount++;

    
    newLeftEcho = GetMedian(leftHist);
    newRightEcho = GetMedian(rightHist);

    
    uint32_t currentDistance = (newLeftEcho + newRightEcho) / 2;

    
    int32_t distanceToTarget = currentDistance - FOLLOWING_DISTANCE;

    
    int32_t leftRightDiff = newLeftEcho - newRightEcho;

    
    if (leftPinger.echoTime >= PINGER_LIMIT)
    {
        MotorSpin(-(TURN_SPEED_UPPER));
    }
    
    else if (rightPinger.echoTime >= PINGER_LIMIT)
    {
        MotorSpin((TURN_SPEED_UPPER));
    }
    
    else if ((((distanceToTarget) < 0) ? -(distanceToTarget) : (distanceToTarget)) <= DISTANCE_TOL)
    {
        int8_t speed = 0;
        
        if ( (((leftRightDiff) < 0) ? -(leftRightDiff) : (leftRightDiff)) >= PINGER_OFFSET_TOL_LOWER)
        {
            
            if ((((leftRightDiff) < 0) ? -(leftRightDiff) : (leftRightDiff)) >= PINGER_OFFSET_TOL_UPPER)
            {
                
                speed = Sign32(leftRightDiff) * TURN_SPEED_UPPER;
            }
            else
            {
                
                
                
                speed = Sign32(leftRightDiff)
                      * ((((((leftRightDiff) < 0) ? -(leftRightDiff) : (leftRightDiff)) - PINGER_OFFSET_TOL_LOWER)
                      / (TURN_SPEED_SLOPE * 64)) + TURN_SPEED_LOWER);
            }
            
            
            MotorSpin(speed);
        }
        else
        {
            
            MotorStop();
        }
    }
    else
    {
        
        int16_t speed = 0;

        if (distanceToTarget > 0)
        {
            speed = distanceToTarget / (SPEED_SLOPE_FOR * 64);
        }
        else
        {
            speed = (distanceToTarget * SPEED_SLOPE_REV) / (64);
        }
        
        
        if (distanceToTarget < 0)
            
            speed += -SPEED_START_OFFSET_REV;
        else
            
            speed += SPEED_START_OFFSET_FOR;

        
        if (speed >= SPEED_LIMIT) speed = SPEED_LIMIT;

        if (speed <= -SPEED_LIMIT) speed = -SPEED_LIMIT;
        
        
        int8_t speed1 = speed;
        int8_t speed2 = speed;

        
        
        if ( (((leftRightDiff) < 0) ? -(leftRightDiff) : (leftRightDiff)) > PINGER_OFFSET_TOL_LOWER)
        {
            if ((((leftRightDiff) < 0) ? -(leftRightDiff) : (leftRightDiff)) > PINGER_OFFSET_TOL_UPPER)
            {
                
                speed1 += Sign32(leftRightDiff) * TURN_SPEED_UPPER;
                speed2 -= Sign32(leftRightDiff) * TURN_SPEED_UPPER;
            }
            else
            {
                
                
                
                speed1 += Sign32(leftRightDiff) * ((((((leftRightDiff) < 0) ? -(leftRightDiff) : (leftRightDiff)) - PINGER_OFFSET_TOL_LOWER) / (TURN_SPEED_SLOPE * 64)) + TURN_SPEED_LOWER);
                speed2 -= Sign32(leftRightDiff) * ((((((leftRightDiff) < 0) ? -(leftRightDiff) : (leftRightDiff)) - PINGER_OFFSET_TOL_LOWER) / (TURN_SPEED_SLOPE * 64)) + TURN_SPEED_LOWER);
            }
        }

        
        if (speed1 >= SPEED_LIMIT) speed1 = SPEED_LIMIT;

        if (speed1 <= -SPEED_LIMIT) speed1 = -SPEED_LIMIT;

        if (speed2 >= SPEED_LIMIT) speed2 = SPEED_LIMIT;

        if (speed2 <= -SPEED_LIMIT) speed2 = -SPEED_LIMIT;

        MotorSet(speed1, MOTOR_1);
        MotorSet(speed2, MOTOR_2);
        
    }


}

void main(void)
{
    WDTCTL = (0x5A00u) | (0x0080u);                 
    P2SEL = 0;
    SetupClock();
    SetupPinger(&leftPinger);
    SetupPinger(&rightPinger);

    SetupTimer();

    MotorInit();

    P1DIR |= 0x03;                            
    P1OUT &= ~0x03;
    P1OUT |= 0x01;

    
    


    while ( 1)
    {
        
        
        
        
        usePinger = &leftPinger;
        
        
        TBCCTL0 |= (0x0010u);
        
        __enable_interrupt();
        (__bis_SR_register( (1<<3) | (1<<4) | (1<<6)));
        __disable_interrupt();


        
        if (calibrationCount != 0)
        {
            calibrationCount--;
            Calibrate();
        }
        else
        {
            
            Drive();

        }
    }
}
