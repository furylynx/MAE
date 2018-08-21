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

//        System.out.println("1");
//        FlMovementController mc = new FlMovementController();
//        System.out.println("2");
//        IPoseListener ipl = new IPoseListener(){
//
//            @Override
//            public void onPose(java.math.BigInteger timestamp, GeneralPose pose) {
//                System.out.println("cb");
//            }
//        };
//
//
//        System.out.println("3");
//        mc.addListener(ipl);
//
//        System.out.println("4");
//        for (int i = 0; i < sv.size(); i++) {
//            System.out.println(i+"b");
//            mc.nextFrame(BigInteger.valueOf(1), sv.get(i));
//            System.out.println(i+"a");
//        }

        System.out.println(mvc);

    }
}
