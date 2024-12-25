import numpy as np
import matplotlib.pyplot as plt

def grad(x):
    return 2*x+ 10*np.cos(x)

def cost(x):
    return x**2 + 10*np.sin(x)
# check convergence
def has_converged(theta_new, grad):
    return np.linalg.norm(grad(theta_new))/len(theta_new) < 0.001

def GD_momentum(theta_init, alpha=0.1, beta=0.9):
    theta = [theta_init]
    v_old = np.zeros_like(theta_init)
    for it in range(1000):
        v_new = beta*v_old + alpha*grad(theta[-1])
        theta_new = theta[-1] - v_new
        theta.append(theta_new)
        v_old = v_new
    return (theta,it)
def myGD1(x0,alpha=0.1, gra = 1e-3, loop = 1000):
    x = [x0]
    for it in range(loop):
        x_new = x[-1] - alpha*grad(x[-1])
        if abs(grad(x_new)) < gra:
            break
        x.append(x_new)
    return (x, it)
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
    num_samples = X.shape[0]
    gradient = np.zeros(theta.shape)

    for i in range(num_samples):
        xi = X[i]
        yi = y[i]

        error = np.dot(xi, theta) - yi
        gradient += xi * error

    gradient /= num_samples

    return gradient
if __name__ == '__main__':
    print("OK");
    (x3, it3) = myGD1(5,0.1)
    print('GD_Solution x3 = %f, cost = %f, obtained after %d iterations'%(x3[-1], cost(x3[-1]), it3))
    (x1, it1) = GD_momentum(5, 0.1, beta=0.9)
    print('Momentum_Solution x1 = %f, cost = %f, obtained after %d iterations'%(x1[-1], cost(x1[-1]), it1))

