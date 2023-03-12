#include <iostream>
#include <math.h>
#include <string.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>


bool isPrime(long int prime);
long int calculateE( long int t );
long int greatestCommonDivisor( long int e, long int t );
long int calculateD( long int e, long int t );
long int encrypt( long int i, long int e, long int n );
long int decrypt(long int i, long int d, long int n );

int main( )
{
	setlocale(LC_ALL, "Russian");
    long int p, q, n, t, e, d;    
    long int encryptedText[100];
    memset(encryptedText, 0, sizeof(encryptedText));
    long int decryptedText[100];
    memset(decryptedText, 0, sizeof(decryptedText));
    
    bool flag;
    std::string msg;
    std::cout << "\n\n\n<<<___   Вiтаємо у програмi шифрування RSA   ___>>>" << std::endl << std::endl;
    do // 1 крок: Вибираються два великі прості числа p і q  приблизно 512 біт завдовжки кожне
    {
        std::cout << "Введіть перше просте число p:" << std::endl;
        std::cin >> p;
        flag = isPrime( p );
        if ( flag == false )
        {
            std::cout << "\n<<<НЕВІРНЕ ВВЕДЕННЯ>>>\nЧисло не є простим. Спробуйте ввести число ще раз\n" << std::endl;
        }
    } while ( flag == false );
    do
    {
        std::cout << "Введіть друге просте число q:" << std::endl;
        std::cin >> q;
        flag = isPrime( q );
        if ( flag == false )
        {
            std::cout << "\n<<<НЕВІРНЕ ВВЕДЕННЯ>>>\nЧисло не є простим. Спробуйте ввести число ще раз\n" << std::endl;
        }
    } while ( flag == false);
    n = p * q; // 2 крок: Обчислюється їх добуток 
    std::cout << "\nРезультат добутку n = p*q = " << n << std::endl;
    t = ( p - 1 ) * ( q - 1 ); //3 крок: Обчислюється функція Ейлера φ(n)=(p − 1)(q − 1)
    std::cout << "Результат застосування функції Ейлера:\t t = " << t << std::endl;
	// 4 крок: Вибирається ціле число e таке, що 1 < e < φ(n) та e взаємно просте з φ(n)
    e = calculateE( t );
    
    // 5 крок: За допомогою розширеного алгоритму Евкліда знаходиться число d таке, що
    // d ⋅ e ≡ 1 (mod φ(n))
    d = calculateD( e, t );
    
    std::cout << "\nRSA відкритий ключ: (n = " << n << ", e = " << e << ")" << std::endl;
    std::cout << "RSA приватний ключ: (n = " << n << ", d = " << d << ")" << std::endl;
    
    std::cout << "\nВведіть повідомлення, яке хочете зашифрувати:" << std::endl;
    std::cin.ignore();
    std::getline( std::cin, msg );
    std::cout << "\nВведене повідомлення: " << msg << std::endl;
    // Шифрування
    for (long int i = 0; i < msg.length(); i++)
    {
        encryptedText[i] = encrypt( msg[i], e, n);
    }
    std::cout << "\nЗашифроване повідомлення:" << std::endl;
    for ( long int i = 0; i < msg.length(); i++ )
    {
        printf( "%ld ", encryptedText[i] );
    } 
	// Розшифрування
    
    for (long int i = 0; i < msg.length(); i++)
    {
        decryptedText[i] = decrypt(encryptedText[i], d, n);
    }
    
    std::cout << "\n\nРозшифроване повідомлення:" << std::endl;
    for (long int i = 0; i < msg.length(); i++)
    {
        printf( "%c", (char)(decryptedText[i]));
    }
    std::cout << std::endl << std::endl;    
    return 0;
}

bool isPrime( long int prime)
{
    long int i, j;
    
    j = (long int)sqrt((long double)prime);
    
    for ( i = 2; i <= j; i++)
    {
        if ( prime % i == 0 )
        {
            return false;
        }
    }
    
    return true;
}

long int calculateE( long int t )
{
    long int e;
    
    for ( e = 2; e < t; e++ )
    {
        if (greatestCommonDivisor( e, t ) == 1 )
        {
            return e;
        }
    }
    
    return -1;
}

long int greatestCommonDivisor( long int e, long int t )
{
    while ( e > 0 )
    {
        long int myTemp;
        
        myTemp = e;
        e = t % e;
        t = myTemp;
    }
    
    return t;
}

long int calculateD( long int e, long int t)
{
    long int d;
    long int k = 1;
    
    while ( 1 )
    {
        k = k + t;
        
        if ( k % e == 0)
        {
            d = (k / e);
            return d;
        }
    }
    
}

long int encrypt( long int i, long int e, long int n )
{
    long int current, result;
    
    current = i;
    result = 1;
    for ( long int j = 0; j < e; j++ )
	{
        result = result * current;
        result = result % n;
	}
    return result;
}

long int decrypt(long int i, long int d, long int n)
{
    long int current, result;
    
    current = i;
    result = 1;
    
    for ( long int j = 0; j < d; j++ )
	{
        result = result * current;
        result = result % n;
	}
    return result;
}
