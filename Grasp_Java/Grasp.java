import java.util.*;
import java.io.*;


public class Grasp  {

     int NbVariable;
     int NbConstraint;
     int [] PriceVariable; 
     Float [][] ConstraintMatrix;
     Float[] Constraints; 
     Utility[] utility;
     int[] Solution;
     int IndCandidat;
     List<Integer> RCL; 

     List<Utility> ListUtility;



     Grasp(String name){  
         
        File input = new File(name);
        try{
          
            Scanner reader = new Scanner(input);
            String[] nums = reader.nextLine().split(",");
            this.NbVariable = Integer.parseInt(nums[0]);
            this.NbConstraint= Integer.parseInt(nums[1]);
            this.PriceVariable = new int[this.NbVariable];
            this.Solution = new int[this.NbVariable]; 
            this.ConstraintMatrix = new Float[this.NbConstraint][this.NbVariable];
            this.Constraints = new Float[this.NbConstraint];
            this.ListUtility = new ArrayList<Utility>(this.NbVariable);
     /*      this.Futility = new Utility[this.NbVariable]; */
            nums = reader.nextLine().split(",");
            
            for(int i = 0; i < this.NbVariable; i++){
              Utility k = new Utility(0,i);
              this.PriceVariable[i] = Integer.parseInt(nums[i]);
              this.ListUtility.add(k);
              Solution[i] = 0;

       
   /*             this.Futility[i].U = 0 ; 
              this.Futility[i].ordre = i;
              this.Futility[i].permu = i; 
              */


            }
            
            for(int i = 0; i < this.NbConstraint; i++){
              nums = reader.nextLine().split(",");

              for(int j = 0; j < this.NbVariable; j++ ){
              this.ConstraintMatrix[i][j] = Float.parseFloat(nums[j]);
            }
          }
          
          nums = reader.nextLine().split(",");
          for(int i = 0; i < this.NbConstraint; i++){
            this.Constraints[i] = Float.parseFloat(nums[i]);
          }

            reader.close();
          
          
          }
          catch (IOException e){
            System.out.println("no file");
           }

        };

      
      
 
public void calculateUtility(){
     int sum = 0; 
    float result;
      for (int i = 0; i < NbVariable; i++){
             for(int j = 0; j < NbConstraint; j++){
                    sum += ConstraintMatrix[j][i];


        }
        result = (float)PriceVariable[i] / sum;
         this.ListUtility.get(i).U = result; 


        sum = 0;

      }
    }


          void BuildRCLAndChoose(){
            Random rand = new Random();
            int indchoice = 0;
            int indice = 0;
            int indRCLcandidat = 0;
            List<Integer> listChoice = new ArrayList<Integer>(); 
            List<Utility> listutility = new ArrayList<Utility>();
            List<Float> listValue = new ArrayList<Float>();
            List<Integer> rcl = new ArrayList<Integer>();
            int indpush = -1;

            double alpha; 
            double Limit;
            double minimum;
            double maximum; 
            for(int i = 0; i < this.NbVariable; i++){
              if (this.ListUtility.get(i).choosen == false){
                indpush++;
                listChoice.add(indpush);
                listutility.add(this.ListUtility.get(i)); 
                listValue.add(this.ListUtility.get(i).U);

              }
            }
/* Il y'a un problème entre les valeurs et indice  */
            alpha =  rand.nextDouble();
            System.out.println("alpha: "+  alpha); 
            minimum = Collections.min(listValue);
            maximum = Collections.max(listValue);
            Limit = minimum + alpha * (maximum - minimum);
            System.out.println("Limit: "+  Limit); 


            for(int i = 0; i < listChoice.size(); i++){

              indchoice = listChoice.get(i);
               System.out.println("indice choix: " + indchoice); 
              if(listValue.get(indchoice) >= Limit){
                rcl.add(indchoice);
              }
            }
            
            this.RCL = rcl; 
            System.out.println( "tailleRCL " + this.RCL.size());
            if(this.RCL.size() > 0){

                          indice = rand.nextInt(0,this.RCL.size());


            }else{
              indice = this.RCL.get(0);
            }

            

            indRCLcandidat = this.RCL.get(indice);
            System.out.println( "le candidat choisie de la liste RCL est: " +  this.IndCandidat );
            this.IndCandidat = listutility.get(indRCLcandidat).ordre; 
            this.ListUtility.get(this.IndCandidat).choosen = true; 

            


          }

          
    
    

    
    
            
        
    
        void ChackUpdateSolution(){
            float sum; 
            Solution[IndCandidat] = 1;
            int j = 0;
    
            while(j < NbConstraint){
                sum = 0;
                for( int i = 0; i < NbVariable; i++){
    
                    sum += Solution[i] * ConstraintMatrix[j][i];
    
    
                }
                if(sum > Constraints[j]){
                  Solution[IndCandidat] = 0;
    
                System.out.println("Le candidat est rejeté");    
                    break;
    
                }
                    
                    j++;
            
    
    
    
    
            }

            System.out.println("Solution mise à jour");
                
    
    
        }

        
   public  void resolve(){
    int indcount = 0;
      calculateUtility();
      while (indcount < this.NbVariable){
      BuildRCLAndChoose();        
      ChackUpdateSolution();
        indcount++;
        }
        displaySolution();

       
      }


      







     

public void displayGreedy(){

        System.out.println("Le nombre de variable est: " + NbVariable);
        System.out.println("Le nombre de contraintes est: " + NbConstraint);
        System.out.println("La liste des prix est: " + "\t");
                for(int i = 0; i < this.NbVariable; i++ ){
                        System.out.println(this.PriceVariable[i] + "\t");

                        

            };
        System.out.println("la liste des contraintes est: ");
        
      
        for (int r = 0; r < NbConstraint; r++) {
          for (int c = 0; c < NbVariable; c++) {
            System.out.print(ConstraintMatrix[r][c] + "\t");
          }
          System.out.println();
        };

        System.out.println("Les contraintes sont: ");
        for(int i = 0; i < NbConstraint; i++)
        {

          System.out.println(Constraints[i] + "\t");
        };

        System.out.println("Les caractéristiques de la fonction d'utilité sont: " );
        for(int i = 0; i < NbVariable ; i++){
          System.out.println("u" + "_i: " + this.ListUtility.get(i).U ); 
         /*    System.out.println("u" + "_i: " +   this.Futility[i].U ); */
          System.out.println("ordre" + "_i: " + this.ListUtility.get(i).ordre ); 
          /*   System.out.println("ordre" + "_i: " +   this.Futility[i].ordre );*/






        }



    //    for(int r = 0; r < AdjacencyList.size(); r++){

      //      	System.out.print(AdjacencyList.get(r)+ "\t");



       // }





    
      
        

    }

    
 public void displaySolution(){
  for(int i = 0; i < NbVariable ; i++){

    System.out.println(this.Solution[i]);
  }
}
}







    

