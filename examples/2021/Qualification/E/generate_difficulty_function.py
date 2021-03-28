#!/usr/bin/env python3

import matplotlib.pyplot as plt
import numpy as np


def sigmoid(values):
    return 1.0 / (1.0 + np.exp(-values))


skills = np.linspace(-3.0, 3.0, num=10001)
skills = 0.5 * (skills[1:] + skills[:-1])

difficulties = skills

probabilities = sigmoid(skills[:, None] - difficulties[None, :])
correct = np.random.rand(*probabilities.shape) < probabilities


correct_ratio = np.mean(correct, axis=0)

plt.plot(difficulties, correct_ratio)
# plt.plot(difficulties, sigmoid(-difficulties))
plt.show()

result_diff = []
for i in range(101):
    idx = np.argmin(np.abs(i / 100.0 - correct_ratio))
    result_diff.append(difficulties[idx])
print(result_diff)
