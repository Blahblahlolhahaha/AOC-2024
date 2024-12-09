import java.util.stream.Stream;
import java.util.HashSet;
import java.util.HashMap;
import java.io.FileNotFoundException;
import java.io.File;
import java.util.ArrayList;
int maxY = 0;
int maxX = 0;

boolean validAnti(Pair<Integer,Integer> test){
    int x = test.getFirst();
    int y = test.getSecond();
    return x >= 0 && x < maxX && y >= 0 && y < maxY;
}

Stream<Pair<Integer,Integer>> calcAnti(Pair<Integer,Integer> a, Pair<Integer,Integer> b){
    int xDiff = b.getFirst() - a.getFirst();
    int yDiff = b.getSecond() - a.getSecond(); 
    Pair<Integer,Integer> first = new Pair<>(a.getFirst() - xDiff, a.getSecond() - yDiff);
    Pair<Integer,Integer> second = new Pair<>(b.getFirst() + xDiff, b.getSecond() + yDiff);
    return Stream.of(first,second).filter(x -> validAnti(x));
}

Stream<Pair<Integer,Integer>> goAllTheWay(Pair<Integer,Integer> a, int x, int y){
    return Stream.iterate(new Pair<>(a.getFirst(), a.getSecond()), pair -> validAnti(pair), pair -> new Pair<>(pair.getFirst() + x, pair.getSecond() + y));
}

Stream<Pair<Integer,Integer>> calcMoreAnti(Pair<Integer,Integer> a, Pair<Integer,Integer> b){
    int xDiff = b.getFirst() - a.getFirst();
    int yDiff = b.getSecond() - a.getSecond(); 
    return Stream.of(a,b).flatMap(x -> goAllTheWay(x, x.equals(a) ? -xDiff : xDiff, x.equals(a) ? -yDiff : yDiff));
}

List<Pair<Integer,Integer>> getAntis(List<Pair<Integer,Integer>> ants, Pair<Integer,Integer> ant){
    return ants.stream().flatMap(x -> calcAnti(x, ant)).toList();
}

List<Pair<Integer,Integer>> getMoreAntis(List<Pair<Integer,Integer>> ants, Pair<Integer,Integer> ant){
    return ants.stream().flatMap(x -> calcMoreAnti(x, ant)).toList();
}

void main(){
    try{
        File file = new File("input");
        String[] lines = new Scanner(file).useDelimiter("\\A").next().split("\n");
        HashSet<Pair<Integer,Integer>> anti = new HashSet<>(); 
        HashSet<Pair<Integer,Integer>> antii = new HashSet<>(); 
        HashMap<Character,ArrayList<Pair<Integer,Integer>>> ants = new HashMap<>();
        maxY = lines.length;
        maxX = lines[0].length(); 
        for(int y = 0; y < lines.length; y++){
            String line = lines[y];
            for(int x = 0; x < line.length(); x++){
               char sad = line.charAt(x);
               if(sad != '.'){
                  Pair<Integer,Integer> coord = new Pair<>(x,y); 
                  if(ants.containsKey(sad)){
                     anti.addAll(getAntis(ants.get(sad), coord));
                     antii.addAll(getMoreAntis(ants.get(sad),coord));
                  } else {
                     ants.put(sad, new ArrayList<>());
                  } 
                  ants.get(sad).add(coord);
               } 
            }
        }
        System.out.println(anti.size());
        System.out.println(antii.size());
    }catch(FileNotFoundException e){
       System.out.println("sad"); 
    }
}
