import maejava.Bone;

public class MinimalLibmaeJava {
    public static void main(String[] args) {
        System.out.println(System.getProperty("java.library.path"));

        try {
            System.load("/path/to/libmaejava.jnilib");
        } catch (UnsatisfiedLinkError e) {
            System.err.println("Native code library failed to load.\n" + e);
            System.exit(1);
        }

//        try {
//            //without lib prefix and .jnilib suffix
//            System.loadLibrary("maejava");
//        } catch (UnsatisfiedLinkError e) {
//            System.err.println("Native code library failed to load. \n" + e);
//            System.exit(1);
//        }

        Bone.defaultBones();
    }
}
