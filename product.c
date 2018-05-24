#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

short* multiply(short*,short*);
void temporary(short*,short,short,short*);
void display(short, short, short*);
int digits(unsigned long long);
void store (short* , unsigned long long);
void reverse(short*);
int sum_digits(short*);
short* copy_array(short*,short*);

int main()
{
    short i;
    unsigned long long a = 9838644839949268, b = 123;
    short *num1 = (short*)malloc(sizeof(short) * (digits(a) + 1) );
    short *num2 = (short*)malloc(sizeof(short) * (digits(b) + 1) );
    short* result;
    num1[0] = digits(a);
    num2[0] = digits(b);
    store(num1,a);
    store(num2,b);
    result = multiply(num1, num2);
    printf("\n");
    num2 = copy_array(num1,num2);
    for (i = 1; i <= num2[0]; i++)
        printf("%d", num2[i]);
    return 0;
}

int sum_digits(short* ptr)
{
    int i, sum = 0;
    for (i = 1; i < ptr[0]; i++)
        sum += ptr[i];
    return sum;
}

short* multiply(short* mul1,short* mul2)//Assuming the first element is size of the array
{
    short* small = ( mul1[0] < mul2[0] ) ? mul1 : mul2;
    short* large = ( mul1[0] > mul2[0] ) ? mul1 : mul2;
    short i, j, k, row = small[0], col = large[0] + 1, sum = 0, l = 1;
    short* temp = (short*)calloc( row * col, sizeof(short));
    short* product = (short*)calloc( l, sizeof(short) );
    small = small + 1;
    large = large + 1;
    for ( i = row - 1, j = 0; i >=0; i--, j++)
        temporary(large,col,small[i],(temp + j * col));
    for (j = col - 1; ; j--)
    {
        for ( i = 0, k = j; i < row ; i++ , k++)
        {
            if ( k >= 0 && k < col)
                sum += *( temp + i * col + k);
            if ( i == (row - 1) && k == 0)
                j = col;
        }
        product[l-1] = sum % 10;
        sum /= 10;
        product = (short*)realloc(product , sizeof(short)*(++l));
        if ( j == col)
            break;
    }
    while (sum > 0)
    {
        product[l-1] = sum % 10;
        sum /= 10;
        product = (short*)realloc( product, sizeof(short)*(++l));
    }
    if (product[l-2] == 0)
        product = (short*)realloc( product, sizeof(short)*(--l));
    for ( i = l - 1; i > 0; i--)
        product[i] = product[i - 1];
    product[0] = l - 1;
    reverse(product);
    return product;
}

void temporary(short* x,short length,short y,short* tmp)
{
    short i, product = 0;
    for(i = length - 1; i >= 0; i--)
    {
        if (i != 0)
            product += x[i-1] * y;
        tmp[i] = product % 10;
        product /= 10;
    }
}

void display(short row, short col,short* temp)
{
    short i,j;
    printf("\n");
    for (i = 0; i < row; i++ )
    {
        for (j = 0; j < col; j++ )
            printf("%d  ",*(temp + i*col + j));
        printf("\n");
    }
}

void store(short* arr, unsigned long long a)
{
    short i;
    for ( i = 1; i <= arr[0]; i++, a /= 10)
    {
        arr[i] = a%10;
    }
    reverse(arr);
}

short* copy_array(short* a,short* b)
{
    short i;
    b = (short*)realloc(b ,sizeof(short)*( a[0] + 1));
    for (i = 0; i <= a[0]; i++)
        b[i] = a[i];
    return b;
}
void reverse(short* x)
{
    short len = x[0], i;
    for ( i = 1; i <= len / 2; i++)
    {
        x[i] += x[len - i + 1];
        x[len - i + 1] = x[i] - x[len - i + 1];
        x[i] = x[i] - x[len - i + 1];
    }
}

int digits(unsigned long long a)
{
    int count = 0;
    while((a/10==0)?((a%10==0)? 0 : 1) : 1)
    {
        count++;
        a /= 10;
    }
    return count;
}
