package Model;

public class PositionInfo {
	
	private int positionId;
	private String positionName;
	
	private int xpos;
	private int ypos;
	private int width;
	private int height;
	
	
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
		
		this.xpos = 0;
		this.ypos = 0;
		this.width = 0;
		this.height = 0;
	}
	
	/**
	 * Creates a new PositionInfo object containing information on a position. 
	 * The position is defined by an ID. For more details, the position name 
	 * is given.
	 * 
	 * @param positionId The position ID.
	 * @param positionName The position name.
	 * @param xpos The room's xpos.
	 * @param ypos The room's ypos.
	 * @param width The room's width.
	 * @param height The room's height.
	 */
	public PositionInfo(int positionId, String positionName, int xpos, int ypos, int width, int height)
	{
		this.setPositionId(positionId);
		this.setPositionName(positionName);
		
		this.xpos = xpos;
		this.ypos = ypos;
		this.width = width;
		this.height = height;
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

	/**
	 * @return the xpos
	 */
	public int getXpos() {
		return xpos;
	}

	/**
	 * @param xpos the xpos to set
	 */
	public void setXpos(int xpos) {
		this.xpos = xpos;
	}

	/**
	 * @return the ypos
	 */
	public int getYpos() {
		return ypos;
	}

	/**
	 * @param ypos the ypos to set
	 */
	public void setYpos(int ypos) {
		this.ypos = ypos;
	}

	/**
	 * @return the width
	 */
	public int getWidth() {
		return width;
	}

	/**
	 * @param width the width to set
	 */
	public void setWidth(int width) {
		this.width = width;
	}

	/**
	 * @return the height
	 */
	public int getHeight() {
		return height;
	}

	/**
	 * @param height the height to set
	 */
	public void setHeight(int height) {
		this.height = height;
	}
}
