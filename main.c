/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 16:20:20 by amert             #+#    #+#             */
/*   Updated: 2025/04/06 16:20:21 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** Ana Program İşleyişi
** ------------------
** Bu dosya, programın giriş noktasını ve temel akışını içerir.
** 
** Öğrenme Noktaları:
** 1. Program Argümanları:
**    - argc: Argüman sayısı (program adı dahil)
**    - argv: Argüman dizisi (ilk eleman program adıdır)
**
** 2. MiniLibX Events (Olaylar):
**    - mlx_hook: Fare ve klavye olaylarını yakalamak için kullanılır
**    - 2: KeyPress olayı için event kodu
**    - 17: WindowClose olayı için event kodu
**    - 1L<<0: Maske biti (hangi olay tiplerini dinleyeceğimizi belirtir)
**
** 3. Event Loop:
**    - mlx_loop: Sonsuz döngü başlatır ve olayları dinler
**    - Program bu noktada asenkron çalışmaya başlar
*/
int main(int argc, char **argv)
{
    t_fractol f;  // Ana program yapısı

    /*
    ** Argüman Kontrolü ve Başlatma
    ** ---------------------------
    ** 1. parse_args: Komut satırı argümanlarını işler
    **    - Fraktal tipini belirler (Mandelbrot/Julia)
    **    - Julia seti için gerekli parametreleri alır
    **
    ** 2. init_fractol: Program yapılarını başlatır
    **    - MiniLibX penceresi oluşturur
    **    - Görüntü tamponunu ayarlar
    **    - Varsayılan değerleri atar
    */
    if (parse_args(argc, argv, &f) != 0)
    {
        print_usage();  // Kullanım bilgilerini göster
        return (1);
    }
    init_fractol(&f, argv[1]);

    /*
    ** İlk Render ve Olay Dinleyicileri
    ** -------------------------------
    ** 1. render_fractol: İlk fraktal görüntüsünü çizer
    **
    ** 2. Event Handlers:
    **    - handle_keypress: Klavye tuşları için (ESC, ok tuşları vb.)
    **    - handle_mouse: Fare olayları için (zoom, pan)
    **    - close_window: Pencere kapatma için
    */
    render_fractol(&f);
    mlx_hook(f.win, 2, 1L << 0, handle_keypress, &f);
    mlx_hook(f.win, 17, 0, close_window, &f);
    mlx_mouse_hook(f.win, handle_mouse, &f);
    
    /*
    ** Event Loop Başlatma
    ** -----------------
    ** Program bu noktadan sonra olay güdümlü çalışır
    ** - Kullanıcı girdilerini bekler
    ** - Gerektiğinde ekranı yeniler
    ** - Kapatma sinyali gelene kadar çalışır
    */
    mlx_loop(f.mlx);
    return (0);
}