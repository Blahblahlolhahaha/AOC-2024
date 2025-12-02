import java.util.stream.Stream;
import java.util.ArrayList;
import java.io.File;
import java.io.FileNotFoundException;



void main(){
    try{
        File file = new File("input");
        String[] sad = new Scanner(file).useDelimiter("\\A").next().split("\n");
        int columns = sad[0].length();
        int rows = sad.length;
        int[][] grid = new int[rows][columns];
        ArrayList<Pair<Integer,Integer>> startPoints = new ArrayList<>();
        for(int i = 0;i < rows; i++){
            for(int j = 0; j < columns; j++){
                char test = sad[i].charAt(j);
                if(test == '0'){
                    startPoints.add(new Pair<>(j,i));
                }
                grid[i][j] = sad[i].charAt(j); 
            }
        }
        Map map = new Map(rows,columns,grid);
        System.out.println(startPoints.stream().map(x -> map.getOrder(x)).reduce(0, (x,y) -> x + y)); 
        System.out.println(startPoints.stream().map(x -> map.getSecondOrder(x)).reduce(0, (x,y) -> x + y)); 
    }catch(FileNotFoundException e){
        System.out.println("sad");
    }

}
 
