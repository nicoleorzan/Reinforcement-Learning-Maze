import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

folder = 'data/'


data = pd.read_csv(folder+"data.txt", skiprows=6)
df = pd.DataFrame(data)

fig = plt.figure(figsize=(15,8))

plt.plot(df['step'], df['SARSA'], label="SARSA")
plt.plot(df['step'], df['Q_learning'], label="Q-learning")
plt.plot(df['step'], df['double_Q_learning'], label="double Q-learning")
plt.plot(df['step'], df['QV_learning'], label="QV-learning")
plt.yscale('log')
plt.title("Average Steps", fontsize=20)
plt.legend(fontsize=15,loc='upper right')
plt.xlim(0,10000)
#plt.ylim(-25,0)
plt.xticks(fontsize=15)
plt.yticks(fontsize=15)
plt.xlabel("Steps", fontsize=19)
plt.ylabel("Average steps", fontsize=19)
plt.grid()
#plt.show()
plt.savefig("avg_steps_example.png",bbox_inches="tight")

data = pd.read_csv(folder+"returns_data.txt", skiprows=0)
df = pd.DataFrame(data)

fig = plt.figure(figsize=(15,8))

plt.plot(df['step'], df['SARSA'], label="SARSA")
plt.plot(df['step'], df['Q_learning'], label="Q-learning")
plt.plot(df['step'], df['double_Q_learning'], label="double Q-learning")
plt.plot(df['step'], df['QV_learning'], label="QV-learning")
plt.title("Average Steps", fontsize=20)
plt.legend(fontsize=15,loc='upper right')
plt.xlim(0,10000)
plt.ylim(-50, 10)
plt.xticks(fontsize=15)
plt.yticks(fontsize=15)
plt.xlabel("Steps", fontsize=19)
plt.ylabel("Average Return", fontsize=19)
plt.grid()
#plt.show()
plt.savefig("avg_returns_example.png",bbox_inches="tight")

"""

data = pd.read_csv(folder+"data_evals.txt")
df = pd.DataFrame(data)

fig = plt.figure(figsize=(15,8))

plt.plot(df['step'], df['SARSA'], label="SARSA")
plt.plot(df['step'], df['Q_learning'], label="Q-learning")
plt.plot(df['step'], df['double_Q_learning'], label="double Q-learning")
plt.plot(df['step'], df['QV_learning'], label="QV-learning")
plt.title("Average Steps", fontsize=20)
plt.legend(fontsize=15,loc='upper right')
plt.xlim(0,len(df))
plt.xticks(fontsize=15)
plt.yticks(fontsize=15)
plt.xlabel("Steps", fontsize=19)
plt.ylabel("Average steps", fontsize=19)
plt.grid()
#plt.show()
plt.savefig("avg_steps_eval.png",bbox_inches="tight")



data = pd.read_csv(folder+"data_modif.txt")
df = pd.DataFrame(data)

fig = plt.figure(figsize=(15,8))

plt.plot(df['step'], df['SARSA'], label="SARSA")
plt.plot(df['step'], df['Q_learning'], label="Q-learning")
plt.plot(df['step'], df['double_Q_learning'], label="double Q-learning")
plt.plot(df['step'], df['QV_learning'], label="QV-learning")
plt.title("Average Steps Modifying final state", fontsize=20)
plt.legend(fontsize=15,loc='upper right')
plt.xlim(0,400)
plt.xticks(fontsize=15)
plt.yticks(fontsize=15)
plt.xlabel("Steps", fontsize=19)
plt.ylabel("Average steps", fontsize=19)
plt.grid()
plt.show()
#plt.savefig("avg_steps_modif_final_state.png",bbox_inches="tight")


"""