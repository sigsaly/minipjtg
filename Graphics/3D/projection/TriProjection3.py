import pygame
import math, time
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
    theta = 0.0
    vCamera = np.zeros(3)

    def __init__(self):
        fNear = 0.1
        fFar = 100.0
        fFov = 50.0
        fAspectRatio = SCREEN_HEIGHT/SCREEN_WIDTH
        fFovRad = 1/math.tan(fFov * 0.5/180 * math.pi)

        self.mat4x4[0,0] = fAspectRatio * fFovRad
        self.mat4x4[1,1] = fFovRad
        self.mat4x4[2,2] = fFar / (fFar - fNear)
        self.mat4x4[3,2] = -fFar*fNear / (fFar - fNear)
        self.mat4x4[2,3] = 1.0
        self.mat4x4[3,3] = 0.0

    def multiplyMat(self, i, mat):
        '''
        o = np.zeros(3)
        o[0] = i[0] * mat[0,0] + i[1] * mat[1,0] + i[2] * mat[2,0] + mat[3,0]
        o[1] = i[0] * mat[0,1] + i[1] * mat[1,1] + i[2] * mat[2,1] + mat[3,1]
        o[2] = i[0] * mat[0,2] + i[1] * mat[1,2] + i[2] * mat[2,2] + mat[3,2]
        '''
        o = np.dot(i,mat[:3, :3])
        w = i[0] * mat[0,3] + i[1] * mat[1,3] + i[2] * mat[2,3] + mat[3,3]

        if w != 0:
            o[0] = o[0]/w
            o[1] = o[1]/w
            o[2] = o[2]/w
        return o

    def draw(self, elaptime):
        screen.fill((0, 0, 180))

        # rotation matrix
        self.theta += elaptime
        #print(self.theta)
        thetaRad = self.theta * math.pi / 180.0 
        matRotZ = np.zeros((4,4))
        matRotX = np.zeros((4,4))

        matRotZ[0][0] = math.cos(thetaRad)
        matRotZ[0][1] = math.sin(thetaRad)
        matRotZ[1][0] = -math.sin(thetaRad)
        matRotZ[1][1] = math.cos(thetaRad)
        matRotZ[2][2] = 1
        matRotZ[3][3] = 1

        matRotX[0][0] = 1
        matRotX[1][1] = math.cos(thetaRad * 0.5)
        matRotX[1][2] = math.sin(thetaRad * 0.5)
        matRotX[2][1] = -math.sin(thetaRad * 0.5)
        matRotX[2][2] = math.cos(thetaRad * 0.5)
        matRotX[3][3] = 1

        # draw triangles
        rotz = np.zeros((3,3))
        rotx = np.zeros((3,3))
        projected = np.zeros((3,3))
        pointers = np.zeros((3,2))
        #print(pjtd)
        for tri in self.meshCube:
            rotz[0] = self.multiplyMat(tri[0], matRotZ) # point0 (x,y,z)
            rotz[1] = self.multiplyMat(tri[1], matRotZ) # point1
            rotz[2] = self.multiplyMat(tri[2], matRotZ) # point2

            rotx[0] = self.multiplyMat(rotz[0], matRotX) # point0 (x,y,z)
            rotx[1] = self.multiplyMat(rotz[1], matRotX) # point1
            rotx[2] = self.multiplyMat(rotz[2], matRotX) # point2

            # add offset to z axis
            rotx[0][2] = rotx[0][2] + 3
            rotx[1][2] = rotx[1][2] + 3
            rotx[2][2] = rotx[2][2] + 3

            # get the normal unit vector
            line1 = np.zeros(3)
            line2 = np.zeros(3)
            normal = np.zeros(3)

            line1[0] = rotx[1][0] - rotx[0][0] 
            line1[1] = rotx[1][1] - rotx[0][1] 
            line1[2] = rotx[1][2] - rotx[0][2] 

            line2[0] = rotx[2][0] - rotx[0][0] 
            line2[1] = rotx[2][1] - rotx[0][1] 
            line2[2] = rotx[2][2] - rotx[0][2] 

            normal[0] = line1[1] * line2[2] - line1[2] * line2[1]
            normal[1] = line1[2] * line2[0] - line1[0] * line2[2]
            normal[2] = line1[0] * line2[1] - line1[1] * line2[0]

            l = math.sqrt(normal[0]*normal[0] + normal[1]*normal[1] + normal[2]*normal[2])
            normal[0] /= l
            normal[1] /= l
            normal[2] /= l
            #print(normal)

            #if normal[2] < 0:
            if (normal[0]*(rotx[0][0]-self.vCamera[0])
                +normal[1]*(rotx[0][1]-self.vCamera[1])
                +normal[2]*(rotx[0][2]-self.vCamera[2]) < 0.0):

                projected[0] = self.multiplyMat(rotx[0], self.mat4x4) # point0 (x,y,z)
                projected[1] = self.multiplyMat(rotx[1], self.mat4x4) # point1
                projected[2] = self.multiplyMat(rotx[2], self.mat4x4) # point2

                pointers[0][0] = (projected[0][0] + 1.0) * 0.5 * SCREEN_WIDTH
                pointers[0][1] = (projected[0][1] + 1.0) * 0.5 * SCREEN_HEIGHT
                pointers[1][0] = (projected[1][0] + 1.0) * 0.5 * SCREEN_WIDTH
                pointers[1][1] = (projected[1][1] + 1.0) * 0.5 * SCREEN_HEIGHT
                pointers[2][0] = (projected[2][0] + 1.0) * 0.5 * SCREEN_WIDTH
                pointers[2][1] = (projected[2][1] + 1.0) * 0.5 * SCREEN_HEIGHT
                #print(ptrs)

                pygame.draw.polygon(screen,(255,255,255),pointers,1)    
        pygame.display.update()        
        return True
   
pygame.init()
screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption('Simple Triangle Projection')    

engine = SimpleEngine3D()
running = True
cnt = 0.0
while running == True:
    engine.draw(1)
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
    time.sleep(0.01)

    

