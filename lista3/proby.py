import numpy as np

def sigmoid(x):
    return 1 / (1 + np.exp(-x))

def relu(x):
    return np.maximum(0, x)

def forward_propagation(X, W1, b1, W2, b2, activation):
    Z1 = np.dot(W1, X) + b1
    A1 = activation(Z1)
    Z2 = np.dot(W2, A1) + b2
    A2 = sigmoid(Z2)
    return A2

def backward_propagation(X, Y, A2, W2, activation):
    dZ2 = A2 - Y
    dW2 = np.dot(dZ2, A2.T)
    db2 = np.sum(dZ2, axis=1, keepdims=True)
    dA1 = np.dot(W2.T, dZ2)
    dZ1 = dA1 * activation(A2)
    dW1 = np.dot(dZ1, X.T)
    db1 = np.sum(dZ1, axis=1, keepdims=True)
    return dW1, db1, dW2, db2

def train(X, Y, hidden_units, activation, learning_rate, epochs):
    input_size = X.shape[0]
    output_size = Y.shape[0]

    np.random.seed(0)
    W1 = np.random.randn(hidden_units, input_size) * 0.01
    b1 = np.zeros((hidden_units, 1))
    W2 = np.random.randn(output_size, hidden_units) * 0.01
    b2 = np.zeros((output_size, 1))

    for epoch in range(epochs):
        A2 = forward_propagation(X, W1, b1, W2, b2, activation)
        dW1, db1, dW2, db2 = backward_propagation(X, Y, A2, W2, activation)

        W1 -= learning_rate * dW1
        b1 -= learning_rate * db1
        W2 -= learning_rate * dW2
        b2 -= learning_rate * db2

        if epoch % 100 == 0:
            cost = np.mean(-Y * np.log(A2) - (1 - Y) * np.log(1 - A2))
            print(f"Epoch {epoch}: cost = {cost}")

    return W1, b1, W2, b2

# Przygotowanie danych treningowych
X_train = np.array([[0.4, 0.7, -0.2, -0.5],
                    [0.1, -0.3, 0.5, -0.8]])
Y_train = np.array([[1, 0, 1, 1]])

# Znormalizowane normą L1
X_train_l1 = X_train / np.linalg.norm(X_train, ord=1)

# Znormalizowane normą L2
X_train_l2 = X_train / np.linalg.norm(X_train, ord=2)

# Wartości hiperparametrów
hidden_units = 4
activation = sigmoid
learning_rate = 0.01
epochs = 1000

# Trening dla danych nieznormalizowanych
print("Training on unnormalized data:")
W1, b1, W2, b2 = train(X_train, Y_train, hidden_units, activation, learning_rate, epochs)

# Trening dla danych znormalizowanych normą L1
print("\nTraining on L1 normalized data:")
W1_l1, b1_l1, W2_l1, b2_l1 = train(X_train_l1, Y_train, hidden_units, activation, learning_rate, epochs)

# Trening dla danych znormalizowanych normą L2
print("\nTraining on L2 normalized data:")
W1_l2, b1_l2, W2_l2, b2_l2 = train(X_train_l2, Y_train, hidden_units, activation, learning_rate, epochs)

X_test = np.array([[0.3, 0.9, -0.1, -0.4],
                   [0.2, -0.5, 0.7, -0.2]])

# Normalize test data with L1 norm
X_test_l1 = X_test / np.linalg.norm(X_test, ord=1)

# Normalize test data with L2 norm
X_test_l2 = X_test / np.linalg.norm(X_test, ord=2)

# Perform forward propagation on unnormalized data
print("Forward propagation on unnormalized data:")
predictions = forward_propagation(X_test, W1, b1, W2, b2, activation)
print(predictions)

# Perform forward propagation on L1 normalized data
print("\nForward propagation on L1 normalized data:")
predictions_l1 = forward_propagation(X_test_l1, W1_l1, b1_l1, W2_l1, b2_l1, activation)
print(predictions_l1)

# Perform forward propagation on L2 normalized data
print("\nForward propagation on L2 normalized data:")
predictions_l2 = forward_propagation(X_test_l2, W1_l2, b1_l2, W2_l2, b2_l2, activation)
print(predictions_l2)