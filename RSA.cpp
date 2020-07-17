// RSA.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>

#include "RSA.h"




const int rango = 78498;
const int tam_vec = 4;
const int tam = 3;

RSA::RSA() {

    //p = Primo_Aleatorio();
    //q = Primo_Aleatorio();
    Primos_Criba();
    Generar_n();
    Generar_e();
    Generar_d();
    cout << "p = " << p << endl;
    cout << "q = " << q << endl;
    cout << "n = " << n << endl;
    cout << "o_p = " << o_n << endl;
    cout << "e = " << e << endl;
    cout << "d = " << d << endl << endl;
    //*/
}

RSA::~RSA()
{
    //dtor
}

ZZ RSA::modulo(ZZ a, ZZ b)
{
    return a - ((a / b) * b);
}

ZZ RSA::Primo_Aleatorio() {

    return RandomPrime_ZZ(20, 10);

}

ZZ RSA::Euclides(ZZ a, ZZ b)
{
    ZZ r = ZZ(a % b);
    while (r != 0)
    {
        //cout << a << " = " << a / b << " (" << b << ") + " << a - (b * (a / b)) << endl;
        a = b;
        b = r;
        r = a % b;
    }
    //cout << a << " = " << a / b << " (" << b << ") + " << a - (b * (a / b)) << endl;
    return b;
}

ZZ RSA::Extendido_Euclides(ZZ a, ZZ b)
{
    ZZ q;
    ZZ r, r1, r2;
    ZZ s, s1, s2;
    ZZ t, t1, t2;

    r1 = a;
    r2 = b;
    s1 = (1);
    s2 = (0);
    t1 = (0);
    t2 = (1);

    while (r2 > 0) {

        q = r1 / r2;
        r = r1 - (q * r2);
        r1 = r2;
        r2 = r;

        s = s1 - (q * s2);
        s1 = s2;
        s2 = s;

        t = t1 - (q * t2);
        t1 = t2;
        t2 = t;
    }
    r = r1;
    s = s1;
    t = t1;
    if (s < 0)
        s = s % b;
    if (t < 0)
        t = t % a;
    //cout << a << "(" << s << ") + " << b << "(" << t << ") = " << r << endl;
    return s;
}

ZZ RSA::Inversa(ZZ a, ZZ b) {

    ZZ r = ZZ(0);
    ZZ c;
    if (Euclides(a, b) == 1) {

        c = Extendido_Euclides(a, b);
        if (c < 0)
            c = c % b;

    }
    else
    {
        cout << a << " No tiene inversa" << endl << endl;
        return ZZ(0);
    }
    return c;
}

void RSA::Primos_Criba() {

    PrimeSeq a;
    ZZ Criba[78498];
    long b, c, d, e;
    c = 0;
    b = a.next();
    while (b <= 1000000) {
        //cout << b << " ";
        b = a.next();
        Criba[c] = b;
        c++;
    }
    d = 0;
    e = 0;
    srand(time(NULL));
    while (d == e && Euclides(Criba[d], Criba[e]) != 1) {
        d = rand() % 78498;
        e = rand() % 78498;
    }
    d = rand() % 78498;
    this->p = Criba[d];
    this->q = Criba[e];
    /*cout << b << endl;
    cout << endl << endl;
    cout << "yo sor r = " << c << endl << endl;
    //delete[] Criba;
    //*/
    //free (Criba);
}

ZZ RSA::Exponenciacion_modular(ZZ base, ZZ exp, ZZ mod) {
        
    ZZ b;
    b = 1;
    if (exp == 0)
        return b;
    ZZ A = base;
    if (modulo (exp, ZZ (2)) == 1)
        b = base;
    while ((exp = exp / 2) != 0) {
        A = modulo((A * A), mod);
        if (modulo (exp, ZZ (2)) == 1)
            b = modulo((A * b), mod);
    }
    /*while ( b > this->alfabeto.size() ){
        b = b - this->alfabeto.size();
    }*/
    return b;
}

void RSA::Generar_n() {

    n = p * q;
    o_n = (p - 1) * (q - 1);
}

void RSA::Generar_e() {

    e = modulo(ZZ(rand()), (o_n - 1));
    //e = Primo_Aleatorio();
    int i = 0;
    while (Euclides(e, o_n) != 1) {
        e = modulo(ZZ(rand()), (o_n - 1));
        i++;
    }
    //cout << "yo soy r = " << i << endl;
}

void RSA::Generar_d() {

    d = Inversa(e, o_n);
    while (d == 0) {
        d = Inversa(e, o_n);
    }
}

bool RSA::Primos_Entre_Si(ZZ* Primos, ZZ tam) {

    for (int i = 0; i < tam; i++) {

        for (int j = i + 1; j < tam; j++) {
            if (Euclides(Primos[i], Primos[j]) != 1 || Primos[i] == Primos[j]) {

                cout << Primos[i] << " y " << Primos[j] << " no son primos relativos" << endl;
                return false;
            }
        }
    }

    return true;
}

