#include <stdio.h>
#include <math.h> 

#define EARTH_GRAVITY 9.81

double calculate_velocity(double g, double H, double L, double t) {
    // Perhitungan kecepatan aliran air berdasarkan rumus water flow
    double tanh_argument =  sqrt(2.0 * g * H) / (2.0 * L) * t; 
    return sqrt(2.0 * g * H) * tanh(tanh_argument);
}

void bisection_method(double xl, double xu, double es, double v_target, double L, double t, int max_iter) {
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
        printf("| %-7d | %10.6f | %10.6f | %10.6f | %12.6f | %9.2f |\n", i + 1, xl, xu, xr, f_xr, (i == 0) ? 0.0 : ea);

        // Cek kondisi berhenti (setelah iterasi pertama)
        if (ea < es && i > 0 || i > max_iter) break;
        
        // Perbarui interval
        double f_xl = calculate_velocity(EARTH_GRAVITY, xl, L, t) - v_target;
        if (f_xl * f_xr < 0) xu = xr;
        else xl = xr;
    }   
}


int main() {
    // Bagian 1: Simulasi untuk berbagai nilai H
    double L_const = 5.0, t_const = 3.0, H, v, H_initial_double, interval_double; 
    int num_tests, H_initial_int, interval_int;

    printf("Masukkan Jumlah Data, Interval Data, H Awal (contoh: 10 2 1): ");
    scanf("%d %d %d", &num_tests, &interval_int, &H_initial_int);

    H_initial_double = H_initial_int;
    interval_double = interval_int;
    
    
    printf("--- Bagian 1: Simulasi Kecepatan ---\n");
    printf("\n=============================================================\n");
    printf("           PROGRAM SIMULASI KECEPATAN ALIRAN AIR\n");
    printf("=============================================================\n");
    printf("Parameter yang digunakan:\n");
    printf(" - Gaya Gravitasi (g) = %.2f m/s^2\n", EARTH_GRAVITY);
    printf(" - Panjang Saluran (L) = %.2f m\n", L_const);
    printf(" - Waktu (t) = %.2f s\n", t_const);
    printf(" - Tinggi Air Awal (H0) dimulai dari %.2f m dengan interval %.2f m\n", H_initial_double, interval_double);
    printf("=============================================================\n\n");

    printf("+------------+-----------+-----------+-----------+-------------------+\n");
    printf("| Uji Coba   |  H (m)    |  L (m)    |  t (s)    |  Kecepatan (m/s)  |\n");
    printf("+------------+-----------+-----------+-----------+-------------------+\n");
    for (int i = 0; i < num_tests; i++) {
        H = H_initial_double + (i * interval_double);
        v = calculate_velocity(EARTH_GRAVITY, H, L_const, t_const);
        printf("| %-10d | %9.2f | %9.2f | %9.2f | %17.6f |\n", i + 1, H, L_const, t_const, v);
    }
    printf("+------------+-----------+-----------+-----------+-------------------+\n");
    
// ===============================================================================================

    // Bagian 2: Pencarian Akar dengan Bisection Method
    printf("\n\n--- Bagian 2: Pencarian Akar dengan Bisection Method ---\n");
    
    // Parameter untuk pencarian akar
    double v_target = 4.0, xl_init = 0.0, xu_init = 2.0, es_target = 1.0;
    int max_iterations = 50;
    
    printf("+---------+------------+------------+------------+--------------+-----------+\n");
    printf("| Iterasi |     xl     |     xu     |     xr     |    f(xr)     |  ea (%%)   |\n");
    printf("+---------+------------+------------+------------+--------------+-----------+\n");
    bisection_method(xl_init, xu_init, es_target, v_target, L_const, t_const, max_iterations);
    printf("+---------+------------+------------+------------+--------------+-----------+\n");
    
    printf("\nSemua %d uji coba simulasi telah selesai.\n", num_tests);
    return 0; 
}