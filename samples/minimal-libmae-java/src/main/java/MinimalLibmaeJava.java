import maejava.Bone;
import maejava.BoneVector;

public class MinimalLibmaeJava {
    public static void main(String[] args) {

        BoneVector bones = Bone.defaultHandBones(false);

        for (int i = 0; i < bones.size(); i++) {
            System.out.println(bones.get(i).getName());
        }

    }
}
