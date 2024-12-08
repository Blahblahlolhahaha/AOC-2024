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
        Guard newGuard = guard.changeDirection(sad.getSecond());
        if(sad.getSecond().equals(end)){
            return new Pair<>(true,
                    new Pair<>(newGuard, 
                        new Map(this.rows,this.columns,sad.getFirst())));
        }

        return new Pair<>(false ,
                new Pair<>(newGuard, 
                    new Map(this.rows,this.columns,sad.getFirst())));
        
    }

    public boolean isObstacle(int i){
        State state = grid[i/columns][i%columns];
        if(state == State.OBSTACLE || state == State.WALKED){
            return true;
        }
        return false;
    }

    public boolean isGoodObstacle(Guard guard, int i){
        Pair<Integer, Integer> origCoord = new Pair<>(guard.getX(), guard.getY());
        int origDir = guard.getDirection();
        grid[i/columns][i%columns] = State.OBSTACLE;
        Guard stupid = new Guard(origCoord,origDir);
        Map dummyMap = new Map(rows,columns,this.grid);
        Pair<Boolean,Pair<Guard,Map>> start = new Pair<>(false,new Pair<>(stupid, dummyMap));
        Pair<Boolean,Pair<Guard,Map>> end = Stream.iterate(start, 
                    x -> !x.getFirst() && !x.getSecond().getFirst().isLooping(), 
                    x -> x.getSecond().getSecond().getNextState(x.getSecond()))
                .reduce(start, (x,y) -> y);
        grid[i/columns][i%columns] = State.NOT_WALKED; 
        return !end.getSecond().getSecond().getNextState(end.getSecond()).getFirst();
    }
    
    public long getWays(Guard guard){
        return Stream.iterate(0,i -> i < rows * columns, i -> i + 1)
            .filter(i -> !isObstacle(i))
            .map(i -> isGoodObstacle(guard, i))
            .filter(x -> x).count(); 
    }

    public long getWalked(){
        return Stream.of(grid)
            .map(x -> Arrays.stream(x).filter(y -> y == State.WALKED).count())
            .reduce((long)0,(x, y) -> x + y);
    }
}


