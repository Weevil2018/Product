#include <stdio.h>
#include <stdlib.h>
#include <string.h>

short* multiply(short*,short*);
void temporary(short*,short,short,short*);
void display(short, short, short*);
int digits(unsigned long long);
void store (short* , char*);
void reverse(short*);
int sum_digits(short*);
short* copy_array(short*,short*);

int main()
{
    short i = 0;
    char a[] = "6668014432879854274079851790721257797144758322315908160396257811764037237817632071521432200871554290742929910593433240445888801654119365080363356052330830046095157579514014558463078285911814024728965016135886601981690748037476461291163877376";
    char b[] = "1606938044258990275541962092341162602522202993782792835301376";
    short *num1 = (short*)malloc(sizeof(short) * (strlen(a) + 1) );
    short *num2 = (short*)malloc(sizeof(short) * (strlen(b) + 1) );
    short* result;
    num1[0] = strlen(a);
    num2[0] = strlen(b);
    store(num1,a);
    store(num2,b);
    result = multiply(num1,num2);
    printf("\n");
    for (i = 0; i <= result[0]; i++)
        printf("%d", result[i]);
    printf("\n\nSum = %d\n",sum_digits(result));
    return 0;
}

int sum_digits(short* ptr)
{
    int i, sum = 0;
    for (i = 1; i <= ptr[0]; i++)
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
    free(temp);
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

void store(short* arr, char* a)
{
    short i;
    for ( i = 1; i <= arr[0]; i++)
        arr[i] = a[i - 1] - 48;
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
