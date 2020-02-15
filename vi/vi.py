import pygame
from enum import Enum
import sys

WIDTH = 1800
HEIGHT = 800
FPS = 15
OFFSET = 50
TURN_PARTS = 4
TIME_IN_SECONDS = 0
QUANT = TURN_PARTS * FPS
#LEMIN VARS
TURN = 0


STATE = 'running'

# Задаем цвета
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLUE = (0, 0, 255)
YELLOW = (255, 255, 0)
BEIGE = (235, 200, 178)

BG_COLOR = pygame.Color('gray12')
PLAYER_IMG = pygame.Surface((30, 50), pygame.SRCALPHA)
pygame.draw.polygon(PLAYER_IMG, pygame.Color('dodgerblue'), [(0, 50), (15, 0), (30, 50)])
ENEMY_IMG = pygame.Surface((50, 30))
ENEMY_IMG.fill(pygame.Color('darkorange1'))
BULLET_IMG = pygame.Surface((9, 15))
BULLET_IMG.fill(pygame.Color('aquamarine2'))




class Speed():
	def __init__(self, speed_val):		
		self.speed_tuple = ((60, 0.25), (15, 1), (5, 3), (3, 5))
		self.speed_choice = speed_val
		print('speed arg = ' + str(self.speed_choice), ', speed x' + str(self.speed_tuple[self.speed_choice][1]))
		self.speed = self.speed_tuple[self.speed_choice][0]
		self.delta_turn = self.speed_tuple[self.speed_choice][1]

	def speed_increase(self):
		if self.speed_choice < len(self.speed_tuple) - 1:
			self.speed_choice += 1
			print(self.speed_choice)

	def speed_decrease(self):
		if self.speed_choice > 0:
			self.speed_choice -= 1
			print(self.speed_choice)	

	def get_speed(self):
		return 'x%.2f' % self.delta_turn

	def __repr__(self):
		return 'SPEED = %d' % self.speed

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
		self.image.fill(WHITE)
		self.rect = self.image.get_rect(x = pos_x, y = pos_y)
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

	def count_way_coords(self, start_room, room_start):
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
		self.image.fill(BLACK)
		self.rect = self.image.get_rect(center = (20,20))
		self.rect.x = start_room.rect.x
		self.rect.y = start_room.rect.y

	def update(self):
		#print(self.turn, TURN)
		if (int(TURN) >= self.turn):
			self.current_way += 1			
			if self.current_way * QUANT // speed.speed >= self.path.way_size:
				self.turn = 0x7fffffff
				self.kill()
				return
			elif self.current_way < 0:
				self.current_way = 0
				return
			self.rect.x, self.rect.y = \
				self.path.way[self.current_way * QUANT // speed.speed]
			self.rect.x += room_size / 2
			self.rect.y += room_size / 2

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
	if sys.argv == 2:	
		f = open(sys.argv[1], "r")
		s = f.read()		
		f.close()
	else:
		s = sys.stdin.read()		
	return s

def get_paths(s):	
	lines = s.split()	
	paths_input = list(input_to_dict2(lines).values())
	paths_unique = list(set(map(tuple, paths_input)))	
	return paths_unique

def	handle_error(error):
	print(handle_error)
	exit()
	return 

def get_ants_number(input):
	first_row = ''
	if not input:
		exit()		
		first_row = input[:input.find(' ')]	
		if first_row != "ERROR":
			exit()
		else:
			handle_error()
	number = int(input[:input.find('\n')])
	return number

speed_val = 2
if len(sys.argv) != 2:	
	print ('invalid speed arg. Pass a number from 0 to 3')
	exit()
else:
	try:
		speed_val = int(sys.argv[1])
		if speed_val not in range(0,4):
			print('argument passed not in ragne 0-3. Speed arg set to 2 (x3)')
			speed_val = 2		
	except ValueError:
		print ('Please enter speed value as INT from 0 to 3')
		exit()
speed = Speed(speed_val)

# Создаем игру и окно
pygame.init()

screen = pygame.display.set_mode((WIDTH, HEIGHT))
#SPHERE_IMG = pygame.image.load("preview1.jpg").convert_alpha()
pygame.display.set_caption("1")
clock = pygame.time.Clock()
#все спрайты
all_sprites = pygame.sprite.Group()
#комнаты
room_sprites = pygame.sprite.Group()
rooms = Rooms()

#создаем объект Paths
input_str = get_input()
ants_number = get_ants_number(input_str)
input_str = input_str[input_str.find('\nL1-') + 1 : ]
paths_list = get_paths(input_str)

paths_list.sort(key=lambda x: len(x))
rooms_list = get_rooms_from_paths(paths_list)
paths = Paths(paths_list)

#размер комнаты в зависимости от количества путей
room_size = (WIDTH - 4 * OFFSET) / (paths.max_path_size - 2) / 10
room_size = room_size if room_size <= 30 else 30

#ROOM_START ROOM_END

end_room_name = paths_list[0][-1]
room_start = Room("start", OFFSET, HEIGHT / 2, room_size)
room_end = rooms.add_room(end_room_name, WIDTH - OFFSET, HEIGHT / 2, room_size)
room_sprites.add(room_start)
all_sprites.add(room_start)
room_sprites.add(room_end)
all_sprites.add(room_end)




# создаем объекты путей и комнат
i = 0
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
	path_obj.count_way_coords(room_start, room_size)


#создаем муравьев
def get_ants_first_room_n_turn(ants_number, input):
	lines = input_str.splitlines()
	l = 1
	lines_counter = 0
	turn_counter = 0
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
#добавляем муравьев в группу спрайтов муравьев, группы спрайтов не используется
ant_sprites = pygame.sprite.Group()

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
start_time =  0
prev_time = 0

#отобразить все изменения в одной функции
def draw_game():	
	all_sprites.update()
	screen.fill(BEIGE)
	screen.blit(text_to_screen('TURN', BLACK),(50,50))
	screen.blit(text_to_screen(str(int(TURN)), WHITE),(150,50))
	screen.blit(text_to_screen('SPEED', BLACK),(250,50))
	screen.blit(text_to_screen(speed.get_speed(), WHITE),(400,50))
	screen.blit(text_to_screen('TIME', BLACK),(550,50))
	screen.blit(text_to_screen(str(TIME_IN_SECONDS), WHITE),(650,50))
	all_sprites.draw(screen)
	pygame.display.flip()
	return

def text_to_screen(text, color):
	text_on_screen = myfont.render(text, False, color)
	return text_on_screen
#вывод текста
myfont = pygame.font.SysFont('arialboldttf', 30)

seconds_counter = 0
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
			elif event.key == pygame.K_EQUALS:				
				speed.speed_choice += 1
			elif event.key == pygame.K_MINUS:
				speed.speed_choice -= 1

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
	start_time = pygame.time.get_ticks() if not start_time else start_time
	time_since_enter = pygame.time.get_ticks() - start_time
	#print(time_since_enter // 1000, TURN)	
	
	
	if time_since_enter // (1000) > prev_time:
		TIME_IN_SECONDS += 1                                                                                                                               
		prev_time = time_since_enter // (1000)

	if ant_sprites:
		TURN += speed.delta_turn / FPS
		
	
	
	
	



	
#выход
pygame.quit()




