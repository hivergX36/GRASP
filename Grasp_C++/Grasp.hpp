#include<vector> 
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <bits/stdc++.h> 


/* At first iterative Grasp and then Reactive Grasp */

struct tabsolution{
    std::vector<int> solution; 
    float obj; 


    float operator()(tabsolution tab1, tabsolution tab2){
        return tab1.obj > tab2.obj; 
    }


};


struct utility{
 

    float u;   /*u_i */
    int ordre; /* order of priority of our utility singleton*/
    bool choosen; 
};


struct Grasp{

    int NbVariable;
    int NbConstraints;
    int IndCandidat;
    int Nbiteration; 
    float objective; 
    int NumberIter;
    /* Price function */
    std::vector<int> * Price;
    /*Utilisty function*/
    std::vector<utility> * Utility;
    std::vector<int> RCL;
    std::vector<tabsolution>  ListSolution;

    /*Matrix of constraint*/
    std::vector<int>*CostMatrix;
    /*Vector of solution*/
    std::vector<int> * Solution;
    std::vector<int> * Utilityorder;
    std::vector<bool> * Candidate_choosen; 
    std::vector<float> * constraint;

 
    Grasp(std::string name, int nbiter){

        int k = 0;
        int number;
        int candidat; 
         NumberIter = nbiter;
        float objective = 0;

            std::ifstream fichier(name);
                if(fichier){

                   

                     fichier >> NbVariable;
                     fichier >> NbConstraints; 

                     Price = new std::vector<int>; 
                     Solution = new std::vector<int>;

                     CostMatrix = new  std::vector<int>[NbConstraints];
                     Utility = new std::vector<utility>[NbVariable];
                     Utilityorder = new std::vector<int>[NbVariable];
                     Candidate_choosen = new std::vector<bool>;
                     constraint = new std::vector<float>; 



                     while(k < NbVariable){
                        fichier >> number; 
                        std::cout << number << std::endl;
                        Candidate_choosen[0].push_back(0);
                        Price[0].push_back(number);
                        Solution[0].push_back(0); 
                        Utility->push_back({0,k,false});
                        k++;



                     };



                     for(int i = 0; i < NbConstraints; i++){
                        k = 0;

                        while(k < NbVariable){
                            fichier >> number; 
                            CostMatrix[i].push_back(number);
                            k++;
                        }
                     }

                     for(int i = 0; i < NbConstraints; i++){
                        fichier >> number;
                        constraint[0].push_back(number);
                     }
                     
                };
                



    };

    void displayCostMatrix(){
        for(int i = 0; i < NbConstraints; i++){
            for(int j = 0; j < NbVariable; j++)
            {
                std::cout << CostMatrix[i][j] << " ";

        }

        std::cout << std::endl;
        }
    };


    void calculateUtility(){
        int sum = 0; 
        float result;
        for (int i = 0; i < NbVariable; i++){
             for(int j = 0; j < NbConstraints; j++){
                    sum += CostMatrix[j][i];
                    }
                    std::cout << std::endl;
                    std::cout << "La somme est: " << sum << std::endl;
                    result = (float)Price[0][i] / sum;
                    std::cout << "le résultat est: " << result << std::endl;
                    Utility[0][i].u = result; 
                    sum = 0;
                    }
                }
    
    void buildRCLandchoosecandidate(){
        int indchoice = 0;
        int indice = 0;
        int indRCLcandidat = 0;
        std::vector<int> listChoice; 
        std::vector<utility> listutility;
        std::vector<float>  listValue;
         std::vector<int> rcl;
        int indpush = -1;
        float alpha; 
        float Limit;
        float minimum;
        float maximum;
            for(int i = 0; i < NbVariable; i++){
              if (Utility[0][i].choosen == false){
                indpush++;
                listChoice.push_back(indpush);
                listutility.push_back(Utility[0][i]); 
                listValue.push_back(Utility[0][i].u);

              }
            }

            alpha =  0.2;
            std::cout << "alpha: " << alpha << std::endl; 
            minimum = *std::min_element(listValue.begin(), listValue.end());
            maximum = *std::max_element(listValue.begin(), listValue.end());
            Limit = minimum + alpha * (maximum - minimum);
            std::cout << "Limit: " << Limit << std::endl; 
            for(int i = 0; i < listChoice.size(); i++){
                indchoice = listChoice[i];
                std::cout << "indice choix: " << indchoice << std::endl; 
              if(listValue[indchoice] >= Limit){
                rcl.push_back(indchoice);
              }
            }
            
            RCL = rcl; 
            std::cout << "tailleRCL: " << RCL.size() << std::endl;
            if(RCL.size() > 0){
                
                indice = rand() % RCL.size();


            }else{
              indice = RCL[0];
            }

            

            indRCLcandidat = RCL[indice];
            std::cout <<  "le candidat choisie de la liste RCL est: " << IndCandidat << std::endl;
            IndCandidat = listutility[indRCLcandidat].ordre; 
            Utility[0][IndCandidat].choosen = true; 

     
            }

