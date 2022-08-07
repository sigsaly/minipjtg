import numpy as np
import pygame
import random
import time

# up, down, left, right
env = [
     [[None, None, None, None],[None, 0, None, None],[None, None, None, None],[None, None, None, None],[None, None, None, None],
    [None, None, None, None],[None, None, None, None],[None, None, None, None],[None, None, None, None],
    [None, None, None, None],[None, None, None, None],[None, None, None, None],[None, None, None, None],
    [None, None, None, None],[None, None, None, None],[None, None, None, None],[None, None, None, None],
    [None, None, None, None],[None, None, None, None],[None, None, None, None],[None, None, None, None],[None, None, None, None]],

    [[None, None, None, None],[None, 0, None, 0],[None, None, 0, 0],[None, None, 0, 0],[None, 0, 0, None],
    [None, None, None, None],[None, 0, None, 0],[None, None, 0, 0],[None, None, 0, 0],
    [None, None, 0, 0],[None, 0, 0, 0],[None, None, 0, None],[None, None, None, None],
    [None, 0, None, 0],[None, None, 0, 0],[None, None, 0, 0],[None, None, 0, 0],
    [None, None, 0, 0],[None, 0, 0, None],[None, None, None, None],[None, 0, None, None],[None, None, None, None]],
    
    [[None, None, None, None],[0, 0, None, None],[None, None, None, None],[None, None, None, None],[0, 0, None, None],
    [None, None, None, None],[0, 0, None, None],[None, None, None, None],[None, None, None, None],
    [None, None, None, None],[0, 0, None, None],[None, None, None, None],[None, None, None, None],
    [0, 0, None, None],[None, None, None, None],[None, None, None, None],[None, None, None, None],
    [None, None, None, None],[0, 0, None, None],[None, None, None, None],[0, 0, None, None],[None, None, None, None]],

    [[None, None, None, None],[0, 0, None, None],[None, None, None, None],[None, None, None, 0],[0, None, 0, None],
    [None, None, None, None],[0, None, None, 0],[None, None, 0, 0],[None, 0, 0, None],
    [None, None, None, None],[0, None, None, 0],[None, None, 0, 0],[None, None, 0, 0],
    [0, 0, 0, None],[None, None, None, None],[None, 0, None, None],[None, None, None, None],
    [None, 0, None, 0],[0, None, 0, None],[None, None, None, None],[0, 0, None, None],[None, None, None, None]],

    [[None, None, None, None],[0, 0, None, None],[None, None, None, None],[None, None, None, None],[None, None, None, None],
    [None, None, None, None],[None, None, None, None],[None, None, None, None],[0, 0, None, None],
    [None, None, None, None],[None, None, None, None],[None, None, None, None],[None, None, None, None],
    [0, 0, None, None],[None, None, None, None],[0, 0, None, None],[None, None, None, None],
    [0, 0, None, None],[None, None, None, None],[None, None, None, None],[0, 0, None, None],[None, None, None, None]],

    [[None, None, None, None],[0, None, None, 0],[None, None, 0, 0],[None, 0, 0, None],[None, None, None, None],
    [None, 0, None, 0],[None, None, 0, None],[None, None, None, None],[0, 0, None, 0],
    [None, None, 0, 0],[None, None, 0, 0],[None, 0, 0, None],[None, None, None, None],
    [0, None, None, 0],[None, None, 0, 0],[0, None, 0, None],[None, None, None, None],
    [0, 0, None, None],[None, None, None, None],[None, 0, None, 0],[0, None, 0, None],[None, None, None, None]],

    [[None, None, None, None],[None, None, None, None],[None, None, None, None],[0, 0, None, None],[None, None, None, None],
    [0, 0, None, None],[None, None, None, None],[None, None, None, None],[0, 0, None, None],
    [None, None, None, None],[None, None, None, None],[0, 0, None, None],[None, None, None, None],
    [None, None, None, None],[None, None, None, None],[None, None, None, None],[None, None, None, None],
    [0, 0, None, None],[None, None, None, None],[0, 0, None, None],[None, None, None, None],[None, None, None, None]],

    [[None, None, None, None],[None, 0, None, 0],[None, None, 0, 0],[0, None, 0, 0],[None, None, 0, 0],
    [0, None, 0, None],[None, None, None, None],[None, 0, None, 0],[0, None, 0, 0],   
    [None, 0, 0, None],[None, None, None, None],[0, None, None, 0],[None, None, 0, None],
    [None, None, None, None],[None, 0, None, 0],[None, None, 0, 0],[None, None, 0, 0],
    [0, None, 0, 0],[None, None, 0, 0],[0, None, 0, 0],[None, None, 0, None],[None, None, None, None]],

    [[None, None, None, None],[0, 0, None, None],[None, None, None, None],[None, None, None, None],[None, None, None, None],
    [None, None, None, None],[None, None, None, None],[0, 0, None, None],[None, None, None, None],
    [0, 0, None, None],[None, None, None, None],[None, None, None, None],[None, None, None, None],
    [None, None, None, None],[0, 0, None, None],[None, None, None, None],[None, None, None, None],
    [None, None, None, None],[None, None, None, None],[None, None, None, None],[None, None, None, None],[None, None, None, None]],

    [[None, None, None, None],[0, None, None, 0],[None, None, 0, 0],[None, None, 0, 0],[None, None, 0, 0],
    [None, None, 0, 0],[None, None, 0, 0],[0, None, 0, None],[None, None, None, None],
    [0, None, None, 0],[None, None, 0, None],[None, None, None, None],[None, None, None, 0],
    [None, None, 0, 0],[0, None, 0, 0],[None, None, 0, 0],[None, None, 0, 0],
    [None, None, 0, 0],[None, None, 0, 0],[None, None, 0, 0],[None, 100, 0, None],[None, None, None, None]],

    [[None, None, None, None],[None, None, None, None],[None, None, None, None],[None, None, None, None],[None, None, None, None],
    [None, None, None, None],[None, None, None, None],[None, None, None, None],[None, None, None, None],
    [None, None, None, None],[None, None, None, None],[None, None, None, None],[None, None, None, None],
    [None, None, None, None],[None, None, None, None],[None, None, None, None],[None, None, None, None],
    [None, None, None, None],[None, None, None, None],[None, None, None, None],[None, 0, None, None],[None, None, None, None]],
]

