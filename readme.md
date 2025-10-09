### Algorithm system Signa in silico (AsSis)
[Original algorithm by Erwin P. Stoschek & Dagmar Schönfeld](https://www.algorithmicschannel-dresden-guilin.net/wordpress/wp-content/uploads/Signa-in-silico.pdf)

## Example Usage
# Basic Shapes
Spiral: ./AsSis -s 2 -r 0.99

Triangle: ./AsSis -s 2 -r 0.33333

Square: ./Asis -s 2 -r 0.25

Pentagon: ./AsSis -s 2 -r 0.2

Dodecahedron ./AsSis -2 -r 0.1

# Less Basic Shapes
Spiky ball: ./AsSis -s 0 -r 0.33333

Flower: ./AsSis -s 0 -r 0.34 -t 1

Bracelet: ./AsSis -s 2 -r 0.34 -c 5

Swirly hexagon: ./AsSis -t 4 -s 1 -r 0.167 -n 2000
