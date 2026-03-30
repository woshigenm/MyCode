#include <stdio.h>
#include <string.h>

#define N 128

void setStr(char *str, int target_len) {
	int current_len = strlen(str);
	if (current_len < target_len) {
		// 移动字符串到右侧，左侧补零
		memmove(str + (target_len - current_len), str, current_len + 1); // +1 包含结束符
		memset(str, '0', target_len - current_len);
	}
}

int main() {
	char str1[N] = {0};
	char str2[N] = {0};
	char result[N + 2] = {0}; // 多两位：可能进位和结束符

	scanf("%127s%127s", str1, str2); // 限制输入长度

	int len1 = strlen(str1);
	int len2 = strlen(str2);
	int max_len = len1 > len2 ? len1 : len2;

	// 将两个字符串补零到相同长度
	setStr(str1, max_len);
	setStr(str2, max_len);

	int carry = 0;

	// 从右向左逐位相加
	int i;
	for (i = max_len - 1; i >= 0; i--) {
		int num1 = str1[i] - '0';
		int num2 = str2[i] - '0';
		int sum = num1 + num2 + carry;

		carry = sum / 10;
		result[i] = (sum % 10) + '0'; // 存储当前位结果
	}

	// 处理最高位进位
	if (carry) {
		memmove(result + 1, result, max_len);
		result[0] = '1';
		result[max_len + 1] = '\0'; // 确保字符串结束
		puts(result);
	} else {
		puts(result + i + 1); // 跳过前导零存储位置
	}

	return 0;
}
