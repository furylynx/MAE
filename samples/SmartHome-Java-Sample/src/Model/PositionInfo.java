package Model;

public class PositionInfo {
	
	private int positionId;
	private String positionName;
	
	/**
	 * Creates a new PositionInfo object containing information on a position. 
	 * The position is defined by an ID. For more details, the position name 
	 * is given.
	 * 
	 * @param positionId The position ID.
	 * @param positionName The position name.
	 */
	public PositionInfo(int positionId, String positionName)
	{
		this.setPositionId(positionId);
		this.setPositionName(positionName);
	}

	/**
	 * Returns the position ID.
	 * 
	 * @return the positionId
	 */
	public int getPositionId() {
		return positionId;
	}

	/**
	 * Sets the position ID.
	 * 
	 * @param positionId the positionId to set
	 */
	public void setPositionId(int positionId) {
		this.positionId = positionId;
	}

	/**
	 * Returns the position name.
	 * 
	 * @return the positionName
	 */
	public String getPositionName() {
		return positionName;
	}

	/**
	 * Sets the position name.
	 * 
	 * @param positionName the positionName to set
	 */
	public void setPositionName(String positionName) {
		this.positionName = positionName;
	}
}
