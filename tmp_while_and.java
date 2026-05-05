class T {
    public static void main(String[] args) {
        int i;
        i = 0;

        while (i < 100000 && 1 == 1) {
            i = i + 1;
        }

        System.out.print(i);
        System.out.print("\n");
    }
}
