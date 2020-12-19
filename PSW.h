#ifndef PSW_H
#define PSW_H
#include "Struct.h"

class PSW
{
private:
    uint16_t IP : 16;                                   //IP-адрес
    uint16_t ZF : 1;                                    //Флаг нуля
    uint16_t SF : 1;                                    //Флаг знака
    uint16_t reserved : 14;                             //Резерв
public:
    PSW() : IP(0), ZF(0), SF(0) {};
    
    uint16_t getIP() const noexcept { return IP; }      //Выгружаем значение IP
    uint8_t getZF() const noexcept { return ZF; }       //Выгружаем значение ZF
    uint8_t getSF() const noexcept { return SF; }       //Выгружаем значение SF

    void setIP(uint16_t adr) noexcept { IP = adr; }     //Кладем значение IP
    void setZF(int16_t val) noexcept                    //Кладем значение ZF
    {
        if (val == 0) ZF = 0;
        else ZF = 1;
    }
    void setSF(int16_t val) noexcept                    //Ккладем значение SF
    {
        if (val == 0) SF = 0;
        else SF = 1;
    }

    void resetFlags() noexcept { ZF = 0; SF = 0; }      //Очищаем флаги
};
#endif // PSW_H
