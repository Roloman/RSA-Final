#pragma once

#include <NTL/ZZ.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdlib.h>
#include <conio.h>
#include <cmath>
#include <vector>
#include <time.h>


#include <string>
#include <iomanip>
#include <string.h>
#include <sstream>
#include <stdio.h>
#include <ctime>

#include <random>

//using namespace System;
//using namespace System::Management;

using namespace std;
using namespace NTL;


class RSA
{
	public:

		RSA(int);
		RSA();
		virtual ~RSA();
		ZZ Exponenciacion_modular(ZZ, ZZ, ZZ);
		void Resto_Chino(ZZ*, ZZ*);
		string Cifrardo_Por_Partes(string);
		string Descifrardo_Por_Partes(string);
		ZZ Euclides(ZZ, ZZ);
		ZZ Extendido_Euclides(ZZ, ZZ);
		ZZ Inversa(ZZ, ZZ);
		bool Test_Primalidad(ZZ);

		void Generar_n();
		void Generar_e();
		void Generar_d();

		ZZ o_n;
		ZZ modulo(ZZ, ZZ);


		ZZ Primo_Aleatorio();

		bool Primos_Entre_Si(ZZ*, ZZ);
		
		void Primos_Criba();



		void Cifrar(string);
		ZZ Generar_Aleatorio(int);
		void New_Criba(int, int);
		string Descifrar(ZZ mensaje[4]);

		string De_ZZ_A_String(ZZ);

		

	protected:
	private:
		ZZ d;
		ZZ e;
		ZZ n;
		ZZ p;
		ZZ q;
		string alfabeto = "ABCDEFGHIJKLMNOPQRSTUVWXYZ,.-( )abcdefghijklmnopqrstuvwxyz<>*1234567890";
};

