#include <sil/sil.hpp>
#include "random.hpp"
#include <cmath>

// ⭐ Ne garder que le vert
void keep_green_only(sil::Image& image){

    for (int x{0}; x < image.width(); x++){
        for (int y{0}; y < image.height(); y++){
            image.pixel(x, y).r = 0.f;
            image.pixel(x, y).b = 0.f;
        }
    }
}

// ⭐ Échanger les canaux
void swap_red_and_blue_channels(sil::Image& image){
    for (int x{0}; x < image.width(); x++){
        for (int y{0}; y < image.height(); y++){
            std::swap(image.pixel(x, y).r, image.pixel(x, y).b);
        }
    }
}

// ⭐ Noir & Blanc
void black_and_white(sil::Image& image){
    for (glm::vec3& color : image.pixels()){
        float grayscale = 0.3 * color.r + 0.59 * color.g + 0.11 * color.b;
        color.r = grayscale;
        color.b = grayscale;
        color.g = grayscale;
    }
}

// ⭐ Négatif
void negatif(sil::Image& image){
    for (glm::vec3& color : image.pixels()){
        color.r = 1 - color.r;
        color.g = 1 - color.g;
        color.b = 1 - color.b;
    }
}

// ⭐ Dégradé
void gradiant(sil::Image& image){
    for (int x{0}; x < image.width(); x++){
        float black_value = float(x) / (image.width() - 1);

        for (int y{0}; y < image.height(); y++){
            image.pixel(x, y).r = black_value;
            image.pixel(x, y).g = black_value;
            image.pixel(x, y).b = black_value;
        }
    }
}

// ⭐⭐ Miroir
void mirror(sil::Image& image){
    sil::Image copy_image = image;

    for (int x{0}; x < image.width() - 1; x++){
         for (int y{0}; y < image.height(); y++){
            image.pixel(x, y).r = copy_image.pixel(image.width() - (x + 1), y).r;
            image.pixel(x, y).g = copy_image.pixel(image.width() - (x + 1), y).g;
            image.pixel(x, y).b = copy_image.pixel(image.width() - (x + 1), y).b;
        }
    }
}

// ⭐⭐ Image bruitée
void noise(sil::Image& image){
    for (int x{0}; x < image.width() - 1; x++){
         for (int y{0}; y < image.height(); y++){
            if(true_with_probability(0.3)) {
                image.pixel(x, y).r = random_float(0, 1);
                image.pixel(x, y).g = random_float(0, 1);
                image.pixel(x, y).b = random_float(0, 1);
            }
        }
    }
}

// ⭐⭐ Rotation de 90°
void rotation_90(sil::Image& image){
    sil::Image new_image{image.height(), image.width()};

    for (int x{0}; x < image.width(); x++){
        for (int y{0}; y < image.height(); y++){
            new_image.pixel(new_image.width() - y - 1, x).r = image.pixel(x, y).r;
            new_image.pixel(new_image.width() - y - 1, x).g = image.pixel(x, y).g;
            new_image.pixel(new_image.width() - y - 1, x).b = image.pixel(x, y).b;
        }
    }
    new_image.save("output/rotation_90.png");
}

// ⭐⭐ RGB split
void rgb_split(sil::Image& image){
    sil::Image new_image{image.width(), image.height()};

    for (int x{0}; x < image.width(); x++){
        for (int y{0}; y < image.height(); y++){
            if(x + 30 < image.width()) {
                new_image.pixel(x, y).b = image.pixel((x + 30), y).b;
            }

            new_image.pixel(x, y).g = image.pixel(x, y).g;

            if((x - 30 > 0)) {
                new_image.pixel(x, y).r = image.pixel((x - 30), y).r;
            }
        }
    }
    new_image.save("output/rgb_split.png");
}

// ⭐⭐ Luminosité
void luminosity(sil::Image& image, bool dark){
    for (int x{0}; x < image.width(); x++){
        for (int y{0}; y < image.height(); y++){
            if(dark) {
                image.pixel(x,y).r = std::pow(image.pixel(x, y).r, 2);
                image.pixel(x,y).g = std::pow(image.pixel(x, y).g, 2);
                image.pixel(x,y).b = std::pow(image.pixel(x, y).b, 2);
            } else {
                image.pixel(x,y).r = std::sqrt(image.pixel(x, y).r);
                image.pixel(x,y).g = std::sqrt(image.pixel(x, y).g);
                image.pixel(x,y).b = std::sqrt(image.pixel(x, y).b);
            }
        }
    }  
}

// ⭐⭐(⭐) Disque
void disque(sil::Image& image){
    for (int x{0}; x < image.width(); x++){
        for (int y{0}; y < image.height(); y++){
            if((x - 250) * (x - 250) + (y - 250) * (y - 250) <=  100 * 100) {
                image.pixel(x, y).r = 1;
                image.pixel(x, y).g = 1;
                image.pixel(x, y).b = 1;
            };
        }
    }  
}

// ⭐ Cercle
void cercle(sil::Image& image, int thickness){
    for (int x{0}; x < image.width(); x++){
        for (int y{0}; y < image.height(); y++){
            if(((100 - thickness) * (100 - thickness) <= (x - 250) * (x - 250) + (y - 250) * (y - 250)) && ((x - 250) * (x - 250) + (y - 250) * (y - 250) <= 100 * 100)) {
                image.pixel(x, y).r = 1;
                image.pixel(x, y).g = 1;
                image.pixel(x, y).b = 1;
            };
        }
    }  
}



int main()
{
    // //⭐ Ne garder que le vert
    // sil::Image image{"images/logo.png"};
    // keep_green_only(image);
    // image.save("output/keep_green_only.png");

    // // ⭐ Échanger les canaux
    // sil::Image image{"images/logo.png"};
    // swap_red_and_blue_channels(image);
    // image.save("output/swap_red_and_blue_channels.png");

    // // ⭐ Noir & Blanc
    // sil::Image image{"images/logo.png"};
    // black_and_white(image);
    // image.save("output/black_and_white.png");

    // // ⭐ Négatif
    // sil::Image image{"images/logo.png"};
    // negatif(image);
    // image.save("output/negatif.png");

    // // ⭐ Dégradé
    // sil::Image image{300, 200};
    // gradiant(image);
    // image.save("output/gradiant.png");

    // // ⭐⭐ Miroir
    // sil::Image image{"images/logo.png"};
    // mirror(image);
    // image.save("output/mirror.png");

    // // ⭐⭐ Image bruitée
    // sil::Image image{"images/logo.png"};
    // noise(image);
    // image.save("output/noise.png");

    // // ⭐⭐ Rotation de 90°
    // sil::Image image{"images/logo.png"};
    // rotation_90(image);

    // // ⭐⭐ RGB split
    // sil::Image image{"images/logo.png"};
    // rgb_split(image);

    // // ⭐⭐ Luminosité
    // sil::Image image{"images/photo.jpg"};
    // luminosity(image, true);
    // image.save("output/luminosity_dark.png");
    
    // sil::Image image2{"images/photo.jpg"};
    // luminosity(image2, false);
    // image2.save("output/luminosity_bright.png");

    // // ⭐⭐(⭐) Disque
    // sil::Image image{500, 500};
    // disque(image);
    // image.save("output/disque.png");

    // ⭐ Cercle
    sil::Image image{500, 500};
    cercle(image, 5);
    image.save("output/cercle.png");
}