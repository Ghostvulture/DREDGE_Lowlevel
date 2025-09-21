from maix.image import ApriltagFamilies

def generate_map_dict(rows=15, cols=20):
    """generate a map dictionary for AprilTag IDs to coordinates
    Args:
        rows (int): number of rows in the map
        cols (int): number of columns in the map
    Returns:
        dict: mapping of AprilTag IDs to (row, col) coordinates
    """
    mapping = {}
    num = 1
    for row in range(1, rows + 1):
        for col in range(1, cols + 1):
            mapping[num] = (row, col)
            num += 1
    return mapping

class AprilTagConfig:
    """
    Configuration for AprilTag detection. User should import this class to gain AprilTag family and map dictionary.

    Attributes:
        families (ApriltagFamilies): AprilTag family used for detection.
        map (Dict[int, Tuple[int, int]]): Dictionary mapping AprilTag IDs to (row, col) coordinates.
    """
    families = ApriltagFamilies.TAG36H11
    map = generate_map_dict()