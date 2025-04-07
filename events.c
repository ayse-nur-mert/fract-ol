/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 16:20:25 by amert             #+#    #+#             */
/*   Updated: 2025/04/06 16:20:26 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** Klavye Olayları İşleyicisi
** ------------------------
** Klavye tuşlarına basıldığında çağrılır
** Öğrenme Noktaları:
** - X11 key event sistemini anlama
** - Event-driven programlama
** - Program kontrolü
*/
int handle_keypress(int keycode, t_fractol *f)
{
    /*
    ** Tuş Kontrolleri:
    ** ESC (65307) - Programı sonlandır
    ** Ok tuşları (65361-65364) - Görüntüyü kaydır
    ** +/- tuşları (65451/65453) - İterasyon sayısını değiştir
    */
    if (keycode == 65307) // ESC
        close_window(f);
    else if (keycode == 65361) // Sol ok
        f->move_x -= 0.1 / f->zoom;
    else if (keycode == 65363) // Sağ ok
        f->move_x += 0.1 / f->zoom;
    else if (keycode == 65362) // Yukarı ok
        f->move_y -= 0.1 / f->zoom;
    else if (keycode == 65364) // Aşağı ok
        f->move_y += 0.1 / f->zoom;
    else if (keycode == 65451) // Numpad +
        f->max_iter += 10;
    else if (keycode == 65453) // Numpad -
        f->max_iter = f->max_iter > 10 ? f->max_iter - 10 : f->max_iter;
    
    // Her tuş işleminden sonra görüntüyü yenile
    render_fractol(f);
    return (0);
}

/*
** Fare Olayları İşleyicisi
** ----------------------
** Fare tuşları ve tekerlek hareketlerini işler
** Öğrenme Noktaları:
** - Fare koordinatları ve düğme kodları
** - Zoom hesaplama matematiği
** - Smooth zooming tekniği
*/
int handle_mouse(int button, int x, int y, t_fractol *f)
{
    double zoom_factor;
    double x_before;
    double y_before;

    /*
    ** Fare Tekerleği İşleme:
    ** 1. Tıklama noktasının mevcut koordinatlarını kaydet
    ** 2. Zoom faktörünü uygula
    ** 3. Tıklama noktasının yeni koordinatlarını hesapla
    ** 4. Görüntüyü tıklama noktası etrafında yakınlaştır/uzaklaştır
    */
    if (button == 4 || button == 5) // Tekerlek yukarı/aşağı
    {
        // Zoom öncesi koordinatları hesapla
        x_before = (x - WINDOW_WIDTH / 2.0) / (0.5 * WINDOW_WIDTH * f->zoom) + f->move_x;
        y_before = (y - WINDOW_HEIGHT / 2.0) / (0.5 * WINDOW_HEIGHT * f->zoom) + f->move_y;
        
        // Zoom faktörünü uygula
        zoom_factor = (button == 4) ? 1.2 : 0.8;
        f->zoom *= zoom_factor;
        
        // Yeni koordinatları hesapla ve kaydırma değerlerini güncelle
        f->move_x = x_before - (x - WINDOW_WIDTH / 2.0) / (0.5 * WINDOW_WIDTH * f->zoom);
        f->move_y = y_before - (y - WINDOW_HEIGHT / 2.0) / (0.5 * WINDOW_HEIGHT * f->zoom);
        
        render_fractol(f);
    }
    return (0);
}

/*
** Pencere Kapatma İşleyicisi
** ------------------------
** Program sonlandırma ve temizlik işlemleri
** Öğrenme Noktaları:
** - MiniLibX kaynak temizleme
** - Bellek sızıntılarını önleme
*/
int close_window(t_fractol *f)
{
    /*
    ** Temizlik İşlemleri:
    ** 1. Görüntü tamponunu temizle
    ** 2. Pencereyi kapat
    ** 3. Programı sonlandır
    */
    mlx_destroy_image(f->mlx, f->img.img);
    mlx_destroy_window(f->mlx, f->win);
    exit(0);
    return (0);
}