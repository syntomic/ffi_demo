package cn.syntomic.ffi;

/** Foreign function interface demo */
public class FFIDemo {

    static {
        System.load(System.getenv("LIBPYTHON"));
        System.load(String.format("%s/FFIDemo.dylib", System.getProperty("user.dir")));
    }

    public static void main(String[] args) {
        System.out.println(new FFIDemo().dayOfWeek("1994-05-05"));
    }

    /**
     * 判断日期是星期几
     * @param date 日期
     */
    private native int dayOfWeek(String date);
}
