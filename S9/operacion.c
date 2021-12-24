#include <stdio.h>

int main() {
	int valor_x = 665857;
	int valor_y = 470832;
    {
		double x = valor_x;
		double y = valor_y;
		double z = (x*x*x*x) - 4*(y*y*y*y) - 4*(y*y);
		printf("Doble precisión: %lf\n", z);
    }
    {
		float x = valor_x;
		float y = valor_y;
		float z = (x*x*x*x) - 4*(y*y*y*y) - 4*(y*y);
		printf("Simple precisión: %f\n", z);
    }
    {
		long long x = valor_x;
		long long y = valor_y;
		long long z = (x*x*x*x) - 4*(y*y*y*y) - 4*(y*y);
		printf("Entero: %lld\n", z);
    }
}
