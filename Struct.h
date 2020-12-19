#ifndef STRUCT_H
#define STRUCT_H
#include <cinttypes>

union word16                    //������ � 16 �����
{
    int16_t i16;                //����� ��������
    uint16_t ui16;              //����� �����������
};

union word32                    //������ � 32 ����
{
    int32_t i32;                //����� ��������
    uint32_t ui32;              //����� �����������
    float f;                    //������������
};

struct cmd16                    //������� � 16 �����
{
    int KOP : 7;            //��� ��������
    int s : 1;              //������ ��������
    int r1 : 4;             //������ �������
    int r2 : 4;             //������ �������
};

struct cmd32                    //������� � 32 ����
{
    cmd16 command16;            //������� � 16 �����
    uint16_t off;               //��������
};

union datatype16               //16-������ �����
{
    word16 w16;                 //�����
    cmd16 command16;            //������� � ����
};

struct datatype32                //32-������ �����
{
    word32 w32;                 //������� �����
    word16 t16[2];
    cmd32 command32;
};

union ROH
{
    word16 w16[2];
    word32 w32;
};
#endif // STRUCT_H
