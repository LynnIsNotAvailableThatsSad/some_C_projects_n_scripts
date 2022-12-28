#include <stdio.h>

int width = 80;
int height = 25;
int xball = 40;
int yball = 11;
int racket_p_one = 10;
int racket_p_two = 10;
int dxball = 1;
int dyball = -1;
int move_ball();
int draw();
char move_rackets();
int win1 = 0;
int win2 = 0;
int winner1 = 0;
int winner2 = 0;


int draw() {
    printf("\33c\e[3J");
    int w, h;
     for (h = 0; h < height; h++) {
        for (w = 0; w < width; w++) {
      if (w == 0 || w == width-1 || h == 0 || h == height-1) {
         printf("#");
        } else if (h == 3 && ((win1 < 10 && w == 39) || (win2 < 10 && w == 41))) {
             if (w == 39) printf("%d", win1);
             if (w == 41) printf("%d", win2);
        } else if (h == 3 && ((win1 >= 10 && w == 37) || (win2 >= 10 && w == 41))) {
if(w == 37) printf("%d", win1);
if(w == 41) printf("%d", win2);
w++;
        } else if (w == 4 && (racket_p_one == h || racket_p_one + 1 == h || racket_p_one + 2 == h)) {
printf("[");
        } else if (w == 75 && (racket_p_two == h || racket_p_two + 1 == h || racket_p_two + 2 == h)) {
printf("[");
        } else if (w == xball && h == yball) {
    printf("o");
        } else {
    (printf(" "));
}
        }
        printf("\n");
    }
    return 0;
}

int move_ball() {
    xball += dxball;
    yball += dyball;

    if (yball == racket_p_one+3 && dyball == -1 && xball == 5) {
            dxball = - dxball;
            dyball = - dyball;
    } else if (xball == 5 && (yball == racket_p_one || yball == racket_p_one+1 || yball == racket_p_one+2)) {
             dxball = - dxball;
    } else if (yball == racket_p_one-1 && dyball == 1 && xball == 5) {
            dxball = - dxball;
            dyball = - dyball;
    }

    if (yball == racket_p_two+3 && dyball == -1 && xball == 74) {
            dxball = - dxball;
            dyball = - dyball;
    } else if (xball == 74 && (yball == racket_p_two || yball == racket_p_two+1 || yball == racket_p_two+2)) {
             dxball = - dxball;
    } else if (yball == racket_p_two-1 && dyball == 1 && xball == 74) {
            dxball = - dxball;
            dyball = - dyball;
    }
    if (yball == 1 || yball == 23) {
    dyball = - dyball;
    }
    if (xball == 1) {
        win2++;
        if (win2 == 1)
        winner2 = 1;
        xball = 5;
        yball = 11;
        dxball = -dxball;
        racket_p_one = 10;
        racket_p_two = 10;
    } else if (xball == 79) {
        win1++;
        if (win1 == 1)
        winner1 = 1;
        xball = 74;
        yball = 11;
        dxball = -dxball;
        racket_p_one = 10;
        racket_p_two = 10;
    }
    return 0;
}

char move_rackets() {
char up;

    if (scanf("%c", &up)) {
       if (up == 'a') {  // движение вверх правой ракетки
           if (racket_p_one == 1) {
               return 0;
            }
            racket_p_one += -1;
        } else if (up == 'z') {  // движение вниз правой ракетки
                  if (racket_p_one == 21) {
                       return 0;
                    }
                    racket_p_one += 1;
                } else if (up == 'k') {  // движение вверх левой ракетки
                          if (racket_p_two == 1) {
                               return 0;
                            }
                            racket_p_two += -1;
                        } else if (up == 'm') {  // движение вниз левой ракетки
                                    if (racket_p_two == 21) {
                                       return 0;
                                    }
                                    racket_p_two += 1;
                                 }
    }
    return 0;
}

int main() {
    for (int i = 0; win1 != 21 && win2 != 21; i++) {
        draw();
        move_ball();
        move_rackets();
    }
if (win1 == 21)
  printf("CONGRATS, PLAYER 1 WON!\n");
else
  printf("CONGRATS, PLAYER 2 WON!\n");
}

