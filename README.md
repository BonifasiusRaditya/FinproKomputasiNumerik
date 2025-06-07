# Laporan dan Implementasi Program: Metode Gauss-Legendre untuk Integral Tentu

## Deskripsi Singkat

Repositori ini berisi:
- **Laporan ilmiah** dalam format LaTeX (`laporan_latex/laporan.tex`) yang membahas penerapan metode Gauss-Legendre untuk menghitung integral tentu $\int_{-3}^{3} \frac{1}{1+x^2} dx$ secara numerik.
- **Program C (`main.c`)** yang mengimplementasikan metode Gauss-Legendre dengan titik dan bobot yang dihitung secara dinamis (iterasi 2-6).

---

## Isi Laporan

Laporan membahas:
- **Pendahuluan**: Pentingnya integrasi numerik dan keunggulan metode Gauss-Legendre.
- **Studi Literatur**: Perbandingan integrasi analitik dan numerik, serta penjelasan transformasi integral ke bentuk standar Gauss-Legendre.
- **Metode**: Transformasi integral, rumus umum Gauss-Legendre, dan cara menghitung galat relatif sejati.
- **Hasil Eksperimen**: Tabel dan grafik hasil aproksimasi integral untuk n = 2 hingga 6, serta analisis konvergensi galat.
- **Kesimpulan**: Efisiensi dan akurasi metode Gauss-Legendre dalam mengaproksimasi integral.
- **Referensi** dan **tautan ke GitHub/Youtube**.

---

## Program main.c

Program C pada repositori ini:
- Menghitung integral $\int_{-3}^{3} \frac{1}{1+x^2} dx$ dengan mengubahnya ke bentuk $\int_{-1}^{1} \frac{3}{1+9t^2} dt$.
- Menghitung titik dan bobot Gauss-Legendre secara dinamis untuk n = 2 hingga 6.
- Menampilkan hasil aproksimasi integral dan galat relatif sejati dalam format tabel.
- Kode mudah dimodifikasi untuk jumlah titik lain atau fungsi lain.

**Contoh Output Program:**
![picture 1](https://i.imgur.com/0qypuNt.png)  
