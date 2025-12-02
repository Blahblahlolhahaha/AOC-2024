import java.util.ArrayList;

class Guard{
    private final Pair<Integer,Integer> coord;
    private final int direction;
    private final ArrayList<Pair<Pair<Integer,Integer>,Integer>> loop;

    public Guard(Pair<Integer,Integer> coord, int direction){
        this.coord = coord;
        this.direction = direction;
        this.loop = new ArrayList<>();
    }

    private Guard(Pair<Integer,Integer> coord, int direction, ArrayList<Pair<Pair<Integer,Integer>,Integer>> loop){
        this.coord = coord;
        this.direction = direction;
        this.loop = loop; 
        this.loop.add(new Pair<>(this.coord,this.direction));
    }

    public int getX(){
        return coord.getFirst();
    }

    public int getY(){
        return coord.getSecond();
    }

    public int getDirection(){
        return this.direction;
    }
    
    public boolean isLooping(){
        for(int i = 0; i < loop.size() - 1; i++){
            if(loop.get(i).equals(new Pair<>(this.coord,this.direction))){
                return true;
            }
        }
       return false; 
    }
    
    public Guard changeDirection(Pair<Integer,Integer> coord){
        ArrayList<Pair<Pair<Integer,Integer>,Integer>> loop = new ArrayList<>(this.loop); 
        return new Guard(coord, (direction + 90) % 360, loop);
    }
}


