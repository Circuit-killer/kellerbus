/*
This work is licensed under the Creative Commons Attribution-ShareAlike 3.0 Unported License. To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/3.0/ or send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

#include <Arduino.h>
#include <CRC16.h>

#ifndef _H_KELLERBUS
#define _H_KELLERBUS

#define RS_ERROR 										-1
#define RS_TIMEOUT          				-4
#define RS_BADDATA 									-5
#define SW_INVALIDPARAM							-6
#define TX_ERROR										-7
#define COMM_OK                     0

#define COMM_TX_MAX                 20
#define COMM_RX_MAX                 260

#define P_BAR												0 		// Bar
#define P_MBAR											1 		// mBar
#define P_PSI												2 		// Psi
#define P_PA												3 		// Pascal
#define P_HPA												1 		// hPascal
#define P_KPA												4 		// kPascal
#define P_MPA												5 		// MPascal
#define P_MH2O											6 		// mH2O
#define P_MWS												6 		// mWs Meter Wassers�ule
#define P_MWG												6 		// mWg meters, water gauge
#define P_INHG											7 		// inHg
#define P_MMHG											8 		// mmHg
#define P_INH2O											9 		// inH2O
#define P_TORR											8 		// Torr
#define P_FTH2O											10		// ftH2O

#define T_DEGC											0			// �C Celsius
#define T_DEGK											1			// �K Kelvin
#define T_DEGF											2			// �F Fahreinheit
#define T_DEGR											3			// �R Rankine

#define MAX_CHANNELS                6

#define CH_0												0
#define CH_P1												1
#define CH_P2												2
#define CH_T												3
#define CH_TOB1											4
#define CH_TOB2											5

class CKellerBus
{
  private:
    HardwareSerial *Comm;
    
    CRC checksum;
    
    uint16_t baudrate;
    uint8_t RTS_PIN;
    uint16_t timeout;
        
    uint8_t TxBuffer[COMM_TX_MAX];
    uint8_t RxBuffer[COMM_TX_MAX + COMM_RX_MAX];

    uint8_t Error;
    
    uint8_t device;
    
    void Open();
    void Close();
    
    void TransferData(uint8_t, uint8_t);
    float readChannel(uint8_t);
    float pressureConversion(float, uint8_t);
    float temperatureConversion(float, uint8_t);
     
  public:  
    CKellerBus(HardwareSerial*, uint16_t, uint8_t, uint16_t);
    
    void initDevice(uint8_t _device); 
    void initDevice(uint8_t, uint8_t*, uint8_t*, uint8_t*, uint8_t*, uint8_t*, uint8_t*); 
    
    uint8_t getDevice();
    uint32_t getSerialnumber();
    
    float getCH0();
    float getP1(uint8_t);
    float getP2(uint8_t);
    float getTOB1(uint8_t);
    float getTOB2(uint8_t);
    float getT(uint8_t);    
};
#endif
