class T {
    public static int count(String[] x) {
        return x.length;
    }

    public static int first(String[] x) {
        return Integer.parseInt(x[0]);
    }

    public static void main(String[] args) {
        System.out.print(count(args));
        System.out.print("\n");
        System.out.print(first(args));
        System.out.print("\n");
    }
}
