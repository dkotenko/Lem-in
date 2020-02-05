import pygame
from enum import Enum

WIDTH = 1800
HEIGHT = 800
FPS = 60
SPEED = 20
OFFSET = 50
TURN_PARTS = 4
QUANT = TURN_PARTS * FPS

STATE = 'running'

# Задаем цвета
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLUE = (0, 0, 255)
YELLOW = (255, 255, 0)

BG_COLOR = pygame.Color('gray12')
PLAYER_IMG = pygame.Surface((30, 50), pygame.SRCALPHA)
pygame.draw.polygon(PLAYER_IMG, pygame.Color('dodgerblue'), [(0, 50), (15, 0), (30, 50)])
ENEMY_IMG = pygame.Surface((50, 30))
ENEMY_IMG.fill(pygame.Color('darkorange1'))
BULLET_IMG = pygame.Surface((9, 15))
BULLET_IMG.fill(pygame.Color('aquamarine2'))



#LEMIN VARS
TURN = 0


class Rooms:
	def __init__(self):
		self.rooms = {}
		self.current_size = 0

	def add_room(self, name, pos_x, pos_y, size):
		new_room = Room(name, pos_x, pos_y, size)
		self.rooms[name] = new_room
		self.current_size += 1
		return new_room

	def get_room_by_name(self, room_name):
		for room in self.rooms:
			if room.name == room_name:
				return room


class Room(pygame.sprite.Sprite):
	def __init__(self, name, pos_x, pos_y, size):
		pygame.sprite.Sprite.__init__(self)
		self.name = name
		self.image = pygame.Surface((size, size))
		self.image.fill(GREEN)
		self.rect = self.image.get_rect()
		self.rect.centerx = pos_x
		self.rect.centery = pos_y
		pass


class Paths:
	def __init__(self, paths_list):
		self.paths_list = []
		self.paths = []
		self.current_path = 0
		self.size = len(paths_list)
		self.max_path_size = max(len(x) for x in paths_list)

	def add_path(self, path):
		new_path = Path(path)
		self.paths.append(new_path)
		self.paths_list.append(path)
		self.current_path += 1
		return new_path

	def get_path_by_1st_room(self, first_room):
		needed_path = None
		for i in range(self.size):
			if self.paths[i].rooms_list[0] == first_room:
				needed_path = self.paths[i]
				return needed_path


class Path:
	def __init__(self, path):
		self.rooms_list = path
		self.rooms = []
		self.current_room = 0
		self.size = len(path)
		self.way = []
		self.way_size = 0

	def count_way_coords(self, start_room):
		way_coords = []
		room_base = start_room
		for room in self.rooms:
			deltax_per_quant = (room.rect.x - room_base.rect.x) / QUANT
			deltay_per_quant = (room.rect.y - room_base.rect.y) / QUANT
			roomx = room_base.rect.x
			roomy = room_base.rect.y
			for i in range(QUANT):
				roomx += deltax_per_quant
				roomy += deltay_per_quant
				way_coords.append((roomx, roomy))
			room_base = room
		self.way_size = len(way_coords)
		self.way = way_coords
		return way_coords

	def add_room(self, room_obj):
		self.rooms.append(room_obj)
		self.current_room += 1

class Ants:
	def __init__(self):
		self.ants_list = []
		self.ants = []
		self.current_ant = 0

	def add_ant(self, turn, path, start_room):
		new_ant = Ant(turn, path, start_room)		
		self.ants.append(new_ant)		
		self.current_ant += 1
		return new_ant
	
	def next_move(self):
		for ant in self.ants:
			ant.current_way += QUANT // SPEED
	
	def prev_move(self):
		for ant in self.ants:
			ant.current_way -= QUANT // SPEED
		

class Ant(pygame.sprite.Sprite):
	def __init__(self, turn, path, start_room):
		pygame.sprite.Sprite.__init__(self)
		#self.image = pygame.transform.scale(SPHERE_IMG, (15, 15))
		self.path = path
		self.turn = turn
		self.current_way = 0
		self.image = pygame.Surface((5, 5))
		self.image.fill(RED)
		self.rect = self.image.get_rect(center = (20,20))
		self.rect.x = start_room.rect.x
		self.rect.y = start_room.rect.y

	def update(self):
		#print(self.turn, TURN)
		if (TURN >= self.turn):
			self.current_way += 1
			if self.current_way * SPEED >= self.path.way_size:
				self.turn = 0x7fffffff
				self.kill()
				return
			elif self.current_way < 0:
				self.current_way = 0
				return

			self.rect.x, self.rect.y = \
				self.path.way[self.current_way * SPEED]

def get_rooms_from_paths(paths_list):
	rooms_list = [list(x) for x in set(tuple(x) for x in paths_list)]
	return rooms_list

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

def input_to_dict2(lst):
	d = {}
	for elem in lst:
		ant_name, room_name = elem.split("-")
		if not ant_name in d:
			d[ant_name] = []
		d[ant_name].append(room_name)
	return d

def get_input():
	#str = sys.stdin.read()
	f = open("input.txt", "r")
	str = f.read()
	f.close()
	return str

