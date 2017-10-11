package minimallibmaejava;

import maejava.Bone;
import maejava.BoneVector;
import maejava.LabanSequence;
import maejavawrapper.WrappedMovementController;
import maejavawrapper.IJSequenceListener;

import java.math.BigInteger;

public class MinimalLibmaeJava {
    public static void main(String[] args) {

        BoneVector bones = Bone.defaultHandBones(false);

        for (int i = 0; i < bones.size(); i++) {
            System.out.println(bones.get(i).getName());
        }

        WrappedMovementController mvc = new WrappedMovementController();

        mvc.addListener(new IJSequenceListener() {
            @Override
            public void onSequence(BigInteger bigInteger, LabanSequence labanSequence) {
                System.out.println("next seq");
            }
        });

        System.out.println(mvc);

    }
}
