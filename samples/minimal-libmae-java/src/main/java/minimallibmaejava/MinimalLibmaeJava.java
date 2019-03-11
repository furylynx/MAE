package minimallibmaejava;

import maejava.*;
import maejavawrapper.WrappedMovementController;
import maejavawrapper.IJSequenceListener;

import java.math.BigInteger;

public class MinimalLibmaeJava {
    public static void main(String[] args) {

        BoneVector bones = Bone.defaultHandBones(false);

        for (int i = 0; i < bones.size(); i++) {
            System.out.println(bones.get(i).getName());
        }

//        NativeLabanSequenceSequenceListener listener = MaeJava.makeNative(new ILabanSequenceSequenceListener() {
//            @Override
//            public void onSequence(BigInteger bigInteger, LabanSequence labanSequence) {
//                System.out.println(""+bigInteger.toString()+" - "+labanSequence.getTitle());
//            }
//        });
//
//        NativePoseListener poseListener = MaeJava.makeNative(new IPoseListener() {
//            @Override
//            public void onPose(BigInteger bigInteger, GeneralPose generalPose) {
//                System.out.println("Pose "+bigInteger.toString());
//            }
//        });
//
//        FlMovementController mc = new FlMovementController();
//        mc.addListener(listener);
//        mc.addListener(poseListener);
//
//        BvhController bvhController = new BvhController();
//        BvhData data = bvhController.readBvhFile("../tutorial-bvhreader/file.bvh", BvhSpec.defaultSpec());

//        for (int i = 0; i < data.getSkeletonData().size(); i++) {
//            mc.nextFrame(BigInteger.valueOf(i), data.getSkeletonData().get(i));
//        }

//        WrappedMovementController mvc = new WrappedMovementController();
//
//        mvc.addListener(new IJSequenceListener() {
//            @Override
//            public void onSequence(BigInteger bigInteger, LabanSequence labanSequence) {
//                System.out.println("next seq");
//            }
//        });
//
//        System.out.println(mvc);

    }
}
