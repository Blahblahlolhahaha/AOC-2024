import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;

boolean check(int up, int left, int row, int column,int length ,String input){
    return (input.charAt(length * (row + up * 1) + column + left * 1) == 'M'
                            && input.charAt(length * (row + up * 2) + column + left * 2) == 'A'
                            && input.charAt(length * (row + up * 3) + column + left * 3) == 'S');
}

boolean checkXMAS(int row, int column,int length ,String input){
    char upbackdiag = input.charAt(length * (row - 1) + column - 1);   
    char upfordiag = input.charAt(length * (row - 1) + column + 1);  
    char downbackdiag = input.charAt(length * (row + 1) + column - 1);  
    char downfordiag = input.charAt(length * (row + 1) + column + 1);  
    return ((downfordiag == 'M' && upbackdiag == 'S') || (downfordiag == 'S' && upbackdiag == 'M')) && 
     ((downbackdiag == 'M' && upfordiag == 'S') || (downbackdiag == 'S' && upfordiag == 'M')); 
    
    
}



int countXMAS(String input, int length){
    int sum = 0;
    int maxRows = (int)Math.floor(input.length() / length);
    for(int i = 0; i < input.length(); i++){
        if(input.charAt(i) == 'A'){
            int column = i % length;
            int row = (int) Math.floor(i / length);
            if((column < length - 1 && column >= 1 && row >= 1 && row < maxRows - 1 && checkXMAS(row,column,length,input))){
               sum++; 
            }
        }
    }
    
    return sum;
}

int count(String input, int length){
    int sum = 0;
    int maxRows = (int)Math.floor(input.length() / length);
    for(int i = 0; i < input.length(); i++){
        if(input.charAt(i) == 'X'){
            int column = i % length;
            int row = (int) Math.floor(i / length);
            if(row >= 3){
                //up
                if(check(-1,0, row, column, length, input)){
                    sum++; 
                }
            }
            if(row < maxRows - 3){
                if(check(1,0,row,column,length, input)){
                    //down
                    sum++;
                }
            }

            if(column < length - 3){
                if(input.substring(i,i+4).equals("XMAS")){
                    //forward
                    sum++;
                }

                if(row < maxRows - 3){
                    if(check(1,1, row, column, length, input)){
                        //diag down forward
                        sum++;
                    }
                }

                if(row >= 3){
                    //diag up forward
                    if(check(-1,1, row, column, length, input)){
                        sum++; 
                    }
                    
                }

            }
            if(column >= 3){
                //forward check
                if(input.substring(i-3,i+1).equals("SAMX")){
                    sum++;
                }

                if(row < maxRows - 3){
                    //diag down backwards
                    if(check(1, -1,row, column, length, input)){
                        sum++; 
                    }
                }

                if(row >= 3){
                    //diag up back
                    if(check(-1,-1,row,column,length, input)){
                        sum++;
                    }
                }
            }
        }
    }
    
    return sum;
}

void main(){
    try{
        File file = new File("input");
        List<String> xmas = new Scanner(file).useDelimiter("\n").tokens().toList();
        int lineLen = xmas.get(0).length();
        System.out.println(count(String.join("",xmas),lineLen));
        System.out.println(countXMAS(String.join("",xmas),lineLen));
    }catch(FileNotFoundException e){
        System.out.println("sad");
    }


}
