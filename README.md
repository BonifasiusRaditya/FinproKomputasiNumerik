# Pembuktian Bisection Method dalam Perhitungan Ketinggian Awal Air pada Tangki

**Nama:** Bonifasius Raditya Pandu Hendrianto  
**NPM:** 23062423450

## Deskripsi

Program ini menggunakan metode **Bisection** untuk mencari akar dari fungsi kecepatan aliran air berdasarkan rumus Bernoulli. Program membuktikan rumus tersebut dan melakukan validasi hasil. Output utama dari program adalah nilai ketinggian air awal pada tangki ($H_0$) agar kecepatan aliran air ($v$) mencapai target $v_{target} = 4$ m/s.

## Fitur Program

- Menghitung akar fungsi kecepatan aliran air dengan metode Bisection.
- Membuktikan hasil dengan rumus Bernoulli.
- Validasi hasil numerik dengan perhitungan analitik.
- Menampilkan tabel iterasi bisection dan galat relatif.

## Cara Kerja Singkat

1. **Input Parameter:**  
   - Gravitasi ($g$)
   - Panjang saluran ($L$)
   - Waktu ($t$)
   - Interval awal $[x_l, x_u]$
   - Target kecepatan $v_{target}$

2. **Proses Bisection:**  
   Fungsi yang dicari akarnya:  
   $$ f(H) = \sqrt{2gH} \tanh\left(\frac{\sqrt{2gH}}{2L} t\right) - v_{target} $$

3. **Output:**  
   - Tabel iterasi bisection method
   - Nilai kecepetan aliran air dengan nilai H dari bisection method
   - Validasi hasil dengan rumus Bernoulli

## Contoh Output
![picture 0](https://i.imgur.com/x0HLPLz.png)  