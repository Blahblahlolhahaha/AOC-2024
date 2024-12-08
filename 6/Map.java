import java.util.stream.Stream;
import java.util.Arrays;
class Map{
    private final int rows;
    private final int columns;
    private final State[][] grid;
    private static Pair<Integer,Integer> end = new Pair<>(-1,-1);
    public Map(int rows, int columns, State[][] grid){
        this.rows = rows;
        this.columns = columns;
        this.grid = grid;
    }

    public Pair<State[][],Pair<Integer, Integer>> getStoppingCoord(Guard guard){
        int direction = guard.getDirection();
        State[][] newGrid = Arrays.stream(grid).map(x -> x.clone()).toArray(State[][]::new);
        
        Pair<Integer,Integer> plus = new Pair<>(direction == 90 ? 1 : direction == 270 ? -1 : 0,
                direction == 0 ? -1 : direction == 180 ? 1 : 0);
        
        int x = guard.getX() + plus.getFirst();
        int y = guard.getY() + plus.getSecond();
        while((x >= 0 && x < rows) && (y >= 0 && y < columns)){
            if(grid[y][x] == State.OBSTACLE){
                return new Pair<>(newGrid, new Pair<>(x - plus.getFirst(),y - plus.getSecond()));
            }
            newGrid[y][x] = State.WALKED;
            x += plus.getFirst();
            y += plus.getSecond();
        }
        return new Pair<>(newGrid, new Pair<>(-1,-1));
        
    }

    public Pair<Boolean,Pair<Guard,Map>> getNextState(Pair<Guard,Map> state){
        Guard guard = state.getFirst();
        Pair<State[][], Pair<Integer,Integer>> sad = getStoppingCoord(guard);
        Guard newGuard = new Guard(sad.getSecond(),guard.getDirection()).changeDirection();
        if(sad.getSecond().equals(end)){
            return new Pair<>(true,
                    new Pair<>(newGuard, 
                        new Map(this.rows,this.columns,sad.getFirst())));
        }

        return new Pair<>(false ,
                new Pair<>(newGuard, 
                    new Map(this.rows,this.columns,sad.getFirst())));
        
    }

    public long getWalked(){
        return Stream.of(grid)
            .map(x -> Arrays.stream(x).filter(y -> y == State.WALKED).count())
            .reduce((long)0,(x, y) -> x + y);
    }
}


