/*
    * Program ini menghitung integral dari fungsi g(t) = 3 / (1 + 9t^2)
    * menggunakan metode Gauss-Legendre dengan titik dan bobot yang dihitung secara dinamis.
    * Program ini juga menampilkan galat relatif sejati terhadap nilai integral yang diketahui.
    
    * Nama: Bonifasius Raditya Pandu Hendrianto
    * NPM: 2306242350
 
    * Deskripsi Program:
    * Program ini mengimplementasikan metode Gauss-Legendre untuk menghitung integral numerik
    * dari fungsi g(t) = 3 / (1 + 9t^2). Titik dan bobot untuk integrasi dihitung secara dinamis
    * menggunakan polinomial Legendre. Program ini juga menghitung galat relatif sejati
    * terhadap nilai integral yang diketahui, yaitu 2 * arctan(3). Hasilnya ditampilkan dalam
    * format tabel yang mencakup jumlah titik (n), nilai aproksimasi integral, dan galat relatif sejati.
    
    * ver 2.0
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h> // Diperlukan untuk malloc dan free

// Toleransi untuk metode pencarian akar Newton-Raphson
#define TOLERANCE 1e-15
#define MAX_ITERATIONS 100
#define M_PI 3.14159265358979323846



// --- Bagian 1: Fungsi-fungsi Polinomial Legendre ---
double legendre_poly(int n, double t) {
    if (n == 0) return 1.0;
    if (n == 1) return t;

    double p_n_minus_2 = 1.0; // P_0(t)
    double p_n_minus_1 = t;   // P_1(t)
    double p_n = 0;

    for (int i = 1; i < n; i++) {
        p_n = ((2.0 * i + 1.0) * t * p_n_minus_1 - i * p_n_minus_2) / (i + 1.0);
        p_n_minus_2 = p_n_minus_1;
        p_n_minus_1 = p_n;
    }
    return p_n;
}

double legendre_derivative(int n, double t) {
    if (fabs(t*t - 1.0) < TOLERANCE) {
        // Hindari pembagian dengan nol di titik ujung
        return (t > 0) ? (n * (n + 1.0) / 2.0) : (-n * (n + 1.0) / 2.0);
    }
    return n * (t * legendre_poly(n, t) - legendre_poly(n - 1, t)) / (t * t - 1.0);
}


// --- Bagian 2: Fungsi Pencarian Akar dan Perhitungan Bobot ---
double find_root(int n, double initial_guess) {
    double t = initial_guess;
    int iter = 0;
    while (iter < MAX_ITERATIONS) {
        double delta_t = -legendre_poly(n, t) / legendre_derivative(n, t);
        t += delta_t;
        if (fabs(delta_t) < TOLERANCE) {
            return t;
        }
        iter++;
    }
    return t; // Kembalikan nilai terbaik jika tidak konvergen
}

void points_weight(int n, double* points, double* weights) {
    for (int i = 0; i < n; i++) {
        // Tebakan awal untuk akar (cukup akurat untuk konvergensi)
        double initial_guess = cos(M_PI * (i + 0.75) / (n + 0.5));
        
        // 1. Cari titik (akar)
        points[i] = find_root(n, initial_guess);
        
        // 2. Hitung turunan di titik tersebut
        double p_prime = legendre_derivative(n, points[i]);
        
        // 3. Hitung bobot menggunakan formula
        weights[i] = 2.0 / ((1.0 - points[i] * points[i]) * p_prime * p_prime);
    }
}


// --- Bagian 3: Fungsi Integrasi dan Main Program ---
double g(double t) {
    return 3.0 / (1.0 + 9.0 * t * t);
}

// Fungsi yang menjalankan seluruh proses untuk n-titik
void gauss_legendre(int n, double true_value, double * approximation) {
    // Alokasi memori dinamis untuk menyimpan titik dan bobot
    double* points = (double*)malloc(n * sizeof(double));
    double* weights = (double*)malloc(n * sizeof(double));

    if (points == NULL || weights == NULL) {
        printf("Gagal mengalokasikan memori!\n");
        return;
    }

    // Hitung titik dan bobot secara dinamis
    points_weight(n, points, weights);

    // Lakukan integrasi numerik
    double integral_approximation = 0.0;
    for (int i = 0; i < n; i++) {
        integral_approximation += weights[i] * g(points[i]);
    }
    
    // Hitung galat relatif sejati
    double error = fabs((true_value - integral_approximation) / true_value) * 100.0;
    
    // Tampilkan hasil dalam format tabel
    printf("| %-18d | %-35.15f | %-25.10f |\n", n, integral_approximation, error);
    *approximation = integral_approximation;

    // Bebaskan memori yang sudah dialokasikan
    free(points);
    free(weights);
}

int main() {
    double TRUE_VALUE = 2.0 * atan(3.0), approximation;

    printf("Tabel Gauss Legendre 2-titik hingga 6-titik\n");
    printf("----------------------------------------------------------------------------------------\n");
    printf("| %-18s | %-35s | %-25s |\n", "Jumlah Titik (n)", "Nilai Aproksimasi Integral", "Galat Relatif Sejati (%)");
    printf("----------------------------------------------------------------------------------------\n");

    for (int n = 2; n <= 6; n++) {
        gauss_legendre(n, TRUE_VALUE, &approximation);
    }

    printf("----------------------------------------------------------------------------------------\n");
    printf("Nilai Target = %.6f\n", TRUE_VALUE);
    printf("Nilai Akprosimasi Integral ke-6 = %.15f\n", approximation);
    printf("Galat Relatif = %.6f%%\n\n", fabs((TRUE_VALUE - approximation) / TRUE_VALUE) * 100.0);

    return 0;
}