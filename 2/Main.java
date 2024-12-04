import java.util.stream.Stream;
import java.util.List;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.io.File;
public class Main{
    public static boolean validLine(String line){
        String[] numbers = line.split(" ");
        int first = Integer.parseInt(numbers[0]);
        boolean increasing = false;
        for(int i = 1; i < numbers.length; i++){
            int second = Integer.parseInt(numbers[i]);
            int diff = second - first;
            if(diff == 0 || diff < -3 || diff > 3) {
                return false;
            } 
            else if(i == 1 && diff > 0){
                increasing = true;
            }
            else if((increasing && diff < 0) || (!increasing && diff > 0)){
                return false;
            }
            first = second;
        }
        return true;
    }
    
    public static boolean validLine(List<String> line,int skip){
        boolean increasing = false;
        for(int i = 0; i < line.size()-1; i++){
            if(i == skip){
                continue;
            }
            int x = i + 1;
            if(x == skip){
                x += 1;
                if(x == line.size()){
                    break;
                }
            }
            int first = Integer.parseInt(line.get(i));
            int second = Integer.parseInt(line.get(x));
            int diff = second - first;
            if(diff == 0 || diff < -3 || diff > 3) {
                return false;
            } 
            else if(((i == 0 && skip != 0) || (i == 1 && skip == 0))  && diff > 0){
                increasing = true;
            }
            else if((increasing && diff < 0) || (!increasing && diff > 0)){
                return false;
            }
            first = second;
        }
        return true;
    }
    
    public static boolean validSafeLine(String line){
        if(validLine(line)){
            return true;
        }

        String[] numbers = line.split(" ");
        for(int i = 0; i < numbers.length; i++){
            List<String> nums = List.of(numbers);
            if(validLine(nums,i)){
                return true;
            }   
        }

        return false;
    }

    public static void main(String[] args){
        try{
            File file = new File("input");
            Scanner scanner = new Scanner(file);
            System.out.println(scanner.useDelimiter("\n").tokens().filter(x -> validSafeLine(x)).count()); 
        }catch(FileNotFoundException e){
            System.out.println("sad");
        }

    }
}
