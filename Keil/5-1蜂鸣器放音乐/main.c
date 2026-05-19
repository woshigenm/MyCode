#include <REGX52.H>
#include "timer0.h"
#include "Delay.h"
#include <intrins.h>  // 解决 _nop_ 报错

// ================== 硬件与速度配置 ==================
#define SPEED 450  // 节奏速度（可调整，数值越大越慢）
#define BASE_DELAY (SPEED / 4)

sbit beep = P2^5;   // 蜂鸣器引脚
sbit K1 = P3^1;     // 播放/暂停按键引脚

// ================== 音符索引定义（C调） ==================
#define M1  12  // 中音1 (C)
#define M2  14  // 中音2 (D)
#define M3  16  // 中音3 (E)
#define M4  17  // 中音4 (F)
#define M5  19  // 中音5 (G)
#define M6  21  // 中音6 (A)
#define M7  23  // 中音7 (B)
#define SILENCE 36

// ================== 音符时值宏定义 ==================
#define WHOLE_NOTE       16  // 全音符（4拍）
#define HALF_NOTE        8   // 二分音符（2拍）
#define QUARTER_NOTE     4   // 四分音符（1拍）
#define EIGHTH_NOTE      2   // 八分音符（0.5拍）
#define DOTTED_QUARTER_NOTE (QUARTER_NOTE + EIGHTH_NOTE)  // 附点四分音符（1.5拍）

#define SLUR 0x80  // 圆滑线标志
#define END_MARKER 0xFF

// ================== 频率表（11.0592MHz晶振，C调标准音高） ==================
unsigned int code FreqTable[] = {
    62013, 62210, 62397, 62574, 62740, 62897, 63045, 63185, 63317, 63441, 63559, 63669,
    63774, 63873, 63967, 64055, 64138, 64216, 64291, 64360, 64426, 64489, 64547, 64603,
    64655, 64705, 64751, 64795, 64837, 64876, 64913, 64948, 64981, 65012, 65042, 65069,
    0  // 休止符
};

// ================== 乐谱结构体 ==================
typedef struct
{
    unsigned char noteIndex;  // 音符索引
    unsigned char duration;   // 时值（含标志位）
} ScaleNote;

