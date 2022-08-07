import pygame
import math
import numpy as np
           
SCREEN_HEIGHT = 400
SCREEN_WIDTH = 400

tri = np.array([[0.0,0.0],[1.0,0.0],[0.5,1.0]])
rad = 30 / 180 * math.pi
mat2x2 = np.array([[math.cos(rad), math.sin(rad)], [-math.sin(rad), math.cos(rad)]])

def draw(mat, col):
    pts = np.zeros((3,2))
    pts[0][0] = mat[0][0] * SCREEN_WIDTH
    pts[0][1] = mat[0][1] * SCREEN_HEIGHT
    pts[1][0] = mat[1][0] * SCREEN_WIDTH
    pts[1][1] = mat[1][1] * SCREEN_HEIGHT
    pts[2][0] = mat[2][0] * SCREEN_WIDTH
    pts[2][1] = mat[2][1] * SCREEN_HEIGHT

    pygame.draw.polygon(screen,col,pts,1)        
    pygame.display.update()        

    
pygame.init()
screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption('2D Rotation')    

tri2 = np.zeros((3,2))
tri2[0] = np.dot(mat2x2, tri[0])
tri2[1] = np.dot(mat2x2, tri[1])
tri2[2] = np.dot(mat2x2, tri[2])

screen.fill((0, 0, 180))
draw(tri, (255,255,255))
draw(tri2,(0,255,255))

running = True
while running == True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