void RSA::Resto_Chino(ZZ* ai, ZZ* pi) {

    ZZ X = ZZ(0), P = ZZ(1);
    ZZ Pi[tam];
    ZZ qi[tam];
    ZZ x0[tam];

    if (Primos_Entre_Si(pi, ZZ(tam)) == 1) {

        for (int i = 0; i < tam; i++) {

            P *= pi[i];
        }

        for (int i = 0; i < tam; i++) {

            Pi[i] = P / pi[i];
            qi[i] = Inversa(Pi[i], pi[i]);
        }

        for (int i = 0; i < tam; i++) {

            x0[i] = modulo(ai[i] * Pi[i] * qi[i], P);
        }

        for (int i = 0; i < tam; i++) {

            X += x0[i];
        }
        X = modulo(X, P);
        //cout << "X = " << X << " (mod " << P << ")" << endl;
        //cout << "X = " << X << " + " << P << "k" << endl;
    }
    else
    {
        cout << "algo salio mal" << endl;
    }

    //Fines de no escritura
    for (int i = 0; i < tam; i++) {
        cout << "P" << i + 1 << " = " << Pi[i] << endl;
    }
    for (int i = 0; i < tam; i++) {
        cout << "q" << i + 1 << " = " << qi[i] << endl;
    }
    for (int i = 0; i < tam; i++) {
        cout << "x" << i + 1 << " = " << x0[i] << endl;
    }
    cout << "X = " << X << " (mod " << P << ")" << endl;
    cout << "X = " << X << " + " << P << "k" << endl;
}

void RSA::Cifrar(string mensaje) {

    ZZ m;
    ZZ mensaje_cifrado [tam_vec];
    for (int i = 0; i < mensaje.size(); i++)
    {
        m = alfabeto.find(mensaje[i]);
        m = Exponenciacion_modular(m, e, n);
        mensaje_cifrado[i] = m;
    }
    for (int i = 0; i < tam_vec; i++) {
        cout << "letra del mensaje " << i + 1 << " = " << mensaje_cifrado[i] << endl << endl;
    }
    //return mensaje_cifrado;
    cout << "Mensaje cifrado: ";
    for (int i = 0; i < tam_vec; i++) {
        cout << mensaje_cifrado[i];
    }
    cout << endl << endl;
    Descifrar(mensaje_cifrado);
}

string RSA::Descifrar(ZZ mensaje [4]) {

    ZZ m;
    int a = 0;
    int r = 0;
    string mensaje_cifrado;
    for (int i = 0; i < tam_vec; i++)
    {
        m = Exponenciacion_modular(mensaje[i], d, n);
        cout << "m = " << m << endl;
        while (m > 0) {
            m--;
            a++;
        }
        mensaje_cifrado += alfabeto[a];
        a = 0;
    }
    cout << "mensaje descifrado = " << mensaje_cifrado << endl;
    return mensaje_cifrado;
}

ZZ RSA::Generar_Aleatorio(int N_bits) {

    ZZ a;
    int bits = N_bits / 2;
    RandomPrime(a, bits, 10);
    return a;
}

void RSA::New_Criba(int Intervalo_Mayor, int Intervalo_Menor) {

    ZZ inicio, final;
    vector <ZZ> vec;
    vector <ZZ> criba;

    inicio = power_ZZ((2), (Intervalo_Menor));
    final = (power_ZZ((2), (Intervalo_Mayor)));

    for (ZZ i = inicio; i < final; i ++) {
        if (ProbPrime(i) != 0)
            criba.push_back(i);
    }
    

    cout << "hecho" << endl;
    /*for (int i = 0; i < vec.size(); i++) {
        if (ProbPrime(vec[i]) != 0)
            criba.push_back(vec[i]);
    }
    for (int i = 0; i < criba.size(); i++)
        cout << criba[i] << endl;
        */

}

bool RSA::Test_Primalidad(ZZ primo) {

    if (modulo(primo, ZZ(2)) == 0) {
        cout << primo << " no es primo" << endl;
        return false;
    }

    ZZ i;

    for ( i = 3; i <= primo / 2; i+=2) {
        cout << i << endl;
        if (primo % i == 0) {
            cout << primo << " no es primo" << endl;
            return false;
        }
    }
    return true;
}

