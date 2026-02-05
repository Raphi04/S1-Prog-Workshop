#include <sil/sil.hpp>
#include "random.hpp"
#include <cmath>
#include <numbers>
#include <algorithm>
#include <complex>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <iostream>

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

// ⭐⭐⭐(⭐) Fractale de Mandelbrot
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

// ⭐⭐⭐ Tri de pixels
void fractale(sil::Image& image) {
    for (int x{0}; x < image.width(); x++){
        for (int y{0}; y < image.height(); y++){
            int intervale_a = 0;
            int intervale_b = 500;
            float intervale_c = -2;
            float intervale_d = 2;


            float reel = intervale_c + (x - intervale_a) * (intervale_d - intervale_c)/(intervale_b - intervale_a);
            float imag = intervale_c + (y - intervale_a)  * (intervale_d - intervale_c)/(intervale_b - intervale_a);

            std::complex<float> c{reel, imag};
            std::complex<float> z{0, 0};

            float increment {0};
            float increment_max {20};

            for(int i{1}; i <= increment_max; i++) {
                increment++;

                z = z * z + c;
                
                if(std::abs(z) > 2) {
                    break;
                }
            }

            if(increment == increment_max) {
                image.pixel(x, y).r = 1;
                image.pixel(x, y).g = 1;
                image.pixel(x, y).b = 1;
            } else {
                image.pixel(x, y).r = increment / increment_max;
                image.pixel(x, y).g = increment / increment_max;
                image.pixel(x, y).b = increment / increment_max;
            }
        }
    }  
}


float srgb_to_linear(float c) {
    if (c <= 0.04045f)
        return c / 12.92f;
    else
        return std::pow((c + 0.055f) / 1.055f, 2.4f);
}

float linear_to_srgb(float c) {
    if (c <= 0.0031308f)
        return c * 12.92f;
    else
        return 1.055f * std::pow(c, 1.0f / 2.4f) - 0.055f;
}

glm::vec3 linear_srgb_to_oklab(glm::vec3 c) 
{
    float l = 0.4122214708f * c.r + 0.5363325363f * c.g + 0.0514459929f * c.b;
	float m = 0.2119034982f * c.r + 0.6806995451f * c.g + 0.1073969566f * c.b;
	float s = 0.0883024619f * c.r + 0.2817188376f * c.g + 0.6299787005f * c.b;

    float l_ = cbrtf(l);
    float m_ = cbrtf(m);
    float s_ = cbrtf(s);

    return {
        0.2104542553f*l_ + 0.7936177850f*m_ - 0.0040720468f*s_,
        1.9779984951f*l_ - 2.4285922050f*m_ + 0.4505937099f*s_,
        0.0259040371f*l_ + 0.7827717662f*m_ - 0.8086757660f*s_,
    };
}

glm::vec3 oklab_to_linear_srgb(glm::vec3 c) 
{
    float l_ = c.r + 0.3963377774f * c.g + 0.2158037573f * c.b;
    float m_ = c.r - 0.1055613458f * c.g - 0.0638541728f * c.b;
    float s_ = c.r - 0.0894841775f * c.g - 1.2914855480f * c.b;

    float l = l_*l_*l_;
    float m = m_*m_*m_;
    float s = s_*s_*s_;

    return {
		+4.0767416621f * l - 3.3077115913f * m + 0.2309699292f * s,
		-1.2684380046f * l + 2.6097574011f * m - 0.3413193965f * s,
		-0.0041960863f * l - 0.7034186147f * m + 1.7076147010f * s,
    };
}

// ⭐⭐⭐(⭐) Dégradés dans l'espace de couleur Lab
void color_gradiant(sil::Image& image) {
     for (int x{0}; x < image.width(); x++){
        float proportion = float(x) / (image.width() - 1);

        float max_color_value = srgb_to_linear(1);

        glm::vec3 oklab_color_red = linear_srgb_to_oklab({max_color_value, 0, 0});
        glm::vec3 oklab_color_green = linear_srgb_to_oklab({0, max_color_value, 0});

        glm::vec3 mixed_color = glm::mix(oklab_color_red, oklab_color_green, proportion);

        glm::vec3 back_to_rgb = oklab_to_linear_srgb(mixed_color);
        float back_to_srgb_red = linear_to_srgb(back_to_rgb.r);
        float back_to_srgb_green = linear_to_srgb(back_to_rgb.g);


        for (int y{0}; y < image.height(); y++){
            image.pixel(x, y).r = back_to_srgb_red;
            image.pixel(x, y).g = back_to_srgb_green;
        }
    }
}

