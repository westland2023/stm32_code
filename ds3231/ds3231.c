#include "include.h"

_calendar_obj calendar;

// �������Ʊ����ʮ���ƣ�BCD��ת��Ϊʮ����
uint8_t bcd_to_dec(uint8_t val) 
{
    return (val >> 4) * 10 + (val & 0x0F);
}

// ��ʮ����ת��Ϊ�����Ʊ����ʮ���ƣ�BCD��
uint8_t dec_to_bcd(uint8_t val) 
{
    return ((val / 10) << 4) | (val % 10);
}

// ��DS3231��ȡһ���ֽ�
uint8_t ds3231_read_byte(uint8_t reg_addr) 
{
    uint8_t data;
    HAL_I2C_Mem_Read(&hi2c2, DS3231_ADDR, reg_addr, I2C_MEMADD_SIZE_8BIT, &data, 1, HAL_MAX_DELAY);
    return data;
}

// ��DS3231д��һ���ֽ�
void ds3231_write_byte(uint8_t reg_addr, uint8_t data) 
	{
    HAL_I2C_Mem_Write(&hi2c2, DS3231_ADDR, reg_addr, I2C_MEMADD_SIZE_8BIT, &data, 1, HAL_MAX_DELAY);
}

// ��ȡDS3231������
void ds3231_get_seconds(void) 
{
	calendar.sec=bcd_to_dec(ds3231_read_byte(0x00));
	calendar.min=bcd_to_dec(ds3231_read_byte(0x01));
	calendar.hour=bcd_to_dec(ds3231_read_byte(0x02));
	calendar.week=bcd_to_dec(ds3231_read_byte(0x03));
	calendar.date=bcd_to_dec(ds3231_read_byte(0x04));
	calendar.month=bcd_to_dec(ds3231_read_byte(0x05));
	calendar.year=bcd_to_dec(ds3231_read_byte(0x06));
	//calendar.temperature=(uint16_t)(ds3231_read_byte(0x11)<<8|ds3231_read_byte(0x12));
}

// ����DS3231������
void ds3231_set_seconds(uint8_t year,uint8_t month,uint8_t date,uint8_t week,uint8_t hour,uint8_t minute,uint8_t second) 
{
    ds3231_write_byte(0x06, dec_to_bcd(year));
	ds3231_write_byte(0x05, dec_to_bcd(month));
	ds3231_write_byte(0x04, dec_to_bcd(date));
	ds3231_write_byte(0x03, dec_to_bcd(week));
	ds3231_write_byte(0x02, dec_to_bcd(hour));
	ds3231_write_byte(0x01, dec_to_bcd(minute));
	ds3231_write_byte(0x00, dec_to_bcd(second));
}
