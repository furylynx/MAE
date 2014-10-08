package maejavasample;

import maejava.general_joint;
import maejava.general_skeleton;
import maejava.i_pose_listener;


public class MAEJavaSample 
{

	public static void main(String[] args)
	{
		System.loadLibrary("mae");
		
		general_skeleton skel = new general_skeleton();
		skel.set_joint(1, new general_joint(1,2,3,0,1));
		
		
		System.out.println(skel.str());
	}
}
