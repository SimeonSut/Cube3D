Reprenons l'ensemble du texture mapping du raycasting, valeur par valeur, pour que tu voies bien à quoi correspond chaque terme physiquement.

## 1. `perpWallDist` — la distance perpendiculaire au mur

C'est la distance (pas la distance euclidienne brute du rayon, mais corrigée de l'effet fisheye) entre le joueur et le point d'impact sur le mur, mesurée perpendiculairement au plan de la caméra. Cette valeur sert à calculer la hauteur apparente du mur à l'écran : plus le mur est loin, plus `perpWallDist` est grand, plus le mur paraît petit.

## 2. `lineHeight` — la hauteur du mur à l'écran, en pixels

```
lineHeight = screenHeight / perpWallDist
```
(à un facteur d'échelle près selon ta convention). C'est littéralement combien de pixels verticaux ce mur va occuper sur cette colonne d'écran. Si le mur est très proche, `lineHeight` peut dépasser largement `screenHeight`.

## 3. `drawStart` / `drawEnd` — les bornes verticales à l'écran

Le mur de hauteur `lineHeight` est centré verticalement autour du milieu de l'écran (`screenHeight / 2`). Donc :
```
drawStart = -lineHeight/2 + screenHeight/2
drawEnd   =  lineHeight/2 + screenHeight/2
```
Ces valeurs peuvent sortir de l'écran (négatives ou > screenHeight) si le mur est très proche — c'est pour ça qu'on les clamp à `[0, screenHeight-1]` avant de boucler dessus à l'affichage, **mais on garde la valeur non clampée pour le calcul de texture**, sinon la texture se désynchronise.

## 4. `wallX` — où sur le mur (dans le monde) le rayon a touché, en position relative

C'est une valeur flottante entre 0 et 1, indépendante de l'écran. Si le rayon touche pile au coin gauche de la case-mur, `wallX = 0` ; s'il touche pile au coin droit, `wallX = 1`. Concrètement, c'est la partie fractionnaire de la coordonnée d'impact sur l'axe qui varie (X du monde si le mur touché est une face nord/sud, Y du monde si c'est une face est/ouest).

## 5. `texX` — colonne de la texture à afficher

```
texX = wallX * texWidth
```
Puisque `wallX` va de 0 à 1 et que la texture a une largeur `texWidth` (en pixels), on obtient directement l'indice de colonne dans la texture. C'est fixe pour toute la colonne verticale de mur — un seul rayon touche un seul point du mur, donc une seule colonne de texture est utilisée pour toute la hauteur de cette colonne à l'écran.

## 6. `step` — de combien on avance dans la texture à chaque pixel écran

```
step = texHeight / lineHeight
```
C'est le facteur d'échelle entre "un pixel de texture" et "un pixel écran" pour cette colonne précise. Si le mur est loin (`lineHeight` petit), `step` est grand : on saute plusieurs lignes de texture par pixel écran (la texture est compressée). Si le mur est proche (`lineHeight` grand, mur zoomé), `step` est petit, potentiellement < 1 : plusieurs pixels écran successifs lisent la même ligne de texture (la texture est étirée).

## 7. `texPos` — la position courante dans la texture (avant arrondi), pour le pixel écran qu'on est en train de dessiner

C'est la valeur qu'on incrémente de `step` à chaque ligne descendue à l'écran. Son point de départ tient compte du fait que le mur peut commencer hors écran :
```
texPos = (drawStart - screenHeight/2 + lineHeight/2) * step
```
Cette expression compense le fait que si `drawStart` a été clampé à 0 pour l'affichage, il ne faut pas non plus recommencer la texture à zéro — il faut reprendre à l'endroit correspondant à ce qui aurait été affiché hors écran.

## 8. `texY` — la ligne de texture pour ce pixel écran précis

```
texY = (int)texPos & (texHeight - 1)
```
C'est la valeur finale : l'indice de ligne dans le tableau de pixels de la texture, qu'on va combiner avec `texX` pour récupérer la couleur du pixel à dessiner.

## Résumé du lien logique entre toutes ces valeurs

`perpWallDist` (distance réelle) → `lineHeight` (taille à l'écran) → `drawStart/drawEnd` (où dessiner) → `step` (vitesse de parcours de la texture) → `texPos` (position courante, flottante) → `texY` (position finale, entière, dans la texture). En parallèle, indépendamment de tout ça : `wallX` (où sur le mur) → `texX` (quelle colonne de texture).

Le point clé à retenir : `texX` est constant pour toute la colonne, `texY` varie à chaque pixel dessiné du haut vers le bas de cette colonne.