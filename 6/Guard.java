class Guard{
    private final Pair<Integer,Integer> coord;
    private final int direction;

    public Guard(Pair<Integer,Integer> coord, int direction){
        this.coord = coord;
        this.direction = direction;
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

    public Guard changeDirection(){
        return new Guard(this.coord, (direction + 90) % 360);
    }
}


