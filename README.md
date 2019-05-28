# lem-in (Поиск оптимального пути в графе)

Один из школьных проетов

Цель проекта состоит в нахождении оптимального колиства путей для прохождения муравьев из точки А в точку Б в 
связанном графе, где вес каждого ребра равен 1.

Для более легкого понимания ниже приведен пример работы программы.

## Start
```
./lem-in < exp.map
```
## Cat exp.map
```
5          //Amount of the ants
##start     //Establish starting room
1 100 100   //Name of the room;     x position;       y position;
2 400 100
3 700 100
##end       //Establish ending room
4 700 400
5 400 400
6 100 400
1-2         //Start connecting rooms
2-3
3-4
4-5
5-6
1-6
1-5
2-6
2-4
5-3
5-2         //Finish connecting rooms
```
## Example of the vizualization (./lem-in < exp.amp)
![](https://media.giphy.com/media/5tgWLNAm8aNhkG8hDB/giphy.gif)

## Install
First, install SDL.h
```
brew install sdl2; brew install sdl2_gfx;
```
Then, run this:
```
git clone https://github.com/ksnow-be/lem_in.git; cd lem-in; make;
```

**Этот проект сделал на [`MacOs`], следовательно все правила в Makefile будут корректны на этой платформе**

## Usage Для визуализации предложенны 6 карт, находящиеся в папке vismaps/. Но есть специальный скрипт который 
запускает их по очереди(vis.sh).

## Информация о алгоритме

Алгоритм основан на построении графа и матрицы смежности его вершин. Далее происходит обход графа в ширину с конца с 
расставлением меток веса в каждой вершине. На основе весов происходит поиск путей. После нахождения всех путей 
удовлетворяющих критериям поиска, происходит группировка не пересекающихся путей.
