import numpy as np

# Hàm kiểm tra ma trận có đối xứng không
def is_symmetric(matrix):
    return np.allclose(matrix, matrix.T)

# Hàm kiểm tra ma trận có phải ma trận vuông không
def is_square(matrix):
    return matrix.shape[0] == matrix.shape[1]

# Hàm kiểm tra ma trận có đủ số lượng chỉ số riêng không
def has_eigenvalues(matrix, num_eigenvalues):
    eigenvalues = np.linalg.eigvals(matrix)
    return len(eigenvalues) >= num_eigenvalues

# Hàm tính ma trận chuyển vị
def transpose(matrix):
    return matrix.T

# Hàm tính tích ma trận
def matrix_multiply(A, B):
    return np.dot(A, B)

# Hàm in ma trận
def print_matrix(matrix, name):
    print(f"\nMa trận {name}:")
    for row in matrix:
        print(" ".join(f"{value:.4f}" for value in row))

# Nhập kích thước của ma trận vuông
n = int(input("Nhập kích thước của ma trận vuông (n): "))

# Nhập ma trận A từ người dùng
print("Nhập ma trận A:")
A = np.zeros((n, n))
for i in range(n):
    for j in range(n):
        A[i, j] = float(input(f"A[{i+1},{j+1}]: "))

# Kiểm tra nếu ma trận là ma trận đối xứng
if is_symmetric(A):
    print("\nMa trận đối xứng.")
else:
    print("\nMa trận không đối xứng.")

# Tính và in ra danh sách chỉ số riêng
if has_eigenvalues(A, n):
    eigenvalues, eigenvectors = np.linalg.eig(A)
    print("\nChỉ số riêng:")
    for i, eigenvalue in enumerate(eigenvalues):
         # Tính ma trận A - λI
        A_minus_lambdaI = A - eigenvalue * np.eye(n)
        
        # In ra định thức của ma trận A - λI
        determinant = np.linalg.det(A_minus_lambdaI)
        
        # In ra thông tin
        print(f"Định thức của A - λ_{i+1}I:")
        print_matrix(A_minus_lambdaI, f"A - λ_{i+1}I")
        print(f"Định thức: det(A - λ_{i+1}I) = {determinant}")
        print(f"λ_{i+1} = {eigenvalue}\n")
    choice = input("\nBạn muốn tính vectơ riêng (Y/N)? ").strip().lower()
    if choice == 'y':
        # Tính và in ra vectơ riêng
        print("\nVectơ riêng:")
        for i, eigenvalue in enumerate(eigenvalues):
            if abs(eigenvalue) > 1e-10:  # Kiểm tra nếu eigenvalue không gần bằng 0
                eigenvector = eigenvectors[:, i]
                print(f"v_{i+1} =", eigenvector)
            else:
                print(f"v_{i+1} = Không xác định (λ gần bằng 0)")

        # In ra ma trận vectơ riêng và ma trận giá trị riêng
        eigenvalues_matrix = np.diag(eigenvalues)
        print_matrix(eigenvectors, "vectơ riêng")
        print_matrix(eigenvalues_matrix, " giá trị riêng")
        
        # Tính và in ra ma trận phân rã
        A_reconstructed = matrix_multiply(eigenvectors, matrix_multiply(eigenvalues_matrix, np.linalg.inv(eigenvectors)))
        print_matrix(A_reconstructed, " phân rã")

    else:
        print("\nChương trình kết thúc.")
else:
    print("\nKhông đủ số lượng chỉ số riêng để tính.")
