# Texture mapping — cub3D

## 1. Charger le fichier XPM et récupérer l'accès aux pixels

MiniLibX fournit une fonction dédiée pour lire un fichier `.xpm` et le transformer en image utilisable :

```c
void *mlx_xpm_file_to_image(void *mlx_ptr, char *filename, int *width, int *height);
```

Elle retourne un pointeur opaque vers l'image (à garder précieusement, tu en auras besoin pour la libérer proprement avec `mlx_destroy_image` à la fin du programme), et elle remplit `width` et `height` par référence avec les dimensions réelles du fichier chargé.

Une fois l'image chargée, ce pointeur seul ne permet pas encore de lire les pixels un par un — c'est juste une référence opaque côté MiniLibX. Pour accéder aux données brutes, il faut une deuxième fonction.

## 2. Accéder aux pixels de l'image chargée

```c
char *mlx_get_data_addr(void *img_ptr, int *bits_per_pixel, int *line_length, int *endian);
```

Cette fonction prend le pointeur d'image retourné par `mlx_xpm_file_to_image`, et donne en retour l'adresse mémoire du buffer de pixels bruts. Elle remplit aussi trois variables par référence, à stocker impérativement pour cette texture :

- **`bits_per_pixel`** : généralement 32 (donc 4 octets par pixel, format ARGB ou similaire)
- **`line_length`** : le nombre d'octets par ligne dans le buffer — attention, ce n'est pas forcément égal à `width * (bpp/8)`, il peut y avoir du padding ajouté par MiniLibX pour l'alignement mémoire. Ne le recalcule jamais toi-même, utilise toujours la valeur retournée.
- **`endian`** : l'ordre des octets (peu importe en pratique si tu lis en `int` d'un coup plutôt qu'octet par octet)

Une fois `addr`, `bpp`, `line_length` connus, on peut lire n'importe quel pixel `(x, y)` de la texture avec :

```c
pixel = *(unsigned int *)(addr + (y * line_len + x * (bpp / 8)))
```

Ça donne la couleur du pixel sous forme d'entier. Ce sera la même formule pour écrire dans le buffer de rendu à l'écran.

## 3. Trouver `texX` — quelle colonne verticale de la texture afficher

Le principe : il faut savoir où exactement sur la face du mur le rayon a touché — pas juste dans quelle case de la grille, mais la position fractionnaire précise sur cette face, entre 0 et 1 (0 = un bord de la case, 1 = l'autre bord).

On utilise `perpWallDist` (déjà calculé) pour retrouver le point d'impact exact en coordonnées monde :

```
si side == 0 :
    wallX = posY + perpWallDist * rayDirY
sinon :
    wallX = posX + perpWallDist * rayDirX
```

**Pourquoi `posY + ... * rayDirY` quand `side == 0`** (mur touché sur une face verticale) ? Parce que si le rayon a touché une ligne verticale de la grille, la coordonnée X est automatiquement entière (`mapX`), donc elle ne dit rien d'utile sur la position horizontale du point d'impact — c'est la coordonnée Y qui varie continûment le long de cette face, et qu'il faut donc calculer. Symétriquement pour `side == 1`.

Ensuite on ne garde que la partie fractionnaire :

```c
wallX -= floor(wallX)
```

Ça isole la position relative sur la face touchée, indépendamment de quelle case précise de la grille il s'agit.

Enfin on convertit cette position continue `[0,1]` en un indice de colonne dans la texture :

```c
texX = (int)(wallX * texWidth)
```

## 4. Trouver `texY` pour chaque pixel de la colonne à l'écran

Il s'agit d'étirer (ou compresser) verticalement la texture pour remplir la hauteur du mur calculée (`lineHeight`), qui correspond presque jamais exactement à `texHeight`.

L'idée : avancer dans la texture avec un pas constant à chaque pixel écran, plutôt que de recalculer une position depuis zéro à chaque itération.

D'abord, le pas d'incrément — combien de pixels de texture on avance par pixel d'écran parcouru :

```c
step = (double)texHeight / lineHeight
```

Si `lineHeight` est petit (mur loin, donc écrasé à l'écran), `step` est grand — on saute plusieurs lignes de texture par pixel écran (compression). Si `lineHeight` est grand (mur proche, étiré), `step` est petit voire inférieur à 1 — on répète certaines lignes de texture sur plusieurs pixels écran (étirement).

Ensuite, il faut calculer le point de départ dans la texture, `texPos`. **Le piège** : le mur ne commence pas forcément en haut de l'écran — `lineHeight` peut dépasser la hauteur de l'écran (murs très proches), donc le rendu réel est découpé entre `drawStart` et `drawEnd` (clampés aux bords de l'écran). Il faut donc calculer où on en serait dans la texture *avant* ce clampage, pour ne pas désynchroniser le mapping :

```c
texPos = (drawStart - screenHeight / 2 + lineHeight / 2) * step
```

Puis, pour chaque pixel `y` de `drawStart` à `drawEnd` :

```c
texY = (int)texPos & (texHeight - 1)
texPos += step
```

Une fois `texX` et `texY` connus pour ce pixel, on lit la couleur avec la formule de l'étape 2 (`addr + y*line_len + x*(bpp/8)`) et on l'écrit dans le buffer de rendu à `(x, y)` sur l'écran.

## Étape suivante

Choisir *quelle* texture (nord / sud / est / ouest) utiliser selon la face touchée.