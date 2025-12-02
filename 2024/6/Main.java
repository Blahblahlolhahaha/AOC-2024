import java.util.stream.Stream;
import java.io.File;
import java.util.List;
import java.util.Scanner;
import java.io.FileNotFoundException;

State toState(int yes){
    switch(yes){
        case 35:
           return State.OBSTACLE; 
        case 46:
           return State.NOT_WALKED;
        case 94:
           return State.WALKED;
    };
    return State.NOT_WALKED;
}

Map generateMap(String[] input){
    State[][] state = Stream.of(input)
        .map(x -> x.chars()
                .mapToObj(y -> toState(y))
                .toArray(State[]::new))
        .toArray(State[][]::new);
    int rows = state.length;
    int columns = state[0].length;
    return new Map(rows, columns, state);
}



void main(){
    try{
        File file = new File("input");
        String input = new Scanner(file).useDelimiter("\\A").next();
        String[] sad = input.split("\n");
        Guard guard = new Guard(new Pair<>(0,0),0);
        for(int y = 0; y < sad.length; y++){
            for(int x = 0; x < sad[y].length(); x++){
                if(sad[y].charAt(x) == '^'){
                    guard = new Guard(new Pair<>(x,y),0);
                }
            }
        }
        Map map = generateMap(sad);
        Pair<Boolean,Pair<Guard,Map>> start = new Pair<>(false,new Pair<>(guard, map));
        Pair<Boolean, Pair<Guard,Map>> end = Stream.iterate(start, 
                    x -> !x.getFirst(), 
                    x -> x.getSecond().getSecond().getNextState(x.getSecond()))
                .reduce(start, (x,y) -> y);
        System.out.println(end.getSecond().getSecond().getNextState(end.getSecond()).getSecond().getSecond().getWalked());
        System.out.println(map.getWays(guard));

    }catch(FileNotFoundException e){
        System.out.println("sad");
    }
}
