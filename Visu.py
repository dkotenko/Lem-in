import pygame
import sys

WIDTH = 1280
HEIGHT = 720
FPS = 60
BLACK = (0, 0, 0)

str = sys.stdin.read()
lst = str.split()

arr = []
# for elem in lst:
#     print(elem[0: elem.find('-')])

pygame.init()
pygame.display.init()
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Lem-in")
clock = pygame.time.Clock()

running = True

while running:
    clock.tick(FPS)
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
    screen.fill(BLACK)
pygame.quit()