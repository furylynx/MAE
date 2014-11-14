package maejavasample;

import maejava.bone;
import maejava.bvh_controller;
import maejava.bvh_spec;
import maejava.column_definition;
import maejava.fl_movement_controller;
import maejava.general_skeleton;
import maejava.general_skeleton_vector;
import maejava.laban_sequence;
import maejavawrapper.IJSequenceListener;
import maejavawrapper.WrappedMovementController;


public class MAEJavaSample 
{

	public static void main(String[] args)
	{
		System.loadLibrary("mae");
		
		WrappedMovementController movementController = new WrappedMovementController(bone.default_bones(), column_definition.default_definitions());
		movementController.addListener(new IJSequenceListener() {
			
			@Override
			public void onSequence(int timestamp, laban_sequence sequence) {
				System.out.println("on sequence!");
			}
		});
		
		bvh_controller bvhc = new bvh_controller();
		
		//
		general_skeleton_vector skelvec = bvhc.read_bvh_file("/home/keks/mae/eval/boerge/dontcare01/next_sequence.bvh", bvh_spec.default_spec()).getFirst();

		for (int i = 0; i < skelvec.size(); i++)
		{
			System.out.println(i);
			
			general_skeleton gskeleton = skelvec.get(i);
			
			movementController.next_frame(i*30, gskeleton);
		}
		laban_sequence s = movementController.get_current_sequence();
		s.set_title("Java generated sequence");
		s.xml_file("/home/keks/java-labanotation-sequence.laban");
	}
}
