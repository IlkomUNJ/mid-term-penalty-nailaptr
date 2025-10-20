Metode dan Proses Analisis
1. Analisis Window (Milestone 1 & 2)
Program menggunakan pendekatan sliding window dengan beberapa ukuran jendela yang diuji:
    - 16×16
    - 32×32
    - 48×48
    - 64×64

Setiap jendela diperiksa menggunakan metode perhitungan intensitas piksel (grayscale) untuk mengetahui apakah jendela tersebut kosong (empty) atau berisi (non-empty).

Langkah-langkah utama:
    - Gambar dimuat ke dalam objek QImage.
    - Window digeser dari kiri ke kanan dan atas ke bawah sesuai ukuran yang diuji.
    - Untuk setiap jendela:
    - Hitung rata-rata intensitas piksel.
    - Jika intensitasnya melewati ambang batas tertentu, maka dianggap non-empty.
    - Jumlah jendela non-empty untuk setiap ukuran dicatat dan dibandingkan.

**Hasil Analisis**
Ukuran Window	Jumlah Non-Empty Window	Observasi
16×16	84	Terlalu kecil; banyak noise dan potongan tidak lengkap.
32×32	52	Cukup stabil; pola segment terlihat jelas tanpa kehilangan detail.
48×48	29	Mulai kehilangan area kecil; terlalu besar untuk detail halus.
64×64	17	Terlalu besar; hanya menangkap area dominan, detail hilang.

→ Window ukuran 32×32 dipilih sebagai ukuran ideal.

Alasan pemilihan:
- Ukuran 32×32 cukup besar untuk menangkap satu segmen penuh.
- Tidak terlalu kecil sehingga menghindari noise, dan tidak terlalu besar sehingga detail tetap terjaga.


