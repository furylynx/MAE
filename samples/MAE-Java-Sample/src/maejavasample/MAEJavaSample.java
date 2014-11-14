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


public class MAEJavaSample 
{

	public static void main(String[] args)
	{
		System.loadLibrary("mae");
		
		WrappedMovementController movementController = new WrappedMovementController(Bone.defaultBones(), ColumnDefinition.defaultDefinitions());
		movementController.addListener(new IJSequenceListener() {

			@Override
			public void onSequence(int timestamp, LabanSequence sequence) {
				System.out.println("on sequence!");
			}
		});
		
		BvhController bvhController = new BvhController();
		
		GeneralSkeletonVector skelVec = bvhController.readBvhFile("/home/keks/mae/eval/boerge/dontcare01/next_sequence.bvh", BvhSpec.defaultSpec()).getFirst();

		for (int i = 0; i < skelVec.size(); i++)
		{
			System.out.println(i);
			
			GeneralSkeleton gSkeleton = skelVec.get(i);
			
			movementController.nextFrame(i*30, gSkeleton);
		}
		LabanSequence s = movementController.getCurrentSequence();
		s.setTitle("Java generated sequence");
		s.xmlFile("/home/keks/java-labanotation-sequence.laban");
	}
}
