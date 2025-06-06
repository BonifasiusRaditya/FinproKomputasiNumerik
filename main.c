#include <stdio.h>
#include <math.h> 

#define EARTH_GRAVITY 9.81

double calculate_velocity(double g, double H, double L, double t) {
    // Perhitungan kecepatan aliran air berdasarkan rumus water flow
    double tanh_argument =  sqrt(2.0 * g * H) / (2.0 * L) * t; 
    return sqrt(2.0 * g * H) * tanh(tanh_argument);
}

void bisection_method(double xl, double xu, double es, double v_target, double L, double t, int max_iter, double * h_init) {
    double xr = xl; // Inisialisasi awal untuk perhitungan galat
    double xr_lama;
    double ea = 100.0; // Inisialisasi galat dengan nilai besar
    
    // Fungsi f(H) yang ingin dicari akarnya: f(H) = calculate_velocity(H) - v_target
    double f_xl_check = calculate_velocity(EARTH_GRAVITY, xl, L, t) - v_target;
    double f_xu_check = calculate_velocity(EARTH_GRAVITY, xu, L, t) - v_target;

    // Pastikan akar berada di dalam interval awal
    if (f_xl_check * f_xu_check >= 0) {
        printf("Error: Akar tidak berada dalam interval awal [%.2f, %.2f].\n", xl, xu);
        return;
    }

    for (int i = 0; i < max_iter; i++) {
        xr_lama = xr;
        xr = (xl + xu) / 2.0;
        
        if (xr != 0) ea = fabs((xr - xr_lama) / xr) * 100.0;

        double f_xr = calculate_velocity(EARTH_GRAVITY, xr, L, t) - v_target;
        
        // Menampilkan 0.00 untuk galat pada iterasi pertama agar lebih rapi
        printf("| %-7d | %10.4f | %10.4f | %10f | %12.4f | %9.4f |\n", i + 1, xl, xu, xr, f_xr, (i == 0) ? 0.0 : ea);

        // Cek kondisi berhenti (setelah iterasi pertama)
        if (ea < es && i > 0 || i > max_iter) break;
        
        // Perbarui interval
        double f_xl = calculate_velocity(EARTH_GRAVITY, xl, L, t) - v_target;
        if (f_xl * f_xr < 0) xu = xr;
        else xl = xr;
    }
    *h_init = xr;
}

int main() {
    double L_const = 5.0, t_const = 3.0, h_init; 

    // Bagian 1: Pencarian Akar dengan Bisection Method
    printf("\n\n--- Bagian 1: Pencarian Akar dengan Bisection Method ---\n");

    // Parameter untuk pencarian akar
    double v_target = 4, xl_init = 0.0, xu_init = 2.0, es_target = 1.0;
    int max_iterations = 50;    

    printf("+---------+------------+------------+------------+--------------+-----------+\n");
    printf("| Iterasi |     xl     |     xu     |     xr     |    f(xr)     |  ea (%%)   |\n");
    printf("+---------+------------+------------+------------+--------------+-----------+\n");
    bisection_method(xl_init, xu_init, es_target, v_target, L_const, t_const, max_iterations, &h_init);
    printf("+---------+------------+------------+------------+--------------+-----------+\n");


    // Bagian 2: Pembuktian Rumus Bernoulli
    printf("\n\n--- Bagian 2: Pembuktian Rumus Bernoulli ---\n");
    printf("=============================================================\n");
    printf("                   Perhitungan Rumus Bernouli                \n");
    printf("=============================================================\n");
    printf("Parameter yang digunakan:\n");
    printf(" - Gaya Gravitasi (g) = %.2f m/s^2\n", EARTH_GRAVITY);
    printf(" - Panjang Saluran (L) = %.2f m\n", L_const);
    printf(" - Waktu (t) = %.2f s\n", t_const);
    printf(" - Tinggi Air Awal = %f m\n", h_init);
    printf("=============================================================\n");
    printf("v = sqrt(2 * g * H) * tanh(sqrt(2 * g * H) / (2 * L) * t)\n");
    printf("v = sqrt(2 * %.2f * %.4f) * tanh(sqrt(2 * %.2f * %.4f) / (2 * %.2f) * %.2f)\n", EARTH_GRAVITY, h_init, EARTH_GRAVITY, h_init, L_const, t_const);
    printf("v = %f m/s\n", calculate_velocity(EARTH_GRAVITY, h_init, L_const, t_const));
    

    // Bagian 3: Validasi Hasil
    printf("\n\n--- Bagian 3: Validasi Hasil ---\n");
    printf("Bisection Method: h = %f m/s\n", h_init);
    printf("Hasil Kecepatan Aliran Air: \n");
    printf("v = %f m/s\n", calculate_velocity(EARTH_GRAVITY, h_init, L_const, t_const));
    printf("v_target = %.4f m/s\n", v_target);

    printf("Error: %.4f %%\n", fabs((calculate_velocity(EARTH_GRAVITY, h_init, L_const, t_const))-v_target)/v_target*100);
    return 0; 
}