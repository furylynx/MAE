package maejavasample;

import maejava.bone;
import maejava.bvh_controller;
import maejava.bvh_spec;
import maejava.column_definition;
import maejava.fl_movement_controller;
import maejava.general_skeleton;
import maejava.general_skeleton_vector;



public class MAEJavaSample 
{

	public static void main(String[] args)
	{
		System.loadLibrary("mae");
		
		fl_movement_controller movementController = new fl_movement_controller(bone.default_bones(), column_definition.default_definitions());
		movementController.add_listener(new SequenceListener());

		
		bvh_controller bvhc = new bvh_controller();
		
		general_skeleton_vector data = bvhc.read_bvh_file("/home/keks/mae/eval/boerge/dontcare01/next_sequence.bvh", bvh_spec.default_spec()).getFirst();

		for (int i = 0; i < data.size(); i++)
		{
			System.out.println(i);
			
			general_skeleton skeleton = data.get(i);
			
			movementController.next_frame(i*30, skeleton);
		}
		
	}
}
