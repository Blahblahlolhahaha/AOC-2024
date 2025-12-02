import java.util.stream.Stream;
import java.util.List;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.HashMap;

HashMap<String,List<String>> mapping = new HashMap<>();

List<String> nextStone(String x){
    if(mapping.containsKey(x)){
        return mapping.get(x);
    } 
    int length = x.length();
    if(length % 2 == 0){
        int half = length / 2;
        String front = x.substring(0,half);
        String back = Long.toString(Long.parseLong(x.substring(half)));
        List<String> res = List.of(front,back);
        mapping.put(x,res);
        return res;
    }
    List<String> res = List.of(Long.toString(Long.parseLong(x) * 2024));
    mapping.put(x,res);
    return res;
}

int nextIter(List<String> list, int times){
    if(times == 0){
        return list.size();
    }
    return list.stream().map(y -> nextIter(nextStone(y),times - 1)).reduce(0, (x, y) -> x + y);
}

void main() throws FileNotFoundException{
    mapping.put("0",List.of("1"));
    File file = new File("input");
    List<String> input = List.of(new Scanner(file).nextLine().split(" "));
    System.out.println(nextIter(input,75));
        
}
