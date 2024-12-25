import numpy as np # tính toán trên ma trận
import pandas as pd # đọc dữ liệu từ file csv
from pprint import pprint # dùng cho mục đích in "đẹp"
from collections import defaultdict # để đếm số lượng lần xảy ra của các trạng thái (đơn lẻ và cặp)

df = pd.read_csv('breakfast.csv')
data = df.Food.tolist()
data[-5:] # xuất ra 5 món ăn cuối cùng bạn ăn

# tạo nơi lưu trữ giá trị
food_count = defaultdict(int)
food_pair_count = defaultdict(lambda: defaultdict(float))

# food_count: đếm số lần xuất hiện của một trạng thái
# food_pair_count: đếm tất cả các cặp trạng thái có thể [current][future]
n = len(data)
for i in range(n):
    food_count[data[i]] += 1
    if i == n - 1:
        # self loop
        food_pair_count[data[i]][data[i]] += 1
        break
    food_pair_count[data[i]][data[i + 1]] += 1
# chuẩn hóa theo tổng hàng
for key, value in food_pair_count.items():
    for k, v in value.items():
        food_pair_count[key][k] /= food_count[key] # chuẩn hóa

# lấy index của các món ăn để dễ thao tác
keys = list(food_count.keys())
idx = range(len(keys))
key_to_idx = dict(zip(keys, idx)) # key to index


# food_pair_count = {
#     'Food1': {'Food1': 0.15942311, 'Food2': 0.28214324, 'Food3': 0.66668835, 'Food4': 0.15217166},
#     'Food2': {'Food1': 0.44815416, 'Food2': 0.52792997, 'Food3': 0.33871752, 'Food4': 0.63606479},
#     'Food3': {'Food1': 0.05680344, 'Food2': 0.47170207, 'Food3': 0.61611266, 'Food4': 0.5254097},
#     'Food4': {'Food1': 0.42616303, 'Food2': 0.46234476, 'Food3': 0.80109347, 'Food4': 0.03363998},
# }
pprint(food_pair_count)
P = []
for i in range(len(keys)):
    row = []
    for j in range(len(keys)):
        row.append(food_pair_count[keys[i]][keys[j]])
    P.append(row)
        
# chuyển list sang numpy để dễ tính toán
P = np.array(P)

print('Ma trận chuyển trạng thái P: ')
pprint(P)

# dự đoán món ăn 
curr_food = data[-1]
curr_distribution = P[key_to_idx[curr_food]]
predicted_food = np.random.choice(keys, p=curr_distribution) # random walk with known distribution
predicted_probability = P[key_to_idx[curr_food]][key_to_idx[predicted_food]]

print(f'Món ăn chúng ta ăn hôm trước: {data[-1]}')
print(f'Món ăn nên ăn vào hôm nay là "{predicted_food}"\
 với khả năng xảy ra là {round(predicted_probability * 100, 2)}%')