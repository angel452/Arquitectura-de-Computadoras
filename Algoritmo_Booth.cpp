#include <iostream>
#include <bitset>

/*
Cases:
Para cambiar el tamaño de bits: linea 12
Ingresar el multiplicando y multiplicador en el main: linea 196 - 197
*/

using namespace std;

#define longitud_bits 4  //Cantidad de bits

bitset<longitud_bits>funcion_suma( bitset <longitud_bits> num1, bitset<longitud_bits> num2 )
{
    bitset <longitud_bits> resultado; 
    int acarreo = 0;
        
    //(acarreo)
    //(0) 1 + 0 = (0)1
    //(0) 1 + 1 = (1)0
    //(0) 0 + 0 = (0)0
    //(0) 0 + 1 = (0)1
    //(1) 0 + 0 = (0)1
    //(1) 1 + 1 = (1)1

    int iterador = 0;
    while (iterador < longitud_bits)
    {
        if (num1[iterador] == 1 && num2[iterador] == 0 && acarreo == 0)
        {
            resultado[iterador] = 1; 
            acarreo = 0;
            iterador++;
        }
        else if (num1[iterador] == 1 && num2[iterador] == 1 && acarreo == 0)
        {
            resultado[iterador] = 0;
            acarreo = 1;
            iterador++;
        }
        else if (num1[iterador] == 0 && num2[iterador] == 0 && acarreo == 0)
        {
            resultado[iterador] = 0;
            acarreo = 0;
            iterador++;
        }
        else if (num1[iterador] == 0 && num2[iterador] == 1 && acarreo == 0)
        {
            resultado[iterador] = 1;
            acarreo = 0;
            iterador++;
        }
        else if (num1[iterador] == 0 && num2[iterador] == 0 && acarreo == 1)
        {
            resultado[iterador] = 1;
            acarreo = 0;
            iterador++;
        }
        else if (num1[iterador] == 1 && num2[iterador] == 1 && acarreo == 1)
        {
            resultado[iterador] = 1;
            acarreo = 1;
            iterador++;
        }
        else
        {
            iterador++;
        }
    }

    return resultado;
}

bitset<longitud_bits>funcion_resta(bitset<longitud_bits>num1, bitset<longitud_bits>num2) 
{  
    //lo mismo de la suma pero con complemento a 2 en num2
    num2 = funcion_suma(~num2, 1);

    bitset <longitud_bits> resultado;
    int acarreo = 0;

    //(acarreo)
    //(0) 1 + 0 = (0)1
    //(0) 1 + 1 = (1)0
    //(0) 0 + 0 = (0)0
    //(0) 0 + 1 = (0)1
    //(1) 0 + 0 = (0)1
    //(1) 1 + 1 = (1)1

    int iterador = 0;
    while (iterador < longitud_bits)
    {
        if (num1[iterador] == 1 && num2[iterador] == 0 && acarreo == 0)
        {
            resultado[iterador] = 1;
            acarreo = 0;
            iterador++;
        }
        else if (num1[iterador] == 1 && num2[iterador] == 1 && acarreo == 0)
        {
            resultado[iterador] = 0;
            acarreo = 1;
            iterador++;
        }
        else if (num1[iterador] == 0 && num2[iterador] == 0 && acarreo == 0)
        {
            resultado[iterador] = 0;
            acarreo = 0;
            iterador++;
        }
        else if (num1[iterador] == 0 && num2[iterador] == 1 && acarreo == 0)
        {
            resultado[iterador] = 1;
            acarreo = 0;
            iterador++;
        }
        else if (num1[iterador] == 0 && num2[iterador] == 0 && acarreo == 1)
        {
            resultado[iterador] = 1;
            acarreo = 0;
            iterador++;
        }
        else if (num1[iterador] == 1 && num2[iterador] == 1 && acarreo == 1)
        {
            resultado[iterador] = 1;
            acarreo = 1;
            iterador++;
        }
        else
        {
            iterador++;
        }
    }

    return resultado;
}

void corrimiento(bitset<longitud_bits>& A, bitset<longitud_bits>& Q, int& q1) 
{  
    int aux1, aux2, aux3;

    aux1 = A.test(longitud_bits - 1);
    aux2 = A.test(0);

    A = A >> 1;
    A.set(longitud_bits - 1, aux1);
    aux3 = Q.test(0);

    Q = Q >> 1;
    Q.set(longitud_bits - 1, aux2);
    q1 = aux3;
}

void algoritmo_booth(bitset<longitud_bits> num1, bitset<longitud_bits> num2) 
{ 
    bitset <longitud_bits> A = 0; //siempre 0000
    bitset <longitud_bits> Q = num1;  
    int q1 = 0;
    bitset <longitud_bits> M = num2;        

    cout << "-------------------------------------------------" << endl;
    cout << "Proceso" << endl;

    cout << "-------------------------------------------------" << endl;
    for (int i = 0; i < longitud_bits; i++) {
        
        cout << A << "\t" << Q << "\t" << q1 << "\t" << M << "\t" << endl;

        if (Q.test(0) == 1 && q1 == 0) //.test -> devuelve ultima posicion
        {
            A = funcion_resta(A, M);
        }

        else if (Q.test(0) == 0 && q1 == 1) 
        {
            A = funcion_suma(A, M);
        }

        /*
        else
        {
            corrimiento(A, Q, q - 1);
        }
        */

        corrimiento(A, Q, q1);
    }
    cout << "-------------------------------------------------" << endl;
    cout << endl << "Resultado: " << A << " " << Q << endl;
}

int main() {

    
    bitset <longitud_bits> num1 = 3;
    bitset <longitud_bits> num2 = 7;

    /*
    bitset <longitud_bits> num1;
    bitset <longitud_bits> num2;

    cout << "Ingrese el primer numero: ";
    cin >> num1;
    cout << "Ingrese el segundo numero: ";
    cin >> num2;
    */

    algoritmo_booth(num1, num2);

    return 0;
}