// ================== 《兰花草》主旋律乐谱（C调） ==================
// 简谱：1=C 4/4，速度J=96
// (3 6 6 5 3. 2 | 1. 2 1 7 6 3 | 3 1 1 7 6. 3 | 2. 1 7 5 6 - )
// 6 3 3 3 3. 2 | 1. 2 1 7 6 - | 6 6 6 6 6. 5 | 3 5 5 #4 3 - | 3 6 6 5 3. 2 |
// 1. 2 1 7 6 3 | 3 1 1 7 6. 3 | 2. 1 7 5 6 - | (3 1 1 7 6. 3 | 2. 1 7 5 6 - ) :||
code ScaleNote Song[] = {
    // 第一行
    {M3, QUARTER_NOTE},       // 3
    {M6, QUARTER_NOTE},       // 6
    {M6, QUARTER_NOTE},       // 6
    {M5, QUARTER_NOTE},       // 5
    {M3, DOTTED_QUARTER_NOTE},// 3.
    {M2, QUARTER_NOTE},       // 2
    {M1, DOTTED_QUARTER_NOTE},// 1.
    {M2, QUARTER_NOTE},       // 2
    {M1, QUARTER_NOTE},       // 1
    {M7, QUARTER_NOTE},       // 7
    {M6, QUARTER_NOTE},       // 6
    {M3, QUARTER_NOTE},       // 3
    {M3, QUARTER_NOTE},       // 3
    {M1, QUARTER_NOTE},       // 1
    {M1, QUARTER_NOTE},       // 1
    {M7, QUARTER_NOTE},       // 7
    {M6, DOTTED_QUARTER_NOTE},// 6.
    {M3, QUARTER_NOTE},       // 3
    {M2, DOTTED_QUARTER_NOTE},// 2.
    {M1, QUARTER_NOTE},       // 1
    {M7, QUARTER_NOTE},       // 7
    {M5, QUARTER_NOTE},       // 5
    {M6, QUARTER_NOTE},       // 6
    {SILENCE, QUARTER_NOTE},  // -
    
    // 第二行
    {M6, QUARTER_NOTE},       // 6
    {M3, QUARTER_NOTE},       // 3
    {M3, QUARTER_NOTE},       // 3
    {M3, QUARTER_NOTE},       // 3
    {M3, DOTTED_QUARTER_NOTE},// 3.
    {M2, QUARTER_NOTE},       // 2
    {M1, DOTTED_QUARTER_NOTE},// 1.
    {M2, QUARTER_NOTE},       // 2
    {M1, QUARTER_NOTE},       // 1
    {M7, QUARTER_NOTE},       // 7
    {M6, QUARTER_NOTE},       // 6
    {SILENCE, QUARTER_NOTE},  // -
    {M6, QUARTER_NOTE},       // 6
    {M6, QUARTER_NOTE},       // 6
    {M6, QUARTER_NOTE},       // 6
    {M6, QUARTER_NOTE},       // 6
    {M6, DOTTED_QUARTER_NOTE},// 6.
    {M5, QUARTER_NOTE},       // 5
    {M3, QUARTER_NOTE},       // 3
    {M5, QUARTER_NOTE},       // 5
    {M5, QUARTER_NOTE},       // 5
    {M4, QUARTER_NOTE},       // #4（用F代替升4）
    {M3, QUARTER_NOTE},       // 3
    {SILENCE, QUARTER_NOTE},  // -
    {M3, QUARTER_NOTE},       // 3
    {M6, QUARTER_NOTE},       // 6
    {M6, QUARTER_NOTE},       // 6
    {M5, QUARTER_NOTE},       // 5
    {M3, DOTTED_QUARTER_NOTE},// 3.
    {M2, QUARTER_NOTE},       // 2
    
    // 第三行
    {M1, DOTTED_QUARTER_NOTE},// 1.
    {M2, QUARTER_NOTE},       // 2
    {M1, QUARTER_NOTE},       // 1
    {M7, QUARTER_NOTE},       // 7
    {M6, QUARTER_NOTE},       // 6
    {M3, QUARTER_NOTE},       // 3
    {M3, QUARTER_NOTE},       // 3
    {M1, QUARTER_NOTE},       // 1
    {M1, QUARTER_NOTE},       // 1
    {M7, QUARTER_NOTE},       // 7
    {M6, DOTTED_QUARTER_NOTE},// 6.
    {M3, QUARTER_NOTE},       // 3
    {M2, DOTTED_QUARTER_NOTE},// 2.
    {M1, QUARTER_NOTE},       // 1
    {M7, QUARTER_NOTE},       // 7
    {M5, QUARTER_NOTE},       // 5
    {M6, QUARTER_NOTE},       // 6
    {SILENCE, QUARTER_NOTE},  // -
    {M3, QUARTER_NOTE},       // 3
    {M1, QUARTER_NOTE},       // 1
    {M1, QUARTER_NOTE},       // 1
    {M7, QUARTER_NOTE},       // 7
    {M6, DOTTED_QUARTER_NOTE},// 6.
    {M3, QUARTER_NOTE},       // 3
    {M2, DOTTED_QUARTER_NOTE},// 2.
    {M1, QUARTER_NOTE},       // 1
    {M7, QUARTER_NOTE},       // 7
    {M5, QUARTER_NOTE},       // 5
    {M6, QUARTER_NOTE},       // 6
    {SILENCE, QUARTER_NOTE},  // -
    {END_MARKER, 0}           // 结束标记
};

// ================== 全局变量 ==================
unsigned char FreqSelect = 0;
bit is_paused = 0; // 暂停标志位：0-播放中，1-已暂停

