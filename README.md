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

On créer un petit cercle et on verifie que les points soient au-dessus

![Après modification](./output/cercle.png)
