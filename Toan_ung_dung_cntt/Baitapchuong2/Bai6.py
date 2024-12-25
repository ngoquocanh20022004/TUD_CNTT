import numpy as np

def svd_decomposition(A):
    A_T = np.transpose(A)
    A_T_A = np.dot(A_T, A)
    A_A_T = np.dot(A, A_T)

    eigvals_A_T_A, eigvecs_A_T_A = np.linalg.eigh(A_T_A)
    eigvals_A_A_T, eigvecs_A_A_T = np.linalg.eigh(A_A_T)
    
    sorted_indices_A_T_A = np.argsort(eigvals_A_T_A)[::-1]
    sorted_eigvals_A_T_A = eigvals_A_T_A[sorted_indices_A_T_A]
    sorted_eigvecs_A_T_A = eigvecs_A_T_A[:, sorted_indices_A_T_A]
    
    sorted_indices_A_A_T = np.argsort(eigvals_A_A_T)[::-1]
    sorted_eigvals_A_A_T = eigvals_A_A_T[sorted_indices_A_A_T]
    sorted_eigvecs_A_A_T = eigvecs_A_A_T[:, sorted_indices_A_A_T]

    Sigma = np.sqrt(sorted_eigvals_A_T_A)
    
    U = sorted_eigvecs_A_A_T
    V = sorted_eigvecs_A_T_A
    Sigma = np.diag(Sigma)
    
    if U.shape[0] > Sigma.shape[0]:
        U = U[:, :Sigma.shape[0]]
    if V.shape[0] > Sigma.shape[0]:
        V = V[:, :Sigma.shape[0]]
    
    return U, Sigma, V.T

A = np.array([[8, 3, 7], [8, 3, 5], [8, 3, 3]])

print("Ma trận A:")
print(A)
U, Sigma, VT = svd_decomposition(A)

print("Ma trận U:")
print(U)
print("Ma trận Sigma:")
print(Sigma)
print("Ma trận VT:")
print(VT)