    void display_utility(){

        std::cout << "Le vecteur d'utilité est: ";
        for(int i = 0; i < NbVariable; i++){

            std::cout << "u_str_" << Utility[0][i].ordre << "_choosen_" << Utility[0][i].choosen << ": " <<  Utility[0][i].u  << " ";  

        }

    }



    void ChackUpdateSolution(){
        float sum; 
        Solution[0][IndCandidat] = 1;
        int j = 0;

        while(j < NbConstraints){
            sum = 0;
            for( int i = 0; i < NbVariable; i++){

                sum += Solution[0][i] * CostMatrix[j][i];


            }
            if(sum > constraint[0][j]){

                Solution[0][IndCandidat] = 0;

                std::cout << "Le candidat est rejeté" << std::endl;
                break;

            }
                
                j++;
        




        }
            
            std::cout << "Solution mise à jour" << std::endl;


    }


    void checkneighbor(std::vector<int>& Neigbor, std::vector<int>& S1){
        float sum; 
        int j = 0;
        bool valid = true; 
        float obj1N = 0;
        float obj2S = 0;

        while(j < NbConstraints){
            sum = 0;
            for( int i = 0; i < NbVariable; i++){

                sum += Neigbor[i] * CostMatrix[j][i];


            }
            std::cout << "la somme est: " << sum << std:: endl;
            std::cout << "la contrainte est: " << constraint[0][j] << std::endl;
            if(sum > constraint[0][j]){


                std::cout << "Le candidat est rejeté" << std::endl;
                valid = false;
                break;

            }
                
                j++;
        




        }

        std::cout << "valid?: " << valid << std::endl; 
        if(valid == true){
            for(int i = 0; i < NbVariable; i++){
                
                std::cout << "prix" << Price[0][i] << std::endl;
                obj1N += Neigbor[i] * Price[0][i];
                std::cout << obj1N << std::endl;
                obj2S += S1[i] * Price[0][i];
                std::cout << obj2S << std::endl;


                


            }
            if(obj1N > obj2S){

                S1 = Neigbor;
                objective = obj1N;


            }else 
            {
                objective = obj2S;
            }

        }
            
            std::cout << "Solution mise à jour" << std::endl;

    }


    void NeighborhoodLocalsearch(){

            std::vector<int> Neigbor;
            std::vector<int> InitialSolution; 
            InitialSolution = Solution[0]; 
            
            for(int i = 0; i < NbVariable; i++){
                Neigbor = InitialSolution;
                if(InitialSolution[i] > 0 ){
                    Neigbor[i] = 0;
                }else{
                    Neigbor[i] = 1;
                }

                checkneighbor(Neigbor, Solution[0]); 
                }
    }

        void displaySolution(){
        for(int i = 0; i < NbVariable; i++){

            std::cout << Solution[0][i] << " ";
        }
        std::cout << std::endl;
        std::cout << "La valeur de la fonction objective est: " << objective << std::endl;
    }

    void displayListSolution(){
        for(int i = 0; i < ListSolution.size(); i ++){
            std::cout << "Solution_" << i << " : ";
            for(int k = 0; k < NbVariable; k++){
                 std::cout << ListSolution[i].solution[k] << " ";
                 } 
                 std::cout << "obj: " <<   ListSolution[i].obj << std::endl;     
            }
    }






    void resolve(){
      tabsolution tab;
      int indcount = 0;
      calculateUtility();
      for(int i = 0;  i < NumberIter; i++ ){
      while (indcount < NbVariable){
      buildRCLandchoosecandidate();        
      ChackUpdateSolution();
        indcount++;
        }
        displaySolution();

        NeighborhoodLocalsearch();
        displaySolution();
        tab.obj = objective;
        tab.solution = Solution[0];
        ListSolution.push_back(tab); 



      }

      sort(ListSolution.begin(), ListSolution.end(), tabsolution());
      displayListSolution();

     
    };
};


