#include<iostream> 
#include<vector> 
#include<fstream> 
#include "Grasp.hpp"
/*Normalement l'algorithme est cohérent*/
int main(){
   float a;
   a = 5 / 2;
   std::cout << a << std::endl;

   Grasp grasp = Grasp("knapsack.txt", 100);
   std::cout << grasp.NbConstraints << " ";
   std::cout << grasp.NbVariable << std::endl;
   std::cout << grasp.constraint[0][0] << std::endl;
  /* greedy.displayCostMatrix(); 
   greedy.calculateUtility();
   greedy.display_utility();
   std::cout << std::endl;
   greedy.order_utility();
   greedy.display_utility(); */
   /* greedy.choose_candidate();

   std::cout << std::endl;

   

   std::cout << "Le candidat choisi est: " << greedy.IndCandidat << std::endl;

   greedy.ChackUpdateSolution(); */ 

   grasp.resolve();







}