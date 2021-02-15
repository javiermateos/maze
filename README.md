# Maze

## Descripción

Este proyecto consiste en la realización de las prácticas de la
asignatura de Programación II de la [Escuela Politécnica](https://www.uam.es/ss/Satellite/EscuelaPolitecnica/es/home.htm) de la [Universidad
Autónoma de Madrid](https://uam.es/ss/Satellite/es/home.htm). 

En concreto el proyecto se divide en dos partes: 

Por un lado, la implementación de los siguientes tipos abstractos de datos:

- [Stack](./include/stack.h)
- [Queue](./include/queue.h)
- [List](./include/list.h)
- [Tree](./include/tree.h)

Por otro lado, la utilización de alguna de estas estructuras para la resolución
de laberintos mediante búsqueda en profundidad y búsqueda en anchura. En concreto,
la búsqueda en profundidad se ha implementado mediante una pila y recursividad y,
la búsqueda en anchura se ha implementado mediante una cola.

## Requerimientos

- GCC
- Make

## Instrucciones

Si quieres probar el programa ejecuta los siguientes comandos:
```shell
make all
make run
```

Por otro lado, si quieres lanzar de forma "personalizada" el programa
puedes ejecutar:
```shell
./maze <map_file> <abstract_data_type>
```
donde abstract data type puede ser: stack, queue o recursive.

Los diferentes mapas que se incluyen se encuentran en la carpeta [data](./data).

## Demo
```
> ./maze data/m1.txt recursive
Buscando el camino mediante la estrategia: { RIGHT, LEFT, UP, DOWN }
[(1,5): o]
[(1,4): .]
[(1,3): .]
[(2,3): .]
[(3,3): .]
[(4,3): .]
[(4,2): .]
[(4,1): .]
[(3,1): .]
[(2,1): .]
[(1,1): i]
++++++
+i...+
++++.+
+....+
+.VVV+
+o++V+
++++++
Longitud del camino optimo: 10
Buscando el camino mediante la estrategia: { DOWN, RIGHT, LEFT, UP }
[(1,5): o]
[(1,4): .]
[(1,3): .]
[(2,3): .]
[(3,3): .]
[(4,3): .]
[(4,2): .]
[(4,1): .]
[(3,1): .]
[(2,1): .]
[(1,1): i]
++++++
+i...+
++++.+
+....+
+.VVV+
+o++V+
++++++
Longitud del camino optimo: 10
Buscando el camino mediante la estrategia: { UP, DOWN, RIGHT, LEFT }
[(1,5): o]
[(1,4): .]
[(2,4): .]
[(2,3): .]
[(3,3): .]
[(3,4): .]
[(4,4): .]
[(4,3): .]
[(4,2): .]
[(4,1): .]
[(3,1): .]
[(2,1): .]
[(1,1): i]
++++++
+i...+
++++.+
+ ...+
+....+
+o++V+
++++++
Longitud del camino optimo: 12
Buscando el camino mediante la estrategia: { LEFT, UP, DOWN, RIGHT }
[(1,5): o]
[(1,4): .]
[(1,3): .]
[(2,3): .]
[(3,3): .]
[(4,3): .]
[(4,2): .]
[(4,1): .]
[(3,1): .]
[(2,1): .]
[(1,1): i]
++++++
+i...+
++++.+
+....+
+.   +
+o++ +
++++++
Longitud del camino optimo: 10
```

