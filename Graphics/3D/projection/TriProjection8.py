#videoship

import pygame
import math, time
import numpy as np
           
SCREEN_HEIGHT = 500
SCREEN_WIDTH = 700

class Triangle():
    vts = []
    color = 0
    def __init__(self, _vts, _color = 0):
        self.vts = _vts    
        self.color = _color

class Mesh():
    meshCube = []
    def loadFromObjFile(self, path):
        f = open(path)
        count = 0
        verts = []
        while True:
            count += 1       
            line = f.readline()       
            if not line:
                break
            a = line.split()            
            if a[0] == 'v':
                v = [float(a[1]), float(a[2]), float(a[3]), 1]
                verts.append(v)
            if a[0] == 'f':
                v = [verts[int(a[1])-1], verts[int(a[2])-1], verts[int(a[3])-1]]
                self.meshCube.append(Triangle(v))
        self.meshCube = np.array(self.meshCube)
        return True

class SimpleEngine3D():
    theta = 0.0
    vCamera = np.zeros(4)
    mesh = Mesh()

    def __init__(self):
        fNear = 0.1
        fFar = 100.0
        fFov = 50.0
        fAspectRatio = SCREEN_HEIGHT/SCREEN_WIDTH
        self.matProj = self.MatProjection(fFov, fAspectRatio, fNear, fFar)

    def loadFromObjFile(self, path):
        self.mesh.loadFromObjFile(path)

    def MatProjection(self, fFov, fAspectRatio, fNear, fFar):
        mat = np.zeros((4,4))
        fFovRad = 1/np.tan(fFov * 0.5/180 * np.pi)

        mat[0,0] = fAspectRatio * fFovRad
        mat[1,1] = fFovRad
        mat[2,2] = fFar / (fFar - fNear)
        mat[3,2] = -fFar*fNear / (fFar - fNear)
        mat[2,3] = 1.0
        mat[3,3] = 0.0  
        return mat      

    def RotationX(self, fRad):
        mat = np.zeros((4,4))
        mat[0][0] = 1.0
        mat[1][1] = np.cos(fRad)
        mat[1][2] = np.sin(fRad)
        mat[2][1] = -np.sin(fRad)
        mat[2][2] = np.cos(fRad)
        mat[3][3] = 1.0
        return mat

    def RotationY(self, fRad):
        mat = np.zeros((4,4))
        mat[0][0] = np.cos(fRad)
        mat[0][1] = np.sin(fRad)
        mat[1][0] = -np.sin(fRad)
        mat[1][1] = 1.0
        mat[2][2] = np.cos(fRad)
        mat[3][3] = 1.0        
        return mat

    def RotationZ(self, fRad):
        mat = np.zeros((4,4))
        mat[0][0] = np.cos(fRad)
        mat[0][1] = np.sin(fRad)
        mat[1][0] = -np.sin(fRad)
        mat[1][1] = np.cos(fRad)
        mat[2][2] = 1.0
        mat[3][3] = 1.0        
        return mat

    def Translation(self, fx, fy, fz):
        mat = np.zeros((4,4))
        mat[0][0] = 1.0
        mat[1][1] = 1.0
        mat[2][2] = 1.0
        mat[3][3] = 1.0
        mat[3][0] = fx        
        mat[3][1] = fy        
        mat[3][2] = fz        
        return mat

    def MultiplyMat(self, mat1, mat2):
        mat = np.zeros((4,4))
        np.matmul(mat1, mat2, out=mat)        
        return mat

    def MultiplyVecMat(self, vec, mat):
        o = np.zeros((4))
        #print(vec)
        #print(mat)
        np.dot(vec, mat, out=o)        
        return o          

    def MultVector(self, vec, k):
        return [vec[0]*k, vec[1]*k, vec[2]*k, vec[3]*k]

    def DivVector(self, vec, k):
        return [vec[0]/k, vec[1]/k, vec[2]/k, vec[3]/k]

    def AddVectors(self, v1, v2):
        return [v1[0]+v2[0], v1[1]+v2[1], v1[2]+v2[2], v1[3]+v2[3] ]

    def SubVectors(self, v1, v2):
        return [v1[0]-v2[0], v1[1]-v2[1], v1[2]-v2[2], v1[3]-v2[3] ]

    def DotVectors(self, v1, v2):
        return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2]

    def CrossVectors(self, v1, v2):
        return [v1[1]*v2[2]-v1[2]*v2[1], v1[2]*v2[0]-v1[0]*v2[2], v1[0]*v2[1]-v1[1]*v2[0]]

    def LenVector(self, v):
        return np.sqrt(self.DotVectors(v,v))

    def NormVector(self, v):
        l = self.LenVector(v)
        return [v[0]/l, v[1]/l, v[2]/l]

    def draw(self, elaptime):
        screen.fill((0, 0, 180))

        # rotation matrix
        self.theta += elaptime
        fRad = self.theta * math.pi / 180.0 
        matRotZ = self.RotationZ(fRad)
        matRotX = self.RotationX(fRad * 0.5)
        matTrans = self.Translation(0, 0, 10)
        matWorld = self.MultiplyMat(matRotZ, matRotX)
        matWorld = self.MultiplyMat(matWorld, matTrans)

        # draw triangles
        triProjRender = []   
        for tri in self.mesh.meshCube:

            triTransformed = Triangle([[0,0,0,1.0],[0,0,0,1.0],[0,0,0,1.0]],0)
            triTransformed.vts[0] = self.MultiplyVecMat(tri.vts[0], matWorld)
            triTransformed.vts[1] = self.MultiplyVecMat(tri.vts[1], matWorld)
            triTransformed.vts[2] = self.MultiplyVecMat(tri.vts[2], matWorld)
            normal = np.zeros(3)

            line1 = self.SubVectors(triTransformed.vts[1], triTransformed.vts[0])
            line2 = self.SubVectors(triTransformed.vts[2], triTransformed.vts[0])

            normal = self.CrossVectors(line1, line2)
            normal = self.NormVector(normal)
            camray = self.SubVectors(triTransformed.vts[0], self.vCamera)

            if (self.DotVectors(normal, camray) < 0.0):
                # illumination
                light_dir = np.array([0.0, 0.0, -1.0])
                light_dir = self.NormVector(light_dir)

                # dot product light_dir and normal
                dp = self.DotVectors(normal, light_dir)
                color = int(dp*255)    
                if color < 0:
                    color = 0  

                triProjected = np.zeros((4,4))
                triProjected[0] = self.MultiplyVecMat(triTransformed.vts[0], self.matProj) # point0 (x,y,z)
                triProjected[1] = self.MultiplyVecMat(triTransformed.vts[1], self.matProj) # point1
                triProjected[2] = self.MultiplyVecMat(triTransformed.vts[2], self.matProj) # point2
                triProjected[0] = self.DivVector(triProjected[0], triProjected[0][3])
                triProjected[1] = self.DivVector(triProjected[1], triProjected[1][3])
                triProjected[2] = self.DivVector(triProjected[2], triProjected[2][3])

                offset = [1,1,0,0]

                triProjected[0] = self.AddVectors(triProjected[0], offset)
                triProjected[1] = self.AddVectors(triProjected[1], offset)
                triProjected[2] = self.AddVectors(triProjected[2], offset)

                triProjected[0][0] = triProjected[0][0] * 0.5 * SCREEN_WIDTH
                triProjected[0][1] = triProjected[0][1] * 0.5 * SCREEN_HEIGHT
                triProjected[0][2] = triTransformed.vts[0][2]
                triProjected[1][0] = triProjected[1][0] * 0.5 * SCREEN_WIDTH
                triProjected[1][1] = triProjected[1][1] * 0.5 * SCREEN_HEIGHT
                triProjected[1][2] = triTransformed.vts[1][2]
                triProjected[2][0] = triProjected[2][0] * 0.5 * SCREEN_WIDTH
                triProjected[2][1] = triProjected[2][1] * 0.5 * SCREEN_HEIGHT
                triProjected[2][2] = triTransformed.vts[2][2]

                triProjRender.append(Triangle(triProjected, color))
       
        triProjRender = sorted(triProjRender, key = lambda x: x.vts[0][2] + x.vts[1][2] + x.vts[2][2], reverse=True)
        for tp in triProjRender: 
            v = [[tp.vts[0][0], tp.vts[0][1]], 
                [tp.vts[1][0], tp.vts[1][1]],             
                [tp.vts[2][0], tp.vts[2][1]]]
            pygame.draw.polygon(screen,(tp.color,tp.color,tp.color),v,0)    
        pygame.display.update()        
        return True
   
pygame.init()

screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption('Simple Triangle Projection')    

engine = SimpleEngine3D()
running = True
cnt = 0.0

engine.loadFromObjFile("VideoShip.obj")

while running == True:
    engine.draw(1)
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False


