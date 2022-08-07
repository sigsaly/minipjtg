import pygame
import math
import numpy as np
           
SCREEN_HEIGHT = 500
SCREEN_WIDTH = 700

class SimpleEngine3D():
    meshCube = np.array([
        [[0.,0.,0.],[0.,1.,0.],[1.,1.,0.]], [[0.,0.,0.],[1.,1.,0.],[1.,0.,0.]], #south
        [[1.,0.,0.],[1.,1.,0.],[1.,1.,1.]], [[1.,0.,0.],[1.,1.,1.],[1.,0.,1.]], #east
        [[1.,0.,1.],[1.,1.,1.],[0.,1.,1.]], [[1.,0.,1.],[0.,1.,1.],[0.,0.,1.]], #north
        [[0.,0.,1.],[0.,1.,1.],[0.,1.,0.]], [[0.,0.,1.],[0.,1.,0.],[0.,0.,0.]], #west
        [[0.,1.,0.],[0.,1.,1.],[1.,1.,1.]], [[0.,1.,0.],[1.,1.,1.],[1.,1.,0.]], #top
        [[1.,0.,1.],[0.,0.,1.],[0.,0.,0.]], [[1.,0.,1.],[0.,0.,0.],[1.,0.,0.]], #bottom
    ])

    mat4x4 = np.zeros((4,4))

    def __init__(self):
        fNear = 0.1
        fFar = 1000.0
        fFov = 90.0
        fAspectRatio = SCREEN_HEIGHT/SCREEN_WIDTH
        fFovRad = 1/math.tan(fFov * 0.5/180 * math.pi)

        self.mat4x4[0,0] = fAspectRatio * fFovRad
        self.mat4x4[1,1] = fFovRad
        self.mat4x4[2,2] = fFar / (fFar - fNear)
        self.mat4x4[3,2] = -fFar*fNear / (fFar - fNear)
        self.mat4x4[2,3] = 1.0
        self.mat4x4[3,3] = 0.0

    def multiplyMat(self, i, mat):
        o = np.zeros(3)
        o[0] = i[0] * mat[0,0] + i[1] * mat[1,0] + i[2] * mat[2,0] + mat[3,0]
        o[1] = i[0] * mat[0,1] + i[1] * mat[1,1] + i[2] * mat[2,1] + mat[3,1]
        o[2] = i[0] * mat[0,2] + i[1] * mat[1,2] + i[2] * mat[2,2] + mat[3,2]
        w = i[0] * mat[0,3] + i[1] * mat[1,3] + i[2] * mat[2,3] + mat[3,3]

        if w != 0:
            o[0] = o[0]/w
            o[1] = o[1]/w
            o[2] = o[2]/w
        return o

    def draw(self, elaptime):
        screen.fill((0, 0, 180))
        # draw triangles
        pjtd = np.zeros((3,3))
        ptrs = np.zeros((3,2))
        print(pjtd)
        for tri in self.meshCube:
            # add offset to z axis
            tri[0][2] = tri[0][2] + 3
            tri[1][2] = tri[1][2] + 3
            tri[2][2] = tri[2][2] + 3

            pjtd[0] = self.multiplyMat(tri[0], self.mat4x4) # point0 (x,y,z)
            pjtd[1] = self.multiplyMat(tri[1], self.mat4x4) # point1
            pjtd[2] = self.multiplyMat(tri[2], self.mat4x4) # point2
            ptrs[0][0] = (pjtd[0][0] + 1.0) * 0.5 * SCREEN_WIDTH
            ptrs[0][1] = (pjtd[0][1] + 1.0) * 0.5 * SCREEN_HEIGHT
            ptrs[1][0] = (pjtd[1][0] + 1.0) * 0.5 * SCREEN_WIDTH
            ptrs[1][1] = (pjtd[1][1] + 1.0) * 0.5 * SCREEN_HEIGHT
            ptrs[2][0] = (pjtd[2][0] + 1.0) * 0.5 * SCREEN_WIDTH
            ptrs[2][1] = (pjtd[2][1] + 1.0) * 0.5 * SCREEN_HEIGHT
            print(ptrs)

            pygame.draw.polygon(screen,(255,255,255),ptrs,1)    
        pygame.display.update()        
        return True

    
pygame.init()
screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption('Simple Triangle Projection')    

engine = SimpleEngine3D()
engine.draw(0)

running = True
while running == True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

