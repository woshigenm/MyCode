#include <stdio.h>

int main()
{
    int red, white, black;

    int counter = 0;

    for (red = 1; red <= 3; red++)
    {
        for (white = 1; white <= 7; white++)
        {
            for (black = 0; black <= 4; black++)
            {
                if (red + white + black == 8)
                {
                    printf("红球有%d个,白球有%d个,黑球有%d个\n", red, white, black);
                    counter++;
                }
            }
// black = 8 - red - white;
//
// if(black >= 0 && black <= 4)
// {
// printf("红球有%d个,白球有%d个,黑球有%d个\n", red, white, black);
// counter++;
// }
        }
    }
    printf("共有%d种可能\n", counter);
}
