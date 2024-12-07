#include <stdio.h>
#include <math.h>
#include <gnuplot_i.h>

// Função para calcular a derivada
double derivada(double (*f)(double), double x) {
    double h = 1e-5;
    return (f(x + h) - f(x)) / h;
}

// Função para calcular a integral
double integral(double (*f)(double), double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += f(a + i * h) * h;
    }
    return sum;
}

// Função para calcular o limite
double limite(double (*f)(double), double x) {
    return f(x);
}

// Função exemplo
double funcao(double x) {
    return x * x;  // Exemplo de função: x^2
}

int main() {
    double x0, a, b;
    int n;
    printf("Digite o ponto para o limite e derivada: ");
    scanf("%lf", &x0);
    printf("Digite o intervalo para a integral (a b): ");
    scanf("%lf %lf", &a, &b);
    printf("Digite o número de subintervalos para a integral: ");
    scanf("%d", &n);

    printf("Derivada em x = %lf: %lf\n", x0, derivada(funcao, x0));
    printf("Integral de %lf a %lf: %lf\n", a, b, integral(funcao, a, b, n));
    printf("Limite em x = %lf: %lf\n", x0, limite(funcao, x0));

    // Gerar gráfico com Gnuplot
    gnuplot_ctrl *h = gnuplot_init();
    gnuplot_setstyle(h, "lines");
    gnuplot_cmd(h, "set xrange [%lf:%lf]", a, b);
    gnuplot_cmd(h, "set title 'Grafico da Funcao'");
    gnuplot_cmd(h, "plot '-' using 1:2 with lines title 'f(x)'");

    for (double x = a; x <= b; x += 0.01) {
        gnuplot_cmd(h, "%lf %lf", x, funcao(x));
    }
    gnuplot_cmd(h, "e");
    gnuplot_close(h);

    return 0;
}