// 定时器0初始化 (适配11.0592MHz晶振，16位模式)
void Timer0_Init()
{
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0x00;		//设置定时初值
	TH0 = 0x00;		//设置定时初值
	ET0 = 1;           //允许定时器0中断
	EA = 1;            //开启总中断
    TR0 = 0;           //初始化时先不启动
}

// 1毫秒延时函数 (专为11.0592MHz晶振校准)
void Delay(unsigned int ms)
{
	unsigned char i, j;
    while(ms--)
    {
        i = 2;
        j = 220; // 11.0592MHz下的1ms循环次数
        do
        {
            while (--j);
        } while (--i);
    }
}


// ================== 主函数 ==================
void main()
{
    unsigned int delayTime;
    unsigned int i;
    
    ScaleNote * currentNote = Song;
    Timer0_Init();
    
    ET0 = 1; // 允许定时器0中断
    EA = 1;  // 开启总中断
    
    while(1)
    {
        // ---------------------------------------------------
        // 1. 按键控制逻辑（播放/暂停）
        // ---------------------------------------------------
        if(K1 == 0)
        {
            Delay(20); // 按键消抖
            if(K1 == 0)
            {
                is_paused = !is_paused; // 切换状态
                
                if(is_paused) 
                {
                    TR0 = 0;   // 暂停时关闭定时器
                    beep = 0;  // 确保蜂鸣器静音
                }
                else 
                {
                    // 恢复播放时，重新装载频率并开启定时器
                    if(currentNote->noteIndex != SILENCE && currentNote->noteIndex != END_MARKER) 
                    {
                        TH0 = (unsigned char)(FreqTable[FreqSelect] >> 8);
                        TL0 = (unsigned char)(FreqTable[FreqSelect]);
                        TR0 = 1;
                    }
                }
                while(K1 == 0); // 等待按键松手
            }
        }

        // ---------------------------------------------------
        // 2. 音乐播放逻辑
        // ---------------------------------------------------
        if(!is_paused) 
        {
            if(currentNote->noteIndex != END_MARKER)
            {
                // 处理音符发声或休止
                if(currentNote->noteIndex == SILENCE) 
                {
                    TR0 = 0;    // 遇到休止符，关闭定时器
                    beep = 0;   // 确保蜂鸣器关闭
                }
                else 
                {
                    FreqSelect = currentNote->noteIndex;
                    TH0 = (unsigned char)(FreqTable[FreqSelect] >> 8);
                    TL0 = (unsigned char)(FreqTable[FreqSelect]);
                    TR0 = 1;    // 启动定时器
                }
                
                // 计算实际时值（去除圆滑线标志位）
                delayTime = SPEED / 4 * (currentNote->duration & 0x3F);
                
                // 音符持续时间（非阻塞延时，保证按键响应）
                for(i = 0; i < delayTime; i++)
                {
                    Delay(1); // 使用原有的Delay函数（1ms延时）
                }
                
                // 处理断音（无圆滑线标志）
                if(!(currentNote->duration & SLUR)) 
                {
                    TR0 = 0;     // 停止定时器
                    beep = 0;    // 确保蜂鸣器关闭
                    Delay(5);    // 音符间停顿（5ms）
                }
                
                currentNote++; // 移动到下一个音符
            }
            else
            {   
                // 乐曲播放完毕，等待按键重新播放
                TR0 = 0;
                beep = 0;
                while(1)
                {
                    if(K1 == 0)
                    {
                        Delay(20);
                        if(K1 == 0)
                        {
                            currentNote = Song; // 重置指针到开头
                            is_paused = 0;      // 确保播放状态
                            while(K1 == 0);     // 等待松手
                            break;              // 跳出等待循环
                        }
                    }
                }
            }
        }
    }
}

// ================== 定时器中断服务函数 ==================
void Timer0_Rountine() interrupt 1
{
    if(FreqTable[FreqSelect])
    {
        TH0 = (unsigned char)(FreqTable[FreqSelect] >> 8);
        TL0 = (unsigned char)(FreqTable[FreqSelect]);
        beep = !beep; // 翻转IO口产生方波
    }
}
