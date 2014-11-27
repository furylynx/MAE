package model;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Set;

import maejava.IMovement;
import maejava.ISymbol;
import maejava.LabanSequence;
import maejava.Movement;

public class PoseInfo {

	Map<Integer, ISymbol> poseMap;
	Set<Integer> bodyPartsSet;

	/**
	 * Creates a new PoseInfo objects containing information on the last pose of the sequence.
	 * Uses the map to create the pose.
	 * 
	 * @param poseMap The pose map
	 */
	public PoseInfo(Map<Integer, ISymbol> poseMap) {
		this.poseMap = poseMap;
		bodyPartsSet = new HashSet<Integer>();

		for (Entry<Integer, ISymbol> entry : poseMap.entrySet()) {
			bodyPartsSet.add(entry.getKey());
		}
	}

	/**
	 * Creates a new PoseInfo objects containing information on the last pose of the sequence.
	 * Generates the pose from the sequence.
	 * 
	 * @param sequence The sequence.
	 */
	public PoseInfo(LabanSequence sequence) {
		for (int i = 0; i < sequence.getColumns().size(); i++) {
			Integer bodyPart = sequence.getColumns().get(i);

			bodyPartsSet.add(bodyPart);
			
			if (sequence.getColumnMovements(bodyPart).size() > 0) {
				IMovement imov = sequence.getColumnMovements(bodyPart).get(
						(int) sequence.getColumnMovements(bodyPart).size() - 1);

				if (imov instanceof Movement) {
					Movement mov = (Movement) imov;

					poseMap.put(bodyPart, mov.getSymbol());
					bodyPartsSet.add(bodyPart);
				} else {
					// TODO remove
					System.err.println("Cannot cast IMovement to Movement...");
				}
			}
		}
	}

	/**
	 * 	Creates a new, empty PoseInfo objects containing information on the last pose of the sequence.
	 */
	public PoseInfo() {
		poseMap = new HashMap<Integer, ISymbol>();
	}

	/**
	 * Sets the pose for the body part.
	 * 
	 * @param bodyPart The body part.
	 * @param pose The symbol.
	 */
	public void setBodyPartPose(Integer bodyPart, ISymbol pose) {
		poseMap.put(bodyPart, pose);
		bodyPartsSet.add(bodyPart);
	}

	/**
	 * Returns the pose for the body part.
	 * 
	 * @param bodyPart The body part.
	 * @return The pose.
	 */
	public ISymbol getBodyPartPose(Integer bodyPart) {
		return poseMap.get(bodyPart);
	}

	/**
	 * Checks whether the sequence is matching the pose.
	 * 
	 * @param currentSequence The sequence to be checked. 
	 * @return True if the pose is still held.
	 */
	public boolean matchingPose(LabanSequence currentSequence) {

		for (Integer bodyPart : bodyPartsSet) {
			if (currentSequence.getColumnMovements(bodyPart).size() == 0) {
				if (poseMap.get(bodyPart) != null)
				{
					return false;
				}
			} else {
				IMovement imov = currentSequence.getColumnMovements(bodyPart)
						.get((int) (currentSequence
								.getColumnMovements(bodyPart).size() - 1));
				if (imov instanceof Movement) {
					Movement mov = (Movement) imov;
					if (!mov.getSymbol().equals(poseMap.get(bodyPart))) {
						return false;
					}
				} else {
					// TODO remove
					System.err.println("IMovement is no Movement...");
					return false;
				}
			}
		}

		return true;
	}

}