env = np.array(env)
q_table = np.copy(env)
q_table[q_table == None] = -1
q_table[q_table > 0] = 0
q_table = q_table.astype('float64')
           
MAZE_SIZE_X = 22 
MAZE_SIZE_Y = 11 
ENTRY_POS = [0,1]
EXIT_POS = [10,20]
LEARNING_RATE = 0.7
DISCOUNT = 0.9
EPSILON = 0.3

def getActions(s):
    [y, x] = s
    a = [d != None for d in env[y, x]]
    actions = []
    if a[0]:
        actions.append(0) # up    
    if a[1]:
        actions.append(1) # down
    if a[2]:
        actions.append(2) # left   
    if a[3]:
        actions.append(3) # right
    return(actions)     

def getArgMaxActions(s):
    #print(q_table[s[0],s[1]])
    arr = q_table[s[0],s[1]]
    #print(np.random.choice(np.where(arr == arr.max())[0]))
    #return np.argmax(q_table[s[0],s[1]])
    return np.random.choice(np.where(arr == arr.max())[0])

def isGoalState(s):
    return (s == EXIT_POS)           

def getNextState(s, action):
    _s = list(s)
    if action == 0:
        #print('up')
        _s[0] = s[0] - 1
    elif action == 1:
        #print('down')
        _s[0] = s[0] + 1
    elif action == 2:
        #print('left')
        _s[1] = s[1] - 1
    else:
        #print('right')
        _s[1] = s[1] + 1
    return _s

