package maejavasample;


import maejava.Bone;
import maejava.BvhController;
import maejava.BvhSpec;
import maejava.ColumnDefinition;
import maejava.GeneralSkeleton;
import maejava.GeneralSkeletonVector;
import maejava.LabanSequence;
import maejavawrapper.IJSequenceListener;
import maejavawrapper.WrappedMovementController;
import maenitejava.NiteController;


public class MAEJavaSample 
{

	public static void main(String[] args)
	{
//		System.loadLibrary("mae");
//		System.loadLibrary("mae_nite");
		
		WrappedMovementController movementController = new WrappedMovementController(Bone.defaultBones(), ColumnDefinition.defaultDefinitions());
		movementController.addListener(new IJSequenceListener() {

			@Override
			public void onSequence(int timestamp, LabanSequence sequence) {
				System.out.println("on sequence!");
			}
		});
		
//		BvhController bvhController = new BvhController();
//		
//		GeneralSkeletonVector skelVec = bvhController.readBvhFile("/home/keks/mae/eval/boerge/dontcare01/next_sequence.bvh", BvhSpec.defaultSpec()).getFirst();
//
//		for (int i = 0; i < skelVec.size(); i++)
//		{
//			System.out.println(i);
//			
//			GeneralSkeleton gSkeleton = skelVec.get(i);
//			
//			movementController.nextFrame(i*30, gSkeleton);
//		}
		
		NiteController niteController = new NiteController("SamplesConfig.xml");
		int frameCount = 0;
		
		while(!niteController.wasKeyboardHit())
		{
			GeneralSkeletonVector skeletons = niteController.waitForUpdate();
			
			if (!skeletons.empty())
			{
				GeneralSkeleton skeleton = skeletons.get(0);
				if (skeleton != null)
				{
					movementController.nextFrame(frameCount, skeleton);
					
					frameCount++;
					System.out.println("frames: "+frameCount);
				}
			}
		}
		
//		LabanSequence s = movementController.getCurrentSequence();
//		s.setTitle("Java generated sequence");
//		s.xmlFile("/home/keks/java-labanotation-sequence.laban");
	}
}
