# 🐣 S1 | Prog: Workshop

## ⭐ Ne garder que le vert

J'ai enlevé les couleurs rouges et bleu des pixels.

![Avant modification](./images/logo.png)
![Après modification](./output/keep_green_only.png)

## ⭐ Échanger les canaux

Échange des canaux rouge et bleu.

![Avant modification](./images/logo.png)
![Après modification](./output/swap_red_and_blue_channels.png)

## ⭐ Noir & Blanc

On calcul le noir et blanc avec la formule.

```
0.3 * R + 0.59 * G + 0.11 * B
```

![Avant modification](./images/logo.png)
![Après modification](./output/black_and_white.png)

## ⭐ Négatif

J'ai fais 1 - la couleur

![Avant modification](./images/logo.png)
![Après modification](./output/negatif.png)

## ⭐ Dégradé

J'ai calculé la proportion de x en fonction de la taille de l'image

![Après modification](./output/gradiant.png)

## ⭐⭐ Miroir

J'ai copié l'image dans une variable pour la sauvegarder et j'ai modifié l'image en prenant en prenant les points opposés avec l'image copié

![Avant modification](./images/logo.png)
![Après modification](./output/mirror.png)

## ⭐⭐ Image bruitée

J'ai mis une probabilité de 30% que le pixel soit modifié par une couleur aléatoire

![Avant modification](./images/logo.png)
![Après modification](./output/noise.png)

## ⭐⭐ Rotation de 90°

Il faut penser au changement des axes x et y

![Avant modification](./images/logo.png)
![Après modification](./output/rotation_90.png)

## ⭐⭐ RGB split

Il faut faire attention au bordures et verifier qu'on peut bien prendre la couleur.

![Avant modification](./images/logo.png)
![Après modification](./output/rgb_split.png)

## ⭐⭐ Luminosité

Il faut utiliser les puissances sur les valeurs rouges, vertes et bleues.

![Avant modification](./images/photo.jpg)
![Après modification](./output/luminosity_bright.png)
![Après modification](./output/luminosity_dark.png)

## ⭐⭐(⭐) Disque

Il faut utilisé la formule d'un disque et vérifier si le point est dedans.

![Après modification](./output/disque.png)

### ⭐ Cercle

On créer un petit cercle et on verifie que les points soient au-dessus.

![Après modification](./output/cercle.png)

### ⭐⭐ Animation

On boucle pour créer 25 images et on créer le gif.

![Après modification](./output/animation.gif)

### ⭐⭐⭐ Rosace

On utilise des formules tigonométrique et on boucle pour créer tous les cercles.

![Après modification](./output/rosace.png)

## ⭐⭐ Mosaïque

On copie l'image 5 fois en décalant x et y par la taille de l'image.

![Avant modification](./images/logo.png)
![Après modification](./output/mosaique.png)

## ⭐⭐⭐⭐ Mosaïque miroir

Quand le modulo vaut 1, alors on est sur une case impair et on change le comportement.

![Avant modification](./images/logo.png)
![Après modification](./output/mosaique_miroir.png)

## ⭐⭐⭐ Glitch

Il faut bien penser à prendre une image de référence.

![Avant modification](./images/logo.png)
![Après modification](./output/glitch.png)

## ⭐⭐⭐ Tri de pixels

On fait le tri en fonction de la brightness de la couleur et il faut bien penser à multiplier l'index aléatoire par y \* la taille de l'image

![Avant modification](./images/logo.png)
![Après modification](./output/tri_pixel.png)

## ⭐⭐⭐(⭐) Fractale de Mandelbrot

La principale source de problème était de bien penser à diviser par des float et de trouver la formule de conversion des intervalles.

![Après modification](./output/fractale.png)

## ⭐⭐⭐(⭐) Dégradés dans l'espace de couleur Lab

Il faut bien penser à faire le mix une fois qu'on est passé à OkLab, puis repartir sur du srgb.

![Avant modification](./output/bad_color_gradiant.png)
![Après modification](./output/color_gradiant.png)

## ⭐⭐⭐(⭐) Tramage

Il faut bien pensé à revenir au grayscale vu que l'image est en couleur.

![Avant modification](./images/photo.jpg)
![Après modification](./output/tramage.png)

## ⭐⭐⭐(⭐) Normalisation de l'histogramme

On récupère le min et le max de la luminosité et on adapte l'intervale à [0, 1].

![Avant modification](./images/photo_faible_contraste.jpg)
![Après modification](./output/tramage.png)
