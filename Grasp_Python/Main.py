from Grasp import Grasp
import os

fileDirectory = os. getcwd()

fileName = "knapsack.txt"
os.chdir("Grasp_Python")

grasp = Grasp(1)
grasp.parseKnapsack(fileName)
print(grasp.PriceVariable)
grasp.resolve()