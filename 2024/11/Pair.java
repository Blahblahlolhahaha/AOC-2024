public class Pair<T,U>{
    private T first;
    private U second;

    public Pair(T first, U second){
        this.first = first;
        this.second = second;
    }

    public T getFirst(){
        return first;
    }

    public U getSecond(){
        return second;
    }
    
    @Override
    public boolean equals(Object obj){
        if(obj instanceof Pair<?,?> pair){
            return this.first.equals(pair.first) && this.second.equals(pair.second);
        }
        return false;
    }

    @Override
    public int hashCode(){
       return first.hashCode() ^ second.hashCode(); 
    }

    @Override
    public String toString(){
        return first.toString() + "," + second.toString();
    }
}
