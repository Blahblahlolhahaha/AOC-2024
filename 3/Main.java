import java.util.Scanner;

boolean flag = true;

int getMul(String sad){
    if(sad.equals("do()")){
        flag = true;
        return 0;
    }
    else if(sad.equals("don't()")){
        flag = false;
        return 0;
    }
    return Stream.of(sad.replace("mul(","").replace(")","").split(",")).reduce(flag ? 1 : 0,(x,y) -> x * Integer.parseInt(y),(x,y) -> x * y);
}

void main(){
     System.out.println(new Scanner(System.in).useDelimiter("\n").tokens().map(x -> getMul(x)).reduce(0,(x,y) -> x + y));
}
