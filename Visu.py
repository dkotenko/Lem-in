import pygame
import sys

WIDTH = 1280
HEIGHT = 720
FPS = 60
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)

str = sys.stdin.read()
lst = str.split()


def input_to_dict(data):
    d = {}
    a = 0
    for elem in data:
        ant_name, room_name = elem.split("-")
        if ant_name == "L1":
            a += 1
        if not ant_name in d and a < 2:
            d[ant_name] = []
        if ant_name in d:
            d[ant_name].append(room_name)
    return d


class Room():
    def __init__(self, x, y, radius, color, name):
        self.x = x
        self.y = y
        self.radius = radius
        self.color = color
        self.border = 1
        self.name = name

    def draw(self, win):
        pygame.draw.circle(win, self.color, (self.x, self.y), self.radius, self.border)
        pygame.draw.line(win, self.color, (self.x + self.radius, self.y), (self.x + self.radius + 10, self.y), self.border)
#        screen.blit(myfont.render(self.name, False, (255, 255, 255)), (self.x - 3, self.y - 12))


arr = list(input_to_dict(lst).values())
print(arr)

pygame.init()
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Lem-in")
clock = pygame.time.Clock()
pygame.font.init()
myfont = pygame.font.SysFont('Comic Sans MS', 15)

running = True

while running:
    rooms = []
    offsetX = 0
    offsetY = 0
    for elem in arr:
        offsetX = 0
        for i in elem:
            rooms.append(Room(50 + offsetX, 50 + offsetY, 20, WHITE, i))
            offsetX += 50
        offsetY += 50
    clock.tick(FPS)
    keys = pygame.key.get_pressed()
    if keys[pygame.K_ESCAPE]:
        running = False
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
    screen.fill(BLACK)
    offsetX = 0
    offsetY = 0
    pos_x = 0
    for room in rooms:
        room.draw(screen)
    pygame.display.update()
pygame.quit()