import numpy as np
from scipy.spatial import ConvexHull

# Tập hợp điểm
points = np.array([[-4, 2], [-3, -2], [-1, 4], [-1, -4], [0, 0], 
                   [1, -2], [1, -4], [2, -3], [3, -4], [5, -2]])

# Tính bao lồi
hull = ConvexHull(points)
area = hull.volume
# In các điểm của bao lồi
print("Các điểm của bao lồi:")
for vertex in hull.vertices:
    print(points[vertex])

# Tính diện tích bao lồi

print(f"Dien tich bao loi: {area}")