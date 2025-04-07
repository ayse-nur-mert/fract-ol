/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 16:20:17 by amert             #+#    #+#             */
/*   Updated: 2025/04/06 16:20:18 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <math.h>
# include <stdio.h>

/*
** Pencere ve görüntü ayarları
** --------------------------
** Bu sabitler, programın temel görüntüleme parametrelerini belirler.
** WINDOW_WIDTH ve HEIGHT: Pencerenin boyutlarını piksel cinsinden tanımlar
** MAX_ITERATIONS: Fraktal hesaplamalarında maksimum iterasyon sayısı
** - Daha yüksek değer = Daha detaylı görüntü ama daha yavaş işlem
*/
# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600
# define MAX_ITERATIONS 100

/*
** Fraktal Tipleri
** --------------
** enum kullanımı ile program içinde tip güvenliği sağlanır
** MANDELBROT ve JULIA: Desteklenen fraktal tipleri
** - Her fraktal farklı matematiksel formüller kullanır
*/
typedef enum e_fractal_type {
    MANDELBROT,
    JULIA
} t_fractal_type;

/*
** Karmaşık Sayı Yapısı
** ------------------
** Fraktal hesaplamalarında kullanılan karmaşık sayıları temsil eder
** real: Gerçek kısım
** imag: Sanal kısım
** - Mandelbrot ve Julia setleri karmaşık sayı düzleminde tanımlanır
*/
typedef struct s_complex {
    double real;
    double imag;
} t_complex;

/*
** Renk Yapısı
** ----------
** RGB renk değerlerini saklar
** - Fraktal görselleştirmesinde her piksel için renk değeri üretilir
** - Renk değerleri iterasyon sayısına göre hesaplanır
*/
typedef struct s_color {
    int r;
    int g;
    int b;
} t_color;

/*
** Görüntü Yapısı
** -------------
** MiniLibX kütüphanesi ile görüntü oluşturma ve işleme için gerekli bilgileri içerir
** - img: Görüntü pointer'ı
** - addr: Piksel verilerine direkt erişim için adres
** - bits_per_pixel: Her pikselin kaç bit ile temsil edildiği
** - line_length: Bir satırın bayt cinsinden uzunluğu
** - endian: Byte sıralaması (little/big endian)
*/
typedef struct s_img {
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
} t_img;

/*
** Ana Fraktal Yapısı
** ----------------
** Fraktal çizimi için gerekli tüm parametreleri içerir
** - mlx, win: MiniLibX pencere yönetimi için pointerlar
** - img: Görüntü verisi
** - type: Fraktal tipi (Mandelbrot/Julia)
** - julia_c: Julia seti için sabit karmaşık sayı
** - zoom: Yakınlaştırma seviyesi
** - move_x/y: Görüntü kaydırma değerleri
** - max_iter: Maksimum iterasyon sayısı
** - color: Renk ayarları
*/
typedef struct s_fractol {
    void            *mlx;
    void            *win;
    t_img           img;
    t_fractal_type  type;
    t_complex       julia_c;
    double          zoom;
    double          move_x;
    double          move_y;
    int             max_iter;
    t_color         color;
} t_fractol;

/*
** Temel Fonksiyonlar
** ----------------
*/
// Program başlatma ve yapılandırma
void    init_fractol(t_fractol *f, char *title);
int     render_fractol(t_fractol *f);
void    calculate_pixel(t_fractol *f, int x, int y);

// Olay işleyicileri (Event handlers)
int     handle_keypress(int keycode, t_fractol *f);
int     handle_mouse(int button, int x, int y, t_fractol *f);
int     close_window(t_fractol *f);

// Fraktal hesaplamaları
int     mandelbrot_iteration(t_complex c, int max_iter);
int     julia_iteration(t_complex z, t_complex c, int max_iter);

// Yardımcı fonksiyonlar
void    put_pixel(t_fractol *f, int x, int y, int color);
int     create_color(int iterations, t_fractol *f);
int     parse_args(int argc, char **argv, t_fractol *f);
void    print_usage(void);
double  map(double value, double from[2], double to[2]);

#endif