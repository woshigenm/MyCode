#include <stdio.h>
#include <math.h>

#define SIZE 7
#define SHiWEN 20
#define ON 1

#define x(i) point[i].x
#define y(i) point[i].y

typedef struct Point {
	int x;	//time
	double y;//temperatures
} Point;

double Get_avg(const Point point[], int size);

double Variance(const Point point[], int size);

double Sqrt_R_Exp(const Point point[], int size, double avg_a);

void FitExp(const Point point[], int size);

void FitIn(const Point point[], int size);

double Sqrt_R_In(const Point point[], int size, double avg_a, double k);

int main() {
	Point myfunction[SIZE] = { {0, 80.000000}, {1, 76.900000}, {2, 74.600000}, {3, 72.400000}, {4, 70.900000}, {5, 69.400000}, {6, 68.000000} };
	FitIn(myfunction, SIZE);
	putchar('\n');
	FitExp(myfunction, SIZE);

	return 0;
}

double Get_avg(const Point point[], int size) {
	double sum = 0.0;
	for (int i = 0; i < size; i++)	sum += y(i);
	return sum / size;
}

double Variance(const Point point[], int size) {
	double sum = 0.0, avg_y;

	avg_y = Get_avg(point, size);

	for (int i = 0; i < size; i++)	sum += pow(y(i) - avg_y, 2);

	return sum / (size - 1);
}

double Sqrt_R_Exp(const Point point[], int size, double avg_a) {
	double SST = 0.0, SSR = 0.0;

	double avg_y = Get_avg(point, size);

	for (int i = 0; i < size; i++) {
		SST += pow(y(i) - avg_y, 2);
		SSR += pow(y(i) - (y(0) - SHiWEN) * pow(avg_a, x(i)) - SHiWEN, 2);
	}
#if ON == 1
	printf("EXP: SST -> %lf SSR -> %lf\n", SST, SSR);
#endif

	return 1 - SSR / SST;
}

void FitExp(const Point point[], int size) {
	double sum = 0.0, avg_a, a;

	int count = 0;
	for (int i = 0; i < size; i++) {
		if (x(i) != 0) {
			a = pow((y(i) - SHiWEN) / 60, 1.0 / x(i));
			sum += a;
#if ON == 1
			printf("sum -> %.4lf a -> %.4lf a^%d -> %.4lf\n", sum, a, x(i), pow(a, x(i)));
#endif
			count++;
		}
	}

	avg_a = sum / count;

#if ON == 1
	printf("avg_a -> %lf\n", avg_a);
#endif

	printf("指数模型为 y = %.lf * %lf^x + %d\n", y(0) - SHiWEN, avg_a, SHiWEN);
	printf("Variance(方差): %lf, R^2(拟合优度): %lf\n", Variance(point, size), Sqrt_R_Exp(point, size, avg_a));
}

void FitIn(const Point point[], int size) {
	double sum, a, k, avg_a;
	for (int i = 1; i < size; i++) {
		a = x(i) * (y(i) - SHiWEN) / (y(0) - y(i));
		sum += a;
#if ON == 1
		printf("sum -> %.4lf a -> %.4lf\n", sum, a);
#endif
	}

	avg_a = sum / (size - 1);
	k = avg_a * (y(0) - SHiWEN);

#if ON == 1
	printf("avg_a -> %lf k -> %lf\n", avg_a, k);
#endif

	printf("反比例模型为 y = %.4lf / x + %.4lf + %d\n", k, avg_a, SHiWEN);
	printf("Variance(方差): %lf, R^2(拟合优度): %lf\n", Variance(point, size), Sqrt_R_In(point, size, avg_a, k));
}

double Sqrt_R_In(const Point point[], int size, double avg_a, double k) {
	double SST = 0.0, SSR = 0.0;
	double avg_y = Get_avg(point, size);

	for (int i = 0; i < size; i++) {
		SST += pow(y(i) - avg_y, 2);
		SSR += pow(y(i) - (k / (x(i) + avg_a) + SHiWEN), 2);
		//printf("(%d,%lf),", i, (k / (x(i) + avg_a) + SHiWEN));
	}

#if ON == 1
	printf("IN: SST -> %lf SSR -> %lf\n", SST, SSR);
#endif

	return 1 - SSR / SST;
}

