#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <string.h>

//константы
const double R = 8.31;           //универсальная газовая постоянная
const double Cp_mix = 1.0036;    //Сp смеси азота, аргона и кислорода
const double Cv_mix = 0.7166;    //Сv смеси азота, аргона и кислорода
const double Mu_mix = 0.02897;   //молярная масса смеси азота, аргона и кислорода
const double Cp_h2o = 1.863;     //Сp воды
const double Cv_h2o = 1.403;     //Сv воды
const double Mu_h2o = 0.01801;   //молярная масса воды
const double Cp_co2 = 0.838;     //Сp углекислого газа
const double Cv_co2 = 0.649;     //Сv углекислого газ
const double Mu_co2 = 0.04401;   //молярная масса углекислого газа

void temperature()
{
	double con_h2o, con_co2, speed, con_mix, Mu, Cp, Cv, T, gamma;
	printf("H2O concentration:\t");
	scanf("%lf", &con_h2o);
	printf("CO2 concentration:\t");
	scanf("%lf", &con_co2);
	printf("Speed:\t");
	scanf("%lf", &speed);


	con_mix = 1 - con_h2o - con_co2;         //концентрация смеси газов
	Mu = con_co2 * Mu_co2 + con_h2o * Mu_h2o + con_mix * Mu_mix;           //общая молярная масса
	Cp = con_co2 * Mu_co2 * Cp_co2 + con_h2o * Mu_h2o * Cp_h2o + con_mix * Mu_mix * Cp_mix;   //Сp общее
	Cv = con_co2 * Mu_co2 * Cv_co2 + con_h2o * Mu_h2o * Cv_h2o + con_mix * Mu_mix * Cv_mix;   //Сv общее
	gamma = Cp / Cv;              //показатель адиабаты


	T = (Mu * speed * speed) / (gamma * R);
	printf("Result temperature:\t%.1f\n", T);
}

void concentration()  //функция для нахождения концентрации
{
	double T, con_h2o, speed, a, b, c, con_mix, A, B, C, D, E, F, descr, x;
	printf("H2O concentration:\t");
	scanf("%lf", &con_h2o);
	printf("Temperature:\t");
	scanf("%lf", &T);
	printf("Speed:\t");
	scanf("%lf", &speed);


	A = Mu_mix * Cp_mix + con_h2o * (Mu_h2o * Cp_h2o - Mu_mix * Cp_mix);
	B = Mu_co2 * Cp_co2 - Mu_mix * Cp_mix;
	C = Mu_mix + con_h2o * (Mu_h2o - Mu_mix);
	D = Mu_co2 - Mu_mix;
	E = Mu_mix * Cv_mix + con_h2o * (Mu_h2o * Cv_h2o - Mu_mix * Cv_mix);         //A, B, C - промежуточные числа
	F = Mu_co2 * Cv_co2 - Mu_mix * Cv_mix;


	a = speed * speed * D * F;
	b = speed * speed * (F * C + D * E) - T * R * B;             // коэффициенты квадратного уравнения ax^2 + bx + c = 0
	c = speed * speed * C * E - T * R * A;
	descr = b * b - 4 * a * c;                //дескреминант 


	x = (sqrt(descr) - b) / (2 * a);              //решение уравнения
	printf("%.4lf\t%.2lf%%", x, x*100);
}

int main()
{
	int temp;
	printf("1 - temperature\t2 - co2 concentration\n");
	printf("Calculate:\t");   //интерфейс
	scanf("%d", &temp);
	if (temp == 1)
		temperature();  //функция для нахождения температуры
	else if (temp == 2)
		concentration();  //функция для нахождения концентрации
	return 0;
}