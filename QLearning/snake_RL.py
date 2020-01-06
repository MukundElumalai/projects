import pygame
import sys
import time
import random

from pygame.locals import *

FPS = 5
pygame.init()
fpsClock=pygame.time.Clock()

SCREEN_WIDTH, SCREEN_HEIGHT = 160, 120
screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT), 0, 32)
surface = pygame.Surface(screen.get_size())
surface = surface.convert()
surface.fill((255,255,255))
clock = pygame.time.Clock()

pygame.key.set_repeat(1, 40)

GRIDSIZE=10
GRID_WIDTH = SCREEN_WIDTH / GRIDSIZE
GRID_HEIGHT = SCREEN_HEIGHT / GRIDSIZE
UP    = (0, -1)
DOWN  = (0, 1)
LEFT  = (-1, 0)
RIGHT = (1, 0)
   
screen.blit(surface, (0,0))

def draw_box(surf, color, pos):
    r = pygame.Rect((pos[0], pos[1]), (GRIDSIZE, GRIDSIZE))
    pygame.draw.rect(surf, color, r)

class Snake(object):
    def __init__(self):
        self.lose()
        self.color = (0,0,0)

    def get_head_position(self):
        return self.positions[0]

    def lose(self):
        self.length = 1
        self.positions =  [((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2))]
        self.direction = random.choice([UP, DOWN, LEFT, RIGHT])

    def point(self, pt):
        if self.length > 1 and (pt[0] * -1, pt[1] * -1) == self.direction:
            return
        else:
            self.direction = pt

    def move(self):
        cur = self.positions[0]
        x, y = self.direction
        new = (((cur[0]+(x*GRIDSIZE)) % SCREEN_WIDTH), (cur[1]+(y*GRIDSIZE)) % SCREEN_HEIGHT)
        if len(self.positions) > 2 and new in self.positions[2:]:
            self.lose()
        else:
            self.positions.insert(0, new)
            if len(self.positions) > self.length:
                self.positions.pop()
   
    def draw(self, surf):
        for p in self.positions:
            draw_box(surf, self.color, p)

class Apple(object):
    def __init__(self):
        self.position = (0,0)
        self.color = (255,0,0)
        self.randomize()

    def randomize(self):
        self.position = (random.randint(0, GRID_WIDTH-1) * GRIDSIZE, random.randint(0, GRID_HEIGHT-1) * GRIDSIZE)

    def draw(self, surf):
        draw_box(surf, self.color, self.position)

def check_eat(snake, apple):
    if snake.get_head_position() == apple.position:
        snake.length += 1
        apple.randomize()

def get_state(pt,apple):
    if pt[0]<=apple.position[0] and pt[1]<=apple.position[1]:
        return 0
    elif pt[0]<=apple.position[0] and pt[1]>apple.position[1]:
        return 1
    elif pt[0]>apple.position[0] and pt[1]<=apple.position[1]:
        return 2
    else:
        return 3
   
def find_newstate(snake,apple,pt):
    if snake.length > 1 and (pt[0] * -1, pt[1] * -1) == snake.direction:
        x,y=snake.direction
    else:
        x,y= pt
    cur = snake.positions[0]
    new = (((cur[0]+(x*GRIDSIZE)) % SCREEN_WIDTH), (cur[1]+(y*GRIDSIZE)) % SCREEN_HEIGHT)
    state=get_state(new,apple)
    if len(snake.positions) > 2 and new in snake.positions[2:]:
        return -10,state
    elif new==apple.position:
        return 10,state
    else:
        return -1,state
       
   
   

if __name__ == '__main__':
    snake = Snake()
    apple = Apple()
    qtable=[[0,0,0,0],[0,0,0,0],[0,0,0,0],[0,0,0,0]]
    state=0
    lr=0.75
    dr=0.34
    S=[(0, -1),(0, 1),(-1, 0),(1, 0)]
    while True:
        time.sleep(0.1)
        for event in pygame.event.get():
            if event.type == QUIT:
                pygame.quit()
                sys.exit()
            '''elif event.type == KEYDOWN:
                if event.key == K_UP:
                    snake.point(UP)
                elif event.key == K_DOWN:
                    snake.point(DOWN)
                elif event.key == K_LEFT:
                    snake.point(LEFT)
                elif event.key == K_RIGHT:
                    snake.point(RIGHT)'''
        state=get_state(snake.get_head_position(),apple)
        for i in range(4):
            r,ns=find_newstate(snake,apple,S[i])
            qtable[state][i]+=lr*(r+dr*(max(qtable[ns])-qtable[state][i]))
        maxi=0
        for i in range(1,4):
            if qtable[state][maxi]<qtable[state][i]:
                maxi=i
        snake.point(S[maxi])
        surface.fill((255,255,255))
        snake.move()
        check_eat(snake, apple)
        snake.draw(surface)
        apple.draw(surface)
        font = pygame.font.Font(None, 36)
        text = font.render(str(snake.length), 1, (10, 10, 10))
        textpos = text.get_rect()
        textpos.centerx = 20
        surface.blit(text, textpos)
        screen.blit(surface, (0,0))

        pygame.display.flip()
        pygame.display.update()
fpsClock.tick(FPS + snake.length/3)