RSA::RSA(int bits) {

    cout << "Soy RSA" << endl << endl;
    
    int a = 5;

    this->p = Generar_Aleatorio(1024);
    this->q = Generar_Aleatorio(1024);
    this->n = p * q;
    this->o_n = (p - 1) * (q - 1);
    while (a > 0) {
        this->e = modulo(ZZ(rand()), (o_n - 1));
        a--;
    }
    this->d = Inversa(e, o_n);
    while (d == 0) {
        this->e = modulo(ZZ(rand()), (o_n - 1));
        this->d = Inversa(e, o_n);
    }
    
    cout << "yo soy p = " << p << endl << endl;
    cout << "yo soy q = " << q << endl << endl;
    cout << "yo soy N = " << n << endl << endl;
    cout << "yo soy o_n = " << o_n << endl << endl;
    cout << "yo soy e = " << e << endl << endl;
    cout << "yo soy d = " << d << endl << endl;
    //*/
}

string RSA::De_ZZ_A_String(ZZ letra) {

    stringstream ss;
    ss << letra;

    string str;
    ss >> str;

    return str;
}

string RSA::Cifrardo_Por_Partes(string mensaje) {

    //Esto es para hallar el numero de digitos de n
    string N = De_ZZ_A_String(n);
    int tam_N = N.size();
    int k = tam_N - 1;

    //Recoleccion de la posicion de cada letra
    ZZ m;
    string mensaje_cifrado;

    for (int i = 0; i < mensaje.size(); i++)
    {
        m = alfabeto.find(mensaje[i]);
        if (m < 10) {
            mensaje_cifrado += '0';
            mensaje_cifrado += De_ZZ_A_String(m);
        }
        else
        {
            mensaje_cifrado += De_ZZ_A_String(m);
        }
    }

    //Dividir en bloques y exponenciacion modular
    ZZ temporal;
    ZZ Exp_Mod;
    int Tam_Mensaje_Cifrado = mensaje_cifrado.size();
    string temp;
    string tam_temp;
    string cifrado_final;

    while ( mensaje_cifrado.size() > 0) {
        temp = mensaje_cifrado.substr(0, k);
        mensaje_cifrado = mensaje_cifrado.erase(0, k);
        temporal = stoi(temp);
        Exp_Mod = Exponenciacion_modular(temporal, e, n);
        temp = De_ZZ_A_String(Exp_Mod);
        tam_temp = temp.size();

        if (temp.size() < tam_N) {
            string zeros((tam_N - temp.size()), '0');
            cifrado_final += zeros;
            cifrado_final += De_ZZ_A_String(Exp_Mod);
        }
        else
        {
            cifrado_final += De_ZZ_A_String(Exp_Mod);
        }
    }
    return cifrado_final;
}

string RSA::Descifrardo_Por_Partes(string mensaje) {

    string N = De_ZZ_A_String(n);
    int tam_N = N.size();
    int k = tam_N - 1;

    string mensaje_descifrado;
    string mensaje_descifrado_final;
    string segmento;
    string letra;
    ZZ temp;
    int pos_let;

    while (mensaje.size() > 0) {

        segmento = mensaje.substr(0, tam_N);
        mensaje = mensaje.erase(0, tam_N);
        temp = stoi(segmento);
        temp = Exponenciacion_modular(temp, d, n);
        letra = De_ZZ_A_String(temp);
        if (letra.size() < k) {
            string zeros((k - letra.size()), '0');
            mensaje_descifrado += zeros;
            mensaje_descifrado += letra;
        }
        else
        {
            mensaje_descifrado += letra;
        }
    }
    cout << "soy el casi descifrado = " << mensaje_descifrado << endl << endl;

    while (mensaje_descifrado.size() > 0) {

        segmento = mensaje_descifrado.substr(0, 2);
        mensaje_descifrado = mensaje_descifrado.erase(0, 2);
        pos_let = stoi(segmento);
        mensaje_descifrado_final += alfabeto[pos_let];
    }
    return mensaje_descifrado_final;
}

string A_String(ZZ letra) {

    stringstream ss;
    ss << letra;

    string str;
    ss >> str;

    return str;
}

ZZ Exponenciacion_modular11(ZZ base, ZZ exp, ZZ mod) {

    ZZ b;
    b = 1;
    if (exp == 0)
        return b;
    ZZ A = base;
    if (exp % ZZ(2) == 1)
        b = base;
    while ((exp = exp / 2) != 0) {
        A = ((A * A) % mod);
        if ((exp % ZZ(2)) == 1)
            b = ((A * b) % mod);
    }
    /*while ( b > this->alfabeto.size() ){
        b = b - this->alfabeto.size();
    }*/
    return b;
}

ZZ Potencia_Modulo(ZZ p, ZZ e, ZZ n)
{
    if (e == 0) return ZZ(1);

    long k = NumBits(e);

    ZZ res;
    res = 1;

    for (long i = k - 1; i >= 0; i--) {
        res = SqrMod(res, n);
        if (bit(e, i) == 1) res = MulMod(res, p, n);
    }

    if (e < 0)
        return InvMod(res, n);
    else
        return res;
}

