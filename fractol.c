/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 16:20:22 by amert             #+#    #+#             */
/*   Updated: 2025/04/06 16:20:23 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** Fraktal Başlatma
** --------------
** MiniLibX ve fraktal parametrelerinin başlatılması
** Öğrenme Noktaları:
** - MiniLibX görüntü yönetimi
** - Bellek yönetimi ve yapı başlatma
** - Varsayılan değerlerin atanması
*/
void init_fractol(t_fractol *f, char *title)
{
    /*
    ** MiniLibX Başlatma Aşamaları:
    ** 1. mlx_init: Grafik sistemini başlatır
    ** 2. mlx_new_window: Görüntüleme penceresi oluşturur
    ** 3. mlx_new_image: Çizim için görüntü tamponu oluşturur
    ** 4. mlx_get_data_addr: Görüntü verilerine direkt erişim sağlar
    */
    f->mlx = mlx_init();
    f->win = mlx_new_window(f->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, title);
    f->img.img = mlx_new_image(f->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    f->img.addr = mlx_get_data_addr(f->img.img, &f->img.bits_per_pixel,
                                   &f->img.line_length, &f->img.endian);
    
    /*
    ** Fraktal Parametreleri:
    ** - zoom: Görüntü yakınlaştırma seviyesi
    ** - move_x/y: Görüntü kaydırma koordinatları
    ** - max_iter: Detay seviyesi
    */
    f->zoom = 1.0;
    f->move_x = 0.0;
    f->move_y = 0.0;
    f->max_iter = MAX_ITERATIONS;
}

/*
** Mandelbrot İterasyonu
** -------------------
** Mandelbrot setinin matematiksel hesaplaması
** Formula: z = z² + c
** Öğrenme Noktaları:
** - Karmaşık sayı aritmetiği
** - İteratif hesaplama
** - Kaçış zamanı algoritması
*/
int mandelbrot_iteration(t_complex c, int max_iter)
{
    t_complex z;
    int i;
    double temp;

    /*
    ** Mandelbrot Seti Algoritması:
    ** 1. z = 0 ile başla
    ** 2. z = z² + c işlemini tekrarla
    ** 3. |z| > 2 olduğunda veya max_iter'a ulaşıldığında dur
    ** 4. Döngüden çıkış anındaki iterasyon sayısını döndür
    */
    z.real = 0;
    z.imag = 0;
    i = 0;
    while (i < max_iter)
    {
        temp = z.real * z.real - z.imag * z.imag + c.real;
        z.imag = 2 * z.real * z.imag + c.imag;
        z.real = temp;
        if (z.real * z.real + z.imag * z.imag > 4)
            return (i);
        i++;
    }
    return (max_iter);
}

/*
** Julia İterasyonu
** --------------
** Julia setinin matematiksel hesaplaması
** Formula: z = z² + c (c sabit)
** Öğrenme Noktaları:
** - Mandelbrot'tan farkı başlangıç değerlerinde
** - Parametre olarak gelen z noktası
*/
int julia_iteration(t_complex z, t_complex c, int max_iter)
{
    int i;
    double temp;

    i = 0;
    while (i < max_iter)
    {
        temp = z.real * z.real - z.imag * z.imag + c.real;
        z.imag = 2 * z.real * z.imag + c.imag;
        z.real = temp;
        if (z.real * z.real + z.imag * z.imag > 4)
            return (i);
        i++;
    }
    return (max_iter);
}

/*
** Piksel Hesaplama
** --------------
** Her piksel için fraktal değerinin hesaplanması
** Öğrenme Noktaları:
** - Ekran koordinatlarından matematik koordinatlarına dönüşüm
** - Zoom ve pan etkilerinin uygulanması
*/
void calculate_pixel(t_fractol *f, int x, int y)
{
    t_complex c;
    double x_scaled;
    double y_scaled;
    int iterations;

    /*
    ** Koordinat Dönüşümü:
    ** 1. Piksel koordinatlarını [-2, 2] aralığına ölçekle
    ** 2. Zoom faktörünü uygula
    ** 3. Kaydırma değerlerini ekle
    */
    x_scaled = (x - WINDOW_WIDTH / 2.0) / (0.5 * WINDOW_WIDTH * f->zoom) + f->move_x;
    y_scaled = (y - WINDOW_HEIGHT / 2.0) / (0.5 * WINDOW_HEIGHT * f->zoom) + f->move_y;

    if (f->type == MANDELBROT)
    {
        c.real = x_scaled;
        c.imag = y_scaled;
        iterations = mandelbrot_iteration(c, f->max_iter);
    }
    else // JULIA
    {
        c = f->julia_c;
        t_complex z = {x_scaled, y_scaled};
        iterations = julia_iteration(z, c, f->max_iter);
    }
    put_pixel(f, x, y, create_color(iterations, f));
}

/*
** Fraktal Çizimi
** ------------
** Tüm görüntünün oluşturulması
** Öğrenme Noktaları:
** - İç içe döngülerle piksel tarama
** - MiniLibX görüntü yönetimi
*/
int render_fractol(t_fractol *f)
{
    int x;
    int y;

    /*
    ** Piksel Tarama:
    ** 1. Her satır ve sütunu döngüyle tara
    ** 2. Her piksel için fraktal değerini hesapla
    ** 3. Hesaplanan değere göre renk ata
    ** 4. Görüntüyü pencereye aktar
    */
    y = 0;
    while (y < WINDOW_HEIGHT)
    {
        x = 0;
        while (x < WINDOW_WIDTH)
        {
            calculate_pixel(f, x, y);
            x++;
        }
        y++;
    }
    mlx_put_image_to_window(f->mlx, f->win, f->img.img, 0, 0);
    return (0);
}