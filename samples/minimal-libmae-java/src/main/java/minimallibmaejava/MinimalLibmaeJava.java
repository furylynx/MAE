package minimallibmaejava;

import maejava.Bone;
import maejava.BoneVector;
import maejava.LabanSequence;
import maejavawrapper.WrappedMovementController;
import maejavawrapper.IJSequenceListener;
import maejava.FlMovementController;
import maejava.BvhController;
import maejava.IPoseListener;
import maejava.BvhData;
import maejava.BvhSpec;
import maejava.GeneralSkeletonVector;
import maejava.GeneralPose;

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


        BvhController bvh = new BvhController();
        BvhData bvhData = bvh.readBvhFile("mov.bvh", BvhSpec.defaultSpec());

        GeneralSkeletonVector sv = bvhData.getSkeletonData();

        FlMovementController mc = new FlMovementController();
        mc.addListener(new IPoseListener(){
            @Override
            public void onPose(java.math.BigInteger timestamp, GeneralPose pose) {
                System.out.println("cb");
            }
        });

        for (int i = 0; i < sv.size(); i++) {
            mc.nextFrame(BigInteger.valueOf(i), sv.get(i));
        }

        System.out.println(mvc);

    }
}
