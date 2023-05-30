import numpy as np
import warnings
warnings.filterwarnings("ignore")
np.random.seed(1234)

# Funkcje aktywacji

def sigm(x):
    return 1 / (1 + np.exp(-x))

def derivative_sigm(x):
    return sigm(x) * (1 - sigm(x))

def relu(x):
    return np.maximum(0, x)

def derivative_relu(x):
    if x < 0:
        return 0
    return 1

# Parametry
in_layer = 2
hidden_layer = 4
out_layer = 1

train_data = 100
train_epochs = 1000

learning_rate = 0.2

activation = sigm
derivative_activation = derivative_sigm

# Zadanie

def forward_propagation(arr, activation, weight_1, bias_1, weight_2, bias_2):
    Z1 = np.dot(arr, weight_1) + bias_1
    A1 = activation(Z1)
    Z2 = np.dot(A1, weight_2) + bias_2
    A2 = activation(Z2)

    return A1, A2

def backward_propagation(arr, true_results, activation, weight_2, A1, A2):
    error2 = true_results - A2
    dZ2 = error2 * activation(A2)
    
    error1 = np.dot(dZ2, weight_2.T)
    dZ1 = error1 * activation(A1)

    dW2 = learning_rate * np.dot(dZ2.T, A1)
    db2 = np.sum(dW2)

    dW1 = learning_rate * np.dot(dZ1.T, arr)
    db1 = np.sum(dW1)
    return dW1, db1, dW2, db2

def train(arr, results, size, epochs):
    weight_1 = np.random.randn(in_layer, hidden_layer) * 0.01
    bias_1 = np.zeros((1, hidden_layer))
    weight_2 = np.random.randn(hidden_layer, out_layer) * 0.01
    bias_2 = np.zeros((1, out_layer))

    print("+" + "=" * 10 + "+" + "=" * 10 + "+" + "=" * 10 + "+")
    print(f"|{'Epoch':^10}|{'Cost':^10}|{'Accuracy':^10}|")
    print("+" + "=" * 10 + "+" + "=" * 10 + "+" + "=" * 10 + "+")

    for epoch in range(epochs):
        A1, A2 = forward_propagation(arr, activation, weight_1, bias_1, weight_2, bias_2)
        dW1, db1, dW2, db2 = backward_propagation(arr, results, derivative_activation, weight_2, A1, A2)

        weight_1 += dW1.T
        bias_1 += db1
        weight_2 += dW2.T
        bias_2 += db2

        A2 = np.round(A2)
        accuracy = 0
        for i in range(len(results)):
            if results[i] == int(A2[i]):
                accuracy += 1
        accuracy /= size
        cost = 0
        cost = np.mean(-1 * results * np.log(A2) - (-1 * results) * np.log(-1 * A2))

        

        print(f"|{epoch + 1:^10}|{cost:^10.2f}|{accuracy:^10.2f}|")
        print("+" + "-" * 10 + "+" + "-" * 10 + "+" + "-" * 10 + "+")

if __name__ == "__main__":
    X_train = (2 * np.random.random_sample((train_data, 2)) - 1)
    X_train[X_train == 0] = 1
    X_train_l1 = X_train / np.linalg.norm(X_train, ord=1)
    X_train_l2 = X_train / np.linalg.norm(X_train, ord=2)

    results = np.zeros((train_data, 1), dtype=int)
    for i in range((train_data)):
        if X_train[i][0] * X_train[i][1] > 0:
            results[i] = 1
    
    #print(X_train)
    train(X_train, results, train_data, train_epochs)
    train(X_train_l1, results, train_data, train_epochs)
    train(X_train_l2, results, train_data, train_epochs)