/*void printHardware(String^ hardwareClass, String^ propertyName) {

    ManagementObjectSearcher^ searcher = gcnew ManagementObjectSearcher("root\\CIMv2", "SELECT + FROM " + hardwareClass);
    ManagementObjectCollection^ collection = searcher->Get();

    Console::WriteLine(propertyName);
}*/

int main()
{
    //RSA s;

    ZZ m;
    string mensaje_cifrado;
    string mensaje = "COMEHERE";
    //021412040704170426
    string mensaje_descifrado;
    
    ZZ primo;
    //cin >> primo;
    //s.Test_Primalidad(primo);
    int a = getpid();
    
    cout << getpid() << endl;
    cout << _getdllprocaddr << endl;
    cout << GetAce << endl;
    
    //printHardware("Win32_VideoController", "Name");

    /*
    random_device rd;
    default_random_engine eng(rd());
    default_random_engine eng1(a);

    for (int i = 0; i < 5; i++) {
        cout << "soy eng = " << eng() << endl;
        cout << "soy eng1 = " << eng1() << endl << endl;
    }
    
    //mensaje_cifrado = s.Cifrardo(mensaje);
    //cout << "soy el cifrado = " << mensaje_cifrado << endl;

    //mensaje_descifrado = s.Descifrardo(mensaje_cifrado);
    //cout << "soy el descifrado = " << mensaje_descifrado << endl;
    /*
    string alfabeto = "ABCDEFGHIJKLMNOPQRSTUVWXYZ,.-( )abcdefghijklmnopqrstuvwxyz<>*1234567890";
    ZZ p = ZZ(17);
    ZZ q = ZZ(59);
    ZZ n = ZZ(29531868827);
    ZZ o_n = ZZ(00);
    ZZ e = ZZ(32257);
    ZZ d = ZZ(14608744129);
    
    /*ZZ p = ZZ(17);
    ZZ q = ZZ(59);
    ZZ n = ZZ(1003);
    ZZ o_n = ZZ(00);
    ZZ e = ZZ(3);
    ZZ d = ZZ(619);//*/

    /*string N = s.De_ZZ_A_String(n);
    int tam_N = N.size();
    int k = tam_N - 1;

    for (int i = 0; i < mensaje.size(); i++)
    {
        m = alfabeto.find(mensaje[i]);
        if (m < 10) {
            mensaje_cifrado += '0';
            mensaje_cifrado += A_String(m);
        }
        else
        {
            mensaje_cifrado += A_String(m);
        }
    }
    cout << "Yo soy el cifrado = " << mensaje_cifrado << endl << endl;
    
    string tem;
    ZZ temporal;
    ZZ Expo_Mod;
    string tam_temp;
    int Tam_Mensaje_Cifrado = mensaje_cifrado.size();
    //string temp;
    string cifrado_final;

    while (mensaje_cifrado.size() > 0) {
        tem = mensaje_cifrado.substr(0, k);
        mensaje_cifrado = mensaje_cifrado.erase(0, k);
        temporal = stoi(tem);
        Expo_Mod = Potencia_Modulo(temporal, e, n);

        tem = A_String(Expo_Mod);
        tam_temp = tem.size();

        if (tem.size() < tam_N) {
            string zeros((tam_N - tem.size()), '0');
            cifrado_final += zeros;
            cifrado_final += A_String(Expo_Mod);
        }
        else
        {
            cifrado_final += A_String(Expo_Mod);
        }
    }
    cout << "Yo soy el cifrado final = " << cifrado_final << endl << endl;
    
    mensaje = cifrado_final;
    cout << "soy mensaje a descifrar = " << mensaje << endl << endl;
    //string mensaje_descifrado;
    string mensaje_descifrado_final;
    string segmento;
    string letra;
    ZZ temp;
    int pos_let;

    while (mensaje.size() > 0) {

        segmento = mensaje.substr(0, tam_N);
        mensaje = mensaje.erase(0, tam_N);
        temp = stoi(segmento);
        cout << "segmento del mensaje = " << temp << endl;
        temp = Potencia_Modulo(temp, d, n);
        cout << "segmento del mensaje = " << temp << endl;
        letra = A_String(temp);
        if (letra.size() < k) {
            string zeros((k - letra.size()), '0');
            mensaje_descifrado += zeros;
            mensaje_descifrado += letra;
        }
        else
        {
            mensaje_descifrado += letra;
        }
    }
    cout << "soy el casi descifrado = " << mensaje_descifrado << endl << endl;
    
    while (mensaje_descifrado.size() > 0) {

        segmento = mensaje_descifrado.substr(0, 2);
        mensaje_descifrado = mensaje_descifrado.erase(0, 2);
        pos_let = stoi(segmento);
        mensaje_descifrado_final += alfabeto[pos_let];
    }
    cout << "Soy el descifrado final = " << mensaje_descifrado_final << endl << endl;
    //*/
}