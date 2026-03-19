import pandas as pd
import matplotlib.pyplot as plt

# read the csv output from the c program
data = pd.read_csv("results.csv", encoding="utf-16")

# remove rows where we skipped (quicksort v1 on large sorted arrays)
data = data[data["Time_us"] != "SKIP"]
data["Time_us"] = data["Time_us"].astype(float)
data["Comparisons"] = data["Comparisons"].astype(float)

# just a helper so i dont have to repeat this every time
def get(algo, itype):
    d = data[(data["Algorithm"] == algo) & (data["InputType"] == itype)]
    return d["n"].values, d["Time_us"].values, d["Comparisons"].values

# colors for each algorithm
colors = {
    "Selection": "red",
    "Bubble":    "orange",
    "Insertion": "gold",
    "MergeSort": "green",
    "QuickV1":   "blue",
    "QuickV2":   "purple",
    "QuickV3":   "brown",
    "HeapSort":  "black",
    "RadixSort": "pink"
}

qs = ["QuickV1", "QuickV2", "QuickV3"]
all7 = ["Selection", "Bubble", "Insertion", "MergeSort", "QuickV3", "HeapSort", "RadixSort"]

# Figure 1 - quicksort best case (random input)

plt.figure()
for algo in qs:
    n, t, c = get(algo, "Random")
    plt.plot(n, t, label=algo, color=colors[algo], marker="o")
plt.title("QuickSort versions - Best Case (Random Input)")
plt.xlabel("n")
plt.ylabel("Time (microseconds)")
plt.legend()
plt.grid(True)
plt.savefig("fig1_qs_best.png")
plt.close()


# Figure 2 - quicksort worst case (sorted input)

plt.figure()
for algo in qs:
    n, t, c = get(algo, "Sorted")
    plt.plot(n, t, label=algo, color=colors[algo], marker="o")
plt.title("QuickSort versions - Worst Case (Sorted Input)")
plt.xlabel("n")
plt.ylabel("Time (microseconds)")
plt.legend()
plt.grid(True)
plt.savefig("fig2_qs_worst.png")
plt.close()


# Figure 3 - quicksort average case (random input)
# same as best case basically for random

plt.figure()
for algo in qs:
    n, t, c = get(algo, "Random")
    plt.plot(n, t, label=algo, color=colors[algo], marker="s")
plt.title("QuickSort versions - Average Case (Random Input)")
plt.xlabel("n")
plt.ylabel("Time (microseconds)")
plt.legend()
plt.grid(True)
plt.savefig("fig3_qs_avg.png")
plt.close()


# Figure 4 - all 7 sorts best case (sorted input)

plt.figure()
for algo in all7:
    n, t, c = get(algo, "Sorted")
    plt.plot(n, t, label=algo, color=colors[algo], marker="o")
plt.title("All 7 Sorts - Best Case (Sorted Input)")
plt.xlabel("n")
plt.ylabel("Time (microseconds)")
plt.legend()
plt.grid(True)
plt.savefig("fig4_all7_best.png")
plt.close()


# Figure 5 - all 7 sorts worst case (reverse sorted)

plt.figure()
for algo in all7:
    n, t, c = get(algo, "Reverse")
    plt.plot(n, t, label=algo, color=colors[algo], marker="o")
plt.title("All 7 Sorts - Worst Case (Reverse Sorted Input)")
plt.xlabel("n")
plt.ylabel("Time (microseconds)")
plt.legend()
plt.grid(True)
plt.savefig("fig5_all7_worst.png")
plt.close()


# Figure 6 - all 7 sorts average case (random input)

plt.figure()
for algo in all7:
    n, t, c = get(algo, "Random")
    plt.plot(n, t, label=algo, color=colors[algo], marker="o")
plt.title("All 7 Sorts - Average Case (Random Input)")
plt.xlabel("n")
plt.ylabel("Time (microseconds)")
plt.legend()
plt.grid(True)
plt.savefig("fig6_all7_avg.png")
plt.close()


# Figure 7 - comparisons vs n (to check if correlated with time)

plt.figure()
for algo in all7:
    n, t, c = get(algo, "Random")
    plt.plot(n, c, label=algo, color=colors[algo], marker="^")
plt.title("Comparisons vs n (Random Input)")
plt.xlabel("n")
plt.ylabel("Number of Comparisons")
plt.legend()
plt.grid(True)
plt.savefig("fig7_comparisons.png")
plt.close()


# Figure 8 - time vs n side by side to show correlation

plt.figure()
for algo in all7:
    n, t, c = get(algo, "Random")
    plt.plot(n, t, label=algo, color=colors[algo], marker="^")
plt.title("Time vs n (Random Input) - compare with fig7")
plt.xlabel("n")
plt.ylabel("Time (microseconds)")
plt.legend()
plt.grid(True)
plt.savefig("fig8_time_vs_n.png")
plt.close()

print("done! all graphs saved")
