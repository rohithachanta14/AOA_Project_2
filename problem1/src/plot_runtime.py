import pandas as pd
import matplotlib.pyplot as plt

plt.style.use("seaborn-v0_8")

# Load CSV normally (because your file includes a header row)
df = pd.read_csv("results.csv")

# Convert types
df["papers"] = df["papers"].astype(int)
df["runtime_ms"] = df["runtime_ms"].astype(float)

# ---------------------------
# Pretty Plot (Linear Scale)
# ---------------------------
plt.figure(figsize=(10, 6), dpi=150)

plt.plot(
    df["papers"],
    df["runtime_ms"],
    marker="o",
    markersize=8,
    linewidth=2.5,
    color="#1f77b4"
)

# Annotate points on graph
for x, y in zip(df["papers"], df["runtime_ms"]):
    plt.text(x, y + (max(df["runtime_ms"]) * 0.02), f"{y:.1f}", 
             ha="center", fontsize=9, color="#333")

plt.title("Min-Cost Max-Flow Runtime vs Problem Size", fontsize=18, weight="bold")
plt.xlabel("Number of Papers", fontsize=14)
plt.ylabel("Runtime (ms)", fontsize=14)
plt.grid(True, linestyle="--", linewidth=0.6, alpha=0.7)

plt.tight_layout()
plt.savefig("runtime_plot_pretty.png")
print("Saved runtime_plot_pretty.png")

# ---------------------------
# Pretty Log-Scale Plot
# ---------------------------
plt.figure(figsize=(10, 6), dpi=150)

plt.plot(
    df["papers"],
    df["runtime_ms"],
    marker="o",
    markersize=8,
    linewidth=2.5,
    color="#d62728"
)

plt.yscale("log")

plt.title("Runtime vs Problem Size (Log Scale)", fontsize=18, weight="bold")
plt.xlabel("Number of Papers", fontsize=14)
plt.ylabel("Runtime (ms, log scale)", fontsize=14)
plt.grid(True, which="both", linestyle="--", linewidth=0.6, alpha=0.7)

plt.tight_layout()
plt.savefig("runtime_plot_log_pretty.png")
print("Saved runtime_plot_log_pretty.png")