def get_paths(str):
	lines = str.split()
	paths_input = list(input_to_dict2(lines).values())
	paths_unique = list(set(map(tuple, paths_input)))
	return paths_unique



# Создаем игру и окно
pygame.init()

screen = pygame.display.set_mode((WIDTH, HEIGHT))
SPHERE_IMG = pygame.image.load("preview1.jpg").convert_alpha()
pygame.display.set_caption("1")
clock = pygame.time.Clock()
#все спрайты
all_sprites = pygame.sprite.Group()
#комнаты
room_sprites = pygame.sprite.Group()
rooms = Rooms()

#создаем объект Paths
input_str = get_input()
paths_list = get_paths(input_str)
paths_list.sort(key=lambda x: len(x))
rooms_list = get_rooms_from_paths(paths_list)
paths = Paths(paths_list)
#ROOM_START ROOM_END

end_room_name = paths_list[0][-1]
room_start = Room("start", OFFSET, HEIGHT / 2, 10)
room_end = rooms.add_room(end_room_name, WIDTH - OFFSET, HEIGHT / 2, 10)
room_sprites.add(room_start)
all_sprites.add(room_start)
room_sprites.add(room_end)
all_sprites.add(room_end)


#размер комнаты в зависимости от количества путей
room_size = (WIDTH - 4 * OFFSET) / (paths.max_path_size - 2) / 10
i = 0

# создаем объекты путей и комнат
for path_list in paths_list:
	path_len = len(path_list)
	j = 0
	path_obj = paths.add_path(path_list)
	room_offset_x = (WIDTH - 8 * OFFSET) / (path_len - 2)
	room_offset_y = (HEIGHT - 4 * OFFSET) / (paths.size - 1)
	for room in path_list:
		if j == path_len - 1:
			continue
		room_new = rooms.add_room(room,
						4 * OFFSET + j * room_offset_x,
						2 * OFFSET + i * room_offset_y,
						room_size)
		all_sprites.add(room_new)
		room_sprites.add(room_new)
		j += 1
		path_obj.add_room(room_new)
	i += 1
	path_obj.add_room(room_end)
	path_obj.count_way_coords(room_start)


#создаем муравьев
def get_ants_first_room_n_turn(ants_number, input):
	lines = input_str.splitlines()
	l = 1
	lines_counter = 0
	turn_counter = 1
	ants_first_room_list = []
	ants_first_turn = []
	for line in lines:
		line_splitted =  line.split()
		lines_counter += 1
		turn_counter += 1
		for move in line_splitted:
			if move.find('L' + str(l)) > -1:
				ants_first_room_list.append(move.split('-')[1])
				ants_first_turn.append(turn_counter)
				l += 1
	return ants_first_room_list, ants_first_turn
#добавляем муравьев в группу спрайтов муравьев, не используется
ant_sprites = pygame.sprite.Group()

ants_number = 230

ants_first_room_list, ants_first_turn = \
	get_ants_first_room_n_turn(ants_number, input)
ants = Ants()
for i in range(ants_number):
	
	ant = ants.add_ant(ants_first_turn[i],
			  paths.get_path_by_1st_room(ants_first_room_list[i]),
			  room_start)
	ant_sprites.add(ant)
	all_sprites.add(ant)

#время в игре
start_time =  pygame.time.get_ticks()
prev_time = 0

#отобразить все изменения в одной функции
def draw_game():
	all_sprites.update()
	screen.fill(BLACK)
	all_sprites.draw(screen)
	pygame.display.flip()
	return

# Цикл игры
running = True
while running:
	# Ввод процесса (события)
	for event in pygame.event.get():
	# проверка для закрытия окна

		if event.type == pygame.QUIT:
			running = False
		elif event.type == pygame.KEYDOWN:
			if event.key == pygame.K_ESCAPE:
				running = False
			elif event.key == pygame.K_SPACE:
				if STATE == 'running':
					STATE = 'pause'
				elif STATE == 'pause':
					STATE = 'running'

	#клавиши увеличения/уменьшения скорости игры, не работают
			# elif event.key == pygame.K_EQUALS:
			# 	SPEED += 1
			# elif event.key == pygame.K_MINUS:
			# 	SPEED -= 1

	#клавиши следующего/предыдущено хода по нажатию/удержанию, не работают
	# keys = pygame.key.get_pressed()
	# if STATE == 'pause':
	# 	if keys[pygame.K_RIGHT]:
	# 		TURN += 1
	# 		ants.next_move()
	# 		draw_game()
	# 	elif keys[pygame.K_LEFT]:
	# 		TURN -= 1
	# 		ants.prev_move()
	# 		draw_game()

# пока пауза - выводим текущее состояние
	if STATE == "pause":
		all_sprites.draw(screen)
		continue

	# Рендеринг
	draw_game()

	# Держим цикл на правильной скорости
	clock.tick(FPS)
	#счетчик ходов
	time_since_enter = pygame.time.get_ticks() - start_time

	if time_since_enter // (1000 * TURN_PARTS // SPEED) > prev_time:
		TURN += 1
		prev_time = time_since_enter // (1000 * TURN_PARTS // SPEED)
#выход
pygame.quit()




