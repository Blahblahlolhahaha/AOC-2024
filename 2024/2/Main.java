import java.util.stream.Stream;
import java.util.List;
import java.util.ArrayList;
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

    public static boolean checkValidDiff(int diff){
        return diff <= 3 && diff >= -3 && diff != 0; 
    }

    public static boolean validLine(List<String> line){
        int incr = 0;
        int decr = 0;
        int skip = -1;
        List<Integer> diffs = new ArrayList<Integer>();
        for(int i = 0; i < line.size() - 1; i++){
            if(skip == i){
                continue;
            }
            int diff = Integer.parseInt(line.get(i)) - Integer.parseInt(line.get(i+1));
            if(!checkValidDiff(diff)){
                if(skip != -1){
                    return false;
                }
                if(i + 2 == line.size()){
                    return skip == -1;
                }
                diff = Integer.parseInt(line.get(i)) - Integer.parseInt(line.get(i+2));
                if(!checkValidDiff(diff)){
                    if(i == 0){
                        skip = 0;
                        continue;
                    }
                    return false;
                }
                skip = i + 1;
            }
            if(diff > 0){
                incr += 1;
            }
            else{
                decr += 1;
            }
            diffs.add(diff);
        }

        if(decr == 0 || incr == 0){
            return true;
        }

        if((decr == 1 || incr == 1 ) && skip == -1){
            if(decr == 1){
                for(int i = 0; i < diffs.size(); i++){
                    if(diffs.get(i) < 0){
                        if(i == 0 || i == diffs.size() - 1 || checkValidDiff(diffs.get(i-1) + diffs.get(i)) || checkValidDiff(diffs.get(i) + diffs.get(i+1))){
                            return true;
                        }
                        else{
                            return false;
                        }
                    }
                }
            }
            else{
                for(int i = 0; i < diffs.size(); i++){
                    if(diffs.get(i) > 0){
                        if(i == 0 || i == diffs.size() - 1 || checkValidDiff(diffs.get(i-1) + diffs.get(i)) || checkValidDiff(diffs.get(i) + diffs.get(i + 1))){
                            return true;
                        }
                        else{
                            return false;
                        }
                    }
                }
            }
            return true;
        }
        return false;
    }
    
    public static boolean validSafeLine(String line){
        if(validLine(line)){
            return true;
        }
        boolean flag = false;
        String[] numbers = line.split(" ");
        List<String> nums = List.of(numbers);
        for(int i = 0; i < numbers.length; i++){
            if(validLine(nums,i)){
                flag = true;
            }   
        }
        if(validLine(nums) != flag){
            System.out.println(line);
            System.out.println(flag);
        }
        return validLine(nums);
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