// ⭐⭐⭐(⭐) Tramage
void tramage(sil::Image& image) {
    const int bayer_n = 4;
    float bayer_matrix_4x4[][bayer_n] = {
        {    -0.5,       0,  -0.375,   0.125 },
        {    0.25,   -0.25,   0.375, - 0.125 },
        { -0.3125,  0.1875, -0.4375,  0.0625 },
        {  0.4375, -0.0625,  0.3125, -0.1875 },
    };

    for (int x{0}; x < image.width(); x++){
        for (int y{0}; y < image.height(); y++){
            float grayscale = 0.3 * image.pixel(x, y).r + 0.59 * image.pixel(x, y).g + 0.11 * image.pixel(x, y).b;

            if((grayscale + (1 * bayer_matrix_4x4[x % 4][y % 4]) < 1/2.0f)) {
                image.pixel(x, y).r = 0;
                image.pixel(x, y).g = 0;
                image.pixel(x, y).b = 0;
            } else {
                image.pixel(x, y).r = 1;
                image.pixel(x, y).g = 1;
                image.pixel(x, y).b = 1;
            }
        }
    }
}

// ⭐⭐⭐(⭐) Normalisation de l'histogramme
void normalisation_histogramme(sil::Image& image) {
    float min_actuel{1}; 
    float max_actuel{0}; 

    for (int x{0}; x < image.width(); x++){
        for (int y{0}; y < image.height(); y++){
            float luminosity = (image.pixel(x , y).r + image.pixel(x , y).g + image.pixel(x , y).b) / 3;

            if(min_actuel > luminosity) {
                min_actuel = luminosity;
            }

            if(max_actuel < luminosity) {
                max_actuel = luminosity;
            }
        }
    }

    for (int x{0}; x < image.width(); x++){
        for (int y{0}; y < image.height(); y++){
            float luminosity = (image.pixel(x , y).r + image.pixel(x , y).g + image.pixel(x , y).b) / 3;
            float newLuminosity = 0 + (luminosity - min_actuel) * (1 - 0)/(max_actuel - min_actuel);

            image.pixel(x, y).r = image.pixel(x, y).r * (newLuminosity / luminosity);
            image.pixel(x, y).g = image.pixel(x, y).g * (newLuminosity / luminosity);
            image.pixel(x, y).b = image.pixel(x, y).b * (newLuminosity / luminosity);

            // image.pixel(x, y).r = 0 + (image.pixel(x, y).r - min_actuel) * (1 - 0)/(max_actuel - min_actuel);
            // image.pixel(x, y).g = 0 + (image.pixel(x, y).g - min_actuel) * (1 - 0)/(max_actuel - min_actuel);
            // image.pixel(x, y).b = 0 + ( image.pixel(x, y).b - min_actuel) * (1 - 0)/(max_actuel - min_actuel);
        }
    }
}


glm::vec2 rotated(glm::vec2 point, glm::vec2 center_of_rotation, float angle)
{
    return glm::vec2{glm::rotate(glm::mat3{1.f}, angle) * glm::vec3{point - center_of_rotation, 0.f}} + center_of_rotation;
}

// ⭐⭐⭐⭐ Vortex Fail
void vortex_fail(sil::Image& image) {
    sil::Image imageRef = image;

    for (int x{0}; x < image.width(); x++){
        for (int y{0}; y < image.height(); y++){
            glm::vec2 p1(image.width() / 2, image.height() / 2);
            glm::vec2 p2(x, y);

            float distance = glm::distance(p2, p1);

            glm::vec2 newPoint = rotated(p2, p1, distance * M_PI/2);

            if(newPoint[0] > 0 && newPoint[0] < image.width()) {
                if(newPoint[1] > 0 && newPoint[1] < image.height()) {
                    image.pixel(x, y) = imageRef.pixel(newPoint[0], newPoint[1]);
                }
            }
        }
    }
}

