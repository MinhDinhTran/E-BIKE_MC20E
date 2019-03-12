#include "flash.h"
#include "stmflash.h"

#define PAGE_SIZE  256    //�ֽ�  //ÿ����ַд��Ϊ�ĳ���Ϊ4���ֽڣ�һҳΪ1K�ֽ�

void write_flash(uint32_t write_addr, uint16_t *buffer, uint16_t size)
{
//	STMFLASH_Write(write_addr,buffer,size);
}
void read_flash(uint32_t read_addr, uint16_t* buffer, uint16_t size)
{
//	STMFLASH_Read(read_addr, buffer,size);   	
}
#if 0
//FLASHд������
void write_flash(uint32_t read_addr, uint16_t *buffer, uint16_t size)
{
	  uint32_t i;
    HAL_FLASH_Unlock();
		//����FLASH
    //��ʼ��FLASH_EraseInitTypeDef
    FLASH_EraseInitTypeDef f;
    f.TypeErase = FLASH_TYPEERASE_PAGES;
    f.PageAddress = write_addr;
	  if (size > 256)
			f.NbPages = 2;
		else if (size > 512)
			f.NbPages = 3;
		else
			f.NbPages = 1;
    //����PageError
    uint32_t PageError = 0;
    //���ò�������
    HAL_FLASHEx_Erase(&f, &PageError);
    
    //��FLASHд
	for (i = 0; i < size; i++) 
  	{
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, write_addr, buffer[i]);
  			write_addr += 4;
	}
	HAL_FLASH_Lock();
}
//FLASH��ȡ����
void read_flash(uint32_t read_addr, uint16_t* buffer, uint16_t size)
{
	 uint16_t i;
	 
	 for (i = 0; i < size; i++) 
  	{
		buffer[i] = *(__IO uint32_t*)(read_addr);
		printf("addr:0x%x, data:0x%x\r\n", read_addr, buffer[i]);
		read_addr += 4;
	}
}
#endif



