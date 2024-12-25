import numpy as np
def nesterov_gradient_descent(X, y, learning_rate, momentum, num_iterations):
    num_samples, num_features = X.shape
    theta = np.zeros(num_features)  # Khởi tạo tham số theta ban đầu
    velocity = np.zeros(num_features)  # Khởi tạo velocity ban đầu

    for i in range(num_iterations):
        # Tính gradient dựa trên theta và momentum
        gradient = compute_gradient(X, y, theta + momentum * velocity)

        # Cập nhật velocity
        velocity = momentum * velocity - learning_rate * gradient

        # Cập nhật theta
        theta += velocity

    return theta

# Hàm tính gradient
def compute_gradient(X, y, theta):
    num_samples = X.shape[0
    gradient = np.zeros(theta.shape)

    for i in range(num_samples):
        xi = X[i]
        yi = y[i]

        error = np.dot(xi, theta) - yi
        gradient += xi * error

    gradient /= num_samples

    return gradient