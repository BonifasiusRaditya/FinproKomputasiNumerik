# Metode Gauss-Legendre untuk Integral Tentu Numerik

Nama: Bonifasius Raditya Pandu Hendrianto
NPM: 2306242350

## Deskripsi Singkat

Repositori ini berisi:
- **Laporan ilmiah** dalam format LaTeX (`laporan_latex/laporan.tex`) yang membahas penerapan metode Gauss-Legendre untuk menghitung integral tentu $\int_{-3}^{3} \frac{1}{1+x^2} dx$ secara numerik.
- **Program C (`main.c`)** yang mengimplementasikan metode Gauss-Legendre dengan titik dan bobot yang dihitung secara dinamis (iterasi 2-6).

---

## Program main.c

Program C pada repositori ini:
- Menghitung integral $\int_{-3}^{3} \frac{1}{1+x^2} dx$ dengan mengubahnya ke bentuk $\int_{-1}^{1} \frac{3}{1+9t^2} dt$.
- Menghitung titik dan bobot Gauss-Legendre secara dinamis untuk n = 2 hingga 6.
- Menghitung galat relatif tiap nilai n nya untuk memastikan validasi data
- Menampilkan hasil aproksimasi integral dan galat relatif sejati dalam format tabel.

**Contoh Output Program:**
![picture 1](https://i.imgur.com/0qypuNt.png)  
