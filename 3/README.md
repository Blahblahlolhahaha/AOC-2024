# Day 3
I cant be bothered to implement regex and public static void main in java, please run with the following command:
```bash
//part 1
javac --enable-preview --release 23 Main.java && grep -e"mul([0-9]\+,[0-9]\+)" -o input | java --enable-preview Main

//part 2
javac --enable-preview --release 23 Main.java && grep -e"mul([0-9]\+,[0-9]\+)\|do()\|don't()" -o input | java --enable-preview Main
```