// ⭐⭐⭐⭐ Vortex
void vortex(sil::Image& image) {
    sil::Image newImage = {image.width(),image.height()};


    for (int x{0}; x < newImage.width(); x++){
        for (int y{0}; y < newImage.height(); y++){
            glm::vec2 p1(newImage.width() / 2, newImage.height() / 2);
            glm::vec2 p2(x, y);

            float distance = glm::distance(p2, p1);

            glm::vec2 newPoint = rotated(p2, p1, distance/15 * M_PI/2);

            if(newPoint[0] > 0 && newPoint[0] < newImage.width()) {
                if(newPoint[1] > 0 && newPoint[1] < newImage.height()) {
                    newImage.pixel(x, y) = image.pixel(newPoint[0], newPoint[1]);
                }
            }
        }
    }
    newImage.save("output/vortex.png");
}

glm::vec3 applyKernel(float kernel[5][5], float x, float y, sil::Image const& imageRef){
    glm::vec3 somme{0};

    for (int i = -2; i <= 2; i++) {
        for (int j = -2; j <= 2; j++) {
            if (x + i >= 0 && x + i < imageRef.width() &&
                y + j >= 0 && y + j < imageRef.height()) {
                somme += imageRef.pixel(x + i, y + j) * kernel[i + 1][j + 1];
            }
        }
    }

    return somme;
}

glm::vec3 applyKernel(float kernel[5][5], float x, float y, sil::Image const& imageRef);

glm::vec3 applyKernel2(float kernel[3][3], float x, float y, sil::Image const& imageRef){
    glm::vec3 somme{0};

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (x + i >= 0 && x + i < imageRef.width() &&
                y + j >= 0 && y + j < imageRef.height()) {
                somme += imageRef.pixel(x + i, y + j) * kernel[i + 1][j + 1];
            }
        }
    }

    return somme;
}

glm::vec3 applyKernel2(float kernel[3][3], float x, float y, sil::Image const& image);

glm::vec3 applyKernel3(float kernel[5][5], float x, float y, sil::Image const& imageRef, bool isHorizontal){
    glm::vec3 somme{0};

    if(isHorizontal) {
        for (int i = -2; i <= 2; i++) {
            if (x + i >= 0 && x + i < imageRef.width()) {
                somme += imageRef.pixel(x + i, y) * kernel[i + 1][2];
            } 
        }
    } else {
        for (int i = -2; i <= 2; i++) {
            if (y + i >= 0 && y + i < imageRef.height()) {
                somme += imageRef.pixel(x, y + i) * kernel[2][i + 1];
            } 
        }
    }
    return somme;
}

glm::vec3 applyKernel3(float kernel[5][5], float x, float y, sil::Image const& imageRef, bool isHorizontal);

// ⭐⭐⭐⭐ Convolutions
void convolutions(sil::Image& image, float kernel[5][5]) {
    sil::Image imageRef = image;
    for (int x{0}; x < image.width(); x++){
        for (int y{0}; y < image.height(); y++){
            image.pixel(x, y) = applyKernel(kernel, x, y, imageRef);
        }
    }
    image.save("output/convolutions.png");
}

// ⭐ Emboss
void emboss(sil::Image& image, float kernel[3][3]) {
    sil::Image imageRef = image;
    for (int x{0}; x < image.width(); x++){
        for (int y{0}; y < image.height(); y++){
            image.pixel(x, y) = applyKernel2(kernel, x, y, imageRef);
        }
    }
    image.save("output/emboss.png");
}

// ⭐ Outline
void outline(sil::Image& image, float kernel[3][3]) {
    sil::Image imageRef = image;
    for (int x{0}; x < image.width(); x++){
        for (int y{0}; y < image.height(); y++){
            image.pixel(x, y) = applyKernel2(kernel, x, y, imageRef);
        }
    }
    image.save("output/outline.png");
}

// ⭐ Sharpen
void sharpen(sil::Image& image, float kernel[3][3]) {
    sil::Image imageRef = image;
    for (int x{0}; x < image.width(); x++){
        for (int y{0}; y < image.height(); y++){
            image.pixel(x, y) = applyKernel2(kernel, x, y, imageRef);
        }
    }
    image.save("output/sharpen.png");
}

