import pygame
import random
import time

env = [[None, 0],[0, 0],[0, 0],[0, 0],[0, 0],[0, 0],[0, 100],[0, 0],[100, 0],[0, None]]
q_table = [[0, 0],[0, 0],[0, 0],[0, 0],[0, 0], [0, 0],[0, 0],[0, 0],[0, 0],[0, 0]]

MAZE_SIZE = 10
EXIT_POS = 7
LEARNING_RATE = 0.7
DISCOUNT = 0.8
EPSILON = 0.3

def getActions(s):
    a = [x != None for x in env[s]]
    actions = []
    if a[0]:
        actions.append(0)    
    if a[1]:
        actions.append(1)
    return(actions)     

def getArgMaxActions(s):
    a = env[s]
    b = q_table[s]
    if a[0] == None:
        return 1
    elif a[1] == None:
        return 0
    if b[0] > b[1]:
        return 0
    else:
        return 1

def isGoalState(s):
    return (s == 7)           

def getNextState(s, action):
    if action == 0:
        return s - 1
    else:
        return s + 1   

def render(done):
    screen.fill((255, 255, 255))
    for i in range(MAZE_SIZE):
        pygame.draw.rect(screen, (0,0,0), [50+i*50,50,50,50], 1)
        col = 255 - int(q_table[i][0]/100.0 * 255)
        pygame.draw.polygon(screen,(255,col,col),[[50+i*50+20, 50+10], [50+i*50+2, 50+25], [50+i*50+20, 50+40]])
        col = 255 - int(q_table[i][1]/100.0 * 255)
        pygame.draw.polygon(screen,(255,col,col),[[50+i*50+30, 50+10], [50+i*50+48, 50+25], [50+i*50+30, 50+40]])
    screen.blit(exitImg, (51+EXIT_POS*50,51))
    screen.blit(agentImg, (51+cur_pos*50,51))
    if done:
        screen.blit(textDone, (51, 105))
    screen.blit(textEp, (51, 25))
    pygame.display.update()

pygame.init()

screen = pygame.display.set_mode((600, 150))
pygame.display.set_caption('Maze 1D')
agentImg = pygame.image.load('RL\RL1\mouse.png')
exitImg = pygame.image.load('RL\RL1\exit.png')
fontDone = pygame.font.SysFont("arial", 30, True, False)
textDone = fontDone.render("Done", True, (255, 0,0))
fontEp = pygame.font.SysFont("arial", 20, True, False)

running = True
while running:
    for ep in range(1000):
        cur_pos = random.choice([0,1,2,3,4,5,6,7,8,9])
        if running == False:
            break
        while not isGoalState(cur_pos):
            possible_actions = getActions(cur_pos)
            eps = random.random()
            if eps < EPSILON:
                action = random.choice(possible_actions)
            else :
                action = getArgMaxActions(cur_pos)
            next_state = getNextState(cur_pos, action)
            q_table[cur_pos][action] = q_table[cur_pos][action] + LEARNING_RATE * (env[cur_pos][action] + 
                DISCOUNT * max(q_table[next_state]) - q_table[cur_pos][action])
            cur_pos = next_state        
            textEp = fontEp.render("EP: " + str(ep), True, (0,255,0))            
            render(isGoalState(cur_pos))
            time.sleep(0.05)
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    running = False 
                    break            
    running = False
print(q_table)