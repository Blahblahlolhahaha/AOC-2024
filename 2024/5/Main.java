import java.util.Scanner;
import java.util.HashMap;
import java.util.HashSet;
import java.util.stream.Stream;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.List;
import java.util.ArrayList;
import java.util.Optional;
public class Main{
    public static void addOrder(Pair<Integer,Integer> pair, HashMap<Integer,HashSet<Integer>> set){
        int first = pair.getFirst();
        int second = pair.getSecond();
        if(set.containsKey(first)){
            set.get(first).add(second);
        }
        else{
            set.put(first,new HashSet<>());
            set.get(first).add(second);
        }
    }

    public static HashMap<Integer,HashSet<Integer>> getOrder(String input){
        HashMap<Integer,HashSet<Integer>> set = new HashMap<>();
        Stream.of(input.split("\n")).map(x -> x.split("\\|")).map(x -> new Pair<>(Integer.parseInt(x[0]), Integer.parseInt(x[1]))).forEach(x -> addOrder(x,set));
        return set;
    }

    public static boolean checkSet(Integer num, Optional<HashSet<Integer>> set){
        return set.map(x -> !x.contains(num)).orElse(true);
    }
    
    public static boolean isCorrectOrder(List<Integer> num, HashMap<Integer,HashSet<Integer>> set){
        return Stream.iterate(0, x -> x < num.size(), x -> x + 1)
            .filter(x -> num.subList(x+1,num.size()).stream().allMatch(y -> checkSet(num.get(x),Optional.ofNullable(set.get(y)))))
            .count() == num.size();
    }
    
    public static List<Integer> fixOrder(List<Integer> num, HashMap<Integer,HashSet<Integer>> set){
        return num.stream().sorted((x,y) -> checkSet(x,Optional.ofNullable(set.get(y))) ? 1 : checkSet(y,Optional.ofNullable(set.get(x))) ? -1 : 0).toList();
    }


    public static int getMiddleNumber(List<Integer> x){
        return x.get((int)Math.ceil(x.size()/2)); 
    }

    public static List<Integer> getNums(String input){
        return Stream.of(input.split(",")).map(x -> Integer.parseInt(x)).toList();
    }

    public static int getSum(String input, HashMap<Integer,HashSet<Integer>> set){
        return Stream.of(input.split("\n")).map(x -> getNums(x)).filter(x -> isCorrectOrder(x,set)).map(x -> getMiddleNumber(x)).reduce(0, (x,y) -> x + y);

    }
    
    public static int getFixedSum(String input, HashMap<Integer,HashSet<Integer>> set){
        return Stream.of(input.split("\n")).map(x -> getNums(x)).filter(x -> !isCorrectOrder(x,set)).map(x -> fixOrder(x,set)).map(x -> getMiddleNumber(x)).reduce(0, (x,y) -> x + y);

    }
    
    
    public static void main(String[] args){
        try{
            File file = new File("input");
            String[] yes = new Scanner(file).useDelimiter("\\A").next().split("\n\n");
            HashMap<Integer,HashSet<Integer>> set = getOrder(yes[0]);
            System.out.println(getSum(yes[1],set)); 
            System.out.println(getFixedSum(yes[1],set)); 
            
            
        }catch(FileNotFoundException e){
            System.out.println("sad");
        }

    }
}
