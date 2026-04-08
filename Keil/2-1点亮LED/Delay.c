#include <REGX52.H>
#include <INTRINS.H>

/**
 * @brief 毫秒级延时函数
 * @param xms 延时毫秒数
 */
void Delay(unsigned int xms)	//@11.0592MHz
{
	unsigned char data i, j;

	while(xms--)
	{	
		_nop_();
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
	}
}