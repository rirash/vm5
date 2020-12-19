#ifndef PSW_H
#define PSW_H
#include "Struct.h"

class PSW
{
private:
    uint16_t IP : 16;                                   //IP-�����
    uint16_t ZF : 1;                                    //���� ����
    uint16_t SF : 1;                                    //���� �����
    uint16_t reserved : 14;                             //������
public:
    PSW() : IP(0), ZF(0), SF(0) {};
    uint16_t getIP() const noexcept { return IP; }      //�������� �������� IP
    uint8_t getZF() const noexcept { return ZF; }       //�������� �������� ZF
    uint8_t getSF() const noexcept { return SF; }       //�������� �������� SF

    void setIP(uint16_t adr) noexcept { IP = adr; }     //�������� �������� IP
    void setZF(int16_t val) noexcept                    //�������� �������� ZF
    {
        if (val == 0) ZF = 0;
        else ZF = 1;
    }
    void setSF(int16_t val) noexcept                    //�������� �������� SF
    {
        if (val == 0) SF = 0;
        else SF = 1;
    }

    void resetFlags() noexcept { ZF = 0; SF = 0; }      //������� �����
};

#endif // PSW_H