def render(done):
    screen.fill((255, 255, 255))
    for y in range(MAZE_SIZE_Y):
        for x in range(MAZE_SIZE_X):
            if env[y,x,0] == None and env[y,x,1] == None and env[y,x,2] == None and env[y,x,3] == None:
                pygame.draw.rect(screen, (0,112,192), [30+x*30, 30+30*y, 30,30], 0)
            #    pygame.draw.rect(screen, (0,0,0), [50+i*50,50,50,50], 1)
            if q_table[y,x,0] > 0:
                col = 255 - int(q_table[y,x,0]/100.0 * 255)
                pygame.draw.polygon(screen,(255,col,col,150),[[30+x*30+10, 30+y*30+15], [30+x*30+15, 30+y*30+5], [30+x*30+20, 30+y*30+15]])
            if q_table[y,x,1] > 0:
                col = 255 - int(q_table[y,x,1]/100.0 * 255)
                pygame.draw.polygon(screen,(255,col,col,150),[[30+x*30+10, 30+y*30+15], [30+x*30+15, 30+y*30+25], [30+x*30+20, 30+y*30+15]])
            if q_table[y,x,2] > 0:
                col = 255 - int(q_table[y,x,2]/100.0 * 255)
                pygame.draw.polygon(screen,(255,col,col,150),[[30+x*30+5, 30+y*30+15], [30+x*30+15, 30+y*30+10], [30+x*30+15, 30+y*30+20]])
            if q_table[y,x,3] > 0:
                col = 255 - int(q_table[y,x,3]/100.0 * 255)
                pygame.draw.polygon(screen,(255,col,col,150),[[30+x*30+15, 30+y*30+10], [30+x*30+25, 30+y*30+15], [30+x*30+15, 30+y*30+20]])
            #col = 255 - int(q_table[y,x,1]/100.0 * 255)
            #pygame.draw.polygon(screen,(255,col,col),[[30+x*50+30, 50+10], [50+i*50+48, 50+25], [50+i*50+30, 50+40]])
    screen.blit(agentImg, (30+cur_pos[1]*30, 30+cur_pos[0]*30))
    if done:
        screen.blit(textDone, (100, 380))
    screen.blit(textEp, (30, 380))
    pygame.display.update()

pygame.init()

screen = pygame.display.set_mode((720, 420))
pygame.display.set_caption('Maze 2D')
agentImg = pygame.image.load('RL\RL1\mouse30.png')
#exitImg = pygame.image.load('RL\RL1\exit.png')
fontDone = pygame.font.SysFont("arial", 20, True, False)
textDone = fontDone.render("Done", True, (255, 0,0))
fontEp = pygame.font.SysFont("arial", 20, True, False)

running = True
while running:
    for ep in range(1000):
        print('ep:', ep)
        if running == False:
            break
        cur_pos = ENTRY_POS
        while not isGoalState(cur_pos) and running:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    running = False 
            possible_actions = getActions(cur_pos)
            #print(cur_pos, possible_actions)
            eps = random.random()
            if eps < EPSILON:
                action = random.choice(possible_actions)
            else:
                action = getArgMaxActions(cur_pos)
            #print(action)
            next_state = getNextState(cur_pos, action)
            #print(cur_pos)
            #print(next_state)
            #print(q_table[cur_pos[0], cur_pos[1], action])
            #print(np.max(q_table[next_state[0], next_state[1]]))
            #print(env[cur_pos[0], cur_pos[1], action])
            q_table[cur_pos[0], cur_pos[1], action] = q_table[cur_pos[0], cur_pos[1], action] + LEARNING_RATE * (env[cur_pos[0], cur_pos[1], action] + 
                DISCOUNT * np.max(q_table[next_state[0], next_state[1]]) - q_table[cur_pos[0], cur_pos[1], action])
            #print(q_table[cur_pos[0], cur_pos[1], action])
            cur_pos = next_state        
            textEp = fontEp.render("EP: " + str(ep), True, (0,180,0))            

            if ep % 50 == 0:
            #if ep > 10:
                render(isGoalState(cur_pos))
                time.sleep(0.06)

    print(q_table)
    while running:
        render(isGoalState(cur_pos))
        time.sleep(0.1)
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False 
