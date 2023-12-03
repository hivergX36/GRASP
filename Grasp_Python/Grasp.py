import random

class Grasp :
    
    def __init__(self, nbiter):
        """Constructeur de notre classe"""
        
        self.NbVariable = 0
        self.Nbconstraint = 0 
        self.PriceVariable = []
        self.MatrixConstraint = []
        self.Constraint = []
        self.Utility = []
        self.candidate_choosen = []
        self.solution = []
        self.IndCandidat = 0
        self.alpha = 0 
        self.iter = nbiter
        self.RCL = []
        
        
            
            
    def checknumber(self,lignes,indice):
        ParsedList = []
        compteur1 = 0
        compteur2 = 0
        while(lignes[indice][compteur1] != '\n' and lignes[indice][compteur2] != '\n'):
              while(lignes[indice][compteur2] != " " and lignes[indice][compteur2] != '\n'):
                    compteur2 += 1
              ParsedList.append(int(lignes[indice][compteur1:compteur2]))
              compteur1 = compteur2 + 1
              compteur2 = compteur1

   
              if compteur1 > len(lignes[indice]) - 1:
                    break
        return ParsedList
      
        
        
  
    def parseKnapsack(self,text):
      fichier = open(text, "r",encoding="utf8")
      lignes = fichier.readlines()
      tab = [self.checknumber(lignes,indice) for indice in range(len(lignes) - 1)]
      self.NbVariable = tab[0][0]
      self.NbConstraint = tab[0][1]
      self.PriceVariable = [tab[1][ind1] for ind1 in range(self.NbVariable)]
      self.MatrixConstraint = [[tab[ind][j] for j in range(self.NbVariable)] for ind in range(2,2 + self.NbConstraint )]
      self.Constraint = [tab[-1][ind] for ind in range(self.NbConstraint)]
      self.Utility = [[0,0,i] for i in range(self.NbVariable)]
      self.solution = [0 for i in range(self.NbVariable)]
    
      
      
      
        
      
        
        
        
        
    def CalculateUtility(self):
      listsum = [sum([self.MatrixConstraint[i][j] for i in range(self.NbConstraint)]) for j in range(self.NbVariable)]
      print(listsum)
      U = [self.PriceVariable[i]/listsum[i] for i in range(self.NbVariable)]
      for i in range(self.NbVariable):
        self.Utility[i][0] = U[i]
      print(self.Utility)
      
      
    def BuildRCL(self):
      listeChoice = [self.Utility[i] for i in range(self.NbVariable) if self.Utility[i][1] < 1]
      listeValue = [listeChoice[i][0] for i in range(len(listeChoice))]
      min_value = min(listeValue)
      max_value = max(listeValue) 
      Limit = min_value + self.alpha * (max_value - min_value)
      self.RCL =  [listeChoice[i][2] for i in range(len(listeChoice)) if listeChoice[i][0] >= Limit]    
        
      
      
    def order_utility(self):
      l = sorted(self.Utility, key=lambda x:x[0], reverse=True)
      self.Utility = l
      
      
    def choose_candidate(self):
      self.IndCandidat = random.choice(self.RCL)
      print("Le candiate choisi est: ", {self.IndCandidat})
      self.Utility[self.IndCandidat][1] = 1
      

      
     
      
      
    def CheckUpdateSolution(self):
      self.solution[self.IndCandidat] = 1
      sum_constraint = [sum([self.solution[i]  * self.MatrixConstraint[j][i] for i in range(self.NbVariable)]) for j in range(self.NbConstraint)]
      for i in range(self.NbConstraint):
        if sum_constraint[i] > self.Constraint[i]:
                self.solution[self.IndCandidat] = 0
                print("candidat refusé")
                break 
              
   
    def resolve(self):
      Indcount = 0
      self.CalculateUtility()
      while Indcount < self.NbVariable:
        self.alpha = random.uniform(0,1)
        print(self.alpha)
        self.BuildRCL()
        self.choose_candidate()
        self.CheckUpdateSolution()
        Indcount += 1 
      self.DisplaySolution()

         
       
       
      
              

        
        
    
    
    
      
        
        
        
    def DisplaySolution(self):
      print(self.solution)
        

      
             
        
             
             
            
             
            



             
            
            

            
             
          
            

        
        
        




     






    
      
        

