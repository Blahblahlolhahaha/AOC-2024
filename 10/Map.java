import java.util.stream.Stream;
import java.util.List;
class Map{
    private final int rows;
    private final int columns;
    private final int[][] grid;
    private final static Pair<Integer,Integer> up =  new Pair<>(0,1);
    private final static Pair<Integer,Integer> down =  new Pair<>(0,-1);
    private final static Pair<Integer,Integer> forward =  new Pair<>(1,0);
    private final static Pair<Integer,Integer> back =  new Pair<>(-1,0);
    public Map(int rows, int columns, int[][] grid){
        this.rows = rows;
        this.columns = columns;
        this.grid = grid;
    }
    
    private boolean isValidAdjacent(Pair<Integer,Integer> a, Pair<Integer,Integer> b){
        if((b.getFirst() < 0 || b.getFirst() == columns) || (b.getSecond() < 0 || b.getSecond() == rows )){
            return false;
        }
        return (grid[b.getSecond()][b.getFirst()] - grid[a.getSecond()][a.getFirst()]) == 1;
    }

    public Stream<Pair<Integer,Integer>> getValidAdjacent(Pair<Integer,Integer> coord){
        return Stream.of(up,down,forward,back).map(x -> new Pair<>(coord.getFirst() + x.getFirst(), coord.getSecond() + x.getSecond())).filter(x -> isValidAdjacent(coord,x));
    }

    public int getOrder(Pair<Integer,Integer> start){
        List<Pair<Integer,Integer>> test = getValidAdjacent(start).toList();
        for(int i = 0; i < 8; i++){
            test = test.stream().flatMap(x -> getValidAdjacent(x)).distinct().toList();
        }
        return test.size();
    }  
    
    public int getSecondOrder(Pair<Integer,Integer> start){
        List<Pair<Integer,Integer>> test = getValidAdjacent(start).toList();
        for(int i = 0; i < 8; i++){
            test = test.stream().flatMap(x -> getValidAdjacent(x)).toList();
        }
        return test.size();
    } 
}