// ⭐⭐ Filtres séparables
void filtre_separe(sil::Image& image, float kernel[5][5]) {
    sil::Image finalImage = image;
    sil::Image imageRef = image;
    for (int x{0}; x < image.width(); x++){
        for (int y{0}; y < image.height(); y++){
            image.pixel(x, y) = applyKernel3(kernel, x, y, imageRef, true);
        }
    }

    for (int x{0}; x < image.width(); x++){
        for (int y{0}; y < image.height(); y++){
            finalImage.pixel(x, y) = applyKernel3(kernel, x, y, image, false);
        }
    }
    finalImage.save("output/filtre_separe.png");
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

    // // ⭐⭐⭐ Tri de pixels
    // sil::Image image{"images/logo.png"};
    // tri_pixel(image);
    // image.save("output/tri_pixel.png");

    // // ⭐⭐⭐(⭐) Fractale de Mandelbrot
    // sil::Image image{500, 500};
    // fractale(image);
    // image.save("output/fractale.png");

    // // ⭐⭐⭐(⭐) Dégradés dans l'espace de couleur Lab
    // sil::Image image{500, 500};
    // color_gradiant(image);
    // image.save("output/color_gradiant.png");
    
    // // ⭐⭐⭐(⭐) Tramage
    // sil::Image image{"images/photo.jpg"};
    // tramage(image);
    // image.save("output/tramage.png");

    // // ⭐⭐⭐(⭐) Normalisation de l'histogramme
    // sil::Image image{"images/photo_faible_contraste.jpg"};
    // normalisation_histogramme(image);
    // image.save("output/normalisation_histogramme.png");

    // // ⭐⭐⭐⭐ Vortex fail
    // sil::Image image{"images/logo.png"};
    // vortex_fail(image);
    // image.save("output/vortex_fail.png");

    // // ⭐⭐⭐⭐ Vortex
    // sil::Image image{"images/logo.png"};
    // vortex(image);

    // // ⭐⭐⭐⭐ Convolutions
    // sil::Image image{"images/logo.png"};
    // float kernel[5][5] = {
    //     {1.f/25.f, 1.f/25.f, 1.f/25.f, 1.f/25.f, 1.f/25.f}, 
    //     {1.f/25.f, 1.f/25.f, 1.f/25.f, 1.f/25.f, 1.f/25.f}, 
    //     {1.f/25.f, 1.f/25.f, 1.f/25.f, 1.f/25.f, 1.f/25.f}, 
    //     {1.f/25.f, 1.f/25.f, 1.f/25.f, 1.f/25.f, 1.f/25.f}, 
    //     {1.f/25.f, 1.f/25.f, 1.f/25.f, 1.f/25.f, 1.f/25.f}, 
    // };
    // convolutions(image, kernel);
    
    // // ⭐ Emboss
    // sil::Image image{"images/logo.png"};
    // float kernel[3][3] = {
    //     {-2, -1, 0}, 
    //     {-1, 1, 1}, 
    //     {0, 1, 2}, 
    // };
    // emboss(image, kernel);

    // // ⭐ Outline
    // sil::Image image{"images/logo.png"};
    // float kernel[3][3] = {
    //     {-1, -1, -1}, 
    //     {-1, 8, -1}, 
    //     {-1, -1, -1}, 
    // };
    // outline(image, kernel);

    // // ⭐ Sharpen
    // sil::Image image{"images/logo.png"};
    // float kernel[3][3] = {
    //     {0, -1, 0}, 
    //     {-1, 5, -1}, 
    //     {0, -1, 0}, 
    // };
    // sharpen(image, kernel);

     // // ⭐ Sharpen
    // sil::Image image{"images/logo.png"};
    // float kernel[3][3] = {
    //     {0, -1, 0}, 
    //     {-1, 5, -1}, 
    //     {0, -1, 0}, 
    // };
    // sharpen(image, kernel);

    // ⭐⭐ Filtres séparables
    sil::Image image{"images/logo.png"};
    float kernel[5][5] = {
        {1.f/5.f, 1.f/5.f, 1.f/5.f, 1.f/5.f, 1.f/5.f}, 
        {1.f/5.f, 1.f/5.f, 1.f/5.f, 1.f/5.f, 1.f/5.f}, 
        {1.f/5.f, 1.f/5.f, 1.f/5.f, 1.f/5.f, 1.f/5.f}, 
        {1.f/5.f, 1.f/5.f, 1.f/5.f, 1.f/5.f, 1.f/5.f}, 
        {1.f/5.f, 1.f/5.f, 1.f/5.f, 1.f/5.f, 1.f/5.f}, 
    };
    filtre_separe(image, kernel);
}