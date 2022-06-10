#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

double Sigmoid(double a)
{
    double b;

    b = 1 / (1 + exp(-a));
    return b;
}

double Uniform(void)
{
    return ((double)rand() + 1.0) / ((double)RAND_MAX + 2.0);
}

double rand_normal(double mu, double sigma)
{
    double z = sqrt(-2.0 * log(Uniform())) * sin(2.0 * M_PI * Uniform());
    return mu + sigma * z;
}

int main()
{
    srand((unsigned)time(NULL));

    double mu = 0.7;
    int k, j, i;
    double S[2][3] = {
        {0, 0, 0},
        {0, 0, 0}};
    for (j = 0; j < 2; j++)
    {
        for (k = 0; k < 3; k++)
        {
            S[j][k] = rand_normal(0, 1);
        }
    }
    double dS[2][3] = {
        {0, 0, 0},
        {0, 0, 0}};
    double x[3] = {1, 0, 1};
    int xt[4][3] = {{1, 0, 0}, {1, 0, 1}, {1, 1, 0}, {1, 1, 1}};
    double u[3] = {1, 0, 0};
    double W[3] = {0, 0, 0};
    for (j = 0; j < 2; j++)
    {
        W[j] = rand_normal(0, 1);
    }
    double dW[3] = {0, 0, 0};
    double rs[2] = {0, 0};
    double r, E;
    double z = 0;
    int y = 1;
    int yt[4] = {0, 1, 1, 0};

    int count = 0;
    int index = 0;
    {
        
        for (j = 1; j < 3; j++)
        {
            index = count % 4 ;
            u[j] = xt[index][0] * S[j][0] + xt[index][1] * S[j][1] + xt[index][2] * S[j][2];
            u[j] = Sigmoid(u[j]);
        }

        for (j = 0; j < 3; j++)
        {
            z += u[j] * W[j];
        }

        z = Sigmoid(z);

        printf("z = %f\n", z);

        E = pow((z - yt[index]), 2) / 2;

        printf("Error %f\n", E);

        r = (yt[index] - z) * z * (1 - z);

        for (j = 0; j < 3; j++)
        {
            dW[j] = mu * r * u[j];
        }

        for (j = 1; j < 3; j++)
        {
            rs[j] = r * W[j] * u[j] * (1 - u[j]);
        }

        for (j = 1; j < 3; j++)
        {
            for (k = 0; k < 3; k++)
            {
                dS[j][k] = mu * rs[j] * x[k];
            }
        }

        for (j = 1; j < 3; j++)
        {
            for (k = 0; k < 3; k++)
            {
                S[j][k] = S[j][k] + dS[j][k];
            }
        }

        for (j = 0; j < 3; j++)
        {
            W[j] = W[j] + dW[j];
        }
        count++;
    }

    

    printf("\n");
    for (i = 0; i < 4; i++)
    {
        
        for (j = 1; j < 3; j++)
        {
            u[j] = xt[i][0] * S[j][0] + xt[i][1] * S[j][1] + xt[i][2] * S[j][2];
            u[j] = Sigmoid(u[j]);
        }

        for (j = 0; j < 3; j++)
        {
            z += u[j] * W[j];
        }

        z = Sigmoid(z);

        printf("z = %f\n", z);

        E = pow((z - yt[i]), 2) / 2;

        printf("Error %f\n", E);
    }
}