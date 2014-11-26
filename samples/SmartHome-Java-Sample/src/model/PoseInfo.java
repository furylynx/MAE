package model;

import java.util.HashMap;
import java.util.Map;

import maejava.ISymbol;
import maejava.LabanSequence;

public class PoseInfo {

	Map<Integer, ISymbol> poseMap;
	
	public PoseInfo(Map<Integer, ISymbol> poseMap)
	{
		this.poseMap = poseMap;
	}
	
	public PoseInfo(LabanSequence sequence)
	{
		//TODO fill map according to sequence
	}
	
	public PoseInfo()
	{
		poseMap = new HashMap<Integer, ISymbol>();
	}
	
	
	public void setBodyPartPose(Integer bodyPart, ISymbol pose)
	{
		poseMap.put(bodyPart, pose);
	}
	
	public ISymbol getBodyPartPose(Integer bodyPart)
	{
		return poseMap.get(bodyPart);
	}

	public boolean matchingPose(LabanSequence currentSequence) {
		// TODO matching pose !
		return false;
	}
	
}
