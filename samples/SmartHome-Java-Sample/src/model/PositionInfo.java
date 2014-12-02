package model;

public class PositionInfo {
	
	private int positionId;
	private String positionName;
	
	private PositionType positionType;
	
	private int xpos;
	private int ypos;
	private int width;
	private int height;
	
	private int xdoor;
	private int ydoor;
	private int widthdoor;
	private int heightdoor;
	
	
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
		
		evaluatePositionType(positionName);
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
	public PositionInfo(int positionId, String positionName, int xpos, int ypos, int width, int height, int xdoor, int ydoor, int widthdoor, int heightdoor)
	{
		this.setPositionId(positionId);
		this.setPositionName(positionName);
		
		this.xpos = xpos;
		this.ypos = ypos;
		this.width = width;
		this.height = height;
		
		this.xdoor = xdoor;
		this.ydoor = ydoor;
		this.widthdoor = widthdoor;
		this.heightdoor = heightdoor;
		
		evaluatePositionType(positionName);
	}

	private void evaluatePositionType(String positionName)
	{
		if ("LIVINGROOM".equalsIgnoreCase(positionName))
		{
			positionType = PositionType.LIVINGROOM;
		}
		else if ("KITCHEN".equalsIgnoreCase(positionName))
		{
			positionType = PositionType.KITCHEN;
		}
		else if ("BEDROOM".equalsIgnoreCase(positionName))
		{
			positionType = PositionType.BEDROOM;
		}
		else if ("TERRACE".equalsIgnoreCase(positionName))
		{
			positionType = PositionType.TERRACE;
		}			
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
		
		evaluatePositionType(positionName);
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

	/**
	 * @return the xdoor
	 */
	public int getXdoor() {
		return xdoor;
	}

	/**
	 * @param xdoor the xdoor to set
	 */
	public void setXdoor(int xdoor) {
		this.xdoor = xdoor;
	}

	/**
	 * @return the ydoor
	 */
	public int getYdoor() {
		return ydoor;
	}

	/**
	 * @param ydoor the ydoor to set
	 */
	public void setYdoor(int ydoor) {
		this.ydoor = ydoor;
	}

	/**
	 * @return the widthdoor
	 */
	public int getWidthdoor() {
		return widthdoor;
	}

	/**
	 * @param widthdoor the widthdoor to set
	 */
	public void setWidthdoor(int widthdoor) {
		this.widthdoor = widthdoor;
	}

	/**
	 * @return the heightdoor
	 */
	public int getHeightdoor() {
		return heightdoor;
	}

	/**
	 * @param heightdoor the heightdoor to set
	 */
	public void setHeightdoor(int heightdoor) {
		this.heightdoor = heightdoor;
	}

	/**
	 * @return the positionType
	 */
	public PositionType getPositionType() {
		return positionType;
	}

	/**
	 * @param positionType the positionType to set
	 */
	public void setPositionType(PositionType positionType) {
		this.positionType = positionType;
	}
}
