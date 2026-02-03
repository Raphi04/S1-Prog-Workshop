#include <sil/sil.hpp>
#include "random.hpp"
#include <cmath>
#include <numbers>
#include <algorithm>


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

// ⭐⭐ Animation
void animation(sil::Image& image, int frames){
    int const decalage = image.width() / frames;
    int x_center {0};

    for(int i{0}; i < frames; i++) {
        for (int x{0}; x < image.width(); x++){
            for (int y{0}; y < image.height(); y++){
                if((x - x_center) * (x - x_center) + (y - 250) * (y - 250) <=  100 * 100) {
                    image.pixel(x, y).r = 1;
                    image.pixel(x, y).g = 1;
                    image.pixel(x, y).b = 1;
                }
                else {
                    image.pixel(x, y).r = 0;
                    image.pixel(x, y).g = 0;
                    image.pixel(x, y).b = 0;
                }
            }
        }

        x_center += decalage;
        image.save("output/animation"+ std::to_string(i) + ".png");
    }
}

// ⭐⭐⭐ Rosace
void rosace(sil::Image& image, int thickness){
    for (int x{0}; x < image.width(); x++){
        for (int y{0}; y < image.height(); y++){
            if(((100 - thickness) * (100 - thickness) <= (x - 250) * (x - 250) + (y - 250) * (y - 250)) && ((x - 250) * (x - 250) + (y - 250) * (y - 250) <= 100 * 100)) {
                image.pixel(x, y).r = 1;
                image.pixel(x, y).g = 1;
                image.pixel(x, y).b = 1;
            };
        }
    }  

    for(int i{0}; i < 6; i++) {
        float radian = i * M_PI /3; 
        float centre_x = image.width() / 2 + 100*cos(radian);
        float centre_y = image.height() / 2 + 100*sin(radian);

        for (int x{0}; x < image.width(); x++){
            for (int y{0}; y < image.height(); y++){
                if(((100 - thickness) * (100 - thickness) <= (x - centre_x) * (x - centre_x) + (y - centre_y) * (y - centre_y)) && ((x - centre_x) * (x - centre_x) + (y - centre_y) * (y - centre_y) <= 100 * 100)) {
                    image.pixel(x, y).r = 1;
                    image.pixel(x, y).g = 1;
                    image.pixel(x, y).b = 1;
                };
            }
        }  
    }

}

// ⭐⭐ Mosaïque
void mosaique(sil::Image& image, int repetition){
    sil::Image new_image{image.width() * repetition, image.height() * repetition};

    for(int row{0}; row < repetition; row++) {
        for(int column{0}; column < repetition; column++) {
            for (int x{0}; x < image.width(); x++){
                for (int y{0}; y < image.height(); y++){
                    new_image.pixel(x + column * image.width(), y + row * image.height()) = image.pixel(x, y);
                }
            }  
        }
    }
    
    new_image.save("output/mosaique.png");
}

// ⭐⭐⭐⭐ Mosaïque miroir
void mosaique_miroir(sil::Image& image, int repetition){
    sil::Image new_image{image.width() * repetition, image.height() * repetition};

    for(int row{0}; row < repetition; row++) {
        for(int column{0}; column < repetition; column++) {
            for (int x{0}; x < image.width(); x++){
                for (int y{0}; y < image.height(); y++){
                    if(column % 2 == 1) {
                        if(row % 2 == 1) {
                            new_image.pixel(x + column * image.width(), y + row * image.height()) = image.pixel(image.width() - 1 - x, image.height() - 1 - y);
                        } else {
                            new_image.pixel(x + column * image.width(), y + row * image.height()).r = image.pixel(image.width() - (x + 1), y).r;
                            new_image.pixel(x + column * image.width(), y + row * image.height()).g = image.pixel(image.width() - (x + 1), y).g;
                            new_image.pixel(x + column * image.width(), y + row * image.height()).b = image.pixel(image.width() - (x + 1), y).b;
                        }
                    } else {
                        if(row % 2 == 1) {
                            new_image.pixel(x + column * image.width(), y + row * image.height()).r = image.pixel(x, image.height() - 1 - y).r;
                            new_image.pixel(x + column * image.width(), y + row * image.height()).g = image.pixel(x, image.height() - 1 - y).g;
                            new_image.pixel(x + column * image.width(), y + row * image.height()).b = image.pixel(x, image.height() - 1 - y).b;
                        } else {
                            new_image.pixel(x + column * image.width(), y + row * image.height()) = image.pixel(x, y);
                        }
                    }
                }
            }  
        }
    }
    
    new_image.save("output/mosaique_miroir.png");
}

// ⭐⭐⭐ Glitch
void glitch(sil::Image& image, int nbGlitch) {
    sil::Image new_image{image};

    for(int i{0}; i < nbGlitch; i++) {
        int largeur = random_int(0, 15);
        int hauteur = random_int(0, 8);

        int x1 = random_int(0, image.width() - 1);
        int y1 = random_int(0, image.height() - 1);

        int x2 = random_int(0, image.width() - 1);
        int y2 = random_int(0, image.height() - 1);



        for(int h {0}; h < hauteur; h++) {
            for(int l {0}; l < largeur; l++) {
                if(x1 + l < image.width() && y1 + h < image.height()) {
                    if(x2 + l < image.width() && y2 + h < image.height()) {
                        new_image.pixel(x1 + l, y1 + h) = image.pixel(x2 + l, y2 + h);
                        new_image.pixel(x2 + l, y2 + h) = image.pixel(x1 + l, y1 + h);
                    }
                }
            }
        }
    }
    new_image.save("output/glitch.png");
}

float brightness(glm::vec3 const& color);

float brightness(glm::vec3 const& color) {
    float brightness = (color.r + color.g + color.b) / 3;
    return brightness;
}

// ⭐⭐⭐ Tri de pixels
void tri_pixel(sil::Image& image) {
    for(int y {0}; y < image.height(); y++) {
        int largeur = random_int(25, 100);
        int random_index = random_int(0, image.width() - 1);
        int effective_length {1};

        for(int l{0}; l < largeur; l++) {
            if(random_index + l < image.width() - 1) {
                effective_length++;
            }
        }

        std::sort(image.pixels().begin() +  y * image.width() + random_index, image.pixels().begin() + y * image.width() + random_index + effective_length + 1, [](glm::vec3 const& color1, glm::vec3 const& color2) {
            return brightness(color1) < brightness(color2);
        });
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

    // // ⭐ Cercle
    // sil::Image image{500, 500};
    // cercle(image, 5);
    // image.save("output/cercle.png");

    // // ⭐⭐ Animation
    // sil::Image image{500, 500};
    // animation(image, 25);

    // // ⭐⭐⭐ Rosace
    // sil::Image image{500, 500};
    // rosace(image, 5);
    // image.save("output/rosace.png");

    // // ⭐⭐ Mosaïque
    // sil::Image image{"images/logo.png"};
    // mosaique(image, 5);

    // // ⭐⭐⭐⭐ Mosaïque miroir
    // sil::Image image{"images/logo.png"};
    // mosaique_miroir(image, 5);

    // // ⭐⭐⭐ Glitch
    // sil::Image image{"images/logo.png"};
    // glitch(image, 250);

    // ⭐⭐⭐ Tri de pixels
    sil::Image image{"images/logo.png"};
    tri_pixel(image);
    image.save("output/tri_pixel.png");
}